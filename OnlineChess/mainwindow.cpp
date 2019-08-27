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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    debugOn=true;
    gridSize=53;
    tagSize=gridSize/8 ;
    circleR=gridSize/3;
    col=row=8;
    leftUp = QPoint(50,50) ;
    groundColor[0] = QColor(240,218,181) ;
    groundColor[1] = QColor(181,135,99) ;
    circleColor = QColor(99,181,176);
    iniChessmanStr = QString("white\nking 1 e1\nqueen 1 d1\nbishop 2 c1 f1\nknight 2 b1 g1\nrook 2 a1 h1\npawn 8 a2 b2 c2 d2 e2 f2 g2 h2\nblack\nking 1 e8\nqueen 1 d8\nbishop 2 c8 f8\nknight 2 b8 g8\nrook 2 a8 h8\npawn 8 a7 b7 c7 d7 e7 f7 g7 h7") ;
    for(int i=0;i<MAXM;++i){
        label[i] = new QLabel(this) ;
    }
    setStatus(STATUSNOTRUN) ;
    nowChoose = QPoint(-1,-1);
    memset(canWalkMore,0,sizeof(canWalkMore)) ;
    canWalkMore[2]=canWalkMore[3]=canWalkMore[5]=true;

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
        label[i]->show();
    }
    for(int i=nowChessman.length();i<MAXM;++i)
        label[i]->hide();

    //当前候选位置
    for(int i=0;i<myNextCandidate.length();++i){
        QPoint p=myNextCandidate.at(i) ;
        QPen pen = painter.pen();
        pen.setColor(circleColor);
        pen.setWidth(circleR/5) ;
        painter.setPen(pen) ;
        int margin=(gridSize-2*circleR)/2;
        painter.drawArc(QRect(getPoint(p.x(),p.y()+1)+QPoint(margin,margin),getPoint(p.x()+1,p.y())+QPoint(-margin,-margin)),0,360*16) ;
    }
}

void MainWindow::myMove(int ind, QPoint p){
    //我方的移动操作，将索引为ind的棋子移动到p位置
    int tmpInd = getChessmanIndOnPos(p) ;
    if(tmpInd!=-1){
        nowChessman.removeAt(tmpInd) ;
    }
    Chessman man = nowChessman.at(ind) ;
    man.pos = p ;

    //此处还要检查胜负和升变 TODO
}

bool MainWindow::outGridRange(QPoint pos){
    return pos.x()<1||pos.y()<1||pos.x()>col||pos.y()>row;
}

QList<QPoint> MainWindow::getCandidatePos(Chessman man){
    //计算棋子下一步能走的所有位置
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
                list.append(newPos) ;
            }
            if(tmpInd!=-1) break ; //被遮挡
        }
    }
    return list;
}

void MainWindow::setStatus(int status){
    nowStatus = status;
    if(isRunning()){
        ui->actionLoadInit->setEnabled(false);
        ui->actionLoadFromFile->setEnabled(false);
        ui->actionPVP->setEnabled(false);
        ui->actionOnline->setEnabled(false);
    } else{
        ui->actionLoadInit->setEnabled(true);
        ui->actionLoadFromFile->setEnabled(true);
        ui->actionPVP->setEnabled(true);
        ui->actionOnline->setEnabled(true);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        int x=event->x(), y=event->y() ;
        x=(x-leftUp.x())/gridSize+1;
        y=(y-leftUp.y())/gridSize+1;
        y=row+1-y;
        if(x<1||y<1||x>col||y>row||event->x()<leftUp.x()||event->y()<leftUp.y())  return ;
        debug(QString("Press: (%1,%2)").arg(x).arg(y)) ;
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
                            myMove(ind, QPoint(x,y)) ;
                            suc=true;
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
                myNextCandidate = getCandidatePos(nowChessman.at(ind));
                update();
            } else{
                myNextCandidate.clear();
            }
        }
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
        QString tmp = chessman2str(tmpList[0][i]) ;
        if(tmp!="") ret = ret + tmp + "\n" ;
    }
    ret = ret + (nowColor ? "white\n" : "black\n") ;
    for(int i=1;i<=TYPENUM;++i){
        QString tmp = chessman2str(tmpList[1][i]) ;
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
    if(nowColor!=player[0]->getColor()){
        std::swap(player[0],player[1]);
    }
}
