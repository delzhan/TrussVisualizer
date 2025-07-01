#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected: //определяем виртуальный метод родитеского класса для отрисовки содержимого виджета
    void paintEvent(QPaintEvent *event);
    void drawArrow(QPainter &painter,
                   QPointF start,
                   QPointF end,
                   float arrowSize,
                   QString label,
                   QColor color);  // Добавляем параметр QColor
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
