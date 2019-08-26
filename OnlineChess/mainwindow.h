#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);
    QPoint getPoint(int x, int y);
private:
    Ui::MainWindow *ui;
    int gridSize, col, row;
    QPoint leftUp ;
};

#endif // MAINWINDOW_H
