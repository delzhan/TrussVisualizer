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

//Метод для рисования линий
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
    painter.drawText(textPos, label); 
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 2));


    // ДВУМЕРНАЯ ФЕРМА
    int startX = width()/4;
    int startY = height()/3;
    int size = 150; // Размер грани для каждого элемента двумерной фермы

    // Визуальзиация объектов двумерной фермы
    QPolygonF triangle1;
    triangle1 << QPointF(startX, startY + size)  // Левый нижний угол
              << QPointF(startX + size, startY + size)   // Левый верхний угол
              << QPointF(startX + size, startY);  // Правый верхний угол
    painter.drawPolygon(triangle1);

    QPolygonF triangle3; 
    triangle3 << QPointF(startX + size, startY + size * 1.5)  // Правый нижний угол
              << QPointF(startX, startY + size)   // Левый верхний угол
              << QPointF(startX + size, startY + size);  // Правый верхний угол
    painter.drawPolygon(triangle3);

    QPolygonF triangle4;
    triangle4 << QPointF(startX + size, startY + size * 1.5)  // Левый нижний угол
              << QPointF(startX + size * 2, startY + size)        // Правый верхний угол
              << QPointF(startX + size, startY + size);       // Левый верхний угол
    painter.drawPolygon(triangle4);

    QPolygonF triangle5;
    triangle5 << QPointF(startX + size * 3, startY + size * 1.5)  // Правый нижний угол
              << QPointF(startX + size * 2, startY + size)   // Левый верхний угол
              << QPointF(startX + size * 3, startY + size);  // Правый верхний угол
    painter.drawPolygon(triangle5);

    QPolygonF triangle6;
    triangle6 << QPointF(startX + size * 3, startY + size * 1.5)  // Левый нижний угол
              << QPointF(startX + size * 4, startY + size)        // Правый верхний угол
              << QPointF(startX + size * 3, startY + size);       // Левый верхний угол
    painter.drawPolygon(triangle6);

    QRectF square1(startX + size, startY, size, size);
    painter.drawRect(square1);
    QRectF square2(startX + 2*size, startY, size, size);
    painter.drawRect(square2);

    QPolygonF triangle2;
    triangle2 << QPointF(startX + 3*size, startY)          // Левый верхний угол
              << QPointF(startX + 3*size, startY + size)    // Левый нижний угол
              << QPointF(startX + 4*size, startY + size);   // Правый нижний угол
    painter.drawPolygon(triangle2);



    //ОСИ КООРДИНАТ
    QPointF center(60, height() - 60); // Задаём координаты начала
    
    // 1. Ось Y
    drawArrow(painter,
              center,
              center - QPointF(0, 80),
              10,
              "Y",
              QColor(215,215,4));

    // 2. Ось X 
    drawArrow(painter,
              center,
              center + QPointF(80, 0),
              10,
              "X",
              QColor(185,22,41));

    // 3. точка Z
    painter.setPen(QColor(0,93,0));
    painter.setBrush(QColor(0,93,0));
    painter.drawEllipse(center, 5, 5);
    painter.setPen(Qt::white); // Устанавливаем черный цвет для текста
    painter.drawText(center + QPointF(10, -10), "Z");


    //ГРАДИЕНТ
    // Создаём объект прямоугольника и задаём ему размер
    QRect gradientRect(width() - 110, height() - 260, 30, 200);
    // Вертикальная цветовая шкала
    QLinearGradient gradient(
        gradientRect.left(), gradientRect.top(), 
        gradientRect.left(), gradientRect.bottom() 
        );
    gradient.setColorAt(0, QColor(185,22,41));
    gradient.setColorAt(0.5, Qt::white);
    gradient.setColorAt(1, QColor(75,100,213));

    painter.setBrush(gradient);
    painter.setPen(QPen(Qt::gray, 1));
    painter.drawRect(gradientRect);

    // Настройки текста
    painter.setPen(Qt::white); 
    QFont font = painter.font();
    font.setPointSize(8); 
    painter.setFont(font);

    int textX = gradientRect.right() + 10;  // подписи смещены на 10px от правого края прямоугольника

    // Подписи к цветовой шкале
    painter.drawText(textX, gradientRect.top() + 5,    "3.3e-03");  
    painter.drawText(textX, gradientRect.center().y(), "0");   
    painter.drawText(textX, gradientRect.bottom() - 5, "-3.3e-03");    
    painter.drawText(textX, (gradientRect.top() + gradientRect.center().y()) / 2, "0.002"); 
    painter.drawText(textX, (gradientRect.center().y() + gradientRect.bottom()) / 2, "-0.002"); 
}


