#include "LoginForm.h"
#include "ui_LoginForm.h"
#include "mainwindow.h"
#include "utils.h"
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include <QFontDatabase>
#include "RegisterForm.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>

//Хэширование



LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{

    ui->setupUi(this);

    //Подключаем слод для перехода на регистрацию
    connect(ui->firstTimeButton, &QPushButton::clicked, this, &LoginForm::onFirstTimeButtonClicked);

    QFontDatabase::addApplicationFont(":/fonts/Raleway-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Cinzel-Regular.ttf");

    // Загружаем изображение и растягиваем его на размер QLabel
    QPixmap pixmap(":/images/background.png");
    ui->backgroundLabel->setPixmap(pixmap.scaled(ui->backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-19, 35);     // Смещение по осям X и Y
    shadow->setBlurRadius(8.4);     // Радиус размытия
    shadow->setColor(QColor(0, 0, 0, 255));  // Чёрный цвет с полной непрозрачностью

    ui->groupBox->setGraphicsEffect(shadow);

    connect(ui->LoginButton, &QPushButton::clicked, this, &LoginForm::onLoginButtonClicked);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::onFirstTimeButtonClicked()
{
    RegisterForm* registerForm = new RegisterForm();
    registerForm->show();
    this->close();
}


// Обработка нажатия кнопки "Войти"
void LoginForm::onLoginButtonClicked()
{
    QString email = ui->emailLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text().trimmed();

    // Проверка на пустоту полей
    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    // Хэшируем введённый пароль
    QString hashedPassword = hashPassword(password);

    // Подключаемся к базе данных и выполняем запрос
    QSqlQuery query;
    query.prepare("SELECT password FROM Users WHERE email = :email");
    query.bindValue(":email", email);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Ошибка при проверке пользователя: " + query.lastError().text());
        return;
    }

    // Проверяем, найден ли пользователь
    if (query.next()) {
        QString storedPassword = query.value(0).toString();

        // Сравниваем хэшированные пароли
        if (storedPassword == hashedPassword) {
            QMessageBox::information(this, "Успех", "Вход выполнен успешно!");

            // Открываем главное окно
            MainWindow* mainWindow = new MainWindow();
            mainWindow->show();
            this->close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверный пароль.");
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким email не найден.");
    }
}


