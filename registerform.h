#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>

namespace Ui {
class RegisterForm;
}

class RegisterForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = nullptr);
    ~RegisterForm();
     bool passwordVisible = false;
      bool passwordVisible2 = false;

private:
    Ui::RegisterForm *ui;
private slots:  // Добавляем секцию слотов
    void onReturnButtonClicked();  // Объявляем слот
    void on_registerButton_clicked();
    void togglePasswordVisibility();
    void togglePasswordVisibility2();
};

#endif // REGISTERFORM_H
