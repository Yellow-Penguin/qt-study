//
// Created by Stompred on 09/07/2025.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "point.h"


class Triangle : public Point {
public:
    Triangle(int x = 0, int y = 0, QColor color = Qt::black, int size = 4);
    void draw(QPainter *painter) override;
private:
    int figSize;
};



#endif //TRIANGLE_H
