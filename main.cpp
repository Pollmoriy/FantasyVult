#include <QCoreApplication>
#include "loginform.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include "testsform.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Подключение к базе данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/FantasyVult/fantasy.db");

    if (!db.open()) {
        qDebug() << "Не удалось открыть базу данных!";
        return -1;
    } else {
        qDebug() << "База данных успешно подключена!";
    }

    int userId = 2;  // или передай реальный userId
    TestsForm m(userId);
    m.show();
    QSqlQuery query;





    return a.exec();
}
