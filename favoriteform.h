#ifndef FAVORITEFORM_H
#define FAVORITEFORM_H

#include <QWidget>
#include <QSet>
#include <QString>
#include <QPushButton>
#include "basemainwindow.h"


namespace Ui {
class FavoriteForm;
}

class FavoriteForm : public BaseMainWindow
{
    Q_OBJECT

public:
    explicit FavoriteForm(int userId, QWidget *parent = nullptr); // добавлен userId
    ~FavoriteForm();
    QSet<QString> likedUniverses;
    void setLikedUniverses(const QSet<QString>& likedSet);
    void loadFavoriteUniverses();
    void clearCards();

private:
    Ui::FavoriteForm *ui;
    QPushButton* activeButton = nullptr; // если еще не добавляла
    void setActiveButton(QPushButton* newActive);
     int userId;
    QWidget* createUniverseCard(const QString &name, const QString &imagePath, QWidget *parent);

private slots:
    void goToMain();
    void goToCatalog();
    void goToTests();

};

#endif // FAVORITEFORM_H

