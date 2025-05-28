#include "testform.h"
#include "ui_testform.h"
#include "resultdialog.h"

#include <QFontDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>
#include <QMessageBox>
#include <QScrollBar>


TestForm::TestForm(int userId, int universeId, const QString& testName, QWidget *parent)
    : QWidget(parent), userId(userId), universeId(universeId), testName(testName),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);

    QFontDatabase::addApplicationFont(":/fonts/CinzelDecorative-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto_Condensed-Regular.ttf");

    // Установка фона
    QPixmap pixmap1(":/images/test_background_img.jpg");
    ui->backgroundLabel->setPixmap(pixmap1.scaled(ui->backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    loadUniverseTitle();


    QSqlQuery questionQuery;
    questionQuery.prepare("SELECT id_question, question_text FROM Question WHERE id_tests = :id_tests LIMIT 10");
    questionQuery.bindValue(":id_tests", 1); // или переменная, если у тебя есть
    if (questionQuery.exec()) {
        while (questionQuery.next()) {
            int id_question = questionQuery.value(0).toInt();
            QString questionText = questionQuery.value(1).toString();

            // Загружаем ответы для этого вопроса
            QSqlQuery answerQuery;
            answerQuery.prepare("SELECT id_answer, answer_text, is_correct FROM Answer WHERE id_question = :id_question");
            answerQuery.bindValue(":id_question", id_question);

            QList<AnswerOption> answers;
            if (answerQuery.exec()) {
                while (answerQuery.next()) {
                    AnswerOption opt;
                    opt.id_answer = answerQuery.value(0).toInt();
                    opt.text = answerQuery.value(1).toString();
                    opt.is_correct = answerQuery.value(2).toBool();
                    answers.append(opt);
                }
            }

            // Создаём карточку
            QFrame* card = createQuestionCard(id_question, questionText, answers);
            ui->questionsLayout->addWidget(card);
        }
    }



    // Кнопка завершения теста
    connect(ui->finishButton, &QPushButton::clicked, this, &TestForm::finishTest);
}

QFrame* TestForm::createQuestionCard(int id_question, const QString& questionText, const QList<AnswerOption>& answers)
{
    QFrame* card = new QFrame;
    card->setFixedHeight(271);
    card->setStyleSheet("background-color: #C0FCFF; border-radius: 20px;");
    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(30, 20, 30, 20);
    cardLayout->setSpacing(20);

    QLabel* questionLabel = new QLabel(questionText);
    QFont questionFont("Arial", 40);
    questionFont.setBold(true);
    questionLabel->setFont(questionFont);
    questionLabel->setStyleSheet("color: black;");
    questionLabel->setAlignment(Qt::AlignCenter);
    questionLabel->setWordWrap(true);
    cardLayout->addWidget(questionLabel);

    QGridLayout* answersLayout = new QGridLayout;
    answersLayout->setHorizontalSpacing(60);
    answersLayout->setVerticalSpacing(10);

    QButtonGroup* group = new QButtonGroup(card);
    group->setExclusive(true);

    // Добавляем связь группы с вопросом
    groupToQuestionId[group] = id_question;
    questionGroups.append(group);

    for (int i = 0; i < answers.size(); ++i) {
        QWidget* optionWidget = new QWidget;
        QHBoxLayout* optionLayout = new QHBoxLayout(optionWidget);
        optionLayout->setContentsMargins(0, 0, 0, 0);
        optionLayout->setSpacing(10);
        optionLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        QRadioButton* radio = new QRadioButton;
        radio->setFixedSize(40, 40);
        radio->setStyleSheet(R"(
            QRadioButton::indicator {
                width: 24px;
                height: 24px;
                border-radius: 12px;
                border: 2px solid gray;
                background-color: white;
            }
            QRadioButton::indicator:checked {
                background-color: #54A0FF;
                border: 2px solid #2980b9;
            }
        )");

        QLabel* answerLabel = new QLabel(answers[i].text);
        QFont answerFont("Arial", 20);
        answerLabel->setFont(answerFont);
        answerLabel->setStyleSheet("color: black;");
        answerLabel->setWordWrap(true);

        optionLayout->addWidget(radio);
        optionLayout->addWidget(answerLabel);
        optionLayout->addStretch();

        int row = i / 2;
        int col = i % 2;
        answersLayout->addWidget(optionWidget, row, col);

        // Здесь id ответа — second параметр, доступен через group->id(button)
        group->addButton(radio, answers[i].id_answer);
    }

    connect(group, &QButtonGroup::idClicked, this, [=](int id_answer){
        userAnswers[id_question] = id_answer;
        qDebug() << "User selected answer for question" << id_question << ":" << id_answer;
    });

    cardLayout->addLayout(answersLayout);
    return card;
}


void TestForm::loadUniverseTitle()
{
    QString universeName;
    QSqlQuery query;
    query.prepare("SELECT name FROM Universe WHERE id_universe = :id");
    query.bindValue(":id", universeId);

    if (query.exec() && query.next()) {
        universeName = query.value(0).toString();
    } else {
        qDebug() << "Ошибка загрузки названия вселенной:" << query.lastError().text();
        universeName = "Название не найдено";
    }

    QLabel* nameLabel = new QLabel(universeName);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setWordWrap(true);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/CinzelDecorative-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).value(0, "Arial");
    QFont nameFont(fontFamily);
    nameFont.setPixelSize(128);
    nameFont.setBold(true);
    nameLabel->setFont(nameFont);
    nameLabel->setStyleSheet("color: black; background: transparent;");
    nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    // Проверка и установка layout, если его нет
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    if (!layout) {
        layout = new QVBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(40);
        ui->scrollAreaWidgetContents->setLayout(layout);
    }

    // Добавляем заголовок в начало
    layout->insertWidget(0, nameLabel, 0, Qt::AlignTop);
}


QStringList TestForm::getAnswersByQuestionId(int id_question)
{
    QStringList answers;
    QSqlQuery query;
    query.prepare("SELECT answer_text FROM Answer WHERE id_question = ?");
    query.addBindValue(id_question);

    if (query.exec()) {
        while (query.next()) {
            QString answerText = query.value(0).toString();
            answers << answerText;
        }
    } else {
        qDebug() << "Ошибка при загрузке ответов:" << query.lastError().text();
    }

    return answers;
}

void TestForm::loadCorrectAnswers()
{
    correctAnswers.clear();

    QSqlQuery query;
    query.prepare(R"(
        SELECT id_question, id_answer
        FROM Answer
        WHERE is_correct = 1
          AND id_question IN (
              SELECT id_question FROM Question WHERE id_tests = :testId
          )
    )");
    query.bindValue(":testId", universeId); // текущий ID теста

    if (query.exec()) {
        while (query.next()) {
            int id_question = query.value(0).toInt();
            int id_correct_answer = query.value(1).toInt();
            correctAnswers[id_question] = id_correct_answer;
        }
        qDebug() << "Правильные ответы загружены:" << correctAnswers;
    } else {
        qDebug() << "Ошибка загрузки правильных ответов:" << query.lastError().text();
    }
}


void TestForm::saveTestResult()
{
    int correctCount = 0;
    int totalCount = userAnswers.size();

    QSqlQuery query;
    query.prepare("SELECT id_tests FROM Tests WHERE test_name = :name AND id_universe = :universeId");
    query.bindValue(":name", testName);
    query.bindValue(":universeId", universeId);

    if (query.exec() && query.next()) {
        testId = query.value(0).toInt();
        qDebug() << "testId загружен:" << testId;
    } else {
        qDebug() << "Ошибка при получении testId:" << query.lastError().text();
    }

    // Подсчёт правильных ответов
    for (auto it = userAnswers.begin(); it != userAnswers.end(); ++it) {
        int questionId = it.key();
        int selectedAnswerId = it.value();
        if (correctAnswers.contains(questionId) && correctAnswers[questionId] == selectedAnswerId) {
            correctCount++;
        }
    }

    qDebug() << "Попытка сохранить результат: "
             << "userId:" << userId << ", testId:" << testId
             << ", correct:" << correctCount << ", total:" << totalCount;



    // Проверка, что testId установлен
    if (testId == -1) {
        qDebug() << "testId не найден. Отмена сохранения.";
        return;
    }

    QSqlQuery resultQuery;
    resultQuery.prepare("INSERT INTO TestResults (id_users, id_tests, correct_answers, total_questions) "
                        "VALUES (?, ?, ?, ?)");
    resultQuery.addBindValue(userId);
    resultQuery.addBindValue(testId);
    resultQuery.addBindValue(correctCount);
    resultQuery.addBindValue(totalCount);

    qDebug() << "Пробую выполнить SQL-запрос на сохранение результата...";
    if (!resultQuery.exec()) {
        qDebug() << "Ошибка при сохранении результата:" << resultQuery.lastError().text();
    } else {
        qDebug() << "Результат успешно сохранён!";
    }


}



void TestForm::lockAndColorAnswers()
{
    // Пройдёмся по всем группам вопросов
    for (int i = 0; i < questionGroups.size(); ++i) {
        QButtonGroup* group = questionGroups[i];
        if (!group) continue;

        // Блокируем всю группу (радиокнопки)
        for (QAbstractButton* btn : group->buttons()) {
            btn->setEnabled(false);
        }

        // Получаем id вопроса, связанный с этой группой
        // Предполагаем, что порядок questionGroups совпадает с порядком вопросов в userAnswers
        // Если у тебя есть явная связь, лучше её использовать
        int questionId = userAnswers.keys().value(i, -1);
        if (questionId == -1) continue;

        int userSelectedAnswer = userAnswers.value(questionId, -1);
        int correctAnswer = correctAnswers.value(questionId, -1);

        // Подсвечиваем лейблы у выбранного ответа
        for (QAbstractButton* btn : group->buttons()) {
            if (group->id(btn) == userSelectedAnswer) {
                // Находим QLabel рядом с этой радиокнопкой (родительский виджет -> layout -> второй виджет - QLabel)
                QWidget* parentWidget = btn->parentWidget();
                if (!parentWidget) continue;
                QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(parentWidget->layout());
                if (!layout) continue;

                // Второй виджет в layout — это QLabel с текстом ответа
                QWidget* labelWidget = layout->itemAt(1)->widget();
                QLabel* answerLabel = qobject_cast<QLabel*>(labelWidget);
                if (!answerLabel) continue;

                // Красим в зелёный, если ответ правильный, красный если нет
                if (userSelectedAnswer == correctAnswer) {
                    answerLabel->setStyleSheet("color: green; font-weight: bold;");
                } else {
                    answerLabel->setStyleSheet("color: red; font-weight: bold;");
                }
            }
        }
    }
}


void TestForm::finishTest()
{
    int totalQuestionsCount = 10;
    if (userAnswers.size() != totalQuestionsCount) {
        QMessageBox::warning(this, "Внимание", "Пожалуйста, ответьте на все вопросы перед завершением теста.");
        return;
    }

    loadCorrectAnswers();

    int correctCount = 0;
    for (auto it = userAnswers.constBegin(); it != userAnswers.constEnd(); ++it) {
        int qId = it.key();
        int userAns = it.value();
        if (correctAnswers.contains(qId) && correctAnswers[qId] == userAns) {
            correctCount++;
        }
    }

    ResultDialog* dialog = new ResultDialog(correctCount, userAnswers.size(), this);
    dialog->setWindowTitle("Результат прохождения теста");
    dialog->show();

    connect(dialog, &ResultDialog::saveRequested, this, &TestForm::saveTestResult);
    connect(dialog, &ResultDialog::retryRequested, this, &TestForm::restartTest);

    qDebug() << "Правильных ответов:" << correctCount << "/" << userAnswers.size();

    // Блокируем радиокнопки и подсвечиваем ответы
    lockAndColorAnswers();
}



void TestForm::restartTest()
{
    userAnswers.clear();

    for (QButtonGroup* group : questionGroups) {
        group->setExclusive(false);

        for (QAbstractButton* btn : group->buttons()) {
            btn->setChecked(false);
            btn->setEnabled(true); // разблокируем радиокнопки

            // Сбрасываем стиль соседнего QLabel с текстом ответа
            QWidget* parentWidget = btn->parentWidget();
            if (!parentWidget) continue;
            QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(parentWidget->layout());
            if (!layout) continue;

            QWidget* labelWidget = layout->itemAt(1)->widget();
            QLabel* answerLabel = qobject_cast<QLabel*>(labelWidget);
            if (!answerLabel) continue;

            answerLabel->setStyleSheet("color: black; font-weight: normal;");
        }

        group->setExclusive(true);
    }

    if (ui->scrollArea) {
        ui->scrollArea->verticalScrollBar()->setValue(0);
    }

    qDebug() << "Тест перезапущен, ответы очищены и стили сброшены";
}






TestForm::~TestForm()
{
    delete ui;
}
