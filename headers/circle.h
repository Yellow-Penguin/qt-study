#ifndef DOT_H
#define DOT_H

#include "point.h"

class Circle : public Point {
public:
    Circle(int x = 0, int y = 0, QColor color = Qt::black, int radius = 4);
    void draw(QPainter *painter) override;
private:
    int radius;
};

#endif // DOT_H