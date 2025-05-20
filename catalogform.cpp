#include "catalogform.h"
#include "mainwindow.h"
#include "favoriteform.h"
#include "testsform.h"
#include "ui_catalogform.h"
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



// ==================== // Активная кнопка навигации ====================
void CatalogForm::setActiveButton(QPushButton* newActive)
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
void CatalogForm::goToMain()
{
    setActiveButton(ui->btnMain); // Пример
    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}


// ==================== // Переход на каталог ====================
void CatalogForm::goToCatalog()
{
    setActiveButton(ui->btnCatalog);
    CatalogForm* catalogform = new CatalogForm();
    catalogform->show();
    this->close();
}


// ==================== // Переход на любимую ====================
void CatalogForm::goToFavorite()
{
    setActiveButton(ui->btnFavorite);
    FavoriteForm* favoriteform = new FavoriteForm();
    favoriteform->show();
    this->close();
}



// ==================== // Переход на тесты ====================
void CatalogForm::goToTests()
{
    setActiveButton(ui->btnTests);
    TestsForm* testsform = new TestsForm();
    testsform->show();
    this->close();
}






// ==================== Создание карточки вселенной ====================
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

    // Кнопка лайка
    QPushButton *likeButton = new QPushButton(universeCard);
    likeButton->setIcon(QIcon(":/symbols/heart_white.svg"));
    likeButton->setIconSize(QSize(71, 67));
    likeButton->setStyleSheet("background: transparent; border: none;");
    likeButton->setGeometry(475, 20, 71, 67);
    likeButton->setCheckable(true);

    // Если вселенная уже лайкнута, поставим кнопку в checked
    if (likedUniverses.contains(name)) {
        likeButton->setChecked(true);
        likeButton->setIcon(QIcon(":/symbols/heart_pink.svg"));
    }

    connect(likeButton, &QPushButton::clicked, [this, likeButton, name]() {
        if (likeButton->isChecked()) {
            likeButton->setIcon(QIcon(":/symbols/heart_pink.svg"));
            likedUniverses.insert(name);
            qDebug() << "Лайк поставлен на:" << name;
        } else {
            likeButton->setIcon(QIcon(":/symbols/heart_white.svg"));
            likedUniverses.remove(name);
            qDebug() << "Лайк снят с:" << name;
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
void CatalogForm::clearCards()
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

    if (emptyResultLabel) {
        emptyResultLabel->hide();
    }
}

// ==================== Загрузка и отображение карточек по фильтру ====================
void CatalogForm::loadUniverses(const QString& filter)
{
    clearCards();

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    QString sqlQuery;
    if (filter.isEmpty()) {
        sqlQuery = "SELECT name, main_image FROM Universe";
    } else {
        sqlQuery = "SELECT name, main_image FROM Universe WHERE name LIKE :filter";
    }

    if (!query.prepare(sqlQuery)) {
        qDebug() << "Ошибка подготовки запроса:" << query.lastError().text();
        return;
    }

    if (!filter.isEmpty()) {
        query.bindValue(":filter", "%" + filter + "%");
    }

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
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

    // Возвращаем количество найденных карточек
    // (сохраняем для обработки во внешнем методе)
    this->foundCardsCount = cardCount;
}

// ==================== Обработчик кнопки поиска ====================
void CatalogForm::onSearchButtonClicked()
{
    QString filterText = ui->searchLineEdit->text().trimmed();

    loadUniverses(filterText);

    // Если ничего не найдено — показать наш милый кастомный диалог, НЕ очищать каталог
    if (foundCardsCount == 0) {
        showNoResultsDialog(filterText);

        // После этого снова загрузить ВСЕ вселенные (чтобы каталог не пустел)
        loadUniverses("");
    }
}


// ==================== Вызов ошибки поиска ====================
void CatalogForm::showNoResultsDialog(const QString& searchText)
{
    QDialog dialog(this);
    dialog.setWindowTitle("Результат поиска");
    dialog.setFixedSize(500, 220);
    dialog.setStyleSheet("background-color: #FFE6E6;");

    // Основной вертикальный лэйаут
    QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);

    // Горизонтальный лэйаут для иконки и текста
    QHBoxLayout* contentLayout = new QHBoxLayout();

    // Иконка слева
    QLabel* iconLabel = new QLabel(&dialog);
    QPixmap iconPixmap(":/images/cute_icon.png");
    if (iconPixmap.isNull()) {
        qDebug() << "Ошибка: иконка не загружена!";
    }
    iconLabel->setPixmap(iconPixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    contentLayout->addWidget(iconLabel);

    // Текст справа, центрированный, с белым фоном и отступом снизу
    QLabel* textLabel = new QLabel(&dialog);
    textLabel->setText(QString("В нашей базе знаний не найдена вселенная с названием:\n\"%1\"").arg(searchText));
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setWordWrap(true);
    textLabel->setStyleSheet(
        "background-color: white;"
        "font-family: 'Roboto Condensed', sans-serif;"
        "font-size: 30px;"
        "color: black;"
        "padding: 10px 10px 10px 10px;"  // Отступ снизу 50px для кнопки
        "border-radius: 10px;"
        );
    contentLayout->addWidget(textLabel, /*stretch=*/1);

    mainLayout->addLayout(contentLayout);

    // Кнопка OK внизу по центру
    QPushButton* okButton = new QPushButton("OK", &dialog);
    okButton->setFixedSize(100, 40);
    okButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #FFB6B9;"
        "  border-radius: 10px;"
        "  font-size: 20px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #FF7B7B;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #FF4C4C;"
        "}"
        );
    mainLayout->addWidget(okButton, 0, Qt::AlignCenter);

    // Соединяем кнопку с закрытием диалога и очисткой строки ввода
    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(&dialog, &QDialog::accepted, this, [this]() {
        ui->searchLineEdit->clear();
    });

    dialog.exec();
}


// ==================== Отображение окна тегов ====================
void CatalogForm::toggleFilterFrame()
{
    if (ui->tagsFrame->isVisible()) {
        ui->tagsFrame->hide();
    } else {
        ui->tagsFrame->show();
    }
}



// ==================== Реализация слота нажатия на кнопку тега ====================
void CatalogForm::onTagButtonClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    bool isSelected = button->property("selected").toBool();
    button->setProperty("selected", !isSelected);

    // Обновляем стиль кнопки
    button->style()->unpolish(button);
    button->style()->polish(button);
    button->update();

    // Получаем текст тега из кнопки
    QString tagName = button->text();

    // Добавляем или удаляем тег из множества
    if (!isSelected) {
        selectedTags.insert(tagName);
        qDebug() << "Тег добавлен:" << tagName;
    } else {
        selectedTags.remove(tagName);
        qDebug() << "Тег удален:" << tagName;
    }

    qDebug() << "Выбранные теги:" << selectedTags;
}





// ==================== Функция для установки начального стиля кнопки ====================
void CatalogForm::setupTagButton(QPushButton* button) {
    button->setProperty("selected", false);  // Изначально не выбрана
    button->setStyleSheet(R"(
        QPushButton[selected="false"] {
            background-color: #000000;
            color: #FFFFFF;
            font-family: 'Roboto';
            font-size: 45px;
            border-radius: 40px;
        }
        QPushButton[selected="false"]:hover {
            background-color: rgba(0, 0, 0, 0.4);
        }
        QPushButton[selected="true"] {
            background-color: #610741;
            color: #FFFFFF;
            font-family: 'Roboto';
            font-size: 45px;
            border-radius: 40px;
        }
        QPushButton[selected="true"]:hover {
            opacity: 0.7;  /* Полупрозрачность при наведении */
        }
    )");

    // Подключаем слот к кнопке
    connect(button, &QPushButton::clicked, this, &CatalogForm::onTagButtonClicked);
}




// ==================== // Функция для подключения сигнала к слоту ====================
void CatalogForm::connectTagButton(QPushButton* button) {
    connect(button, &QPushButton::clicked, this, [=]() {
        bool isSelected = button->property("selected").toBool();
        button->setProperty("selected", !isSelected);

        // Обновляем стиль кнопки
        button->style()->unpolish(button);
        button->style()->polish(button);
        button->update();
    });
}


// ==================== Очистка всех выбранных тегов ====================
void CatalogForm::clearTagSelection()
{
    // Перебираем все виджеты внутри контейнера с тегами
    QList<QPushButton*> allButtons = ui->tagsFrame->findChildren<QPushButton*>();

    for (QPushButton* button : allButtons) {
        if (selectedTags.contains(button->text())) {
            // Меняем состояние на "невыбранное"
            button->setProperty("selected", false);

            // Обновляем стиль кнопки
            button->style()->unpolish(button);
            button->style()->polish(button);
            button->update();
        }
    }

    // Очищаем список выбранных тегов (строк)
    selectedTags.clear();
}


// ==================== // Применение фильтрации по тегам ====================
void CatalogForm::applyTagSelection()
{
    if (selectedTags.isEmpty()) {
        // Если список выбранных тегов пуст — загрузить весь каталог
        loadUniverses("");
        ui->tagsFrame->hide();
        return;
    }

    // Преобразуем выбранные теги в нижний регистр для корректного поиска
    QStringList tagsList;
    for (const QString& tag : selectedTags) {
        tagsList << tag.toLower();  // Приводим к нижнему регистру
    }

    loadUniversesByTags(tagsList);
    ui->tagsFrame->hide();
}




// ==================== // Фильтрация по тегам ====================
void CatalogForm::loadUniversesByTags(const QStringList& tagsList)
{
    clearCards();

    if (tagsList.isEmpty()) {
        loadUniverses("");  // Загружаем все, если тегов нет
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    // Формируем условие с AND, чтобы все теги были в колонке tegs
    QStringList conditions;
    for (const QString& tag : tagsList) {
        conditions << QString("LOWER(tegs) LIKE '%%1%'").arg(tag.toLower());
    }
    QString conditionString = conditions.join(" AND ");
    QString sqlQuery = QString("SELECT name, main_image FROM Universe WHERE %1").arg(conditionString);

    if (!query.prepare(sqlQuery)) {
        qDebug() << "Ошибка подготовки запроса:" << query.lastError().text();
        return;
    }

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
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

    if (cardCount == 0) {
        qDebug() << "Не найдено ни одной вселенной с указанными тегами.";
    }
}



// ==================== Конструктор ====================
CatalogForm::CatalogForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CatalogForm)
{
    ui->setupUi(this);

    ui->tagsFrame->hide();


    // Настраиваем каждую теговую кнопку
    setupTagButton(ui->btnTagBooks);
    setupTagButton(ui->btnTagEpicFantasy);
    setupTagButton(ui->btnTagCityFantasy);
    setupTagButton(ui->btnTagAnime);
    setupTagButton(ui->btnTagPolitics);
    setupTagButton(ui->btnTagGames);
    setupTagButton(ui->btnTagDragons);
    setupTagButton(ui->btnTagMagic);
    setupTagButton(ui->btnTagAdventure);
    setupTagButton(ui->btnTagMovies);
    setupTagButton(ui->btnTagDarkFantasy);

    // Проверяем, есть ли layout у контейнера для карточек
    if (!ui->cardContainer->layout()) {
        ui->cardContainer->setLayout(new QVBoxLayout());
        qDebug() << "Создан новый layout для cardContainer.";
    }

    QFontDatabase::addApplicationFont(":/fonts/CinzelDecorative-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto_Condensed-Regular.ttf");


    // Загрузка начального списка вселенных (можно позже заменить на loadUniverses(""))
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    if (!query.exec("SELECT name, main_image FROM Universe WHERE id_universe IN (1,2,3,4,5,6,7,8,9,10,11,12,13,14) ORDER BY id_universe")) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

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

    // Установка фонового изображения с закругленными углами
    QPixmap pixmap3(":/images/button_background.jpg");
    QPixmap roundedPixmap(ui->teg_backlabel->size());
    roundedPixmap.fill(Qt::transparent); // Прозрачный фон

    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Создаем закругленную маску
    QPainterPath path;
    path.addRoundedRect(roundedPixmap.rect(), 45, 45); // Радиус углов 20

    painter.setClipPath(path); // Обрезаем углы
    painter.drawPixmap(0, 0, pixmap3.scaled(ui->teg_backlabel->size(),
                                            Qt::IgnoreAspectRatio,
                                            Qt::SmoothTransformation));
    painter.end();

    ui->teg_backlabel->setPixmap(roundedPixmap);


    // Подключаем сигнал кнопки поиска к слоту
    connect(ui->searchButton, &QPushButton::clicked, this, &CatalogForm::onSearchButtonClicked);
    connect(ui->filterButton, &QPushButton::clicked, this, &CatalogForm::toggleFilterFrame);
    connect(ui->btnCloseTagsWindow, &QPushButton::clicked, this, &CatalogForm::toggleFilterFrame);
   connect(ui->btnClearSelection, &QPushButton::clicked, this, &CatalogForm::clearTagSelection);
   connect(ui->btnApplySelection, &QPushButton::clicked, this, &CatalogForm::applyTagSelection);


   connect(ui->btnMain, &QPushButton::clicked, this, &CatalogForm::goToMain);
   connect(ui->btnCatalog, &QPushButton::clicked, this, &CatalogForm::goToCatalog);
   connect(ui->btnFavorite, &QPushButton::clicked, this, &CatalogForm::goToFavorite);
   connect(ui->btnTests, &QPushButton::clicked, this, &CatalogForm::goToTests);

}

// ==================== Деструктор ====================
CatalogForm::~CatalogForm()
{
    delete ui;
}
