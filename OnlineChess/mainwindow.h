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
    QList<QPoint> dir[COLORNUM][TYPENUM+1] ;  //存储每个颜色和种类的棋子可以朝哪些方向走 TODO  注意兵需要特殊处理
    bool canWalkMore[TYPENUM+1] ;             //记录每个种类的棋子能否沿dir走多步 TODO
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
    int getChessmanIndOnPos(QPoint pos);
    QList<QPoint> getCandidatePos(Chessman man);
    void myMove(int ind, QPoint p);
    QList<QPoint> calcNextCandidate(Chessman man);
    bool outGridRange(QPoint pos);
private slots:
    void on_actionLoadInit_triggered();

    void on_actionLoadFromFile_triggered();

    void on_actionSaveChess_triggered();

private:
    Ui::MainWindow *ui;
    int gridSize, col, row, tagSize, circleR;
    QPoint leftUp;
    QColor groundColor[2];                      //两种格子颜色
    QColor circleColor;                         //圆环的颜色
    QList< Chessman> nowChessman;               //当前的棋子
    QString iniChessmanStr;                     //初始界面对应字符串
    QLabel *label[MAXM+5] ;                     //图像标签
    QPoint nowChoose;                           //我方当前选中的棋子
    QList<QPoint> myNextCandidate;              //我方当前选中的棋子接下来可以走的位置
};

#endif // MAINWINDOW_H
