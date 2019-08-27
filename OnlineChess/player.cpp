#include "player.h"

Player::Player(MainWindow *mainWindow, int _color)
{
    color = _color ;
    this->mainWindow = mainWindow;
}

void Player::play()
{

}

Player::~Player()
{

}

void Player::setColor(int _color)
{
    color = _color;
}

int Player::getColor()
{
    return color;
}
