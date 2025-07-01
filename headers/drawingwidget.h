#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include "point.h"

class DrawingWidget : public QWidget {
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = nullptr);
    void setFigure(Point *f);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Point *figure = nullptr;
};

#endif // DRAWINGWIDGET_H