#include "Player.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>
#include "Load.h"

Player::Player()
{
    LoadPlayer();
}

Player::~Player()
{
    SDL_FreeSurface(PlayerI);
}


void Player::LoadPlayer()
{
    PlayerI = load_image("gfx/Player.bmp");
}

SDL_Surface* Player::Left()
{
    SDL_Rect tmp;
    tmp.x = 0;
    tmp.y = 0;
    tmp.w = 16;
    tmp.h = 16;

    SDL_Surface *playGround = NULL;
    apply_surface(0, 0, PlayerI, playGround, &tmp);
    return playGround;
}

SDL_Surface* Player::Right()
{
    SDL_Rect tmp;
    tmp.x = 16;
    tmp.y = 0;
    tmp.w = 16;
    tmp.h = 16;

    SDL_Surface *playGround = NULL;
    apply_surface(0, 0, PlayerI, playGround, &tmp);
    return playGround;
}

SDL_Surface* Player::Down()
{
    SDL_Rect tmp;
    tmp.x = 16;
    tmp.y = 0;
    tmp.w = 16;
    tmp.h = 16;

    SDL_Surface *playGround = NULL;
    apply_surface(0, 0, PlayerI, playGround, &tmp);
    return playGround;
}
