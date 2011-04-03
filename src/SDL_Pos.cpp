#include "SDL_Pos.h"

SDL_Pos::SDL_Pos()
{
    X = 0;
    Y = 0;
}

SDL_Pos::~SDL_Pos()
{
    //dtor
}

int SDL_Pos::getX()
{
    return X;
}

int SDL_Pos::getY()
{
    return Y;
}

void SDL_Pos::setX(int value)
{
    X = value;
}

void SDL_Pos::setY(int value)
{
    Y = value;
}
