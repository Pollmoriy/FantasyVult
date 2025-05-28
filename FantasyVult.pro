QT += core gui
QT += sql
QT += svg
QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buttonstyles.cpp \
    catalogform.cpp \
    favoriteform.cpp \
    loginform.cpp \
    main.cpp \
    mainwindow.cpp \
    registerform.cpp \
    resultdialog.cpp \
    testform.cpp \
    testsform.cpp \
    utils.cpp

HEADERS += \
    buttonstyles.h \
    catalogform.h \
    favoriteform.h \
    loginform.h \
    mainwindow.h \
    registerform.h \
    resultdialog.h \
    testform.h \
    testsform.h \
    utils.h

FORMS += \
    catalogform.ui \
    favoriteform.ui \
    loginform.ui \
    mainwindow.ui \
    registerform.ui \
    resultdialog.ui \
    testform.ui \
    testsform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
