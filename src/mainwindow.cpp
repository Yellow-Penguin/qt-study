#include "../headers/mainwindow.h"
#include "../headers/drawingwidget.h"
#include "../headers/dot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    figure = new Dot(100, 100, Qt::red);

    canvas = new DrawingWidget(this);
    canvas->setFigure(figure);

    setCentralWidget(canvas);
    setWindowTitle("Draw a Point");
    resize(400, 400);
}

MainWindow::~MainWindow() {
    delete figure;
}