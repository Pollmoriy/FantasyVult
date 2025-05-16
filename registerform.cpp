#include "registerform.h"
#include "ui_registerform.h"
#include "mainwindow.h"
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include <QFontDatabase>
#include "LoginForm.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QRegularExpression>
#include "utils.h"


//Регистрация, проверка пароля и почты. Хэшширование



bool isPasswordStrong(const QString &password) {
    if (password.length() < 7) {
        return false;
    }

    QRegularExpression letterRegex("[A-Za-z]");
    if (!letterRegex.match(password).hasMatch()) {
        return false;
    }

    return true;
}

void RegisterForm::on_registerButton_clicked() {
    QString email = ui->emailLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text().trimmed();
    QString confirmPassword = ui->confirmPasswordLineEdit->text().trimmed();

    // Проверка на пустоту полей
    if (email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    // Проверка сложности пароля
    if (!isPasswordStrong(password)) {
        QMessageBox::warning(this, "Ошибка",
                             "Пароль слишком простой.\n"
                             "Требования к паролю:\n"
                             "- Минимум 7 символов\n"
                             "- Хотя бы одна буква (латинская)");
        return;
    }

    // Проверка совпадения паролей
    if (password != confirmPassword) {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают.");
        return;
    }

    // Проверка формата email
    QRegularExpression emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат email.");
        return;
    }

    // Подключение к базе данных
    QSqlQuery query;

    // Проверка на существование пользователя
    query.prepare("SELECT COUNT(*) FROM Users WHERE email = :email");
    query.bindValue(":email", email);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Ошибка при проверке пользователя: " + query.lastError().text());
        return;
    }

    query.next();
    if (query.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким email уже существует.");
        return;
    }

    // Хэшируем пароль перед сохранением
    QString hashedPassword = hashPassword(password);

    // Сохранение нового пользователя
    query.prepare("INSERT INTO Users (email, password) VALUES (:email, :password)");
    query.bindValue(":email", email);
    query.bindValue(":password", hashedPassword);

    if (query.exec()) {
        QMessageBox::information(this, "Успех", "Регистрация прошла успешно!");
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();

        delete this;
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось зарегистрировать: " + query.lastError().text());
    }
}

//Конец регистрации

RegisterForm::RegisterForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterForm)
{
    ui->setupUi(this);

    connect(ui->ReturnButton, &QPushButton::clicked, this, &RegisterForm::onReturnButtonClicked);

    QFontDatabase::addApplicationFont(":/fonts/Raleway-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Cinzel-Regular.ttf");

    // Загружаем изображение и растягиваем его на размер QLabel
    QPixmap pixmap1(":/images/singin_img.jpg");
    ui->backgroundLabel->setPixmap(pixmap1.scaled(ui->backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    //растягиваю картинку для регистрации
    QPixmap pixmap2(":/images/singin_img2.jpg");
    ui->label->setPixmap(pixmap2.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-19, 35);     // Смещение по осям X и Y
    shadow->setBlurRadius(8.4);     // Радиус размытия
    shadow->setColor(QColor(0, 0, 0, 255));  // Чёрный цвет с полной непрозрачностью

    ui->groupBox->setGraphicsEffect(shadow);
}

RegisterForm::~RegisterForm()
{
    delete ui;
}

void RegisterForm::onReturnButtonClicked()
{
    // Создаём объект окна регистрации
    LoginForm* loginForm = new LoginForm();

    // Показываем форму регистрации
    loginForm->show();

    // Закрываем форму авторизации
    this->close();
}
