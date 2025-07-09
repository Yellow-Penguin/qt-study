//
// Created by Stompred on 09/07/2025.
//

#include "../headers/triangle.h"

Triangle::Triangle(int x, int y, QColor color, int size)
    : Point(x, y, color), figSize(size) {}

void Triangle::draw(QPainter *painter) {
    painter->setBrush(color);
    QPolygon polygon;
    polygon << QPoint(x, y - figSize * 0.433)
            << QPoint(x + figSize * 0.433, y + figSize * 0.433)
            << QPoint(x - figSize * 0.433, y + figSize * 0.433);
    painter->drawPolygon(polygon);
}