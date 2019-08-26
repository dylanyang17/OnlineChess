#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QColor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gridSize=40;
    tagSize=gridSize/8 ;
    col=row=8;
    leftUp = QPoint(50,50) ;
    groundColor[0] = QColor(240,218,181) ;
    groundColor[1] = QColor(185,131,99) ;
}

QPoint MainWindow::getPoint(int x, int y){
    y = row+2-y;
    return QPoint((x-1)*gridSize, (y-1)*gridSize);
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

int MainWindow::getGroundType(int x, int y){
    //返回地面颜色（黑色为1，白色为0）
    return (x+y)%2^1 ;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this) ;
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    painter.translate(leftUp) ;

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
    this->setMinimumSize(tmp.x()+110, tmp.y()+80);
    this->setMaximumSize(tmp.x()+110, tmp.y()+80);



}

MainWindow::~MainWindow()
{
    delete ui;
}
