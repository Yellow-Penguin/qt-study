#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include "../headers/mainwindow.h"
#include "../headers/circle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), figure(nullptr), mousePos(QPoint(0, 0))
{
    holdTimer.setInterval(16);
    connect(&holdTimer, &QTimer::timeout, this, &MainWindow::updateFigure);
    setMinimumSize(800, 600);
    createMenu();
    setMouseTracking(true);
}

MainWindow::~MainWindow() {
    delete figure;
}

void MainWindow::createMenu() {
    QMenu *shapeMenu = menuBar()->addMenu(tr("Shape"));
    QAction *circleAction = shapeMenu->addAction(tr("Circle"));
    QAction *triangleAction = shapeMenu->addAction(tr("Triangle"));
    QAction *squareAction = shapeMenu->addAction(tr("Square"));

    connect(circleAction, &QAction::triggered, this, &MainWindow::createCircle);
    connect(triangleAction, &QAction::triggered, this, &MainWindow::createTriangle);
    connect(squareAction, &QAction::triggered, this, &MainWindow::createSquare);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (figure) {
        figure->draw(&painter);
    }
}


void MainWindow::createCircle() {
    delete figure;
    figure = new Circle(100, 100, Qt::black);
    update();
}

void MainWindow::createTriangle() {
    delete figure;
    update();
}

void MainWindow::createSquare() {
    delete figure;
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        mouseHeld = true;
        holdTimer.start();
        mousePos = event->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    mousePos = event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        mouseHeld = false;
        holdTimer.stop();
    }
}

void MainWindow::updateFigure() {
    if (!mouseHeld) {
        return;
    }
    QPoint figurePos = figure->getPos();
    QPointF delta = (mousePos - figurePos) * 0.1;
    figure->setPos(figurePos.x() + delta.x(), figurePos.y() + delta.y());
    update();
}
