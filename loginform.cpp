#include "LoginForm.h"
#include "ui_LoginForm.h"
#include "mainwindow.h"
#include "basemainwindow.h"
#include "utils.h"
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include <QFontDatabase>
#include "RegisterForm.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>

// ==================== // Обработка нажатия кнопки "Зашел впервые" ====================//
void LoginForm::onFirstTimeButtonClicked()
{
    RegisterForm* registerForm = new RegisterForm();
    registerForm->show();
    this->close();
}

// ==================== // Обработка нажатия кнопки "Войти" ====================//
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
            int userId = -1;

            QSqlQuery idQuery;
            idQuery.prepare("SELECT id_users FROM Users WHERE email = :email");
            idQuery.bindValue(":email", email);
            if (idQuery.exec() && idQuery.next()) {
                userId = idQuery.value(0).toInt();
            }

            if (userId != -1) {
                MainWindow* mainWindow = new MainWindow(userId);
                mainWindow->show();
                this->close();
            } else {
                QMessageBox::critical(this, "Ошибка", "Не удалось получить ID пользователя.");
                ui->passwordLineEdit->clear();
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверный пароль.");
            ui->passwordLineEdit->clear();
        }
    } else {
        // Пользователь с таким email не найден
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким email не найден.");
        ui->emailLineEdit->clear();
        ui->passwordLineEdit->clear();
    }
}

// ==================== // Отображение пароля в виде звездочек ====================//
void LoginForm::togglePasswordVisibility()
{
    passwordVisible = !passwordVisible;

    if (passwordVisible) {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        ui->togglePasswordButton->setIcon(QIcon("://symbols/open_eye.svg"));

    } else {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        ui->togglePasswordButton->setIcon(QIcon("://symbols/close_eye.svg"));

    }
}

LoginForm::LoginForm(QWidget *parent) :
     BaseMainWindow(parent),
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
    connect(ui->togglePasswordButton, &QPushButton::clicked, this, &LoginForm::togglePasswordVisibility);

}

LoginForm::~LoginForm()
{
    delete ui;
}


