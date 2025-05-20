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
     QSet<QString> likedUniverses;  // множество уникальных имён вселенных, которые лайкнули

private slots:
    void onSearchButtonClicked();
    void toggleFilterFrame();
    void onTagButtonClicked();
    void clearTagSelection();
     void applyTagSelection();

    void goToMain();
    void goToCatalog();
    void goToFavorite();
    void goToTests();


private:
    Ui::CatalogForm *ui;
    QLabel* emptyResultLabel = nullptr;
    int foundCardsCount = 0;
    QWidget* createUniverseCard(const QString &name, const QString &imagePath, QWidget *parent = nullptr);
     QSet<QString> selectedTags;
    void setupTagButton(QPushButton* button);
    void connectTagButton(QPushButton* button);

    QPushButton* activeButton = nullptr; // если еще не добавляла
    void setActiveButton(QPushButton* newActive);
};

#endif // CATALOGFORM_H
