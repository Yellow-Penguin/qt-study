#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <vector>
#include "point.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createMenu();
    Point *figure;
    std::vector<Point*> figures;
    QTimer holdTimer;
    bool mouseHeld;
    QPoint mousePos;

private slots:
    void updateFigure();
    void createSquare();
    void createTriangle();
    void createCircle();
    void randomMode();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H