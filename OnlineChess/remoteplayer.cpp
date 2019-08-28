#include "remoteplayer.h"
#include "mainwindow.h"

RemotePlayer::RemotePlayer(MainWindow *mainWindow, int _color) : Player(mainWindow, _color)
{

}

void RemotePlayer::play()
{
    mainWindow->nowChoose = QPoint(-1,-1) ;
    mainWindow->setStatus(MainWindow::STATUSOPPTURN) ;
    mainWindow->nowColor = color ;
}

void RemotePlayer::gameEnd(int status)
{
    if(status==MainWindow::STATUSTIE){
        mainWindow->sendMessage(mainWindow->MESSAGETIE) ;
    } else{
        mainWindow->sendMessage(mainWindow->MESSAGELOSE) ;
    }
}
