#include <QMenuBar>
#include <QMouseEvent>
#include <random>
#include <chrono>
#include "../headers/mainwindow.h"
#include "../headers/triangle.h"
#include "../headers/square.h"
#include "../headers/circle.h"

std::mt19937 MainWindow::gen{
    static_cast<unsigned>(
        std::chrono::system_clock::now().time_since_epoch().count()
    )
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), figure(nullptr), mouseHeld(false), mousePos(QPoint(0, 0))
{
    holdTimer.setInterval(16);
    connect(&holdTimer, &QTimer::timeout, this, &MainWindow::updateFigure);
    setMinimumSize(800, 600);
    createMenu();
    setMouseTracking(true);
    createCircle();
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
    for (Point* f : figures) {
        delete f;
    }
    figures.clear();
    figure = new Circle(400, 300, Qt::darkYellow, 20);
    update();
}

void MainWindow::createTriangle() {
    delete figure;
    for (Point* f : figures) {
        delete f;
    }
    figures.clear();
    figure = new Triangle(400, 300, Qt::darkRed, 40);
    update();
}

void MainWindow::createSquare() {
    delete figure;
    for (Point* f : figures) {
        delete f;
    }
    figures.clear();
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
    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (figure) {
        figure->draw(&painter);
    }
    if (!figures.empty()) {
        for (Point* f : figures) {
            if (f) {
                f->draw(&painter);
            }
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        for (Point* f : figures) {
            delete f;
        }
        figures.clear();
        mouseHeld = true;
        holdTimer.start();
        mousePos = event->pos();
    }
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    mousePos = event->pos();

    if (mouseHeld && figure == nullptr && figures.size() < 20) {
        std::uniform_int_distribution<int> dist(0, 2);
        std::uniform_int_distribution<int> hue(0, 359);
        std::uniform_int_distribution<int> sizeDist(20, 40);

        Point* newFigure = nullptr;
        QColor color = QColor::fromHsv(hue(gen), 255, 200);
        int size = sizeDist(gen);

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
        if (newFigure) {
            figures.push_back(newFigure);
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        mouseHeld = false;
        holdTimer.stop();
        for (Point* f : figures) {
            delete f;
        }
        figures.clear();
        update();
    }
}

void MainWindow::updateFigure() {
    QPoint currPos, prevPos;
    QPointF delta;
    if (!mouseHeld) {
        return;
    }
    if (figure) {
        currPos = figure->getPos();
        delta = (mousePos - currPos) * 0.1;
        figure->setPos(currPos.x() + delta.x(), currPos.y() + delta.y());
        update();
    }
    if (!figures.empty()) {
        for (int i = figures.size() - 1; i > 0; --i) {
            prevPos = figures[i - 1]->getPos();
            currPos = figures[i]->getPos();
            delta = (prevPos - currPos) * 0.3;
            figures[i]->setPos(currPos.x() + delta.x(), currPos.y() + delta.y());
        }
        currPos = figures[0]->getPos();
        delta = (mousePos - currPos) * 0.3;
        figures[0]->setPos(currPos.x() + delta.x(), currPos.y() + delta.y());
        update();
    }
}
