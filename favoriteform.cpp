#include "favoriteform.h"
#include "catalogform.h"
#include "mainwindow.h"
#include "testsform.h"
#include "basemainwindow.h"
#include "ui_favoriteform.h"
#include "universeform.h"
#include "clickablelabel.h"
#include <QFontDatabase>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QMessageBox>
#include <QDialog>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QStyle>
#include "buttonstyles.h"

// ==================== Создание карточки вселенной ====================
QWidget* FavoriteForm::createUniverseCard(const QString &name, const QString &imagePath, QWidget *parent)
{
    // Можно использовать тот же код, что и в CatalogForm, возможно вынести в общий helper
    QWidget *cardWidget = new QWidget(parent);
    cardWidget->setStyleSheet("background-color: transparent; border-radius: 20px;");
    cardWidget->setFixedSize(566, 372);

    QFrame *universeCard = new QFrame(cardWidget);
    universeCard->setStyleSheet("background-color: transparent;");
    universeCard->setFixedSize(566, 372);

    ClickableLabel *imageLabel = new ClickableLabel(universeCard);
    imageLabel->setFixedSize(566, 321);
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        pixmap = QPixmap(":/images/placeholder.png");
    }
    imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    imageLabel->setStyleSheet("border: none;");
    imageLabel->setGeometry(0, 0, 566, 321);

    connect(imageLabel, &ClickableLabel::clicked, this, [=]() {
        QSqlQuery idQuery;
        idQuery.prepare("SELECT id_universe FROM Universe WHERE name = :name");
        idQuery.bindValue(":name", name);
        if (!idQuery.exec() || !idQuery.next()) {
            qDebug() << "Не удалось получить id_universe для перехода:" << name;
            return;
        }

        int universeId = idQuery.value(0).toInt();
        UniverseForm* universeForm = new UniverseForm();
        universeForm->setData(userId, universeId);
        universeForm->show();
        this->close();
    });

    // Кнопка лайка
    QPushButton *likeButton = new QPushButton(universeCard);
    likeButton->setIcon(QIcon(":/symbols/heart_pink.svg")); // по умолчанию любимая — розовая
    likeButton->setIconSize(QSize(71, 67));
    likeButton->setStyleSheet("background: transparent; border: none;");
    likeButton->setGeometry(475, 20, 71, 67);
    likeButton->setCheckable(true);
    likeButton->setChecked(true);

    // Обработка клика лайка (удаление из избранного)
    connect(likeButton, &QPushButton::clicked, [this, likeButton, name]() {
        QSqlQuery query;

        QSqlQuery idQuery;
        idQuery.prepare("SELECT id_universe FROM Universe WHERE name = :name");
        idQuery.bindValue(":name", name);
        if (!idQuery.exec() || !idQuery.next()) {
            qDebug() << "Не удалось получить id вселенной по имени:" << name;
            return;
        }
        int universeId = idQuery.value(0).toInt();

        if (!likeButton->isChecked()) { // сняли лайк
            likeButton->setIcon(QIcon(":/symbols/heart_white.svg"));

            // Удаляем из БД лайков
            query.prepare("DELETE FROM Likes WHERE id_user = :userId AND id_universe = :universeId");
            query.bindValue(":userId", userId);
            query.bindValue(":universeId", universeId);
            if (!query.exec()) {
                qDebug() << "Ошибка при удалении лайка:" << query.lastError().text();
            }

            // Обновляем UI с помощью уже готовых функций
            clearCards();
            loadFavoriteUniverses();
        }
    });




    // Нижняя панель с названием
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

    return cardWidget;
}

// ==================== Очистка всех карточек с экрана ====================
void FavoriteForm::clearCards()
{
    QList<QHBoxLayout*> horizontalLayouts = {
        ui->horizontalLayout_3,
        ui->horizontalLayout_4,
        ui->horizontalLayout_5,
        ui->horizontalLayout_6,
        ui->horizontalLayout_7,
        ui->horizontalLayout_8,
        ui->horizontalLayout_9
    };

    for (QHBoxLayout* hlayout : horizontalLayouts) {
        if (!hlayout) continue;
        QLayoutItem* item;
        while ((item = hlayout->takeAt(0)) != nullptr) {
            QWidget* widget = item->widget();
            if (widget) {
                widget->setParent(nullptr);
                widget->deleteLater();
            }
            delete item;
        }
    }
    for (QHBoxLayout* hlayout : horizontalLayouts) {
        hlayout->update();
        hlayout->invalidate();
    }
    ui->cardContainer->update();
    ui->cardContainer->adjustSize();

}

// ==================== Загрузка и отображение только лайкнутых вселенных ====================
void FavoriteForm::loadFavoriteUniverses()
{
    clearCards();

    QSqlQuery query;
    // Получаем лайкнутые вселенные для текущего пользователя с изображениями
    query.prepare(
        "SELECT Universe.name, Universe.main_image "
        "FROM Likes "
        "JOIN Universe ON Likes.id_universe = Universe.id_universe "
        "WHERE Likes.id_user = :userId"
        );
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса для любимых вселенных:" << query.lastError().text();
        return;
    }

    QList<QHBoxLayout*> horizontalLayouts = {
        ui->horizontalLayout_3,
        ui->horizontalLayout_4,
        ui->horizontalLayout_5,
        ui->horizontalLayout_6,
        ui->horizontalLayout_7,
        ui->horizontalLayout_8,
        ui->horizontalLayout_9
    };

    int cardCount = 0;
    int rowIndex = 0;

    while (query.next()) {
        QString name = query.value(0).toString();
        QString imagePath = query.value(1).toString();

        QWidget* card = createUniverseCard(name, imagePath, ui->cardContainer);
        if (!card) continue;

        if (rowIndex >= horizontalLayouts.size()) {
            qDebug() << "Превышено количество строк, дополнительные карточки не добавлены";
            break;
        }

        horizontalLayouts[rowIndex]->addWidget(card);
        cardCount++;

        if (cardCount % 2 == 0) {
            rowIndex++;
        }
    }
}

// ==================== // Переход на страницу вселенной ====================
    void FavoriteForm::openUniverse(int universeId)
{
    UniverseForm* universeForm = new UniverseForm();
    universeForm->setData(userId, universeId);
    universeForm->show();
    this->close(); // или hide()
}

// ==================== // Активная кнопка навигации ====================
void FavoriteForm::setActiveButton(QPushButton* newActive)
{
    // Сбросить стиль у предыдущей кнопки
    if (activeButton && activeButton != newActive) {
        activeButton->setStyleSheet(defaultButtonStyle);
    }

    // Назначить новую активную кнопку
    activeButton = newActive;

    // Применить активный стиль
    activeButton->setStyleSheet(activeButtonStyle);
}

// ==================== // Переход на главную ====================
void FavoriteForm::goToMain()
{
    setActiveButton(ui->btnMain);

    MainWindow* mw = new MainWindow(this->userId);

    QRect screenGeometry = this->geometry();
    mw->setGeometry(screenGeometry.x() + screenGeometry.width(), screenGeometry.y(),
                    screenGeometry.width(), screenGeometry.height());
    mw->show();

    QPropertyAnimation* animNew = new QPropertyAnimation(mw, "geometry");
    animNew->setDuration(300);
    animNew->setStartValue(mw->geometry());
    animNew->setEndValue(screenGeometry);
    animNew->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation* animOld = new QPropertyAnimation(this, "geometry");
    animOld->setDuration(300);
    animOld->setStartValue(screenGeometry);
    animOld->setEndValue(QRect(screenGeometry.x() - screenGeometry.width(), screenGeometry.y(),
                               screenGeometry.width(), screenGeometry.height()));
    animOld->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animOld, &QPropertyAnimation::finished, this, &FavoriteForm::close);
}

void FavoriteForm::goToCatalog()
{
    setActiveButton(ui->btnCatalog);

    CatalogForm* catalog = new CatalogForm(this->userId);

    QRect screenGeometry = this->geometry();
    catalog->setGeometry(screenGeometry.x() + screenGeometry.width(), screenGeometry.y(),
                         screenGeometry.width(), screenGeometry.height());
    catalog->show();

    QPropertyAnimation* animNew = new QPropertyAnimation(catalog, "geometry");
    animNew->setDuration(300);
    animNew->setStartValue(catalog->geometry());
    animNew->setEndValue(screenGeometry);
    animNew->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation* animOld = new QPropertyAnimation(this, "geometry");
    animOld->setDuration(300);
    animOld->setStartValue(screenGeometry);
    animOld->setEndValue(QRect(screenGeometry.x() - screenGeometry.width(), screenGeometry.y(),
                               screenGeometry.width(), screenGeometry.height()));
    animOld->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animOld, &QPropertyAnimation::finished, this, &FavoriteForm::close);
}

// ==================== // Переход на тесты ====================
void FavoriteForm::goToTests()
{
    setActiveButton(ui->btnTests);

    TestsForm* testsform = new TestsForm(this->userId);

    QRect screenGeometry = this->geometry();
    testsform->setGeometry(screenGeometry.x() + screenGeometry.width(), screenGeometry.y(),
                           screenGeometry.width(), screenGeometry.height());
    testsform->show();

    QPropertyAnimation* animNew = new QPropertyAnimation(testsform, "geometry");
    animNew->setDuration(300);
    animNew->setStartValue(testsform->geometry());
    animNew->setEndValue(screenGeometry);
    animNew->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation* animOld = new QPropertyAnimation(this, "geometry");
    animOld->setDuration(300);
    animOld->setStartValue(screenGeometry);
    animOld->setEndValue(QRect(screenGeometry.x() - screenGeometry.width(), screenGeometry.y(),
                               screenGeometry.width(), screenGeometry.height()));
    animOld->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animOld, &QPropertyAnimation::finished, this, &FavoriteForm::close);
}

FavoriteForm::FavoriteForm(int userId, QWidget *parent) :
     BaseMainWindow(parent),
    ui(new Ui::FavoriteForm),
    userId(userId) // инициализируем поле
{
    ui->setupUi(this);

    qDebug() << "Текущий userId: " << userId;

    loadFavoriteUniverses();

    QFontDatabase::addApplicationFont(":/fonts/CinzelDecorative-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto_Condensed-Regular.ttf");

    // Установка фонового изображения
    QPixmap pixmap2(":/images/favorite_background_img.jpg");
    ui->backgroundLabel->setPixmap(pixmap2.scaled(ui->backgroundLabel->size(),
                                                  Qt::IgnoreAspectRatio,
                                                  Qt::SmoothTransformation));


    connect(ui->btnMain, &QPushButton::clicked, this, &FavoriteForm::goToMain);
    connect(ui->btnCatalog, &QPushButton::clicked, this, &FavoriteForm::goToCatalog);
    connect(ui->btnTests, &QPushButton::clicked, this, &FavoriteForm::goToTests);

}

FavoriteForm::~FavoriteForm()
{
    delete ui;
}
