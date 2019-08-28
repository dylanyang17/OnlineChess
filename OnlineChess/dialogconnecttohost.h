#ifndef DIALOGCONNECTTOHOST_H
#define DIALOGCONNECTTOHOST_H

#include <QDialog>
#include <QtNetwork>
#include <QHostAddress>

class MainWindow;

namespace Ui {
class DialogConnectToHost;
}

class DialogConnectToHost : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConnectToHost(QWidget *parent = nullptr, MainWindow *mainWindow = nullptr);
    ~DialogConnectToHost();

public slots:
    void handleConnected();
private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonConnect_clicked();

private:
    Ui::DialogConnectToHost *ui;
    QTcpSocket *tcpSocket;
    MainWindow *mainWindow;
    bool isConnecting ;
};

#endif // DIALOGCONNECTTOHOST_H
