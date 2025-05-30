// universeform.h
#ifndef UNIVERSEFORM_H
#define UNIVERSEFORM_H

#include <QWidget>

namespace Ui {
class UniverseForm;
}

class UniverseForm : public QWidget
{
    Q_OBJECT

public:
    explicit UniverseForm(QWidget *parent = nullptr);
    ~UniverseForm();
    void setData(int userId, int universeId);


private:
    Ui::UniverseForm *ui;
    int userId;
    int universeId;


};

#endif // UNIVERSEFORM_H
