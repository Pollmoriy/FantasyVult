#ifndef UNIVERSEFORM_H
#define UNIVERSEFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStackedWidget>
#include <QPushButton>
#include "basemainwindow.h"

struct HeroData {
    QString name;
    QString description;
    QString imagePath;
};

struct FactData {
    QString title;
    QString description;
    QString imagePath;
};


namespace Ui {
class UniverseForm;
}

class UniverseForm : public BaseMainWindow
{
    Q_OBJECT

public:
    explicit UniverseForm(QWidget *parent = nullptr);
    ~UniverseForm();
    void setData(int userId, int universeId);
    QSet<QString> likedUniverses;

private:
    Ui::UniverseForm *ui;
    int userId;
    int universeId;
    QVBoxLayout *verticalLayout = nullptr;

    QVBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QWidget *contentContainer;

    void loadFirstBlock();
    void loadMainTextBlock();
    void loadWorldGeographyBlock();
    void loadPlacesSliderBlock();

    QStackedWidget *sliderStackWidget = nullptr;
    QPushButton *leftArrowButton = nullptr;
    QPushButton *rightArrowButton = nullptr;
    int currentSlideIndex = 0;
    int currentPlaceIndex = 0;
    QVector<QPair<QString, QString>> places; // <image, caption>

    void loadHeroesBlock();
    void showPreviousHero();
    void showNextHero();

    QVector<HeroData> heroesData;

    int currentHeroIndex = 0;
    QWidget *heroCard = nullptr;
    void showHeroAt(int index);

    QVector<FactData> factsData;
    int currentFactIndex = 0;
    QWidget *factCard = nullptr;

    void loadFactsBlock();
    void showFactAt(int index);
    void addLikeBlock(const QString &universeName);
    QString currentUniverseName;

private slots:
    void showPreviousSlide();
    void showNextSlide();
    void goToCatalog();
};

#endif // UNIVERSEFORM_H
