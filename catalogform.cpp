#include "catalogform.h"
#include "ui_catalogform.h"
#include <QFontDatabase>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFontDatabase>
#include <QFont>
#include <QDebug>

QWidget* CatalogForm::createUniverseCard(const QString &name, const QString &imagePath, QWidget *parent)
{
    qDebug() << "Создание карточки с именем:" << name << " и изображением:" << imagePath;

    // Карточка (основной виджет)
    QWidget *cardWidget = new QWidget(parent);
    cardWidget->setStyleSheet("background-color: transparent; border-radius: 20px;");
    cardWidget->setFixedSize(566, 372);

    // Фрейм-контейнер для всей карточки
    QFrame *universeCard = new QFrame(cardWidget);
    universeCard->setStyleSheet("background-color: transparent;");
    universeCard->setFixedSize(566, 372);

    // Метка изображения
    QLabel *imageLabel = new QLabel(universeCard);
    imageLabel->setFixedSize(566, 321);
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        qDebug() << "Ошибка: не удалось загрузить изображение:" << imagePath;
        pixmap = QPixmap(":/images/placeholder.png");
    }
    imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    imageLabel->setStyleSheet("border: none;");
    imageLabel->setGeometry(0, 0, 566, 321);

    // Кнопка лайка
    QPushButton *likeButton = new QPushButton(universeCard);
    likeButton->setIcon(QIcon(":/symbols/heart_white.svg"));
    likeButton->setIconSize(QSize(71, 67));
    likeButton->setStyleSheet("background: transparent; border: none;");
    likeButton->setGeometry(475, 20, 71, 67);
    likeButton->setCheckable(true);
    connect(likeButton, &QPushButton::clicked, [likeButton]() {
        if (likeButton->isChecked()) {
            likeButton->setIcon(QIcon(":/symbols/heart_pink.svg"));
            qDebug() << "Лайк поставлен!";
        } else {
            likeButton->setIcon(QIcon(":/symbols/heart_white.svg"));
            qDebug() << "Лайк снят!";
        }
    });

    // Информационный фрейм снизу
    QFrame *infoFrame = new QFrame(universeCard);
    infoFrame->setGeometry(0, 313, 566, 58);
    infoFrame->setStyleSheet(
        "background-color: #07181D;"
        "border-top-left-radius: 0px; border-top-right-radius: 0px;"
        "border-bottom-left-radius: 20px; border-bottom-right-radius: 20px;"
        );

    // Метка названия
    QLabel *nameLabel = new QLabel(name, universeCard);
    int fontId = QFontDatabase::addApplicationFont(":/fonts/CinzelDecorative-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(family, 25);
    font.setBold(true);
    nameLabel->setFont(font);
    nameLabel->setStyleSheet("color: white; background: transparent;");
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setWordWrap(true);
    nameLabel->setGeometry(0, 295, 566, 77);

    // Добавляем карточку в контейнер rowContainer с компоновкой horizontalLayout_3
    if (ui->horizontalLayout_3) {
        ui->horizontalLayout_3->addWidget(cardWidget);
        qDebug() << "Карточка добавлена в rowContainer!";
    } else {
        qDebug() << "Ошибка: horizontalLayout_3 не найден!";
    }

    // Вернуть готовую карточку
    return cardWidget;
}



CatalogForm::CatalogForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainContainer)
{
    ui->setupUi(this);

    // Проверка и установка компоновки для контейнера карточек
    if (!ui->cardContainer->layout()) {
        ui->cardContainer->setLayout(new QVBoxLayout());
        qDebug() << "Создан новый layout для cardContainer.";
    }

    QFontDatabase::addApplicationFont(":/fonts/CinzelDecorative-Regular.ttf");


    // Пример загрузки названия (позже подключим к БД)
    QSqlDatabase db = QSqlDatabase::database(); // Получаем уже открытое соединение по умолчанию

    QSqlQuery query(db);
    if (query.exec("SELECT name, main_image FROM Universe WHERE id_universe IN (1, 2)")) {
        qDebug() << "Запрос выполнен успешно!";
        while (query.next()) {
            QString name = query.value(0).toString();
            QString imagePath = query.value(1).toString();
            qDebug() << "Обработка вселенной: " << name << " с изображением: " << imagePath;

            // Создаём карточку с полученными данными
            QWidget* card = createUniverseCard(name, imagePath, ui->cardContainer);
            if (card) {
                qDebug() << "Карточка успешно добавлена в контейнер.";
            } else {
                qDebug() << "Ошибка создания карточки!";
            }
        }
    } else {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    }




    // Установка фонового изображения
    QPixmap pixmap2(":/images/catalog_background_img.jpg");
    ui->backgroundLabel->setPixmap(pixmap2.scaled(ui->backgroundLabel->size(),
                                                 Qt::IgnoreAspectRatio,
                                                 Qt::SmoothTransformation));


}

// Деструктор
CatalogForm::~CatalogForm()
{
    delete ui;
}
