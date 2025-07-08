#include "../headers/circle.h"
#include <QPainter>

Circle::Circle(int x, int y, QColor color)
    : Point(x, y, color) {}

void Circle::draw(QPainter *painter) {
    painter->setBrush(color);
    painter->drawEllipse(QPoint(x, y), 6, 6);
}