#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H
#include "player.h"

class LocalPlayer : public Player
{
public:
    LocalPlayer(MainWindow *mainWindow, int _color);
    void play();
    ~LocalPlayer();
};

#endif // LOCALPLAYER_H
