#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(int correctCount, int totalCount, QWidget *parent);
    ~ResultDialog();

signals:
    void saveRequested();
    void retryRequested();

private slots:
    void on_saveButton_clicked();
    void on_retryButton_clicked();
private:
    Ui::ResultDialog *ui;
};


#endif // RESULTDIALOG_H
