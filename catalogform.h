#ifndef CATALOGFORM_H
#define CATALOGFORM_H

#include <QWidget>
#include <QLabel>  // <-- добавь сюда

namespace Ui {
class mainContainer;  // название из твоего ui
}

class CatalogForm : public QWidget
{
    Q_OBJECT

public:
    explicit CatalogForm(QWidget *parent = nullptr);
    ~CatalogForm();

    void clearCards();
    void loadUniverses(const QString& filter);
    void showNoResultsDialog(const QString& searchText);


private slots:
    void onSearchButtonClicked();

private:
    Ui::mainContainer *ui;
    QLabel* emptyResultLabel = nullptr;
 int foundCardsCount = 0;
    QWidget* createUniverseCard(const QString &name, const QString &imagePath, QWidget *parent = nullptr);
};

#endif // CATALOGFORM_H
