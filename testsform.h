#ifndef TESTSFORM_H
#define TESTSFORM_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QFrame>

namespace Ui {
class TestsForm;
}

class TestsForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestsForm(int userId, QWidget *parent = nullptr);
    ~TestsForm();

private:
    Ui::TestsForm *ui;
    QPushButton* activeButton = nullptr; // если еще не добавляла
    void setActiveButton(QPushButton* newActive);
    int userId;
    void loadTestCards();
    QFrame* createTestCard(const QString& name, const QString& imagePath, int index);


private slots:
    void goToMain();
    void goToCatalog();
    void goToFavorite();
    void goToTests();

};

#endif // TESTSFORM_H
