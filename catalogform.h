#ifndef CATALOGFORM_H
#define CATALOGFORM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>  // <-- Добавьте эту строку
#include <QSet>  // Для хранения выбранных тегов

namespace Ui {
class CatalogForm;
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
    void loadUniversesByTags(const QStringList& selectedTags);

private slots:
    void onSearchButtonClicked();
    void toggleFilterFrame();
    void onTagButtonClicked();
    void clearTagSelection();
     void applyTagSelection();

private:
    Ui::CatalogForm *ui;
    QLabel* emptyResultLabel = nullptr;
    int foundCardsCount = 0;
    QWidget* createUniverseCard(const QString &name, const QString &imagePath, QWidget *parent = nullptr);
     QSet<QString> selectedTags;
    void setupTagButton(QPushButton* button);
    void connectTagButton(QPushButton* button);
};

#endif // CATALOGFORM_H
