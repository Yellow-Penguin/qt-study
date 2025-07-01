#include "../headers/dot.h"
#include <QPainter>

Dot::Dot(int x, int y, QColor color)
    : Point(x, y, color) {}

void Dot::draw(QPainter *painter) {
    painter->setBrush(color);
    painter->drawEllipse(QPoint(x, y), 3, 3);
}