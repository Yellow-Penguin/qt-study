#ifndef POINT_H
#define POINT_H
#include <QPainter>

class Point {
public:
    Point(int x=0, int y=0, QColor color = Qt::black);
    virtual ~Point();
    virtual void draw(QPainter *painter) = 0;
    void setPos(int x, int y);
    QPoint getPos();
protected:
    int x, y;
    QColor color;
};
#endif //POINT_H
