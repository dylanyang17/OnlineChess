#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QList>
#include <QTimer>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class Player;
class LocalPlayer;

struct  Chessman{
    //type: 1 king ; 2 queen ; 3 bishop ; 4 knight ; 5 rook ; 6 pawn
    //color: 0 white ; 1 black
    int type, color;
    QPoint pos;
    Chessman(int _type=0, int _color=0, QPoint _pos=QPoint(0,0)){
        type = _type; color = _color ; pos = _pos;
    }

    bool operator== (const Chessman &a) const{
        return a.type==type && a.color==color && a.pos==pos;
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
    const static int STATUSNOTRUN=0, STATUSWHITEWIN=1, STATUSBLACKWIN=2, STATUSTIE=3, STATUSMYTURN=4, STATUSOPPTURN=5 ;
    const static int TYPEKING=1, TYPEQUEEN=2, TYPEBISHOP=3, TYPEKNIGHT=4, TYPEROOK=5, TYPEPAWN=6;
    const static int PAWNINI=1, PAWNNORMAL=2, PAWNUPGRADE=3;
    const static int CHECKNEITHER=0, CHECKWHITE=1, CHECKBLACK=2, CHECKBOTH=3;
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
    void mousePressEvent(QMouseEvent *event);
    int getChessmanIndOnPos(QPoint pos);
    void moveChessman(int ind, QPoint p);
    QList<QPoint> getCandidatePos(Chessman man);
    bool outGridRange(QPoint pos);

    int nowColor ;                              //当前走子方的颜色
    QPoint nowChoose;                           //我方当前选中的棋子

    void setStatus(int status);
    void nextPlayer();
    int getPawnStatus(Chessman man);
    int isCheck();
    QList<QPoint> getCandidatePosWithCheck(Chessman man);
    int isStuck();
    int isCheckMate();
    void checkGameStatus();
    int isStaleMate();
public slots:
    void passOneSec();
private slots:
    void on_actionLoadInit_triggered();

    void on_actionLoadFromFile_triggered();

    void on_actionSaveChess_triggered();

    void on_actionPVP_triggered();

    void on_actionGiveIn_triggered();

private:
    Ui::MainWindow *ui;
    int gridSize, col, row, tagSize, circleR, nowStatus;
    QPoint upgradeLeftUp;                       //升变框的左上角
    QPoint leftUp;                              //棋盘左上角
    QColor groundColor[2];                      //两种格子颜色
    QColor circleColor;                         //圆环的颜色
    QList< Chessman> nowChessman;               //当前的棋子
    QString iniChessmanStr;                     //初始界面对应字符串
    QLabel *label[MAXM+5] ;                     //图像标签
    QLabel *upgradeLabel[4];                    //升变图像标签
    QList<QPoint> myNextCandidate;              //我方当前选中的棋子接下来可以走的位置
    LocalPlayer *localPlayer[2];                //两名本地玩家
    Player *player[2] ;                         //两名玩家
    QTimer *playTimer ;                         //着子的计时器
    int nowPlayerInd;                           //现在正在下棋的玩家索引
    int timeLim, timeRes;                       //时间限制和剩余
    int upgradingInd;                           //正在进行兵升变的棋子索引
   // OnlinePlayer *onlinePlayer;               //在线玩家
};

#endif // MAINWINDOW_H
