/********************************************************************************
** Form generated from reading UI file 'loginform.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginForm
{
public:
    QLabel *backgroundLabel;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *emailLineEdit;
    QLineEdit *passwordLineEdit;
    QLabel *enter_email_label;
    QLabel *enter_password_label;
    QPushButton *LoginButton;
    QPushButton *firstTimeButton;

    void setupUi(QWidget *LoginForm)
    {
        if (LoginForm->objectName().isEmpty())
            LoginForm->setObjectName("LoginForm");
        LoginForm->resize(1920, 1080);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginForm->sizePolicy().hasHeightForWidth());
        LoginForm->setSizePolicy(sizePolicy);
        LoginForm->setMinimumSize(QSize(0, 0));
        LoginForm->setMaximumSize(QSize(1920, 1080));
        LoginForm->setStyleSheet(QString::fromUtf8(""));
        backgroundLabel = new QLabel(LoginForm);
        backgroundLabel->setObjectName("backgroundLabel");
        backgroundLabel->setEnabled(true);
        backgroundLabel->setGeometry(QRect(0, 0, 1920, 1080));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(backgroundLabel->sizePolicy().hasHeightForWidth());
        backgroundLabel->setSizePolicy(sizePolicy1);
        backgroundLabel->setMinimumSize(QSize(1920, 1080));
        backgroundLabel->setMaximumSize(QSize(99999, 99999));
        backgroundLabel->setBaseSize(QSize(0, 0));
        backgroundLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-image: url(:/images/background.png);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat;\n"
"background-size: cover;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: 'Roboto';\n"
"    font-size: 45px;\n"
"    color: #FFFFFF;\n"
"    background-color: #000000;\n"
"    border-radius: 40px;\n"
"}"));
        backgroundLabel->setScaledContents(true);
        groupBox = new QGroupBox(LoginForm);
        groupBox->setObjectName("groupBox");
        groupBox->setEnabled(true);
        groupBox->setGeometry(QRect(200, 130, 1561, 844));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    /* \320\223\321\200\320\260\320\264\320\270\320\265\320\275\321\202\320\275\320\260\321\217 \320\267\320\260\320\273\320\270\320\262\320\272\320\260 */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, \n"
"                                stop:0 rgba(252, 217, 150, 255), /* \321\206\320\262\320\265\321\202 \321\201\320\262\320\265\321\200\321\205\321\203 */\n"
"                                stop:1 rgba(157, 66, 0, 255));   /* \321\206\320\262\320\265\321\202 \321\201\320\275\320\270\320\267\321\203 */\n"
"    /* \320\222\321\213\321\200\320\260\320\262\320\275\320\270\320\262\320\260\320\275\320\270\320\265 \320\277\320\276 \321\206\320\265\320\275\321\202\321\200\321\203 */\n"
"    margin: 0px; /* \320\243\320\261\320\270\321\200\320\260\320\265\320\274 \320\262\320\275\320\265\321\210\320\275\320\270\320\265 \320\276\321\202\321\201\321\202\321\203\320\277\321\213 */\n"
"    padding: 0px; /* \320\243\320\261\320\270\321\200\320\260\320\265\320\274 \320\262\320\275\321\203\321\202"
                        "\321\200\320\265\320\275\320\275\320\270\320\265 \320\276\321\202\321\201\321\202\321\203\320\277\321\213 */\n"
"    border: none; /* \320\243\320\261\320\270\321\200\320\260\320\265\320\274 \321\200\320\260\320\274\320\272\321\203 */\n"
"    /* \320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\262\321\213\321\200\320\260\320\262\320\275\320\270\320\262\320\260\320\275\320\270\321\217 */\n"
"    display: flex;\n"
"    justify-content: center;\n"
"    align-items: center;\n"
"    width: 475px;  /* \320\243\321\201\321\202\320\260\320\275\320\260\320\262\320\273\320\270\320\262\320\260\320\265\320\274 \321\210\320\270\321\200\320\270\320\275\321\203 (\320\277\320\276\320\277\321\200\320\276\320\261\321\203\320\271 \320\262\320\260\321\200\321\214\320\270\321\200\320\276\320\262\320\260\321\202\321\214, \320\265\321\201\320\273\320\270 \320\275\321\203\320\266\320\275\320\276) */\n"
"    height: 844px; /* \320\243\321\201\321\202\320\260\320\275\320\260\320\262\320\273\320\270\320\262\320"
                        "\260\320\265\320\274 \320\262\321\213\321\201\320\276\321\202\321\203 (\320\277\320\276\320\277\321\200\320\276\320\261\321\203\320\271 \320\262\320\260\321\200\321\214\320\270\321\200\320\276\320\262\320\260\321\202\321\214, \320\265\321\201\320\273\320\270 \320\275\321\203\320\266\320\275\320\276) */\n"
"\n"
"}\n"
""));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 475, 844));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-image: url(:/images/login_img.jpg);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat;\n"
"    background-size: cover;\n"
"}\n"
""));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(480, 60, 1081, 101));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: url(:/fonts/Raleway-Bold.ttf);\n"
"    font-weight: bold;\n"
"    font-size: 45px;\n"
"    color: black;\n"
"    }"));
        emailLineEdit = new QLineEdit(groupBox);
        emailLineEdit->setObjectName("emailLineEdit");
        emailLineEdit->setGeometry(QRect(550, 270, 905, 108));
        emailLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid black;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 30px;\n"
"    font-family: 'Raleway';\n"
"    color: black;\n"
"    background-color: white;\n"
"}\n"
"\n"
""));
        passwordLineEdit = new QLineEdit(groupBox);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(550, 500, 905, 108));
        passwordLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid black;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 30px;\n"
"    font-family: 'Raleway';\n"
"    color: black;\n"
"    background-color: white;\n"
"}\n"
"\n"
""));
        enter_email_label = new QLabel(groupBox);
        enter_email_label->setObjectName("enter_email_label");
        enter_email_label->setGeometry(QRect(550, 209, 351, 51));
        enter_email_label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: url(:/fonts/Roboto_Condensed-Regular.ttf);\n"
"    font-size: 45px;\n"
"    color: #000000;\n"
"}"));
        enter_password_label = new QLabel(groupBox);
        enter_password_label->setObjectName("enter_password_label");
        enter_password_label->setGeometry(QRect(550, 429, 351, 61));
        enter_password_label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: url(:/fonts/Roboto_Condensed-Regular.ttf);\n"
"    font-size: 45px;\n"
"    color: #000000;\n"
"}"));
        LoginButton = new QPushButton(groupBox);
        LoginButton->setObjectName("LoginButton");
        LoginButton->setGeometry(QRect(577, 670, 275, 115));
        LoginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-family: 'Roboto';\n"
"    font-size: 45px;\n"
"    color: #FFFFFF;\n"
"    background-color: #000000;\n"
"    border-radius: 40px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 0, 0, 0.4); /* \320\237\320\276\320\273\321\203\320\277\321\200\320\276\320\267\321\200\320\260\321\207\320\275\321\213\320\271 \321\207\321\221\321\200\320\275\321\213\320\271 \321\204\320\276\320\275 \321\201 40% \320\275\320\265\320\277\321\200\320\276\320\267\321\200\320\260\321\207\320\275\320\276\321\201\321\202\321\214\321\216 */\n"
"}"));
        firstTimeButton = new QPushButton(groupBox);
        firstTimeButton->setObjectName("firstTimeButton");
        firstTimeButton->setGeometry(QRect(979, 670, 458, 115));
        firstTimeButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-family: 'Roboto';\n"
"    font-size: 45px;\n"
"    color: #FFFFFF;\n"
"    background-color: #000000;\n"
"    border-radius: 40px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 0, 0, 0.4); /* \320\237\320\276\320\273\321\203\320\277\321\200\320\276\320\267\321\200\320\260\321\207\320\275\321\213\320\271 \321\207\321\221\321\200\320\275\321\213\320\271 \321\204\320\276\320\275 \321\201 40% \320\275\320\265\320\277\321\200\320\276\320\267\321\200\320\260\321\207\320\275\320\276\321\201\321\202\321\214\321\216 */\n"
"}"));

        retranslateUi(LoginForm);

        QMetaObject::connectSlotsByName(LoginForm);
    } // setupUi

    void retranslateUi(QWidget *LoginForm)
    {
        LoginForm->setWindowTitle(QCoreApplication::translate("LoginForm", "LoginForm", nullptr));
        backgroundLabel->setText(QString());
        groupBox->setTitle(QString());
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("LoginForm", "<html><head/><body><p align=\"center\"><span style=\" font-weight:700;\">\320\224\320\276\320\261\321\200\320\276 \320\277\320\276\320\266\320\260\320\273\320\276\320\262\320\260\321\202\321\214, \320\270\321\201\320\272\320\260\321\202\320\265\320\273\321\214 \320\277\321\200\320\270\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\271!</span></p><p align=\"center\"><span style=\" font-weight:700;\"><br/></span></p></body></html>", nullptr));
        enter_email_label->setText(QCoreApplication::translate("LoginForm", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 e-mail", nullptr));
        enter_password_label->setText(QCoreApplication::translate("LoginForm", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        LoginButton->setText(QCoreApplication::translate("LoginForm", "Log In", nullptr));
        firstTimeButton->setText(QCoreApplication::translate("LoginForm", "\320\222\320\277\320\265\321\200\320\262\321\213\320\265 \320\267\320\260\321\210\321\221\320\273?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginForm: public Ui_LoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
