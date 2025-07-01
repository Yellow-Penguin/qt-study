#include "../headers/point.h"

Point::Point(int x, int y, QColor color)
    : x(x), y(y), color(color) {}

Point::~Point() {}

void Point::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}