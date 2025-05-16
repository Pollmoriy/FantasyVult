#ifndef CATALOGFORM_H
#define CATALOGFORM_H

#include <QWidget>

namespace Ui {
class mainContainer;
}

class CatalogForm : public QWidget
{
    Q_OBJECT

public:
    explicit CatalogForm(QWidget *parent = nullptr);
    ~CatalogForm();



private:
    Ui::mainContainer *ui;
    QWidget* createUniverseCard(const QString &name, const QString &imagePath, QWidget *parent = nullptr);



};

#endif // CATALOGFORM_H
