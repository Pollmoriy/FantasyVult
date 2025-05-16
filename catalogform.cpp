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

    QWidget *cardWidget = new QWidget(parent);
    cardWidget->setStyleSheet("background-color: transparent; border-radius: 20px;");
    cardWidget->setFixedSize(566, 372);

    QFrame *universeCard = new QFrame(cardWidget);
    universeCard->setStyleSheet("background-color: transparent;");
    universeCard->setFixedSize(566, 372);

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

    QFrame *infoFrame = new QFrame(universeCard);
    infoFrame->setGeometry(0, 313, 566, 58);
    infoFrame->setStyleSheet(
        "background-color: #07181D;"
        "border-top-left-radius: 0px; border-top-right-radius: 0px;"
        "border-bottom-left-radius: 20px; border-bottom-right-radius: 20px;"
        );

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

    // Убираем добавление сюда!
    // if (ui->horizontalLayout_3) {
    //    ui->horizontalLayout_3->addWidget(cardWidget);
    //    qDebug() << "Карточка добавлена в rowContainer!";
    // } else {
    //    qDebug() << "Ошибка: horizontalLayout_3 не найден!";
    // }

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
    if (!query.exec("SELECT name, main_image FROM Universe WHERE id_universe IN (1,2,3,4,5,6,7,8,9,10,11,12,13,14) ORDER BY id_universe")) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    // Список горизонтальных лэйаутов - создайте 7 в .ui с именами: horizontalLayout_4, ..., horizontalLayout_10
    QList<QHBoxLayout*> rows = {
        ui->horizontalLayout_3,
        ui->horizontalLayout_4,
        ui->horizontalLayout_5,
        ui->horizontalLayout_6,
        ui->horizontalLayout_7,
        ui->horizontalLayout_8,
        ui->horizontalLayout_9
    };


    int cardIndex = 0;
    while (query.next()) {
        QString name = query.value(0).toString();
        QString imagePath = query.value(1).toString();

        QWidget* card = createUniverseCard(name, imagePath, ui->cardContainer);
        if (!card) {
            qDebug() << "Ошибка создания карточки для" << name;
            continue;
        }

        int rowNum = cardIndex / 2;
        if (rowNum >= rows.size()) {
            qDebug() << "Превышено количество рядов!";
            break;
        }

        rows[rowNum]->addWidget(card);

        ++cardIndex;
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
