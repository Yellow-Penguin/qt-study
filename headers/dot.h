#ifndef DOT_H
#define DOT_H

#include "point.h"

class Dot : public Point {
public:
    Dot(int x = 0, int y = 0, QColor color = Qt::black);
    void draw(QPainter *painter) override;
};

#endif // DOT_H