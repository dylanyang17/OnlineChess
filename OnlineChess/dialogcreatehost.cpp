#include "dialogcreatehost.h"
#include "ui_dialogcreatehost.h"
#include "mainwindow.h"
#include <QMessageBox>

DialogCreateHost::DialogCreateHost(QWidget *parent, MainWindow *mainWindow) :
    QDialog(parent),
    ui(new Ui::DialogCreateHost)
{
    ui->setupUi(this);
    isListening = false;
    this->mainWindow = mainWindow;
    tcpServer = new QTcpServer();
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(handleNewConnection())) ;
    ui->lineEdit->setText("127.0.0.1") ;
}

void DialogCreateHost::handleNewConnection(){
    tcpSocket = tcpServer->nextPendingConnection();
    tcpServer->close();
    mainWindow->startOnlineGame(tcpSocket, 0) ;
    this->close();
}

DialogCreateHost::~DialogCreateHost()
{
    delete ui;
}

bool DialogCreateHost::checkIP(QString s)
{
    QRegExp regExp("(((\\d{1,2})|(1\\d{2})|(2[0-4]\\d)|(25[0-5])).){3}((\\d{1,2})|(1\\d{2})|(2[0-4]\\d)|(25[0-5]))");
    return regExp.indexIn(s)!=-1 && regExp.matchedLength()==s.length();
}

void DialogCreateHost::on_pushButtonClose_clicked()
{
    tcpServer->close();
    this->close();
}

void DialogCreateHost::on_pushButtonStart_clicked()
{
    isListening ^= 1;
    if(isListening){
        QString s = ui->lineEdit->text();
        QHostAddress addr(s) ;
        if(!checkIP(s)){
            QMessageBox::critical(this, "错误", "请输入正确ip格式");
            isListening=0;
            return;
        }
        tcpServer->listen(addr, PORT) ;
        ui->pushButtonStart->setText("停止") ;
    } else{
        tcpServer->close();
        ui->pushButtonStart->setText("创建") ;
    }

}
