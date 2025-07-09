#include <QMenuBar>
#include <QMouseEvent>
#include <random>
#include "../headers/mainwindow.h"
#include "../headers/triangle.h"
#include "../headers/square.h"
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
    for (Point* f : figures) {
        delete f;
    }
}

void MainWindow::createMenu() {
    QMenu *shapeMenu = menuBar()->addMenu(tr("Shape"));
    QAction *circleAction = shapeMenu->addAction(tr("Circle"));
    QAction *triangleAction = shapeMenu->addAction(tr("Triangle"));
    QAction *squareAction = shapeMenu->addAction(tr("Square"));
    QAction *randomAction = shapeMenu->addAction(tr("Random"));

    connect(circleAction, &QAction::triggered, this, &MainWindow::createCircle);
    connect(triangleAction, &QAction::triggered, this, &MainWindow::createTriangle);
    connect(squareAction, &QAction::triggered, this, &MainWindow::createSquare);
    connect(randomAction, &QAction::triggered, this, &MainWindow::randomMode);
}

void MainWindow::createCircle() {
    delete figure;
    figure = new Circle(400, 300, Qt::darkYellow, 20);
    update();
}

void MainWindow::createTriangle() {
    delete figure;
    figure = new Triangle(400, 300, Qt::darkRed, 40);
    update();
}

void MainWindow::createSquare() {
    delete figure;
    figure = new Square(400, 300, Qt::darkGreen, 40);
    update();
}

void MainWindow::randomMode() {
    delete figure;
    figure = nullptr;
    for (Point* f : figures) {
        delete f;
    }
    figures.clear();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (figure) {
        figure->draw(&painter);
    }
    if (!figures.empty()) {
        for (Point* f : figures) {
            f->draw(&painter);
        }
    }
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

    if (mouseHeld && figure == nullptr && figures.size() < 20) {
        static std::mt19937 gen{std::random_device{}()};
        std::uniform_int_distribution<int> dist(0, 2);

        Point* newFigure = nullptr;
        QColor color = QColor::fromHsv(rand() % 360, 255, 200);
        int size = 20 + rand() % 20;

        switch (dist(gen)) {
            case 0:
                newFigure = new Circle(mousePos.x(), mousePos.y(), color, size);
                break;
            case 1:
                newFigure = new Triangle(mousePos.x(), mousePos.y(), color, size);
                break;
            case 2:
                newFigure = new Square(mousePos.x(), mousePos.y(), color, size);
                break;
        }

        figures.push_back(newFigure);
    }
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
    if (figure) {
        QPoint figurePos = figure->getPos();
        QPointF delta = (mousePos - figurePos) * 0.1;
        figure->setPos(figurePos.x() + delta.x(), figurePos.y() + delta.y());
        update();
    }
    if (!figures.empty()) {
        for (int i = figures.size() - 1; i > 0; --i) {
            QPoint prevPos = figures[i - 1]->getPos();
            figures[i]->setPos(prevPos.x(), prevPos.y());
        }

        figures[0]->setPos(mousePos.x(), mousePos.y());
        update();
    }
}
