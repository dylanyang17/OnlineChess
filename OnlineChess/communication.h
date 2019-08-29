#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QtNetwork>
#include <QList>
#include "mainwindow.h"

class Communication : public QObject
{
    Q_OBJECT
public:
    explicit Communication(QObject *parent = nullptr, QTcpSocket *tcpSocket = nullptr, MainWindow *mainWindow = nullptr);

    QTcpSocket *tcpSocket;
    QString packHead;

    void sendMessage(QString s) ;

    QString pack(QString s);
    QString unpack(QString s, int &pos);
    bool hasNextPack();
    QString nextPack();
    void initTcpSocket(QTcpSocket *tcpSocket);
    void close();
signals:
    void readyReadPack();

public slots:
    void handleRead();

private:
    QString readBuffer;
    QList<QString> packages;
    MainWindow *mainWindow;
};

#endif // COMMUNICATION_H
