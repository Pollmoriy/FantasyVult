#include "universeform.h"
#include "ui_universeform.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include <QSqlDatabase>

UniverseForm::UniverseForm(QWidget *parent)
    : QWidget(parent)
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

void UniverseForm::setData(int userId, int universeId)
{
    this->userId = userId;
    this->universeId = universeId;

    qDebug() << "UniverseForm::setData called";
    qDebug() << "Received userId:" << userId;
    qDebug() << "Received universeId:" << universeId;

    loadFirstBlock();
    loadMainTextBlock();
    loadWorldGeographyBlock();
    loadPlacesSliderBlock();
}

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
