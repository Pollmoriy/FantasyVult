#include "testsform.h"
#include "ui_testsform.h"
#include "testform.h"
#include "catalogform.h"
#include "mainwindow.h"
#include "favoriteform.h"
#include <QFontDatabase>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QMessageBox>
#include <QDialog>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QStyle>
#include "buttonstyles.h"



// ==================== // Создание одной карточки ====================
QFrame* TestsForm::createTestCard(const QString& testName, const QString& imagePath, int index, int universeId)
{
    QFrame* card = new QFrame();
    card->setObjectName(QString("card%1").arg(index));
    card->setFixedSize(1292, 188);
    card->setStyleSheet("QFrame { background-color: white; }");

    QHBoxLayout* cardLayout = new QHBoxLayout(card);
    cardLayout->setContentsMargins(0, 0, 35, 0);
    cardLayout->setSpacing(30);

    QLabel* imageLabel = new QLabel();
    imageLabel->setFixedSize(334, 188);
    QPixmap pix(imagePath);
    if (pix.isNull()) {
        qDebug() << "[ERROR] Не удалось загрузить изображение:" << imagePath;
    } else {
        imageLabel->setPixmap(pix.scaled(imageLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

    QLabel* nameLabel = new QLabel(testName);
    nameLabel->setFixedSize(419, 188);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setWordWrap(true);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/CinzelDecorative-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).value(0, "Arial");
    QFont nameFont(fontFamily, 25);
    nameFont.setBold(true);
    nameLabel->setFont(nameFont);
    nameLabel->setStyleSheet("color: black; background: transparent;");

    QPushButton* testButton = new QPushButton("Пройти");
    testButton->setFixedSize(275, 115);
    testButton->setStyleSheet(R"(
        QPushButton {
            font-family: 'Roboto';
            font-size: 45px;
            color: #FFFFFF;
            background-color: #000000;
            border-radius: 40px;
        }
        QPushButton:hover {
            background-color: rgba(0, 0, 0, 0.4);
        })");

    QPushButton* questStatusButton = new QPushButton();
    questStatusButton->setFixedSize(116, 116);

    // ❗ Проверка по таблице UserAnswers
    bool testPassed = false;
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM UserAnswers WHERE id_user = :uid AND id_test = :tid");
    checkQuery.bindValue(":uid", userId);
    checkQuery.bindValue(":tid", universeId); // предполагается, что `id_test = id_universe`
    if (checkQuery.exec() && checkQuery.next()) {
        testPassed = checkQuery.value(0).toInt() > 0;
    } else {
        qDebug() << "[ERROR] Ошибка запроса к UserAnswers:" << checkQuery.lastError().text();
    }

    QString iconPath = testPassed
                           ? ":/symbols/green_check_box.svg"
                           : ":/symbols/black_check_box.svg";

    questStatusButton->setStyleSheet(QString(R"(
        QPushButton {
            background-color: transparent;
            border: none;
            qproperty-icon: url(%1);
            qproperty-iconSize: 116px 116px;
        })").arg(iconPath));

    // Подключаем кнопку "Пройти"
    connect(testButton, &QPushButton::clicked, this, [=]() {
        goToTest(universeId, testName, questStatusButton);
    });

    cardLayout->addWidget(imageLabel);
    cardLayout->addWidget(nameLabel);
    cardLayout->addWidget(testButton);
    cardLayout->addWidget(questStatusButton);

    card->setVisible(true);
    return card;
}



// ==================== // Загрузка карточек ====================
void TestsForm::loadTestCards()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    // Теперь запрашиваем также id_universe
    QString sqlQuery = "SELECT id_universe, name, small_image FROM Universe WHERE id_universe IN (1,2,3,4,5,7,9,10,11,14)";

    if (!query.prepare(sqlQuery)) {
        qDebug() << "Ошибка подготовки запроса:" << query.lastError().text();
        return;
    }

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    int index = 0;
    bool hasRows = false;
    while (query.next()) {
        hasRows = true;

        int universeId = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString imagePath = query.value(2).toString();

        qDebug() << "[Загрузка теста] id:" << universeId << ", name:" << name << ", image:" << imagePath;

        QFrame* testCard = createTestCard(name, imagePath, index, universeId);
        if (testCard) {
            ui->cardContainer->layout()->addWidget(testCard);
        }
        ++index;
    }

    if (!hasRows) {
        qDebug() << "По запросу нет результатов.";
    }
}



// ==================== // Активная кнопка навигации ====================
void TestsForm::setActiveButton(QPushButton* newActive)
{
    // Сбросить стиль у предыдущей кнопки
    if (activeButton && activeButton != newActive) {
        activeButton->setStyleSheet(defaultButtonStyle);
    }

    // Назначить новую активную кнопку
    activeButton = newActive;

    // Применить активный стиль
    activeButton->setStyleSheet(activeButtonStyle);
}



// ==================== // Переход на главную ====================
void TestsForm::goToMain()
{
    setActiveButton(ui->btnMain); // Пример
    MainWindow* mw = new MainWindow(this->userId);
    mw->show();
    this->close();

}


// ==================== // Переход на каталог ====================
void TestsForm::goToCatalog()
{
    setActiveButton(ui->btnCatalog);
    CatalogForm* catalogform = new CatalogForm(this->userId);
    catalogform->show();
    this->close();
}


// ==================== // Переход на любимую ====================
void TestsForm::goToFavorite()
{
    setActiveButton(ui->btnFavorite);
    FavoriteForm* fav = new FavoriteForm(this->userId);
    fav->show();
    this->close();
}



// ==================== // Переход на тесты ====================
void TestsForm::goToTests()
{
    setActiveButton(ui->btnTests);
    TestsForm* testsform = new TestsForm(this->userId);
    testsform->show();
    this->close();
}

// ==================== // Переход на тест ====================
void TestsForm::goToTest(int universeId, const QString& testName, QPushButton* questStatusButton)
{
    TestForm* testForm = new TestForm(userId, universeId, testName);
    testForm->show();
    this->close();

    connect(testForm, &TestForm::returnToTests, this, [=]() {
        TestsForm* newTestsForm = new TestsForm(userId);  // пересоздаём страницу
        newTestsForm->show();
    });
}







TestsForm::TestsForm(int userId, QWidget *parent)
    : QWidget(parent), ui(new Ui::TestsForm), userId(userId)
{
    ui->setupUi(this);


    QFontDatabase::addApplicationFont(":/fonts/CinzelDecorative-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto_Condensed-Regular.ttf");

    if (!ui->cardContainer) {
        qDebug() << "cardContainer == nullptr!";
        return;
    }

    if (!ui->cardContainer->layout()) {
        ui->cardContainer->setLayout(new QVBoxLayout());
    }
    ui->cardContainer->layout()->setContentsMargins(310, 0, 0, 0);




    loadTestCards();

    QPixmap pixmap1(":/images/test_background_img.jpg");
    ui->backgroundLabel->setPixmap(pixmap1.scaled(ui->backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    connect(ui->btnMain, &QPushButton::clicked, this, &TestsForm::goToMain);
    connect(ui->btnCatalog, &QPushButton::clicked, this, &TestsForm::goToCatalog);
    connect(ui->btnFavorite, &QPushButton::clicked, this, &TestsForm::goToFavorite);
    connect(ui->btnTests, &QPushButton::clicked, this, &TestsForm::goToTests);


}

TestsForm::~TestsForm()
{
    delete ui;
}
