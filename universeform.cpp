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
        titleLabel->setGeometry(0, 960, 1920, 120);  // 120 пикселей от низа блока

        // Добавляем блок в вертикальный layout
        verticalLayout->addWidget(block);
    } else {
        qDebug() << "Блок main_image не найден для universeId =" << universeId;
    }
}




