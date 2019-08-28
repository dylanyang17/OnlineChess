#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H
#include "player.h"


class RemotePlayer : public Player
{
public:
    void play();
    void gameEnd(int status);
    RemotePlayer(MainWindow *mainWindow, int _color);
};

#endif // REMOTEPLAYER_H
