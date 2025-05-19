#ifndef FAVORITEFORM_H
#define FAVORITEFORM_H

#include <QWidget>
#include <QSet>
#include <QString>

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
};

#endif // FAVORITEFORM_H

