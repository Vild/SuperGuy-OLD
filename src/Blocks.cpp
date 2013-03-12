#include "Blocks.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>
#include "Load.h"

Blocks::Blocks()
{
    LoadBlocks();
}

Blocks::~Blocks()
{
    SDL_FreeSurface(BlocksI);
}

void Blocks::LoadBlocks()
{
    BlocksI = load_image("gfx\\Blocks.bmp");
}

SDL_Surface* Blocks::Solid()
{
    SDL_Rect tmp;
    tmp.x = 0;
    tmp.y = 0;
    tmp.w = 16;
    tmp.h = 16;

    SDL_Surface *playGround = NULL;
    apply_surface(0, 0, BlocksI, playGround, &tmp);
    return playGround;
}

SDL_Surface* Blocks::QMarkBox()
{
    SDL_Rect tmp;
    tmp.x = 16;
    tmp.y = 0;
    tmp.w = 16;
    tmp.h = 16;

    SDL_Surface *playGround = NULL;
    apply_surface(0, 0, BlocksI, playGround, &tmp);
    return playGround;
}
