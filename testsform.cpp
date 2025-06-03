#include "testsform.h"
#include "ui_testsform.h"
#include "testform.h"
#include "catalogform.h"
#include "mainwindow.h"
#include "favoriteform.h"
#include "basemainwindow.h"
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


TestsForm::TestsForm(int userId, QWidget *parent)
    :  BaseMainWindow(parent), ui(new Ui::TestsForm), userId(userId)
{
    ui->setupUi(this);

    // Добавляем шрифты один раз
    static bool fontsLoaded = false;
    if (!fontsLoaded) {
        QFontDatabase::addApplicationFont(":/fonts/CinzelDecorative-Regular.ttf");
        QFontDatabase::addApplicationFont(":/fonts/Roboto_Condensed-Regular.ttf");
        fontsLoaded = true;
    }

    // Устанавливаем layout для контейнера карточек, если его нет
    if (!ui->cardContainer) {
        qDebug() << "cardContainer == nullptr!";
        return;
    }
    if (!ui->cardContainer->layout()) {
        ui->cardContainer->setLayout(new QVBoxLayout());
    }
    ui->cardContainer->layout()->setContentsMargins(310, 0, 0, 0);

    loadTestCards();

    // Задаём фоновое изображение
    QPixmap pixmap1(":/images/test_background_img.jpg");
    ui->backgroundLabel->setPixmap(pixmap1.scaled(ui->backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    // Подключаем кнопки навигации
    connect(ui->btnMain, &QPushButton::clicked, this, &TestsForm::goToMain);
    connect(ui->btnCatalog, &QPushButton::clicked, this, &TestsForm::goToCatalog);
    connect(ui->btnFavorite, &QPushButton::clicked, this, &TestsForm::goToFavorite);
}


TestsForm::~TestsForm()
{
    delete ui;
}

// ==================== // Создание одной карточки теста ====================
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

    // Загрузка и масштабирование изображения с проверкой
    QPixmap pix(imagePath);
    if (pix.isNull()) {
        qDebug() << "[ERROR] Не удалось загрузить изображение:" << imagePath;
        // Можно установить заглушку, если нужно
    } else {
        imageLabel->setPixmap(pix.scaled(imageLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }

    QLabel* nameLabel = new QLabel(testName);
    nameLabel->setFixedSize(419, 188);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setWordWrap(true);

    QFont nameFont("Cinzel Decorative", 25, QFont::Bold);
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

    // Оптимизированная проверка статуса теста одним запросом для всех карточек (см. ниже)

    // Здесь для упрощения передаём функцию, которая вернёт статус теста, чтобы не делать запрос для каждой карточки
    bool testPassed = passedTestsSet.contains(universeId);

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

// ==================== //Загрузка карточек теста ====================
void TestsForm::loadTestCards()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    // Запрашиваем тесты
    QString sqlQuery = "SELECT id_universe, name, small_image FROM Universe WHERE id_universe IN (1,2,3,4,5,7,9,10,11,14)";
    if (!query.exec(sqlQuery)) {
        qDebug() << "Ошибка выполнения запроса Universe:" << query.lastError().text();
        return;
    }

    // Сначала получаем все id тестов, которые пользователь уже прошёл (оптимизация)
    QSqlQuery passedQuery(db);
    passedTestsSet.clear();
    passedQuery.prepare("SELECT DISTINCT id_test FROM UserAnswers WHERE id_user = :uid");
    passedQuery.bindValue(":uid", userId);
    if (passedQuery.exec()) {
        while (passedQuery.next()) {
            int passedTestId = passedQuery.value(0).toInt();
            passedTestsSet.insert(passedTestId);
        }
    } else {
        qDebug() << "Ошибка запроса UserAnswers:" << passedQuery.lastError().text();
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

// Активная кнопка навигации
void TestsForm::setActiveButton(QPushButton* newActive)
{
    if (activeButton && activeButton != newActive) {
        activeButton->setStyleSheet(defaultButtonStyle);
    }
    activeButton = newActive;
    activeButton->setStyleSheet(activeButtonStyle);
}

// ==================== // Навигация ====================
void TestsForm::goToMain()
{
    setActiveButton(ui->btnMain);

    MainWindow* mw = new MainWindow(this->userId);

    QRect screenGeometry = this->geometry();
    mw->setGeometry(screenGeometry.x() + screenGeometry.width(), screenGeometry.y(),
                    screenGeometry.width(), screenGeometry.height());
    mw->show();

    QPropertyAnimation* animNew = new QPropertyAnimation(mw, "geometry");
    animNew->setDuration(300);
    animNew->setStartValue(mw->geometry());
    animNew->setEndValue(screenGeometry);
    animNew->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation* animOld = new QPropertyAnimation(this, "geometry");
    animOld->setDuration(300);
    animOld->setStartValue(screenGeometry);
    animOld->setEndValue(QRect(screenGeometry.x() - screenGeometry.width(), screenGeometry.y(),
                               screenGeometry.width(), screenGeometry.height()));
    animOld->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animOld, &QPropertyAnimation::finished, this, &TestsForm::close);
}

void TestsForm::goToCatalog()
{
    setActiveButton(ui->btnCatalog);

    CatalogForm* catalog = new CatalogForm(this->userId);

    QRect screenGeometry = this->geometry();
    catalog->setGeometry(screenGeometry.x() + screenGeometry.width(), screenGeometry.y(),
                         screenGeometry.width(), screenGeometry.height());
    catalog->show();

    QPropertyAnimation* animNew = new QPropertyAnimation(catalog, "geometry");
    animNew->setDuration(300);
    animNew->setStartValue(catalog->geometry());
    animNew->setEndValue(screenGeometry);
    animNew->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation* animOld = new QPropertyAnimation(this, "geometry");
    animOld->setDuration(300);
    animOld->setStartValue(screenGeometry);
    animOld->setEndValue(QRect(screenGeometry.x() - screenGeometry.width(), screenGeometry.y(),
                               screenGeometry.width(), screenGeometry.height()));
    animOld->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animOld, &QPropertyAnimation::finished, this, &TestsForm::close);
}

void TestsForm::goToFavorite()
{
    setActiveButton(ui->btnFavorite);

    FavoriteForm* fav = new FavoriteForm(this->userId);

    QRect screenGeometry = this->geometry();
    fav->setGeometry(screenGeometry.x() + screenGeometry.width(), screenGeometry.y(),
                     screenGeometry.width(), screenGeometry.height());
    fav->show();

    QPropertyAnimation* animNew = new QPropertyAnimation(fav, "geometry");
    animNew->setDuration(300);
    animNew->setStartValue(fav->geometry());
    animNew->setEndValue(screenGeometry);
    animNew->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation* animOld = new QPropertyAnimation(this, "geometry");
    animOld->setDuration(300);
    animOld->setStartValue(screenGeometry);
    animOld->setEndValue(QRect(screenGeometry.x() - screenGeometry.width(), screenGeometry.y(),
                               screenGeometry.width(), screenGeometry.height()));
    animOld->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animOld, &QPropertyAnimation::finished, this, &TestsForm::close);
}




void TestsForm::goToTest(int universeId, const QString& testName, QPushButton* questStatusButton)
{
    TestForm* testForm = new TestForm(userId, universeId, testName);
    testForm->show();
    this->close();

    connect(testForm, &TestForm::returnToTests, this, [=]() {
        TestsForm* newTestsForm = new TestsForm(userId);
        newTestsForm->show();
    });
}
