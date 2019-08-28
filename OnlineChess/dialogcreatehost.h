#ifndef DIALOGCREATEHOST_H
#define DIALOGCREATEHOST_H

#include <QDialog>
#include <QtNetwork>
#include <QRegExp>
#include <QHostAddress>

class MainWindow;

namespace Ui {
class DialogCreateHost;
}

class DialogCreateHost : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCreateHost(QWidget *parent = nullptr, MainWindow *mainWindow = nullptr);
    ~DialogCreateHost();
    static bool checkIP(QString s);
    const static int PORT = 12345;

public slots:
    void handleNewConnection();
private slots:
    void on_pushButtonClose_clicked();

    void on_pushButtonStart_clicked();

private:
    Ui::DialogCreateHost *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    MainWindow *mainWindow;
    bool isListening;
};

#endif // DIALOGCREATEHOST_H
