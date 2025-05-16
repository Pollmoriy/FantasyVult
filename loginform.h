#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private:
    Ui::LoginForm *ui;
private slots:  // Добавляем секцию слотов
    void onFirstTimeButtonClicked();  // Объявляем слот
    void onLoginButtonClicked();
};

#endif // LOGINFORM_H
