#include "localplayer.h"

LocalPlayer::LocalPlayer(MainWindow *mainWindow, int _color) : Player(mainWindow, _color)
{

}

LocalPlayer::~LocalPlayer()
{

}

void LocalPlayer::play(){
    mainWindow->gameFlag = MainWindow::FLAGMYTURN ;
    mainWindow->nowColor = color ;
}
