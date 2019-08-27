#ifndef PLAYER_H
#define PLAYER_H

#include "mainwindow.h"

class Player
{
public:
    Player(MainWindow *mainWindow, int _color=0);
    virtual void play();
    virtual ~Player();
    void setColor(int color) ;
    int getColor();
protected:
    int color;
    MainWindow *mainWindow;
};

#endif // PLAYER_H
