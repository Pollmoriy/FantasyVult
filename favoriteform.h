#ifndef FAVORITEFORM_H
#define FAVORITEFORM_H

#include <QWidget>
#include <QSet>
#include <QString>
#include <QPushButton>


namespace Ui {
class FavoriteForm;
}

class FavoriteForm : public QWidget
{
    Q_OBJECT

public:
    explicit FavoriteForm(QWidget *parent = nullptr);
    ~FavoriteForm();

    void setLikedUniverses(const QSet<QString>& likedSet);
    void loadFavoriteUniverses();

private:
    Ui::FavoriteForm *ui;
    QSet<QString> likedUniverses;
    QPushButton* activeButton = nullptr; // если еще не добавляла
    void setActiveButton(QPushButton* newActive);

private slots:
    void goToMain();
    void goToCatalog();
    void goToFavorite();
    void goToTests();

};

#endif // FAVORITEFORM_H

