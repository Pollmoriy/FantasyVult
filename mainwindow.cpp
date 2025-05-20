#include "mainwindow.h"
#include "catalogform.h"
#include "favoriteform.h"
#include "testsform.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFontDatabase>
#include "buttonstyles.h"


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



// ==================== // Переход на главную ====================
void MainWindow::goToMain()
{
    setActiveButton(ui->btnMain); // Пример
    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}


// ==================== // Переход на каталог ====================
void MainWindow::goToCatalog()
{
    setActiveButton(ui->btnCatalog);
    CatalogForm* catalogform = new CatalogForm();
    catalogform->show();
    this->close();
}


// ==================== // Переход на любимую ====================
void MainWindow::goToFavorite()
{
    setActiveButton(ui->btnFavorite);
    FavoriteForm* favoriteform = new FavoriteForm();
    favoriteform->show();
    this->close();
}



// ==================== // Переход на тесты ====================
void MainWindow::goToTests()
{
    setActiveButton(ui->btnTests);
    TestsForm* testsform = new TestsForm();
    testsform->show();
    this->close();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    activeButton = ui->btnMain;
    activeButton->setStyleSheet(activeButtonStyle);

    QFontDatabase::addApplicationFont(":/fonts/Raleway-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Cinzel-Regular.ttf");

    QPixmap pixmap1(":/images/main_background_img.jpg");
    ui->backgroundLabel->setPixmap(pixmap1.scaled(ui->backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));


    connect(ui->btnMain, &QPushButton::clicked, this, &MainWindow::goToMain);
    connect(ui->btnCatalog, &QPushButton::clicked, this, &MainWindow::goToCatalog);
    connect(ui->btnFavorite, &QPushButton::clicked, this, &MainWindow::goToFavorite);
    connect(ui->btnTests, &QPushButton::clicked, this, &MainWindow::goToTests);


}

MainWindow::~MainWindow()
{
    delete ui;
}
