#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>

#ifndef BLOCKS_H
#define BLOCKS_H


class Blocks
{
    public:
        Blocks();
        virtual ~Blocks();

        SDL_Surface* Solid();
        SDL_Surface* QMarkBox();
    protected:
    private:
        void LoadBlocks();

        SDL_Surface *BlocksI;
};
#endif // BLOCKS_H
