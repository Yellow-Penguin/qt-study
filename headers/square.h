#ifndef SQUARE_H
#define SQUARE_H

#include "point.h"
class Square : public Point {
public:
    Square(int x = 0, int y = 0, QColor color = Qt::black, int size = 2);
    void draw(QPainter *painter) override;
private:
    int figSize;
};

#endif //SQUARE_H
