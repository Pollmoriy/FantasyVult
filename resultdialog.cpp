#include "resultdialog.h"
#include "ui_resultdialog.h"
#include <QFontDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

ResultDialog::ResultDialog(int correctCount, int totalCount, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);


    connect(ui->retryButton, &QPushButton::clicked, this, [this]() {
        emit retryRequested();
        this->close();
    });



    // Задаём текст результата
    QString resultText = QString("Ваш результат: %1/%2").arg(correctCount).arg(totalCount);
    ui->resultLabel->setText(resultText);


}

ResultDialog::~ResultDialog()
{
    delete ui;
}

void ResultDialog::on_saveButton_clicked()
{
    emit saveRequested();
    this->accept();
}

void ResultDialog::on_retryButton_clicked()
{
    emit retryRequested();
    this->accept();
}



