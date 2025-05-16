/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QLabel *backgroundLabel;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName("MainForm");
        MainForm->resize(1920, 1080);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainForm->sizePolicy().hasHeightForWidth());
        MainForm->setSizePolicy(sizePolicy);
        backgroundLabel = new QLabel(MainForm);
        backgroundLabel->setObjectName("backgroundLabel");
        backgroundLabel->setGeometry(QRect(0, 0, 1920, 1080));
        label = new QLabel(MainForm);
        label->setObjectName("label");
        label->setGeometry(QRect(520, 337, 828, 501));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
" color: black;\n"
"font-family: 'Cinzel';\n"
"font-size: 210px;\n"
"font-weight: bold;\n"
" \n"
"}\n"
""));
        label_2 = new QLabel(MainForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(510, 340, 841, 501));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: white;\n"
"    font-size: 200px;\n"
"    font-family: 'Cinzel';\n"
"    font-weight: bold;\n"
"    text-align: center;\n"
" }\n"
""));

        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        MainForm->setWindowTitle(QCoreApplication::translate("MainForm", "Form", nullptr));
        backgroundLabel->setText(QString());
        label->setText(QCoreApplication::translate("MainForm", "<html><head/><body><p align=\"center\">Fantasy</p><p align=\"center\">Vult</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainForm", "<html><head/><body><p align=\"center\">Fantasy</p><p align=\"center\">Vult</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
