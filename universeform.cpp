#include "universeform.h"
#include "ui_universeform.h"

UniverseForm::UniverseForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UniverseForm)
{
    ui->setupUi(this);
}


void UniverseForm::setData(int userId, int universeId)
{
    this->userId = userId;
    this->universeId = universeId;
    qDebug() << "UniverseForm::setData called";
    qDebug() << "Received userId:" << userId;
    qDebug() << "Received universeId:" << universeId;
}

UniverseForm::~UniverseForm()
{
    delete ui;
}
