#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H
#include "player.h"

class LocalPlayer : public Player
{
public:
    LocalPlayer(MainWindow *mainWindow, int _color);
    void play();
    void gameEnd(int status);
    ~LocalPlayer();
};

#endif // LOCALPLAYER_H
