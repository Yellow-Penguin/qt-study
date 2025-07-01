#include "../headers/drawingwidget.h"
#include <QPainter>

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(400, 400);
}

void DrawingWidget::setFigure(Point *f) {
    figure = f;
    update();
}

void DrawingWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    if (figure)
        figure->draw(&painter);
}