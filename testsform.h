#ifndef TESTSFORM_H
#define TESTSFORM_H

#include <QWidget>

namespace Ui {
class TestsForm;
}

class TestsForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestsForm(QWidget *parent = nullptr);
    ~TestsForm();

private:
    Ui::TestsForm *ui;
};

#endif // TESTSFORM_H
