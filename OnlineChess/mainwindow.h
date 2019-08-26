#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QList>

namespace Ui {
class MainWindow;
}

struct chessman{
    //type: 1 king ; 2 queen ; 3 bishop ; 4 knight ; 5 rook ; 6 pawn
    //color: 0 white ; 1 black
    int type, color;
    QPoint pos;
    chessman(int _type=0, int _color=0, QPoint _pos=QPoint(0,0)){
        type = _type; color = _color ; pos = _pos;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);
    QPoint getPoint(int x, int y);
    int char2ind(QChar s);
    QChar ind2char(int a);
    int getGroundType(int x, int y);
    int type2ind(QString s);
    QString ind2type(int a);
private:
    Ui::MainWindow *ui;
    int gridSize, col, row, tagSize;
    QPoint leftUp ;
    QColor groundColor[2];
};

#endif // MAINWINDOW_H
