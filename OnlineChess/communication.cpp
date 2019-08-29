#include "communication.h"
#include "mainwindow.h"

Communication::Communication(QObject *parent, QTcpSocket *tcpSocket, MainWindow *mainWindow) : QObject(parent)
{
    packHead = "CHESSPACK YYR";
    initTcpSocket(tcpSocket);
    this->mainWindow = mainWindow;
}

void Communication::initTcpSocket(QTcpSocket *tcpSocket){
    this->tcpSocket = tcpSocket ;
    if(tcpSocket != nullptr)
        connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(handleRead())) ;
    readBuffer.clear();
    packages.clear();
}

void Communication::close()
{
    tcpSocket->close();
}

QString Communication::pack(QString s){
    return packHead + "\n" + QString::number(s.length()) + "\n" + s;
}

QString Communication::unpack(QString s, int &pos){
    //拆包成功则返回原信息，否则返回空串。pos用于返回字符串s中包结尾的下一位置
    QStringList strList = s.split('\n');
    pos=-1;
    if(strList.length()<3) return "" ;
    bool ok;
    int contentLen=strList.at(1).toInt(&ok), headLen=strList.at(0).length()+1+strList.at(1).length()+1; //包头和包内容的长度
    if(strList.at(0)!=packHead || !ok) return ""; //不是以包头作为开头
    if(headLen+contentLen>s.length()) return ""; //非完整包
    pos = headLen+contentLen ;
    return s.mid(headLen, contentLen) ;
}

bool Communication::hasNextPack()
{
    return packages.length()>0;
}

QString Communication::nextPack()
{
    QString ret = packages.at(0);
    packages.pop_front();
    return ret;
}

void Communication::handleRead(){
    mainWindow->debug("READ MESSAGE");
    readBuffer += tcpSocket->readAll() ;
    int pos;
    QString tmp;
    if((tmp=unpack(readBuffer, pos))!=""){
        mainWindow->debug("THE MESSAGE IS A PACK");
        readBuffer.remove(0, pos) ;
        packages.append(tmp) ;
        emit(readyReadPack()) ;
    }
}

void Communication::sendMessage(QString s)
{
    if(tcpSocket != nullptr){
        QByteArray *byteArray = new QByteArray;
        byteArray->clear();
        s = pack(s);
        //mainWindow->debug(s) ;
        byteArray->append(s);
        tcpSocket->write(*byteArray);
    }
}
