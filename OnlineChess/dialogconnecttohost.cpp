#include "dialogconnecttohost.h"
#include "ui_dialogconnecttohost.h"
#include "dialogcreatehost.h"
#include "mainwindow.h"
#include <QMessageBox>

DialogConnectToHost::DialogConnectToHost(QWidget *parent, MainWindow *mainWindow) :
    QDialog(parent),
    ui(new Ui::DialogConnectToHost)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket();
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(handleConnected())) ;
    isConnecting=false;
    this->mainWindow = mainWindow;
}

DialogConnectToHost::~DialogConnectToHost()
{
    delete ui;
}

void DialogConnectToHost::handleConnected()
{
    mainWindow->startOnlineGame(tcpSocket, 1) ;
    this->close();
}

void DialogConnectToHost::on_pushButtonCancel_clicked()
{
    tcpSocket->close();
    this->close();
}

void DialogConnectToHost::on_pushButtonConnect_clicked()
{
    isConnecting^=1;
    if(isConnecting){
        QString s = ui->lineEdit->text();
        QHostAddress addr(s) ;
        if(!DialogCreateHost::checkIP(s)){
            QMessageBox::critical(this, "错误", "请输入正确ip格式");
            isConnecting=false;
            return;
        }
        tcpSocket->connectToHost(addr, DialogCreateHost::PORT);
        ui->pushButtonConnect->setText("取消连接") ;
    } else{
        tcpSocket->close();
        ui->pushButtonConnect->setText("连接") ;
    }
}
