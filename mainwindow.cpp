#include "mainwindow.h"
#include "catalogform.h"
#include "favoriteform.h"
#include "testsform.h"
#include "basemainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFontDatabase>
#include "buttonstyles.h"
#include <QPropertyAnimation>
#include <QTimer>

// ==================== // Активная кнопка навигации ====================
void MainWindow::setActiveButton(QPushButton* newActive)
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

// ==================== // Переход на каталог ====================
void MainWindow::goToCatalog()
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

    connect(animOld, &QPropertyAnimation::finished, this, &MainWindow::close);
}

// ==================== // Переход на любимое ====================
void MainWindow::goToFavorite()
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

    connect(animOld, &QPropertyAnimation::finished, this, &MainWindow::close);
}

// ==================== // Переход на тесты ====================
void MainWindow::goToTests()
{
    setActiveButton(ui->btnTests);

    TestsForm* testsform = new TestsForm(this->userId);

    QRect screenGeometry = this->geometry();
    testsform->setGeometry(screenGeometry.x() + screenGeometry.width(), screenGeometry.y(),
                           screenGeometry.width(), screenGeometry.height());
    testsform->show();

    QPropertyAnimation* animNew = new QPropertyAnimation(testsform, "geometry");
    animNew->setDuration(300);
    animNew->setStartValue(testsform->geometry());
    animNew->setEndValue(screenGeometry);
    animNew->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation* animOld = new QPropertyAnimation(this, "geometry");
    animOld->setDuration(300);
    animOld->setStartValue(screenGeometry);
    animOld->setEndValue(QRect(screenGeometry.x() - screenGeometry.width(), screenGeometry.y(),
                               screenGeometry.width(), screenGeometry.height()));
    animOld->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animOld, &QPropertyAnimation::finished, this, &MainWindow::close);
}

MainWindow::MainWindow(int userId, QWidget *parent)
    :  BaseMainWindow(parent), ui(new Ui::MainWindow), userId(userId)
{
    ui->setupUi(this);  // <--- Правильный вызов

    activeButton = ui->btnMain;
    activeButton->setStyleSheet(activeButtonStyle);

    QFontDatabase::addApplicationFont(":/fonts/Raleway-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Cinzel-Regular.ttf");

    QPixmap pixmap1(":/images/main_background_img.jpg");
    ui->backgroundLabel->setPixmap(pixmap1.scaled(ui->backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    connect(ui->btnCatalog, &QPushButton::clicked, this, &MainWindow::goToCatalog);
    connect(ui->btnFavorite, &QPushButton::clicked, this, &MainWindow::goToFavorite);
    connect(ui->btnTests, &QPushButton::clicked, this, &MainWindow::goToTests);
}

MainWindow::~MainWindow()
{
    delete ui;
}
