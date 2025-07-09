#include "../headers/circle.h"
#include <QPainter>

Circle::Circle(int x, int y, QColor color, int radius)
    : Point(x, y, color), radius(radius) {}

void Circle::draw(QPainter *painter) {
    painter->setBrush(color);
    painter->drawEllipse(QPoint(x, y), radius, radius);
}