#ifndef UNIVERSEFORM_H
#define UNIVERSEFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStackedWidget>
#include <QPushButton>


namespace Ui {
class UniverseForm;
}

class UniverseForm : public QWidget
{
    Q_OBJECT

public:
    explicit UniverseForm(QWidget *parent = nullptr);
    ~UniverseForm();
    void setData(int userId, int universeId);

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
private slots:
    void showPreviousSlide();
    void showNextSlide();
};

#endif // UNIVERSEFORM_H
