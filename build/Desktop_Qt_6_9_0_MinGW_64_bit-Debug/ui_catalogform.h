/********************************************************************************
** Form generated from reading UI file 'catalogform.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CATALOGFORM_H
#define UI_CATALOGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainContainer
{
public:
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
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *cardContainer;
    QFrame *rowContainer;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QFrame *rowContainer_2;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_4;
    QFrame *rowContainer_3;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_5;
    QFrame *rowContainer_4;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_6;
    QFrame *rowContainer_5;
    QWidget *horizontalLayoutWidget_8;
    QHBoxLayout *horizontalLayout_7;
    QFrame *rowContainer_6;
    QWidget *horizontalLayoutWidget_9;
    QHBoxLayout *horizontalLayout_8;
    QFrame *rowContainer_7;
    QWidget *horizontalLayoutWidget_10;
    QHBoxLayout *horizontalLayout_9;
    QLabel *backgroundLabel;

    void setupUi(QWidget *mainContainer)
    {
        if (mainContainer->objectName().isEmpty())
            mainContainer->setObjectName("mainContainer");
        mainContainer->resize(1920, 1080);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainContainer->sizePolicy().hasHeightForWidth());
        mainContainer->setSizePolicy(sizePolicy);
        mainContainer->setStyleSheet(QString::fromUtf8(""));
        menuframe = new QFrame(mainContainer);
        menuframe->setObjectName("menuframe");
        menuframe->setGeometry(QRect(0, 55, 1920, 151));
        sizePolicy.setHeightForWidth(menuframe->sizePolicy().hasHeightForWidth());
        menuframe->setSizePolicy(sizePolicy);
        menuframe->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        menuframe->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: rgba(143, 146, 173, 100); /* \320\246\320\262\320\265\321\202 \321\201 \320\277\321\200\320\276\320\267\321\200\320\260\321\207\320\275\320\276\321\201\321\202\321\214\321\216 */\n"
"}\n"
"\n"
""));
        menuframe->setFrameShape(QFrame::Shape::StyledPanel);
        menuframe->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayoutWidget = new QWidget(menuframe);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 1931, 151));
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

        horizontalLayout->addWidget(mainlabel);

        cataloglabel = new QLabel(horizontalLayoutWidget);
        cataloglabel->setObjectName("cataloglabel");
        cataloglabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: url(:/fonts/Roboto_Condensed-Regular.ttf);\n"
"    font-size: 45px;\n"
"    color: #1C1B45;\n"
"background-color: transparent;\n"
" transition: all 0.3s ease;\n"
"}\n"
"\n"
""));

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
"    color: #1C1B45;       /* \320\246\320\262\320\265\321\202 \320\277\321\200\320\270 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\320\270 */\n"
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
"    color: #1C1B45;       /* \320\246\320\262\320\265\321\202 \320\277\321\200\320\270 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\320\270 */\n"
"}"));

        horizontalLayout->addWidget(testlabel);

        widget = new QWidget(mainContainer);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(-1, 252, 1921, 91));
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

        scrollArea = new QScrollArea(mainContainer);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 370, 1921, 711));
        scrollArea->setStyleSheet(QString::fromUtf8("QScrollArea {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QWidget#scrollAreaWidgetContents {\n"
"    background-color: transparent;\n"
"}"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, -424, 1920, 3400));
        scrollAreaWidgetContents->setMinimumSize(QSize(1920, 3400));
        cardContainer = new QWidget(scrollAreaWidgetContents);
        cardContainer->setObjectName("cardContainer");
        cardContainer->setGeometry(QRect(0, 0, 1920, 3400));
        cardContainer->setMinimumSize(QSize(1920, 3400));
        rowContainer = new QFrame(cardContainer);
        rowContainer->setObjectName("rowContainer");
        rowContainer->setGeometry(QRect(0, 0, 1920, 518));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(rowContainer->sizePolicy().hasHeightForWidth());
        rowContainer->setSizePolicy(sizePolicy1);
        rowContainer->setStyleSheet(QString::fromUtf8("QWidget#rowContainer {\n"
"    background-color: transparent;\n"
"}\n"
""));
        rowContainer->setFrameShape(QFrame::Shape::StyledPanel);
        rowContainer->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayoutWidget_4 = new QWidget(rowContainer);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(0, 0, 1921, 521));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_3->setSpacing(209);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(290, 59, 290, 90);
        verticalLayoutWidget = new QWidget(cardContainer);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(-1, 720, 1911, 2681));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        rowContainer_2 = new QFrame(cardContainer);
        rowContainer_2->setObjectName("rowContainer_2");
        rowContainer_2->setGeometry(QRect(0, 518, 1920, 518));
        sizePolicy1.setHeightForWidth(rowContainer_2->sizePolicy().hasHeightForWidth());
        rowContainer_2->setSizePolicy(sizePolicy1);
        rowContainer_2->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: transparent;\n"
"}\n"
""));
        rowContainer_2->setFrameShape(QFrame::Shape::StyledPanel);
        rowContainer_2->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayoutWidget_5 = new QWidget(rowContainer_2);
        horizontalLayoutWidget_5->setObjectName("horizontalLayoutWidget_5");
        horizontalLayoutWidget_5->setGeometry(QRect(0, 0, 1921, 521));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_4->setSpacing(209);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(290, 59, 290, 90);
        rowContainer_3 = new QFrame(cardContainer);
        rowContainer_3->setObjectName("rowContainer_3");
        rowContainer_3->setGeometry(QRect(0, 1036, 1920, 518));
        sizePolicy1.setHeightForWidth(rowContainer_3->sizePolicy().hasHeightForWidth());
        rowContainer_3->setSizePolicy(sizePolicy1);
        rowContainer_3->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: transparent;\n"
"}\n"
""));
        rowContainer_3->setFrameShape(QFrame::Shape::StyledPanel);
        rowContainer_3->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayoutWidget_6 = new QWidget(rowContainer_3);
        horizontalLayoutWidget_6->setObjectName("horizontalLayoutWidget_6");
        horizontalLayoutWidget_6->setGeometry(QRect(0, 0, 1921, 521));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_5->setSpacing(209);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(290, 59, 290, 90);
        rowContainer_4 = new QFrame(cardContainer);
        rowContainer_4->setObjectName("rowContainer_4");
        rowContainer_4->setGeometry(QRect(0, 1554, 1920, 518));
        sizePolicy1.setHeightForWidth(rowContainer_4->sizePolicy().hasHeightForWidth());
        rowContainer_4->setSizePolicy(sizePolicy1);
        rowContainer_4->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: transparent;\n"
"}\n"
""));
        rowContainer_4->setFrameShape(QFrame::Shape::StyledPanel);
        rowContainer_4->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayoutWidget_7 = new QWidget(rowContainer_4);
        horizontalLayoutWidget_7->setObjectName("horizontalLayoutWidget_7");
        horizontalLayoutWidget_7->setGeometry(QRect(0, 0, 1921, 521));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_7);
        horizontalLayout_6->setSpacing(209);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(290, 59, 290, 90);
        rowContainer_5 = new QFrame(cardContainer);
        rowContainer_5->setObjectName("rowContainer_5");
        rowContainer_5->setGeometry(QRect(0, 2072, 1920, 518));
        sizePolicy1.setHeightForWidth(rowContainer_5->sizePolicy().hasHeightForWidth());
        rowContainer_5->setSizePolicy(sizePolicy1);
        rowContainer_5->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: transparent;\n"
"}\n"
""));
        rowContainer_5->setFrameShape(QFrame::Shape::StyledPanel);
        rowContainer_5->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayoutWidget_8 = new QWidget(rowContainer_5);
        horizontalLayoutWidget_8->setObjectName("horizontalLayoutWidget_8");
        horizontalLayoutWidget_8->setGeometry(QRect(0, 0, 1921, 521));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget_8);
        horizontalLayout_7->setSpacing(209);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(290, 59, 290, 90);
        rowContainer_6 = new QFrame(cardContainer);
        rowContainer_6->setObjectName("rowContainer_6");
        rowContainer_6->setGeometry(QRect(0, 2590, 1920, 518));
        sizePolicy1.setHeightForWidth(rowContainer_6->sizePolicy().hasHeightForWidth());
        rowContainer_6->setSizePolicy(sizePolicy1);
        rowContainer_6->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: transparent;\n"
"}\n"
""));
        rowContainer_6->setFrameShape(QFrame::Shape::StyledPanel);
        rowContainer_6->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayoutWidget_9 = new QWidget(rowContainer_6);
        horizontalLayoutWidget_9->setObjectName("horizontalLayoutWidget_9");
        horizontalLayoutWidget_9->setGeometry(QRect(0, 0, 1921, 521));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget_9);
        horizontalLayout_8->setSpacing(209);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(290, 59, 290, 90);
        rowContainer_7 = new QFrame(cardContainer);
        rowContainer_7->setObjectName("rowContainer_7");
        rowContainer_7->setGeometry(QRect(0, 3108, 1920, 518));
        sizePolicy1.setHeightForWidth(rowContainer_7->sizePolicy().hasHeightForWidth());
        rowContainer_7->setSizePolicy(sizePolicy1);
        rowContainer_7->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: transparent;\n"
"}\n"
""));
        rowContainer_7->setFrameShape(QFrame::Shape::StyledPanel);
        rowContainer_7->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayoutWidget_10 = new QWidget(rowContainer_7);
        horizontalLayoutWidget_10->setObjectName("horizontalLayoutWidget_10");
        horizontalLayoutWidget_10->setGeometry(QRect(0, 0, 1921, 521));
        horizontalLayout_9 = new QHBoxLayout(horizontalLayoutWidget_10);
        horizontalLayout_9->setSpacing(209);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(290, 59, 290, 90);
        scrollArea->setWidget(scrollAreaWidgetContents);
        backgroundLabel = new QLabel(mainContainer);
        backgroundLabel->setObjectName("backgroundLabel");
        backgroundLabel->setGeometry(QRect(0, 0, 1920, 1080));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(backgroundLabel->sizePolicy().hasHeightForWidth());
        backgroundLabel->setSizePolicy(sizePolicy2);
        backgroundLabel->raise();
        menuframe->raise();
        widget->raise();
        scrollArea->raise();

        retranslateUi(mainContainer);

        QMetaObject::connectSlotsByName(mainContainer);
    } // setupUi

    void retranslateUi(QWidget *mainContainer)
    {
        mainContainer->setWindowTitle(QCoreApplication::translate("mainContainer", "Form", nullptr));
        mainlabel->setText(QCoreApplication::translate("mainContainer", "\320\223\320\273\320\260\320\262\320\275\320\260\321\217", nullptr));
        cataloglabel->setText(QCoreApplication::translate("mainContainer", "\320\232\320\260\321\202\320\260\320\273\320\276\320\263", nullptr));
        favlabel->setText(QCoreApplication::translate("mainContainer", "\320\233\321\216\320\261\320\270\320\274\320\276\320\265", nullptr));
        testlabel->setText(QCoreApplication::translate("mainContainer", "\320\242\320\265\321\201\321\202\321\213", nullptr));
        searchButton->setText(QString());
        pushButton->setText(QString());
        backgroundLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class mainContainer: public Ui_mainContainer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CATALOGFORM_H
