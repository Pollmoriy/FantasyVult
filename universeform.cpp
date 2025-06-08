#include "universeform.h"
#include "ui_universeform.h"
#include "catalogform.h"
#include "basemainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include <QSqlDatabase>
#include <QDir>
#include <QFileInfo>

UniverseForm::UniverseForm(QWidget *parent)
    : BaseMainWindow(parent)
    , ui(new Ui::UniverseForm)
{
    ui->setupUi(this);

    // Проверяем ui-объекты
    Q_ASSERT(ui->contentContainer != nullptr);

    verticalLayout = new QVBoxLayout(ui->contentContainer);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->setSpacing(0);
    verticalLayout->setAlignment(Qt::AlignTop);

}

UniverseForm::~UniverseForm()
{
    delete ui;
}

// ==================== // Загрузка всех данных из БД ====================
void UniverseForm::setData(int userId, int universeId)
{
    this->userId = userId;
    this->universeId = universeId;

    qDebug() << "UniverseForm::setData called";
    qDebug() << "Received userId:" << userId;
    qDebug() << "Received universeId:" << universeId;

    QSqlQuery nameQuery;
    nameQuery.prepare("SELECT name FROM Universe WHERE id_universe = :id");
    nameQuery.bindValue(":id", universeId);
    if (nameQuery.exec() && nameQuery.next()) {
        currentUniverseName = nameQuery.value(0).toString();
        qDebug() << "[ВСЕЛЕННАЯ] Загружено имя:" << currentUniverseName;
    } else {
        qDebug() << "[ОШИБКА] Не удалось загрузить имя вселенной по ID:" << nameQuery.lastError().text();
        return;
    }


    loadFirstBlock();
    loadMainTextBlock();
    loadWorldGeographyBlock();
    loadPlacesSliderBlock();
    loadHeroesBlock();
    loadFactsBlock();
    addLikeBlock(currentUniverseName);


}

// ==================== // Загрузка главного блока ====================
void UniverseForm::loadFirstBlock()
{
    QSqlQuery query;
    query.prepare(R"(
        SELECT U.name, UC.image
        FROM Universe U
        JOIN UniverseContent UC ON U.id_universe = UC.id_universe
        WHERE U.id_universe = :id AND UC.block_type = 'main_image'
        LIMIT 1
    )");
    query.bindValue(":id", universeId);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString universeName = query.value(0).toString();
        QString imagePath = query.value(1).toString();
        qDebug() << "Загрузка блока: name =" << universeName << ", image =" << imagePath;

        // Создаём контейнер блока 1920x1080
        QWidget *block = new QWidget();
        block->setFixedSize(1920, 1080);

        // Картинка - QLabel с проверкой
        QLabel *imageLabel = new QLabel(block);
        imageLabel->setFixedSize(1920, 1080);

        QPixmap pixmap(imagePath);
        if (pixmap.isNull()) {
            qDebug() << "Ошибка: не удалось загрузить изображение:" << imagePath;
            pixmap = QPixmap(":/images/placeholder.png");  // или любой запасной путь
        }
        imageLabel->setPixmap(pixmap.scaled(imageLabel->size(),
                                            Qt::IgnoreAspectRatio,
                                            Qt::SmoothTransformation));
        imageLabel->setStyleSheet("border: none;");
        imageLabel->setGeometry(0, 0, 1920, 1080);

        // Загружаем шрифт
        int fontId = QFontDatabase::addApplicationFont(":/fonts/CinzelDecorative-Regular.ttf");
        QString family = QFontDatabase::applicationFontFamilies(fontId).isEmpty() ? "Cinzel" : QFontDatabase::applicationFontFamilies(fontId).at(0);

        // Название вселенной
        QLabel *titleLabel = new QLabel(universeName, block);
        QFont font(family, 100);  // 200 слишком много для Qt, 100 - ок
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet("color: white; background: transparent;");
        titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        titleLabel->setGeometry(0, 900, 1920, 120);  // 120 пикселей от низа блока

        // Добавляем блок в вертикальный layout
        verticalLayout->addWidget(block);
    } else {
        qDebug() << "Блок main_image не найден для universeId =" << universeId;
    }
}

// ==================== // Загрузка блока введение ====================
void UniverseForm::loadMainTextBlock()
{
    QSqlQuery query;
    query.prepare(R"(
        SELECT id_universe, block_type, content_text, image
        FROM UniverseContent
        WHERE id_universe = :id
    )");
    query.bindValue(":id", universeId);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    bool blockFound = false;

    while (query.next()) {
        QString blockType = query.value(1).toString();

        qDebug() << "Найден блок:"
                 << "universeId =" << query.value(0).toInt()
                 << "block_type =" << blockType
                 << "content_text =" << query.value(2).toString().left(50)
                 << "image =" << query.value(3).toString();

        if (blockType == "main_block") {
            blockFound = true;

            QString contentText = query.value(2).toString();
            QString imagePath = query.value(3).toString();

            QWidget *block = new QWidget();
            block->setFixedSize(1920, 1080);

            // Фон - картинка
            QLabel *backgroundLabel = new QLabel(block);
            backgroundLabel->setFixedSize(1920, 1080);
            QPixmap pixmap(imagePath);
            if (pixmap.isNull()) {
                qDebug() << "Ошибка: не удалось загрузить изображение main_block:" << imagePath;
                pixmap = QPixmap(":/images/placeholder.png");
            }
            backgroundLabel->setPixmap(pixmap.scaled(backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            backgroundLabel->setGeometry(0, 0, 1920, 1080);
            backgroundLabel->lower();

            // Полупрозрачный черный прямоугольник
            QWidget *overlay = new QWidget(block);
            overlay->setFixedSize(1504, 1080);
            overlay->move((1920 - 1504) / 2, 0);
            overlay->setStyleSheet("background-color: rgba(0, 0, 0, 128);");

            // Создаем layout для текста с отступами
            QVBoxLayout *overlayLayout = new QVBoxLayout(overlay);
            overlayLayout->setContentsMargins(30, 20, 30, 20); // отступы слева, сверху, справа, снизу
            overlayLayout->setSpacing(0);

            // Текст на overlay
            QLabel *textLabel = new QLabel();
            textLabel->setText(contentText);
            textLabel->setAlignment(Qt::AlignJustify | Qt::AlignVCenter);
            QFont font = textLabel->font();
            font.setBold(true);
            font.setPointSize(30);
            textLabel->setFont(font);
            textLabel->setStyleSheet("color: white; background: transparent;");
            textLabel->setWordWrap(true);

            // Чтобы текст занимал всю высоту overlay, устанавливаем растяжение
            overlayLayout->addWidget(textLabel);
            overlayLayout->setStretch(0, 1);

            verticalLayout->addWidget(block);

            // Если нужно загрузить только первый найденный блок main_block,
            // то можно прервать цикл здесь:
            break;
        }
    }

    if (!blockFound) {
        qDebug() << "Блок main_block не найден для universeId =" << universeId;
    }
}

// ==================== // Загрузка блока о мире и географии ====================
void UniverseForm::loadWorldGeographyBlock()
{
    QSqlQuery query;
    query.prepare(R"(
        SELECT content_text, image
        FROM UniverseContent
        WHERE id_universe = :id AND block_type = 'world_geography'
        LIMIT 1
    )");
    query.bindValue(":id", universeId);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString contentText = query.value("content_text").toString();
        QString imagePath = query.value("image").toString();

        qDebug() << "Найден блок: universeId =" << universeId
                 << "block_type = 'world_geography'"
                 << "content_text =" << contentText.left(50)
                 << "image =" << imagePath;

        QWidget *block = new QWidget();
        block->setFixedSize(1920, 1340);

        // Фоновая картинка
        QLabel *backgroundLabel = new QLabel(block);
        backgroundLabel->setFixedSize(1920, 1340);
        QPixmap pixmap(imagePath);
        if (pixmap.isNull()) {
            qDebug() << "Ошибка: не удалось загрузить изображение world_geography:" << imagePath;
            pixmap = QPixmap(":/images/placeholder.png");
        }
        backgroundLabel->setPixmap(pixmap.scaled(backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        backgroundLabel->setGeometry(0, 0, 1920, 1340);
        backgroundLabel->lower();

        // Полупрозрачный прямоугольник
        QWidget *overlay = new QWidget(block);
        overlay->setFixedSize(1503, 1354);
        overlay->move((1920 - 1503) / 2, 0);
        overlay->setStyleSheet("background-color: rgba(0, 0, 0, 128);");

        // Заголовок блока
        QLabel *titleLabel = new QLabel("Мир и география", overlay);
        titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        titleLabel->setFixedWidth(1503);
        titleLabel->move(0, 40);  // отступ сверху
        QFont titleFont("Inter", 64, QFont::Bold);
        titleLabel->setFont(titleFont);
        titleLabel->setStyleSheet("color: white; background: transparent;");

        // Текст блока
        QLabel *textLabel = new QLabel(overlay);
        textLabel->setText(contentText);
        textLabel->setWordWrap(true);
        textLabel->setAlignment(Qt::AlignJustify);
        QFont font("Inter", 30);
        font.setBold(false);
        textLabel->setFont(font);
        textLabel->setStyleSheet("color: white; background: transparent;");
        textLabel->setGeometry(40, 160, 1503 - 80, 1354 - 160);  // отступы по краям и сверху

        verticalLayout->addWidget(block);
    } else {
        qDebug() << "Блок world_geography не найден для universeId =" << universeId;
    }
}

// ==================== // Загрузка блока места ====================
void UniverseForm::loadPlacesSliderBlock()
{
    QSqlQuery query;
    query.prepare(R"(
        SELECT caption, image FROM UniverseSlider
        WHERE id_universe = :id AND slider_type = 'places'
        ORDER BY id_universeslider;
    )");
    query.bindValue(":id", universeId);

    if (!query.exec()) {
        qDebug() << "Ошибка запроса к UniverseSlider:" << query.lastError().text();
        return;
    }

    QVector<QWidget*> slides;

    while (query.next()) {
        QString caption = query.value(0).toString();
        QString imagePath = query.value(1).toString();

        QWidget *slide = new QWidget();
        slide->setFixedSize(1920, 1080);

        QLabel *backgroundLabel = new QLabel(slide);
        backgroundLabel->setFixedSize(1920, 1080);
        QPixmap pixmap(imagePath);
        if (pixmap.isNull()) {
            qDebug() << "Не удалось загрузить изображение слайдера:" << imagePath;
            pixmap = QPixmap(":/images/placeholder.png");
        }
        backgroundLabel->setPixmap(pixmap.scaled(1920, 1080, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        backgroundLabel->move(0, 0);

        // Полупрозрачный черный прямоугольник
        QWidget *captionBackground = new QWidget(slide);
        captionBackground->setGeometry((1920 - 1338) / 2, 829, 1338, 176);
        captionBackground->setStyleSheet("background-color: rgba(0, 0, 0, 180); border-radius: 20px;");

        QLabel *captionLabel = new QLabel(caption, captionBackground);
        captionLabel->setGeometry(30, 20, 1338 - 60, 176 - 40); // Отступы: 30 слева/справа, 20 сверху/снизу
        QFont font("Inter", 30);
        captionLabel->setFont(font);
        captionLabel->setStyleSheet("color: white; background: transparent;");
        captionLabel->setWordWrap(true);
        captionLabel->setAlignment(Qt::AlignCenter);

        slides.append(slide);
    }

    if (slides.isEmpty()) {
        qDebug() << "Нет слайдов для places.";
        return;
    }

    // Слайдер
    QWidget *block = new QWidget();
    block->setFixedSize(1920, 1080);

    sliderStackWidget = new QStackedWidget(block);
    sliderStackWidget->setGeometry(0, 0, 1920, 1080);

    for (QWidget *slide : slides) {
        sliderStackWidget->addWidget(slide);
    }

    // Левая кнопка
    QPushButton *leftButton = new QPushButton(block);
    leftButton->setFixedSize(127, 115);
    leftButton->move(50, 484);  // позиция слева
    leftButton->setStyleSheet(R"(
    QPushButton {
        background-color: black;
        border-radius: 20px;
QPushButton:hover {
        background-color: rgba(0, 0, 0, 180);
    }
)");
    QLabel *leftArrow = new QLabel(leftButton);
    leftArrow->setFixedSize(80, 80);
    leftArrow->setAlignment(Qt::AlignCenter);
    leftArrow->move((127 - 80) / 2, (115 - 80) / 2);
    leftArrow->setPixmap(QPixmap(":/symbols/Arrow.svg").scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Правая кнопка
    QPushButton *rightButton = new QPushButton(block);
    rightButton->setFixedSize(127, 115);
    rightButton->move(1920 - 127 - 50, 484);  // позиция справа
    rightButton->setStyleSheet(R"(
    QPushButton {
        background-color: black;
        border-radius: 20px;
QPushButton:hover {
        background-color: rgba(0, 0, 0, 180);
    }
)");
    QLabel *rightArrow = new QLabel(rightButton);
    rightArrow->setFixedSize(80, 80);
    rightArrow->setAlignment(Qt::AlignCenter);
    rightArrow->move((127 - 80) / 2, (115 - 80) / 2);

    QPixmap arrowPixmap(":/symbols/Arrow.svg");
    QTransform transform;
    transform.scale(-1, 1);  // зеркальное отражение по горизонтали
    arrowPixmap = arrowPixmap.transformed(transform, Qt::SmoothTransformation);

    rightArrow->setPixmap(arrowPixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));


    connect(leftButton, &QPushButton::clicked, this, &UniverseForm::showPreviousSlide);
    connect(rightButton, &QPushButton::clicked, this, &UniverseForm::showNextSlide);


    verticalLayout->addWidget(block);
}

void UniverseForm::showPreviousSlide()
{
    if (!sliderStackWidget) return;
    currentSlideIndex = (currentSlideIndex - 1 + sliderStackWidget->count()) % sliderStackWidget->count();
    sliderStackWidget->setCurrentIndex(currentSlideIndex);
}

void UniverseForm::showNextSlide()
{
    if (!sliderStackWidget) return;
    currentSlideIndex = (currentSlideIndex + 1) % sliderStackWidget->count();
    sliderStackWidget->setCurrentIndex(currentSlideIndex);
}

// ==================== // Загрузка блока героев ====================
void UniverseForm::loadHeroesBlock() {

    qDebug() << "Загрузка блока героев для вселенной с ID:" << universeId;

    QSqlQuery query;
    query.prepare(R"(
    SELECT name, description, image
    FROM UniverseHeroes
    WHERE id_universe = :id
)");
    query.bindValue(":id", universeId);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса героев:" << query.lastError().text();
        return;
    }


    heroesData.clear();

    while (query.next()) {
        QString name = query.value(0).toString();
        QString desc = query.value(1).toString();
        QString imgPath = query.value(2).toString();

        qDebug() << "Найден герой:" << name << "| картинка:" << imgPath;

        HeroData hero;
        hero.name = name;
        hero.description = desc;
        hero.imagePath = imgPath;
        heroesData.append(hero);

        qDebug() << "Loaded hero:" << name << imgPath;

    }

    if (heroesData.isEmpty()) {
        qDebug() << "Нет данных о героях для этой вселенной!";
        return;
    }

    // Базовый блок
    QWidget *block = new QWidget();
    block->setFixedSize(1920, 1213);

    // Фон
    QLabel *backgroundLabel = new QLabel(block);
    backgroundLabel->setFixedSize(1920, 1213);

    QSqlQuery bgQuery;
    bgQuery.prepare("SELECT main_image FROM Universe WHERE id_universe = :id");
    bgQuery.bindValue(":id", universeId);
    if (bgQuery.exec() && bgQuery.next()) {
        QString bgImage = bgQuery.value(0).toString();
        qDebug() << "Фоновое изображение блока героев:" << bgImage;
        QPixmap bgPixmap(bgImage);
        backgroundLabel->setPixmap(bgPixmap.scaled(backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    } else {
        qDebug() << "Ошибка при загрузке фонового изображения для блока героев.";
    }

    // Заголовок
    QLabel *title = new QLabel("HEROES", block);
    int fontId = QFontDatabase::addApplicationFont(":/fonts/CinzelDecorative-Regular.ttf");
    if (fontId == -1) {
        qDebug() << "Не удалось загрузить шрифт CinzelDecorative-Regular.ttf";
    } else {
        QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont font(family, 120, QFont::Bold);
        title->setFont(font);
    }
    title->setStyleSheet("color: white;");
    title->adjustSize();
   title->move((1920 - title->width()) / 2, 20);


    // Карточка героя
    heroCard = new QWidget(block);
    heroCard->setFixedSize(1356, 778);
    heroCard->move((1920 - 1356) / 2, 218);
    heroCard->setStyleSheet("background-color: black; border-radius: 25px;");

    // Стрелки
    QPushButton *leftButton = new QPushButton(block);
    leftButton->setFixedSize(127, 115);
    leftButton->move((1920 / 2) - 127 - 40, 218 + 778 + 59);
    leftButton->setStyleSheet(R"(
        QPushButton {
            background-color: black;
            border-radius: 20px;
        }
        QPushButton:hover {
            background-color: rgba(0, 0, 0, 180);
        }
    )");
    QLabel *leftIcon = new QLabel(leftButton);
    leftIcon->setPixmap(QPixmap(":/symbols/Arrow.svg").scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    leftIcon->setFixedSize(80, 80);
    leftIcon->move((127 - 80) / 2, (115 - 80) / 2);

    QPushButton *rightButton = new QPushButton(block);
    rightButton->setFixedSize(127, 115);
    rightButton->move((1920 / 2) + 40, 218 + 778 + 59);
    rightButton->setStyleSheet(R"(
        QPushButton {
            background-color: black;
            border-radius: 20px;
        }
        QPushButton:hover {
            background-color: rgba(0, 0, 0, 180);
        }
    )");
    QPixmap rightPixmap(":/symbols/Arrow.svg");
    rightPixmap = rightPixmap.transformed(QTransform().scale(-1, 1));
    QLabel *rightIcon = new QLabel(rightButton);
    rightIcon->setPixmap(rightPixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    rightIcon->setFixedSize(80, 80);
    rightIcon->move((127 - 80) / 2, (115 - 80) / 2);

    // Обработчики
    connect(leftButton, &QPushButton::clicked, this, [this]() {
        currentHeroIndex = (currentHeroIndex - 1 + heroesData.size()) % heroesData.size();
        showHeroAt(currentHeroIndex);
    });
    connect(rightButton, &QPushButton::clicked, this, [this]() {
        currentHeroIndex = (currentHeroIndex + 1) % heroesData.size();
        showHeroAt(currentHeroIndex);
    });

    verticalLayout->addWidget(block);
    currentHeroIndex = 0;
    showHeroAt(currentHeroIndex);
}

void UniverseForm::showHeroAt(int index) {
    qDebug() << "Показ героя #" << index << " из " << heroesData.size();

    if (index < 0 || index >= heroesData.size()) {
        qDebug() << "Индекс героя вне диапазона!";
        return;
    }

    // Очистка от предыдущих виджетов
    QList<QWidget*> children = heroCard->findChildren<QWidget*>();
    for (QWidget *child : children) {
        delete child;
    }

    if (heroCard->layout()) {
        delete heroCard->layout();
    }

    QHBoxLayout *cardLayout = new QHBoxLayout(heroCard);
    cardLayout->setContentsMargins(61, 44, 61, 44);
    cardLayout->setSpacing(50);

    // Картинка героя
    QLabel *imageLabel = new QLabel();
    imageLabel->setFixedSize(501, 690);

    QString imagePath = heroesData[index].imagePath;
    QPixmap heroImg;


    // Пробуем загрузить изображение из обычной папки
    if (!heroImg.load(imagePath)) {
        qDebug() << "Не удалось загрузить:" << imagePath;
        heroImg.load(":/images/placeholder.png"); // fallback из ресурсов, если нет картинки
    }
    QString fullPath = QDir::current().absoluteFilePath(heroesData[index].imagePath);
    qDebug() << "Пытаюсь загрузить картинку по пути:" << fullPath;

    QPixmap heroImg1(fullPath);

    qDebug() << "Текущая рабочая директория:" << QDir::currentPath();

    imageLabel->setPixmap(heroImg.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    cardLayout->addWidget(imageLabel);

    // Текст
    QVBoxLayout *textLayout = new QVBoxLayout();
    QLabel *nameLabel = new QLabel(heroesData[index].name);
    nameLabel->setFont(QFont("Inter", 35, QFont::Bold));
    nameLabel->setStyleSheet("color: white;");
    nameLabel->setAlignment(Qt::AlignCenter);
    textLayout->addWidget(nameLabel);

    QLabel *descLabel = new QLabel(heroesData[index].description);
    descLabel->setFont(QFont("Inter", 30));
    descLabel->setStyleSheet("color: white;");
    descLabel->setWordWrap(true);
    textLayout->addWidget(descLabel);

    cardLayout->addLayout(textLayout);
}

void UniverseForm::showPreviousHero()
{
    if (heroesData.isEmpty()) return;
    currentHeroIndex = (currentHeroIndex - 1 + heroesData.size()) % heroesData.size();
    showHeroAt(currentHeroIndex);
}

void UniverseForm::showNextHero()
{
    if (heroesData.isEmpty()) return;
    currentHeroIndex = (currentHeroIndex + 1) % heroesData.size();
    showHeroAt(currentHeroIndex);
}

// ==================== // Загрузка блока фактов ====================
void UniverseForm::loadFactsBlock() {
    qDebug() << "[ФАКТЫ] Загрузка фактов для вселенной ID =" << universeId;

    QSqlQuery query;
    query.prepare(R"(
        SELECT title, description, image
        FROM UniverseFacts
        WHERE id_universe = :id
        LIMIT 3
    )");
    query.bindValue(":id", universeId);

    if (!query.exec()) {
        qDebug() << "[ФАКТЫ] Ошибка запроса:" << query.lastError().text();
        return;
    }

    factsData.clear();

    while (query.next()) {
        FactData fact;
        fact.title = query.value(0).toString();
        fact.description = query.value(1).toString();
        fact.imagePath = query.value(2).toString();

        qDebug() << "[ФАКТЫ] Загружен факт:" << fact.title << "с картинкой:" << fact.imagePath;
        factsData.append(fact);
    }

    if (factsData.isEmpty()) {
        qDebug() << "[ФАКТЫ] Нет фактов для данной вселенной!";
        return;
    }

    // Виджет блока
    QWidget *block = new QWidget();
    block->setFixedSize(1920, 1457);

    // Фон
    QLabel *backgroundLabel = new QLabel(block);
    backgroundLabel->setFixedSize(1920, 1250);

    QSqlQuery bgQuery;
    bgQuery.prepare("SELECT main_image FROM Universe WHERE id_universe = :id");
    bgQuery.bindValue(":id", universeId);
    if (bgQuery.exec() && bgQuery.next()) {
        QString bgImage = bgQuery.value(0).toString();
        qDebug() << "Фоновое изображение блока героев:" << bgImage;
        QPixmap bgPixmap(bgImage);
        backgroundLabel->setPixmap(bgPixmap.scaled(backgroundLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    } else {
        qDebug() << "Ошибка при загрузке фонового изображения для блока героев.";
    }

    // Заголовок
    QLabel *title = new QLabel("Интересные факты", block);
    title->setFont(QFont("Cinzel", 90, QFont::Bold)); // уменьшен размер
    title->setStyleSheet("color: white;");
    title->adjustSize();
    title->move((1920 - title->width()) / 2, 20); // поднят выше

    // Карточка
    factCard = new QWidget(block);
    factCard->setFixedSize(1327, 810);
    factCard->move((1920 - 1327) / 2, 190);
    factCard->setStyleSheet("background-color: black; border-radius: 30px;");

    // Левая кнопка
    QPushButton *leftButton = new QPushButton(block);
    leftButton->setFixedSize(127, 115);
    leftButton->move((1920 / 2) - 127 - 40, 1059);
    leftButton->setStyleSheet(R"(
        QPushButton {
            background-color: black;
            border-radius: 20px;
        }
        QPushButton:hover {
            background-color: rgba(0, 0, 0, 180);
        }
    )");
    QLabel *leftIcon = new QLabel(leftButton);
    leftIcon->setPixmap(QPixmap(":/symbols/Arrow.svg").scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    leftIcon->setFixedSize(80, 80);
    leftIcon->move((127 - 80) / 2, (115 - 80) / 2);

    // Правая кнопка
    QPushButton *rightButton = new QPushButton(block);
    rightButton->setFixedSize(127, 115);
    rightButton->move((1920 / 2) + 40, 1059);
    rightButton->setStyleSheet(R"(
        QPushButton {
            background-color: black;
            border-radius: 20px;
        }
        QPushButton:hover {
            background-color: rgba(0, 0, 0, 180);
        }
    )");
    QPixmap rightPixmap(":/symbols/Arrow.svg");
    rightPixmap = rightPixmap.transformed(QTransform().scale(-1, 1));
    QLabel *rightIcon = new QLabel(rightButton);
    rightIcon->setPixmap(rightPixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    rightIcon->setFixedSize(80, 80);
    rightIcon->move((127 - 80) / 2, (115 - 80) / 2);

    // Обработчики
    connect(leftButton, &QPushButton::clicked, this, [this]() {
        currentFactIndex = (currentFactIndex - 1 + factsData.size()) % factsData.size();
        showFactAt(currentFactIndex);
    });
    connect(rightButton, &QPushButton::clicked, this, [this]() {
        currentFactIndex = (currentFactIndex + 1) % factsData.size();
        showFactAt(currentFactIndex);
    });

    verticalLayout->addWidget(block);

    currentFactIndex = 0;
    showFactAt(currentFactIndex);
}

void UniverseForm::showFactAt(int index) {
    qDebug() << "[ФАКТЫ] Показ факта #" << index;

    if (index < 0 || index >= factsData.size()) {
        qDebug() << "[ФАКТЫ][ОШИБКА] Индекс вне диапазона!";
        return;
    }

    // Полная очистка карточки
    QList<QWidget*> children = factCard->findChildren<QWidget*>();
    for (QWidget *child : children) {
        delete child;
    }

    if (factCard->layout()) {
        delete factCard->layout();
    }

    // Новый layout карточки
    QHBoxLayout *cardLayout = new QHBoxLayout(factCard);
    cardLayout->setContentsMargins(61, 44, 61, 44);
    cardLayout->setSpacing(50);

    // Картинка
    QLabel *imageLabel = new QLabel();
    imageLabel->setFixedSize(590, 722);

    QString imagePath = factsData[index].imagePath;
    QPixmap factImg;

    // Пробуем загрузить изображение из папки на диске
    if (!factImg.load(imagePath)) {
        qDebug() << "[ФАКТЫ][ОШИБКА КАРТИНКИ] Не удалось загрузить:" << imagePath;
        factImg.load(":/images/placeholder.png"); // fallback из ресурсов
    }

    QString fullPath = QDir::current().absoluteFilePath(imagePath);
    qDebug() << "[ФАКТЫ] Пытаюсь загрузить картинку по пути:" << fullPath;
    qDebug() << "[ФАКТЫ] Текущая рабочая директория:" << QDir::currentPath();

    imageLabel->setPixmap(factImg.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    cardLayout->addWidget(imageLabel);

    // Текст
    QVBoxLayout *textLayout = new QVBoxLayout();

    QLabel *titleLabel = new QLabel(factsData[index].title);
    titleLabel->setFont(QFont("Cinzel", 36, QFont::Bold));
    titleLabel->setStyleSheet("color: white;");
    titleLabel->setWordWrap(true);
    textLayout->addWidget(titleLabel);

    QLabel *descLabel = new QLabel(factsData[index].description);
    descLabel->setFont(QFont("Inter", 28));
    descLabel->setStyleSheet("color: white;");
    descLabel->setWordWrap(true);
    descLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    textLayout->addWidget(descLabel);

    cardLayout->addLayout(textLayout);
}

// ==================== // Загрузка блока с лайком и кнопкой возврата ====================
void UniverseForm::addLikeBlock(const QString &universeName) {
    QWidget *likeBlock = new QWidget();
    likeBlock->setFixedSize(1920, 207);
    likeBlock->setStyleSheet("background-color: black;");

    QHBoxLayout *layout = new QHBoxLayout(likeBlock);
    layout->setContentsMargins(60, 0, 60, 0);
    layout->setSpacing(50);
    layout->setAlignment(Qt::AlignVCenter);

    // Кнопка возврата в каталог
    QPushButton *backButton = new QPushButton();
    backButton->setFixedSize(150, 150);
    backButton->setStyleSheet(R"(
        QPushButton {
            border: none;
            border-radius: 15px;
        }
    )");
    QLabel *arrowIcon = new QLabel(backButton);
    arrowIcon->setPixmap(QPixmap(":/symbols/Arrow.svg").scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    arrowIcon->setFixedSize(129, 129);
    arrowIcon->move((129 - 80) / 2, (129 - 80) / 2);

    connect(backButton, &QPushButton::clicked, this, &UniverseForm::goToCatalog);

    // Текст
    QLabel *textLabel = new QLabel("Добавь понравившююся вселенную в любимое");
    textLabel->setFont(QFont("Cinzel", 45));
    textLabel->setStyleSheet("color: white;");
    textLabel->setAlignment(Qt::AlignCenter);

    // Кнопка лайка
    QPushButton *likeButton = new QPushButton();
    likeButton->setFixedSize(130, 114);
    likeButton->setIcon(QIcon(":/symbols/heart_white.svg"));
    likeButton->setIconSize(QSize(130, 114));
    likeButton->setStyleSheet("background: transparent; border: none;");
    likeButton->setCheckable(true);

    // Проверка наличия лайка
    QSqlQuery checkQuery;
    checkQuery.prepare(R"(
        SELECT COUNT(*) FROM Likes
        JOIN Universe ON Likes.id_universe = Universe.id_universe
        WHERE Likes.id_user = :id AND Universe.name = :name
    )");
    checkQuery.bindValue(":id", userId);
    checkQuery.bindValue(":name", universeName);

    if (checkQuery.exec() && checkQuery.next()) {
        if (checkQuery.value(0).toInt() > 0) {
            likeButton->setChecked(true);
            likeButton->setIcon(QIcon(":/symbols/heart_pink.svg"));
            likedUniverses.insert(universeName);
        }
    } else {
        qDebug() << "Ошибка проверки лайка:" << checkQuery.lastError().text();
    }

    connect(likeButton, &QPushButton::clicked, this, [=]() {
        QSqlQuery query;

        QSqlQuery idQuery;
        idQuery.prepare("SELECT id_universe FROM Universe WHERE name = :name");
        idQuery.bindValue(":name", universeName);
        if (!idQuery.exec() || !idQuery.next()) {
            qDebug() << "Не удалось получить id вселенной по имени:" << universeName;
            return;
        }
        int universeId = idQuery.value(0).toInt();

        if (likeButton->isChecked()) {
            likeButton->setIcon(QIcon(":/symbols/heart_pink.svg"));
            likedUniverses.insert(universeName);

            query.prepare("INSERT INTO Likes (id_user, id_universe) VALUES (:userId, :universeId)");
            query.bindValue(":userId", userId);
            query.bindValue(":universeId", universeId);
            if (!query.exec()) {
                qDebug() << "Ошибка при добавлении лайка:" << query.lastError().text();
            }
        } else {
            likeButton->setIcon(QIcon(":/symbols/heart_white.svg"));
            likedUniverses.remove(universeName);

            query.prepare("DELETE FROM Likes WHERE id_user = :userId AND id_universe = :universeId");
            query.bindValue(":userId", userId);
            query.bindValue(":universeId", universeId);
            if (!query.exec()) {
                qDebug() << "Ошибка при удалении лайка:" << query.lastError().text();
            }
        }
    });

    layout->addWidget(backButton);
    layout->addStretch();
    layout->addWidget(textLabel);
    layout->addStretch();
    layout->addWidget(likeButton);

    verticalLayout->addWidget(likeBlock);
}

void UniverseForm::goToCatalog() {
    CatalogForm *catalogForm = new CatalogForm(userId);
    catalogForm->show();
    this->close();
}

