#include "../headers/square.h"
#include <QPainter>

Square::Square(int x, int y, QColor color, int size)
    : Point(x, y, color), figSize(size) {}

void Square::draw(QPainter *painter) {
    painter->setBrush(color);
    painter->drawRect(QRect(QPoint(x-figSize/2.0, y-figSize/2.0), QSize(figSize, figSize)));
}
