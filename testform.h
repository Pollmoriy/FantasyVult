#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QString>
#include <QButtonGroup>
#include <QFrame>


namespace Ui {
class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(int userId, int universeId, const QString& testName, QWidget *parent = nullptr);
    ~TestForm();

private slots:
    void finishTest(); // слот для кнопки "Завершить тест"

private:
    Ui::TestForm *ui;
    int userId;
    int universeId;
    QString testName;

    QFrame* createQuestionCard(const QString& questionText, const QStringList& answers);
    void loadUniverseTitle();

};

#endif // TESTFORM_H

