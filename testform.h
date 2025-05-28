#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QString>
#include <QButtonGroup>
#include <QFrame>

struct AnswerItem {
    int idAnswer;
    QString answerText;
    bool isCorrect;
};

struct QuestionItem {
    int idQuestion;
    QString questionText;
    QVector<AnswerItem> answers;
};

QVector<QuestionItem> loadQuestionsWithAnswers(int id_tests);


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
    QStringList getAnswersByQuestionId(int id_question);


};

#endif // TESTFORM_H

