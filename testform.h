#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QString>
#include <QButtonGroup>
#include <QFrame>

struct AnswerOption {
    int id_answer;
    QString text;
    bool is_correct; // можно пока не использовать
};

struct UserAnswer {
    int id_question;
    int selected_id_answer = -1; // -1 — не выбрано
};


namespace Ui {
class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(int userId, int universeId, const QString& testName, QWidget *parent = nullptr);
    ~TestForm();
public slots:
    void restartTest();


private slots:
    void finishTest(); // слот для кнопки "Завершить тест"


    void saveTestResult(); // слот для обработки сигнала сохранения


private:
    Ui::TestForm *ui;
    int userId;
    int universeId;
    QString testName;

    QFrame* createQuestionCard(int id_question, const QString& questionText, const QList<AnswerOption>& answers);
    void loadUniverseTitle();
    QStringList getAnswersByQuestionId(int id_question);
    void loadCorrectAnswers();
    QMap<int, int> userAnswers;    // id вопроса -> выбранный id ответа
    QMap<int, int> correctAnswers; // id вопроса -> id правильного ответа
    QList<QButtonGroup*> questionGroups;


    QMap<QButtonGroup*, int> groupToQuestionId;
    int testId = -1; // будем устанавливать его при загрузке теста
    void lockAndColorAnswers();

};

#endif // TESTFORM_H

