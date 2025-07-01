#include "widget.h"
#include "ui_widget.h"
#include <cmath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPalette pal = palette(); //выбрать цвет для фона нашего приложения
    pal.setColor(QPalette::Window, QColor( 81, 86, 109));
    setPalette(pal);
    setAutoFillBackground(true);
}

Widget::~Widget()
{
    delete ui;
}

//Метод для рисования
void Widget::drawArrow(QPainter &painter,
                       QPointF start,
                       QPointF end,
                       float arrowSize,
                       QString label,
                       QColor color)
{
    // Устанавливаем цвет для данной оси
    painter.setPen(QPen(color, 2)); // Толщина линии 2px
    painter.setBrush(color); // Цвет заливки стрелки

    // Рисуем линию оси
    painter.drawLine(start, end);

    // Рассчитываем треугольник стрелки
    QPointF diff = end - start;
    float angle = atan2(diff.y(), diff.x());

    QPointF arrowP1 = end - QPointF(
                          cos(angle + M_PI / 3) * arrowSize,
                          sin(angle + M_PI / 3) * arrowSize
                          );
    QPointF arrowP2 = end - QPointF(
                          cos(angle - M_PI / 3) * arrowSize,
                          sin(angle - M_PI / 3) * arrowSize
                          );

    // Рисуем стрелку
    painter.drawPolygon(QPolygonF() << end << arrowP1 << arrowP2);

    // Подпись оси
    painter.setPen(Qt::white);

    QPointF direction = end - start;
    float length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
    if (length > 0) {
        direction /= length; // Нормализация
    }

    // Рассчитываем позицию текста и рисуем его
    QPointF textPos = end + direction * 15;
    painter.drawText(textPos, label); // Эта строка была пропущена!
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 2));


    // ФЕРМА
    // Начальная точка (левая граница фермы)
    int startX = width()/4;
    int startY = height()/3;
    int size = 150; // Размер элементов

    // 1. Первый треугольник
    QPolygonF triangle1;
    triangle1 << QPointF(startX, startY + size)  // Левый нижний угол
              << QPointF(startX + size, startY + size)   // Левый верхний угол
              << QPointF(startX + size, startY);  // Правый верхний угол
    painter.drawPolygon(triangle1);

    QPolygonF triangle3; // нижний треугольник (влево)
    triangle3 << QPointF(startX + size, startY + size * 1.5)  // Правый нижний угол
              << QPointF(startX, startY + size)   // Левый верхний угол
              << QPointF(startX + size, startY + size);  // Правый верхний угол
    painter.drawPolygon(triangle3);

    // 3. Второй нижний треугольник (вправо)
    QPolygonF triangle4;
    triangle4 << QPointF(startX + size, startY + size * 1.5)  // Левый нижний угол
              << QPointF(startX + size * 2, startY + size)        // Правый верхний угол
              << QPointF(startX + size, startY + size);       // Левый верхний угол
    painter.drawPolygon(triangle4);

    // 4. Третий нижний треугольник (влево)
    QPolygonF triangle5;
    triangle5 << QPointF(startX + size * 3, startY + size * 1.5)  // Правый нижний угол
              << QPointF(startX + size * 2, startY + size)   // Левый верхний угол
              << QPointF(startX + size * 3, startY + size);  // Правый верхний угол
    painter.drawPolygon(triangle5);

    // 5. Четвертый нижний треугольник (вправо)
    QPolygonF triangle6;
    triangle6 << QPointF(startX + size * 3, startY + size * 1.5)  // Левый нижний угол
              << QPointF(startX + size * 4, startY + size)        // Правый верхний угол
              << QPointF(startX + size * 3, startY + size);       // Левый верхний угол
    painter.drawPolygon(triangle6);

    // 2. Первый квадрат
    QRectF square1(startX + size, startY, size, size);
    painter.drawRect(square1);

    // 3. Второй квадрат
    QRectF square2(startX + 2*size, startY, size, size);
    painter.drawRect(square2);

    // 4. Зеркальный треугольник
    QPolygonF triangle2;
    triangle2 << QPointF(startX + 3*size, startY)          // Левый верхний угол
              << QPointF(startX + 3*size, startY + size)    // Левый нижний угол
              << QPointF(startX + 4*size, startY + size);   // Правый нижний угол
    painter.drawPolygon(triangle2);



    //ОСИ КООРДИНАТ
    // Центр координат
    QPointF center(60, height() - 60);

    // 1. Зелёная точка с ЧЕРНОЙ подписью "Z"
    painter.setPen(QColor(0,93,0));
    painter.setBrush(QColor(0,93,0));
    painter.drawEllipse(center, 5, 5);
    painter.setPen(Qt::white); // Устанавливаем черный цвет для текста
    painter.drawText(center + QPointF(10, -10), "Z");

    // 2. Ось Y (жёлтая)
    drawArrow(painter,
              center,
              center - QPointF(0, 80),
              10,
              "Y",
              QColor(120,121,27));

    // 3. Ось X (красная)
    drawArrow(painter,
              center,
              center + QPointF(80, 0),
              10,
              "X",
              QColor(73, 9, 16));



    //ГРАДИЕНТ
    // Прямоугольник с градиентом
    QRect gradientRect(width() - 110, height() - 260, 30, 200);
    // Вертикальный градиент (меняем x2,y2 на вертикальное направление)
    QLinearGradient gradient(
        gradientRect.left(), gradientRect.top(),    // Начальная точка (верх)
        gradientRect.left(), gradientRect.bottom() // Конечная точка (низ)
        );
    gradient.setColorAt(0, QColor(24, 36, 77));
    gradient.setColorAt(0.5, Qt::white);
    gradient.setColorAt(1, QColor(73, 9, 16));

    painter.setBrush(gradient);
    painter.setPen(QPen(Qt::gray, 1));
    painter.drawRect(gradientRect);

    // Настройки текста
    painter.setPen(Qt::white); // Цвет текста
    QFont font = painter.font();
    font.setPointSize(8); // Размер шрифта
    painter.setFont(font);

    // Положение текста (справа от прямоугольника)
    int textX = gradientRect.right() + 10;  // 10px от правого края прямоугольника

    // Основные метки
    painter.drawText(textX, gradientRect.top() + 5,    "3.3e-03");  // Верх
    painter.drawText(textX, gradientRect.center().y(), "0");   // Центр
    painter.drawText(textX, gradientRect.bottom() - 5, "-3.3e-03");    // Низ

    // Промежуточные метки
    painter.drawText(textX,
                     (gradientRect.top() + gradientRect.center().y()) / 2,
                     "0.002");  // Между 100% и 50%

    painter.drawText(textX,
                     (gradientRect.center().y() + gradientRect.bottom()) / 2,
                     "-0.002");  // Между 50% и 0%


}

