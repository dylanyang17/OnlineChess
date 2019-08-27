#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QList>
#include <QLabel>

namespace Ui {
class MainWindow;
}

struct  Chessman{
    //type: 1 king ; 2 queen ; 3 bishop ; 4 knight ; 5 rook ; 6 pawn
    //color: 0 white ; 1 black
    int type, color;
    QPoint pos;
     Chessman(int _type=0, int _color=0, QPoint _pos=QPoint(0,0)){
        type = _type; color = _color ; pos = _pos;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool debugOn ;
    const static int TYPENUM=6 ;
    const static int COLORNUM=2 ;
    const static int MAXM=32; //最大棋子数
    const static int FLAGNOTRUN=0, FLAGWIN=1, FLAGLOSE=2, FLAGTIE=3, FLAGMYTURN=4, FLAGOPPTURN=5 ;
    void paintEvent(QPaintEvent *event);
    QPoint getPoint(int x, int y);
    int char2ind(QChar s);
    QChar ind2char(int a);
    int getGroundType(int x, int y);
    int type2ind(QString s);
    QString ind2type(int a);
    QList< Chessman> str2chessman(QString s, int color);
    QPoint str2pos(QString s);
    QString pos2str(QPoint pos);
    QString getChessStr();
    QString chessman2str(QList< Chessman> &list);
    void loadChessStr(QString s);
    void debug(QString s);
    bool isRunning() ;

    int gameFlag, nowColor ;
    void mousePressEvent(QMouseEvent *event);
    Chessman chessmanOnPos(QPoint pos);
private slots:
    void on_actionLoadInit_triggered();

private:
    Ui::MainWindow *ui;
    int gridSize, col, row, tagSize;
    QPoint leftUp;
    QColor groundColor[2];                      //两种格子颜色
    QList< Chessman> nowChessman;               //当前的棋子
    QString iniChessmanStr;                     //初始界面对应字符串
    QLabel *label[MAXM+5] ;                     //图像标签
    QPoint nowChoose;
};

#endif // MAINWINDOW_H
