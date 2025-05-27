#pragma once

#include "ui_testform.h"
#include <QWidget>
#include <QPushButton>

class TestForm : public QWidget
{
    Q_OBJECT

public:
    ~TestForm() override;
    explicit TestForm(int userId, int universeId, const QString& testName, QWidget* parent = nullptr);

private:
    Ui::TestForm *ui;
    int userId;
    int universeId;
    QString testName;
    QPushButton* questStatusButton;

    void completeTest(); // вызывается после завершения
};

