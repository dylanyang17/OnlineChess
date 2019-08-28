#include "localplayer.h"

LocalPlayer::LocalPlayer(MainWindow *mainWindow, int _color) : Player(mainWindow, _color)
{

}

LocalPlayer::~LocalPlayer()
{

}

void LocalPlayer::play(){
    mainWindow->nowChoose = QPoint(-1,-1) ;
    mainWindow->nowColor = color ;
    mainWindow->setStatus(MainWindow::STATUSMYTURN) ;
    mainWindow->checkGameStatus() ;
}

void LocalPlayer::gameEnd(int status){
    ;
}
