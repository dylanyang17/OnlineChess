#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include "localplayer.h"
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QColor>
#include <QMessageBox>
#include <QFileDialog>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    debugOn=true;
    timeLim=timeRes=30; //30秒时间限制
    gridSize=53;
    tagSize=gridSize/8 ;
    circleR=gridSize/3;
    col=row=8;
    leftUp = QPoint(50,100) ;
    upgradeLeftUp=getPoint(3,6) ;
    groundColor[0] = QColor(240,218,181) ;
    groundColor[1] = QColor(181,135,99) ;
    circleColor = QColor(99,181,176);
    castlingColor = QColor(219,54,62) ;
    iniChessmanStr = QString("white\nking 1 e1\nqueen 1 d1\nbishop 2 c1 f1\nknight 2 b1 g1\nrook 2 a1 h1\npawn 8 a2 b2 c2 d2 e2 f2 g2 h2\nblack\nking 1 e8\nqueen 1 d8\nbishop 2 c8 f8\nknight 2 b8 g8\nrook 2 a8 h8\npawn 8 a7 b7 c7 d7 e7 f7 g7 h7") ;
    on_actionLoadInit_triggered();
    upgradingInd=-1;
    for(int i=0;i<MAXM;++i) label[i] = new QLabel(this) ;
    for(int i=0;i<4;++i) upgradeLabel[i] = new QLabel(this);
    nowChoose = QPoint(-1,-1);
    memset(canWalkMore,0,sizeof(canWalkMore)) ;
    canWalkMore[2]=canWalkMore[3]=canWalkMore[5]=true;
    ui->lcdNumber->setDigitCount(2);
    ui->lcdNumber->display(timeRes) ;
    playTimer = new QTimer(this) ;
    connect(playTimer , SIGNAL(timeout()), this, SLOT(passOneSec())) ;
    setStatus(STATUSNOTRUN) ;
    localPlayer[0] = new LocalPlayer(this, 0) ;
    localPlayer[1] = new LocalPlayer(this, 1) ;

    //king
    dir[0][1].append(QPoint(-1,0)) ;
    dir[0][1].append(QPoint(1,0)) ;
    dir[0][1].append(QPoint(0,-1)) ;
    dir[0][1].append(QPoint(0,1)) ;
    dir[0][1].append(QPoint(-1,-1)) ;
    dir[0][1].append(QPoint(1,1)) ;
    dir[0][1].append(QPoint(-1,1)) ;
    dir[0][1].append(QPoint(1,-1)) ;

    //queen
    dir[0][2] = dir[0][1] ;

    //bishop
    dir[0][3].append(QPoint(-1,-1)) ;
    dir[0][3].append(QPoint(1,1)) ;
    dir[0][3].append(QPoint(-1,1)) ;
    dir[0][3].append(QPoint(1,-1)) ;

    //knight
    dir[0][4].append(QPoint(-2,1));
    dir[0][4].append(QPoint(2,-1));
    dir[0][4].append(QPoint(-1,2));
    dir[0][4].append(QPoint(1,-2));
    dir[0][4].append(QPoint(2,1));
    dir[0][4].append(QPoint(-2,-1));
    dir[0][4].append(QPoint(1,2));
    dir[0][4].append(QPoint(-1,-2));

    //rook
    dir[0][5].append(QPoint(-1,0)) ;
    dir[0][5].append(QPoint(1,0)) ;
    dir[0][5].append(QPoint(0,-1)) ;
    dir[0][5].append(QPoint(0,1)) ;

    //pawn
    dir[0][6].append(QPoint(0,1)) ;

    //黑方的棋子能走的dir (实际上只有pawn同白方有区别)
    for(int j=1;j<=TYPENUM;++j){
        for(int k=0;k<dir[0][j].length();++k){
            QPoint p = dir[0][j].at(k) ;
            p.setY(-p.y());
            dir[1][j].append(p) ;
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this) ;
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    //网格及边线
    for(int i=1;i<=col;++i){
        for(int j=1;j<=row;++j){
            QPoint p1=getPoint(i,j+1), p2=getPoint(i+1,j) ;
            painter.setPen(Qt::NoPen);
            painter.setBrush(QBrush(groundColor[getGroundType(i,j)], Qt::SolidPattern)) ;
            painter.drawRect(QRect(p1,p2)) ;
        }
    }
    painter.setPen(Qt::SolidLine);
    for(int i=1;i<=col;++i) {
        painter.setPen(Qt::black);
        painter.drawLine(getPoint(i, 1), getPoint(i+1, 1)) ;
        painter.drawLine(getPoint(i, row+1), getPoint(i+1, row+1)) ;
        QPoint tmp = getPoint(i+1, 1) ;
        painter.setPen(groundColor[getGroundType(i,1)^1]);
        QFont font = painter.font();
        font.setPointSize(tagSize) ;
        painter.drawText(tmp.x()-tagSize-3, tmp.y()-3, ind2char(i)) ;
    }
    for(int j=1;j<=row;++j) {
        painter.setPen(Qt::black);
        painter.drawLine(getPoint(1, j), getPoint(1, j+1)) ;
        painter.drawLine(getPoint(col+1, j), getPoint(col+1, j+1)) ;
        QPoint tmp = getPoint(1, j+1) ;
        painter.setPen(groundColor[getGroundType(1,j)^1]);
        QFont font = painter.font();
        font.setPointSize(tagSize) ;
        painter.drawText(tmp.x()+3, tmp.y()+tagSize+6, QString::number(j)) ;
    }
    QPoint tmp = getPoint(col+1,1);
    this->setMinimumSize(tmp.x()+50, tmp.y()+50);
    this->setMaximumSize(tmp.x()+50, tmp.y()+50);

    //棋子图片
    //debug(QString("nowChessman.length(): %1").arg(nowChessman.length())) ;
    for(int i=0;i<nowChessman.length();++i){
        Chessman man = nowChessman.at(i) ;
        QString path = ":/new/prefix1/res/" + QString(man.color ? "black_" : "white_") + ind2type(man.type) + ".png";
        QPoint pos = man.pos ;
       // debug("path:"+path+QString("   pos:(%1,%2)").arg(pos.x()).arg(pos.y())) ;
        label[i]->setPixmap(QPixmap(path)) ;
        label[i]->setGeometry(QRect(getPoint(pos.x(),pos.y()+1), getPoint(pos.x()+1,pos.y()))) ;
        label[i]->setScaledContents(true) ;
        label[i]->lower();
        label[i]->show();
    }
    for(int i=nowChessman.length();i<MAXM;++i)
        label[i]->hide();

    //当前候选位置
    for(int i=0;i<myNextCandidate.length();++i){
        QPoint p=myNextCandidate.at(i) ;
        QPen pen = painter.pen();
        if(nowChessman.at(getChessmanIndOnPos(nowChoose)).type==TYPEKING
                && std::abs(nowChoose.x()-p.x())>=2){
            //王车易位
            pen.setColor(castlingColor) ;
        }
        else pen.setColor(circleColor);
        pen.setWidth(circleR/5) ;
        painter.setPen(pen) ;
        int margin=(gridSize-2*circleR)/2;
        painter.drawArc(QRect(getPoint(p.x(),p.y()+1)+QPoint(margin,margin),getPoint(p.x()+1,p.y())+QPoint(-margin,-margin)),0,360*16) ;
    }

    //升变
    if(upgradingInd!=-1){
        for(int i=0;i<nowChessman.length();++i){
            QPoint pos = nowChessman.at(i).pos ;
            if(pos.x()>=3 && pos.x()<=6 && pos.y()>=4 && pos.y()<=5)
                label[i]->hide();
        }
        int color = nowChessman.at(upgradingInd).color;
        QPen pen = painter.pen();
        pen.setColor(groundColor[1]) ;
        pen.setWidth(3);
        painter.setPen(pen);
        painter.setBrush(QBrush(groundColor[0],Qt::SolidPattern));
        painter.drawRoundedRect(QRect(upgradeLeftUp,upgradeLeftUp+QPoint(4*gridSize,2*gridSize)),
                                15,15) ;
        for(int i=2;i<=5;++i){
            QString path = ":/new/prefix1/res/" + QString(color ? "black_" : "white_") + ind2type(i) + ".png";
            QPoint pos = getPoint(3+i-2,6) + QPoint(0,gridSize/2) ;
            upgradeLabel[i-2]->setPixmap(QPixmap(path)) ;
            upgradeLabel[i-2]->setGeometry(QRect(pos, pos+QPoint(gridSize,gridSize))) ;
            upgradeLabel[i-2]->setScaledContents(true) ;
            upgradeLabel[i-2]->lower();
            upgradeLabel[i-2]->show();
            QPen pen = painter.pen();
            pen.setColor(groundColor[1]) ;
            pen.setWidth(1);
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            QPoint margin=QPoint(3,3);
            painter.drawRoundedRect(QRect(pos+margin, pos+QPoint(gridSize,gridSize)-margin),10,10) ;
        }
    } else{
        for(int i=0;i<4;++i)
            upgradeLabel[i]->hide();
    }
}

void MainWindow::moveChessman(int ind, QPoint p){
    //移动操作，将索引为ind的棋子移动到p位置，注意可能只是作为测试移动而被其它函数调用
    int tmpInd = getChessmanIndOnPos(p) ;
    Chessman man = nowChessman.at(ind) ;
    man.pos = p ;
    nowChessman.replace(ind, man);
    if(tmpInd!=-1){ //注意删除后会导致索引改变
        nowChessman.removeAt(tmpInd) ;
    }
}

bool MainWindow::outGridRange(QPoint pos){
    return pos.x()<1||pos.y()<1||pos.x()>col||pos.y()>row;
}

int MainWindow::getPawnStatus(Chessman man){
    //分为在起始位置、普通位置以及升变位置三种情况
    int y = man.pos.y();
    if(man.color==1) y=col+1-y; //统一黑白
    if(y==2) return PAWNINI ;
    else if(y==8) return PAWNUPGRADE;
    else return PAWNNORMAL;
}

QList<QPoint> MainWindow::getCandidatePos(Chessman man){
    //计算棋子下一步能走的所有位置，注意这里是不考虑将军的情况下合法能走到的位置
    QList<QPoint> list;
    int type = man.type, color = man.color;
    QPoint pos = man.pos ;
    for(int i=0;i<dir[color][type].length();++i){
        QPoint d = dir[color][type].at(i) ;
        int up = (canWalkMore[type] ? 7 : 1) ;
        for(int j=1;j<=up;++j){
            QPoint newPos = pos + d*j ;
            if(outGridRange(newPos)) break ;
            int tmpInd = getChessmanIndOnPos(newPos) ;
            if(tmpInd==-1 || nowChessman.at(tmpInd).color!=color){ //可移动
                if(type==TYPEPAWN && tmpInd!=-1) //pawn不可直接吃
                    continue;
                list.append(newPos) ;
            }
            if(tmpInd!=-1) break ; //被遮挡
        }
    }
    if(type==TYPEPAWN){ //特殊处理pawn
        QPoint d = dir[color][type].at(0) , newPos = pos+2*d;
        if(getPawnStatus(man)==PAWNINI && getChessmanIndOnPos(pos+d)==-1 && getChessmanIndOnPos(newPos)==-1 && !outGridRange(newPos)){
            list.append(newPos);
        }
        //吃子
        newPos = pos+d+QPoint(1,0);
        if(getChessmanIndOnPos(newPos)!=-1 && nowChessman.at(getChessmanIndOnPos(newPos)).color!=color){
            list.append(newPos);
        }
        newPos = pos+d+QPoint(-1,0);
        if(getChessmanIndOnPos(newPos)!=-1 && nowChessman.at(getChessmanIndOnPos(newPos)).color!=color){
            list.append(newPos);
        }
    }

    return list;
}

QList<QPoint> MainWindow::getCandidatePosWithCheck(Chessman man){
    //计算棋子下一步能走的所有位置，考虑不能被将军
    QList<QPoint> list = getCandidatePos(man) ;
    int ind = nowChessman.indexOf(man) ;
    QList<QPoint>::iterator it = list.begin();
    while(it!=list.end()){
        QPoint newPos = *it;
        QList<Chessman> tmpNowChessman = nowChessman; //备份nowChessman
        moveChessman(ind, newPos) ;
        int ck = isCheck() ;
        nowChessman = tmpNowChessman ;
        if(ck & (man.color ? CHECKBLACK : CHECKWHITE)){
            it = list.erase(it) ;
        } else {
            ++ it ;
        }
    }

    //王车易位
    //TODO
    if(man.type==TYPEKING){
        int y = (man.color ? 8 : 1);
        if(man.pos == QPoint(5,y) && !(isCheck() & (man.color ? CHECKBLACK : CHECKWHITE))){
            bool canLongCastling=false, canShortCastling=false;
            Chessman rook1, rook2 ;
            for(int i=0;i<nowChessman.length();++i){
                Chessman rook = nowChessman.at(i);
                if(rook.color==man.color && rook.type==TYPEROOK){
                    if(rook.pos == QPoint(1,y)){
                        canLongCastling=true;
                        rook1 = rook;
                    }
                    else if(rook.pos == QPoint(8,y)){
                        canShortCastling=true;
                        rook2 = rook;
                    }
                }
            }
            if(getChessmanIndOnPos(QPoint(4,y))!=-1 || getChessmanIndOnPos(QPoint(3,y))!=-1) canLongCastling=false;
            if(getChessmanIndOnPos(QPoint(6,y))!=-1 || getChessmanIndOnPos(QPoint(7,y))!=-1) canShortCastling=false;
            if(canLongCastling){
                QList<Chessman> tmpNowChessman = nowChessman ;
                moveChessman(ind, QPoint(4,y)) ;
                if(isCheck() & (man.color ? CHECKBLACK : CHECKWHITE)){
                    canLongCastling=false;
                }
                moveChessman(ind, QPoint(3,y)) ;
                moveChessman(nowChessman.indexOf(rook1), QPoint(4,y)) ;
                if(isCheck() & (man.color ? CHECKBLACK : CHECKWHITE)){
                    canLongCastling=false;
                }
                nowChessman = tmpNowChessman ;
                if(canLongCastling){
                    list.append(QPoint(3,y));
                }
            }

            if(canShortCastling){
                QList<Chessman> tmpNowChessman = nowChessman ;
                moveChessman(ind, QPoint(6,y)) ;
                if(isCheck() & (man.color ? CHECKBLACK : CHECKWHITE)){
                    canShortCastling=false;
                }
                moveChessman(ind, QPoint(7,y)) ;
                moveChessman(nowChessman.indexOf(rook2), QPoint(6,y)) ;
                if(isCheck() & (man.color ? CHECKBLACK : CHECKWHITE)){
                    canShortCastling=false;
                }
                nowChessman = tmpNowChessman ;
                if(canShortCastling){
                    list.append(QPoint(7,y));
                }
            }
        }
    }

    return list;
}

void MainWindow::passOneSec(){
    if(timeRes>0){
        if(--timeRes == 0 && nowStatus==STATUSMYTURN){
            on_actionGiveIn_triggered();
        }
        ui->lcdNumber->display(timeRes) ;
    }
}

void MainWindow::setStatus(int status){
    //棋盘状态改变
    nowStatus = status;
    nowChoose = QPoint(-1,-1);
    myNextCandidate.clear();
    timeRes = timeLim ;
    ui->lcdNumber->display(timeRes) ;
    playTimer->stop() ;
    upgradingInd = -1;
    if(isRunning()){
        ui->actionLoadInit->setEnabled(false);
        ui->actionLoadFromFile->setEnabled(false);
        ui->actionPVP->setEnabled(false);
        ui->actionOnline->setEnabled(false);
        playTimer->start(1000) ;
    } else{
        ui->actionLoadInit->setEnabled(true);
        ui->actionLoadFromFile->setEnabled(true);
        ui->actionPVP->setEnabled(true);
        ui->actionOnline->setEnabled(true);
    }
    if(status==STATUSMYTURN){
        ui->actionGiveIn->setEnabled(true);
    } else{
        ui->actionGiveIn->setEnabled(false);
    }
    if(status==STATUSWHITEWIN){
        QMessageBox::information(this, "游戏结束", "白方胜利!") ;
    } else if(status==STATUSBLACKWIN){
        QMessageBox::information(this, "游戏结束", "黑方胜利!") ;
    } else if(status==STATUSTIE){
        QMessageBox::information(this, "游戏结束", "和棋!") ;
    }
    update() ;
}

int MainWindow::isCheck(){
    //判断哪个颜色被将军，0为没有被将军，1为白色被将军，2为黑色被将军，3为同时被将军，用常变量表示
    int ret=0;
    QPoint kingPos[2];
    for(int i=0;i<nowChessman.length();++i){
        Chessman man = nowChessman.at(i) ;
        if(man.type==TYPEKING) kingPos[man.color]=man.pos;
    }
    for(int i=0;i<nowChessman.length();++i){
        //枚举走哪个棋子
        Chessman man = nowChessman.at(i) ;
        QList<QPoint> list = getCandidatePos(man) ;
        if(list.indexOf(kingPos[man.color^1])!=-1){
            ret |= (man.color ? CHECKWHITE : CHECKBLACK) ;
        }
    }
    return ret;
}

int MainWindow::isStuck(){
    //判断哪个颜色无法走子，0为没有，1为白色，2为黑色，3为两者用和isCheck一样的常变量进行表示
    int ret=3 ;
    for(int i=0;i<nowChessman.length();++i){
        Chessman man = nowChessman.at(i) ;
        QList<QPoint> list = getCandidatePosWithCheck(man) ;
        if(list.length()>0) {
            ret &= (man.color ? (~CHECKBLACK) : (~CHECKWHITE)) ;
        }
    }
    return ret;
}

int MainWindow::isCheckMate(){
    //判断哪个颜色被将杀，0为没有被将杀，1为白色被将杀，2为黑色被将杀，用和isCheck一样的常变量表示
    return (isCheck()&isStuck()) ;    //正被将军且无法移动的一方被将杀
}

int MainWindow::isStaleMate(){
    //判断哪个颜色被逼和，0为没有被逼和，1为白色被逼和，2为黑色被逼和，用和isCheck一样的常变量表示
    return ((~isCheck())&isStuck()) ; //未被将军且无法移动的一方被逼和
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        int x=event->x(), y=event->y() ;
        if(upgradingInd!=-1){
            //兵升变
            QPoint p = upgradeLeftUp + QPoint(0, gridSize/2) ;
            x=static_cast<int>(std::floor(static_cast<double>(x-p.x())/gridSize)+1);
            y=static_cast<int>(std::floor(static_cast<double>(y-p.y())/gridSize)+1);
            debug(QString("Press: (%1,%2)").arg(x).arg(y)) ;
            if(y==1 && x>=1 && x<=4){
                int type=x+1 ;
                Chessman man = nowChessman.at(upgradingInd) ;
                man.type = type;
                nowChessman.replace(upgradingInd, man) ;
                upgradingInd = -1;
                update();
                nextPlayer();
            }
            return ;
        }
        x=static_cast<int>(std::floor(static_cast<double>(x-leftUp.x())/gridSize)+1);
        y=static_cast<int>(std::floor(static_cast<double>(y-leftUp.y())/gridSize)+1);
        y=row+1-y;
        debug(QString("Press: (%1,%2)").arg(x).arg(y)) ;
        if(x<1||y<1||x>col||y>row)  return ;
        if(nowStatus==STATUSMYTURN){
            if(nowChoose == QPoint(x,y)){
                //选中了上次选中的棋子
                nowChoose = QPoint(-1,-1);
            } else{
                int ind = getChessmanIndOnPos(QPoint(x,y)) ;
                if(nowChoose == QPoint(-1,-1)){
                    //判断是否新选中了棋子
                    if(ind!=-1 && nowChessman.at(ind).color==nowColor){
                        nowChoose = QPoint(x,y);
                    }
                } else{
                    //之前已经选中过某个棋子
                    //移动
                    bool suc=false ;
                    for(int i=0;i<myNextCandidate.length();++i){
                        if(myNextCandidate.at(i) == QPoint(x,y)){
                            suc=true;
                            int ind = getChessmanIndOnPos(nowChoose);
                            moveChessman(ind, QPoint(x,y)) ; //可能导致吃子进而索引改变

                            //处理兵升变
                            ind = getChessmanIndOnPos(QPoint(x,y));
                            Chessman man = nowChessman.at(ind) ;
                            if(man.type==TYPEPAWN && getPawnStatus(man)==PAWNUPGRADE){
                                upgradingInd = ind ;
                                nowChoose = QPoint(-1,-1) ;
                                break ;
                            }

                            //处理王车易位
                            if(man.type==TYPEKING && std::abs(man.pos.x()-nowChoose.x())==2){
                                int y = (man.color ? 8 : 1) ;
                                int x = ((man.pos.x()<nowChoose.x()) ? 1 : 8) ;
                                int rookInd = nowChessman.indexOf(Chessman(TYPEROOK,man.color,QPoint(x,y))) ;
                                moveChessman(rookInd, QPoint(((x==1) ? 4 : 6), y)) ;
                            }

                            nextPlayer() ;
                            nowChoose = QPoint(-1,-1) ;
                            break;
                        }
                    }

                    //重选
                    if(!suc && ind!=-1 && nowChessman.at(ind).color==nowColor){
                        nowChoose = QPoint(x,y);
                    }
                }
            }

            if(nowChoose != QPoint(-1,-1)){
                int ind = getChessmanIndOnPos(nowChoose) ;
                myNextCandidate = getCandidatePosWithCheck(nowChessman.at(ind));
            } else{
                myNextCandidate.clear();
            }
        }
        //debug("test4");
        update();
        //debug("test5");
    }
}

int MainWindow::getChessmanIndOnPos(QPoint pos){
    //返回某个位置上的Chessman索引
    int ret=-1 ;
    for(int i=0;i<nowChessman.length();++i){
        if(nowChessman.at(i).pos == pos){
            ret = i ;
            break ;
        }
    }
    return ret;
}

void MainWindow::debug(QString s){
    if(debugOn)
        qDebug() << s ;
}

bool MainWindow::isRunning()
{
    return nowStatus==STATUSMYTURN || nowStatus==STATUSOPPTURN ;
}

void MainWindow::checkGameStatus(){
    //接下来是本地玩家着子，判断是否已经输了或者逼和
    if(isCheckMate() & (nowColor ? MainWindow::CHECKBLACK : MainWindow::CHECKWHITE)){
        setStatus(nowColor ? MainWindow::STATUSWHITEWIN : MainWindow::STATUSBLACKWIN) ;
        for(int i=0;i<=1;++i) player[i]->gameEnd(nowStatus) ;
    } else if(isStaleMate() & (nowColor ? MainWindow::CHECKBLACK : MainWindow::CHECKWHITE)){
        setStatus(STATUSTIE) ;
        for(int i=0;i<=1;++i) player[i]->gameEnd(nowStatus) ;
    }
}

QPoint MainWindow::getPoint(int x, int y){
    y = row+2-y;
    return QPoint((x-1)*gridSize+leftUp.x(), (y-1)*gridSize+leftUp.y());
}

int MainWindow::char2ind(QChar s){
    return s.toLatin1()-'a'+1;
}

QChar MainWindow::ind2char(int a){
    return QChar(a+'a'-1) ;
}

int MainWindow::type2ind(QString s){
    if(s=="king"){
        return 1;
    } else if(s=="queen"){
        return 2;
    } else if(s=="bishop"){
        return 3;
    } else if(s=="knight"){
        return 4;
    } else if(s=="rook"){
        return 5;
    } else if(s=="pawn"){
        return 6;
    } else{
        return -1;
    }
}

QString MainWindow::ind2type(int a){
    if(a==1){
        return "king" ;
    } else if(a==2){
        return "queen" ;
    } else if(a==3){
        return "bishop" ;
    } else if(a==4){
        return "knight" ;
    } else if(a==5){
        return "rook" ;
    } else if(a==6){
        return "pawn" ;
    } else{
        return "" ;
    }
}

QPoint MainWindow::str2pos(QString s){
    assert(s.length()==2);
    return QPoint(char2ind(s.at(0)), s.mid(1,1).toInt()) ;
}

QString MainWindow::pos2str(QPoint pos){
    return ind2char(pos.x()) + QString::number(pos.y()) ;
}

QList< Chessman> MainWindow::str2chessman(QString s, int color){
    //将一行字符串转换为若干chessman
    QList< Chessman> list;
    QStringList strList = s.split(' ') ;
    int type = type2ind(strList.at(0)) ;
    for(int i=2;i<strList.length();++i){
        if(strList.at(i).trimmed()=="") continue ;
        QPoint pos = str2pos(strList.at(i)) ;
        list.append( Chessman(type, color, pos)) ;
    }
    return list;
}

QString MainWindow::chessman2str(QList< Chessman> &list){
    //将若干相同类型的chessman转成字符串
    if(list.length()==0) return QString("") ;
    QString ret = ind2type(list.at(0).type) + " " + QString::number(list.length()) + " ";
    for(int i=0;i<list.length();++i){
        ret = ret + pos2str(list.at(i).pos) + ((i==list.length()-1) ? "" :" ");
    }
    return ret;
}

QString MainWindow::getChessStr(){
    //把当前局面转化为字符串
    QString ret = (nowColor ? "black\n" : "white\n") ;
    QList< Chessman> tmpList[COLORNUM][TYPENUM+1] ;
    for(int i=0;i<nowChessman.length();++i){
         Chessman man = nowChessman.at(i) ;
        tmpList[man.color][man.type].append(man) ;
    }
    for(int i=1;i<=TYPENUM;++i){
        QString tmp = chessman2str(tmpList[nowColor][i]) ;
        if(tmp!="") ret = ret + tmp + "\n" ;
    }
    ret = ret + (nowColor ? "white\n" : "black\n") ;
    for(int i=1;i<=TYPENUM;++i){
        QString tmp = chessman2str(tmpList[nowColor^1][i]) ;
        if(tmp!="") ret = ret + tmp + "\n" ;
    }
    return ret;
}

void MainWindow::loadChessStr(QString chessStr){
    int color=0 ;
    QStringList strList = chessStr.split('\n') ;
    QList<Chessman> list ;
    int now = 0 ;
    while(now < strList.length()){
        QString s = strList.at(now) ;
        //debug("test:" + s + " " + QString::number(now)) ;
        if(s.trimmed()=="white"){
            color=0 ;
        } else if(s.trimmed()=="black"){
            color=1 ;
        } else {
            list.append(str2chessman(s, color)) ;
        }
        ++now ;
    }
    nowChessman = list ;
    nowColor = color^1 ;
    update() ;
}

int MainWindow::getGroundType(int x, int y){
    //返回地面颜色（黑色为1，白色为0）
    return (x+y)%2^1 ;
}

void MainWindow::nextPlayer(){
    nowPlayerInd^=1;
    player[nowPlayerInd]->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoadInit_triggered()
{
    loadChessStr(iniChessmanStr) ;
    update();
}

void MainWindow::on_actionLoadFromFile_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "./", "All Files(*.*)") ;
    if(filePath=="") return ;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this, "错误", "打开文件失败");
        return ;
    }
    QTextStream in(&file);
    loadChessStr(in.readAll());
    file.close();
}

void MainWindow::on_actionSaveChess_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "保存文件", "./", "All Files(*.*)") ;
    if(filePath=="") return ;
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::critical(this, "错误", "保存文件失败");
        return ;
    }
    QTextStream out(&file);
    out << getChessStr();
    file.close();
}

void MainWindow::on_actionPVP_triggered()
{
    setStatus(STATUSMYTURN) ;
    player[0] = dynamic_cast<Player*>(localPlayer[0]);
    player[1] = dynamic_cast<Player*>(localPlayer[1]);
    nowPlayerInd = 0;
    if(nowColor!=player[0]->getColor()){
        std::swap(player[0],player[1]);
    }
    player[0]->play();
}

void MainWindow::on_actionGiveIn_triggered()
{
    setStatus(nowColor ? STATUSWHITEWIN : STATUSBLACKWIN) ;
    for(int i=0;i<=1;++i) player[i]->gameEnd(nowStatus) ;
}
