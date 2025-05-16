/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *backgroundLabel;
    QLabel *label;
    QLabel *label_2;
    QFrame *menuframe;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *mainlabel;
    QLabel *cataloglabel;
    QLabel *favlabel;
    QLabel *testlabel;
    QWidget *widget;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *emailLineEdit;
    QPushButton *searchButton;
    QPushButton *pushButton;
    QFrame *menuframe_2;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *mainlabel_2;
    QLabel *cataloglabel_2;
    QLabel *favlabel_2;
    QLabel *testlabel_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        backgroundLabel = new QLabel(centralwidget);
        backgroundLabel->setObjectName("backgroundLabel");
        backgroundLabel->setGeometry(QRect(0, 0, 1920, 1080));
        backgroundLabel->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(506, 345, 907, 540));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-image: url(:/symbols/Fantasy Vault.jpg);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat;\n"
"    \n"
"}\n"
""));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(1260, 990, 651, 71));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-image: url(:/symbols/creator_ shevtcova polina.jpg);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat;\n"
"    \n"
"}"));
        menuframe = new QFrame(centralwidget);
        menuframe->setObjectName("menuframe");
        menuframe->setGeometry(QRect(0, 55, 1920, 151));
        menuframe->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        menuframe->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: rgba(201, 29, 55, 100); /* \320\246\320\262\320\265\321\202 \321\201 \320\277\321\200\320\276\320\267\321\200\320\260\321\207\320\275\320\276\321\201\321\202\321\214\321\216 */\n"
"}\n"
"\n"
""));
        menuframe->setFrameShape(QFrame::Shape::StyledPanel);
        menuframe->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayoutWidget = new QWidget(menuframe);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(2, 0, 1926, 151));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(110);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(474, 0, 474, 0);
        mainlabel = new QLabel(horizontalLayoutWidget);
        mainlabel->setObjectName("mainlabel");
        mainlabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: url(:/fonts/Roboto_Condensed-Regular.ttf);\n"
"    font-size: 45px;\n"
"    color: #330C24;\n"
"background-color: transparent;\n"
"}\n"
"\n"
""));

        horizontalLayout->addWidget(mainlabel);

        cataloglabel = new QLabel(horizontalLayoutWidget);
        cataloglabel->setObjectName("cataloglabel");
        cataloglabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: url(:/fonts/Roboto_Condensed-Regular.ttf);\n"
"    font-size: 45px;\n"
"    color: white;\n"
"background-color: transparent;\n"
" transition: all 0.3s ease;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"    color: #330C24;       /* \320\246\320\262\320\265\321\202 \320\277\321\200\320\270 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\320\270 */\n"
"}"));

        horizontalLayout->addWidget(cataloglabel);

        favlabel = new QLabel(horizontalLayoutWidget);
        favlabel->setObjectName("favlabel");
        favlabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: url(:/fonts/Roboto_Condensed-Regular.ttf);\n"
"    font-size: 45px;\n"
"    color: white;\n"
"background-color: transparent;\n"
" transition: all 0.3s ease;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"    color: #330C24;       /* \320\246\320\262\320\265\321\202 \320\277\321\200\320\270 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\320\270 */\n"
"}\n"
"\n"
""));

        horizontalLayout->addWidget(favlabel);

        testlabel = new QLabel(horizontalLayoutWidget);
        testlabel->setObjectName("testlabel");
        testlabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: url(:/fonts/Roboto_Condensed-Regular.ttf);\n"
"    font-size: 45px;\n"
"    color: white;\n"
"background-color: transparent;\n"
" transition: all 0.3s ease;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"    color: #330C24;       /* \320\246\320\262\320\265\321\202 \320\277\321\200\320\270 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\320\270 */\n"
"}"));

        horizontalLayout->addWidget(testlabel);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(-50, 220, 1969, 90));
        horizontalLayoutWidget_2 = new QWidget(widget);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(2, 0, 1941, 91));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(27);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(303, 0, 306, 0);
        emailLineEdit = new QLineEdit(horizontalLayoutWidget_2);
        emailLineEdit->setObjectName("emailLineEdit");
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

        horizontalLayout_2->addWidget(emailLineEdit);

        searchButton = new QPushButton(horizontalLayoutWidget_2);
        searchButton->setObjectName("searchButton");
        searchButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 20px;\n"
"    width: 86px;\n"
"    height: 81px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #E6E6E6;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #CCCCCC;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/symbols/search.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        searchButton->setIcon(icon);
        searchButton->setIconSize(QSize(71, 64));

        horizontalLayout_2->addWidget(searchButton);

        pushButton = new QPushButton(horizontalLayoutWidget_2);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(true);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #F9B9A7;\n"
"    border-radius: 20px;\n"
"    width: 95px;\n"
"    height: 81px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #E8A392;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #D48B7D;\n"
"}\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/symbols/Filter.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(69, 60));

        horizontalLayout_2->addWidget(pushButton);

        menuframe_2 = new QFrame(centralwidget);
        menuframe_2->setObjectName("menuframe_2");
        menuframe_2->setGeometry(QRect(0, 330, 1920, 151));
        sizePolicy.setHeightForWidth(menuframe_2->sizePolicy().hasHeightForWidth());
        menuframe_2->setSizePolicy(sizePolicy);
        menuframe_2->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        menuframe_2->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: rgba(143, 146, 173, 1.0); /* \320\246\320\262\320\265\321\202 \321\201 \320\277\321\200\320\276\320\267\321\200\320\260\321\207\320\275\320\276\321\201\321\202\321\214\321\216 */\n"
"}\n"
"\n"
""));
        menuframe_2->setFrameShape(QFrame::Shape::StyledPanel);
        menuframe_2->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayoutWidget_3 = new QWidget(menuframe_2);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(0, 0, 1931, 151));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(110);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout_3->setContentsMargins(474, 0, 474, 0);
        mainlabel_2 = new QLabel(horizontalLayoutWidget_3);
        mainlabel_2->setObjectName("mainlabel_2");
        mainlabel_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: url(:/fonts/Roboto_Condensed-Regular.ttf);\n"
"    font-size: 45px;\n"
"    color: white;\n"
"background-color: transparent;\n"
"transition: all 0.3s ease;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"    color: #1C1B45;       /* \320\246\320\262\320\265\321\202 \320\277\321\200\320\270 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\320\270 */\n"
"}\n"
"\n"
""));

        horizontalLayout_3->addWidget(mainlabel_2);

        cataloglabel_2 = new QLabel(horizontalLayoutWidget_3);
        cataloglabel_2->setObjectName("cataloglabel_2");
        cataloglabel_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: url(:/fonts/Roboto_Condensed-Regular.ttf);\n"
"    font-size: 45px;\n"
"    color: #1C1B45;\n"
"background-color: transparent;\n"
" transition: all 0.3s ease;\n"
"}\n"
"\n"
""));

        horizontalLayout_3->addWidget(cataloglabel_2);

        favlabel_2 = new QLabel(horizontalLayoutWidget_3);
        favlabel_2->setObjectName("favlabel_2");
        favlabel_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: url(:/fonts/Roboto_Condensed-Regular.ttf);\n"
"    font-size: 45px;\n"
"    color: white;\n"
"background-color: transparent;\n"
" transition: all 0.3s ease;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"    color: #1C1B45;       /* \320\246\320\262\320\265\321\202 \320\277\321\200\320\270 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\320\270 */\n"
"}\n"
"\n"
""));

        horizontalLayout_3->addWidget(favlabel_2);

        testlabel_2 = new QLabel(horizontalLayoutWidget_3);
        testlabel_2->setObjectName("testlabel_2");
        testlabel_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: url(:/fonts/Roboto_Condensed-Regular.ttf);\n"
"    font-size: 45px;\n"
"    color: white;\n"
"background-color: transparent;\n"
" transition: all 0.3s ease;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"    color: #1C1B45;       /* \320\246\320\262\320\265\321\202 \320\277\321\200\320\270 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\320\270 */\n"
"}"));

        horizontalLayout_3->addWidget(testlabel_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        backgroundLabel->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
        label_2->setText(QString());
        mainlabel->setText(QCoreApplication::translate("MainWindow", "\320\223\320\273\320\260\320\262\320\275\320\260\321\217", nullptr));
        cataloglabel->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\321\202\320\260\320\273\320\276\320\263", nullptr));
        favlabel->setText(QCoreApplication::translate("MainWindow", "\320\233\321\216\320\261\320\270\320\274\320\276\320\265", nullptr));
        testlabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202\321\213", nullptr));
        searchButton->setText(QString());
        pushButton->setText(QString());
        mainlabel_2->setText(QCoreApplication::translate("MainWindow", "\320\223\320\273\320\260\320\262\320\275\320\260\321\217", nullptr));
        cataloglabel_2->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\321\202\320\260\320\273\320\276\320\263", nullptr));
        favlabel_2->setText(QCoreApplication::translate("MainWindow", "\320\233\321\216\320\261\320\270\320\274\320\276\320\265", nullptr));
        testlabel_2->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
