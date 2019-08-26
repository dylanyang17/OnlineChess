#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gridSize=40;
    col=row=8;
    leftUp = QPoint(50,50) ;
}

QPoint MainWindow::getPoint(int x, int y){
    return QPoint((x-1)*gridSize, (y-1)*gridSize);//TODO
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this) ;
    painter.translate(leftUp) ;
    for(int i=1;i<=col;++i){
        for(int j=1;j<=row;++j){

        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
