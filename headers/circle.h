#ifndef DOT_H
#define DOT_H

#include "point.h"

class Circle : public Point {
public:
    Circle(int x = 0, int y = 0, QColor color = Qt::black);
    void draw(QPainter *painter) override;
};

#endif // DOT_H