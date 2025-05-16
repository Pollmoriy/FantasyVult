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

private:
    Ui::RegisterForm *ui;
private slots:  // Добавляем секцию слотов
    void onReturnButtonClicked();  // Объявляем слот
    void on_registerButton_clicked();
};

#endif // REGISTERFORM_H
