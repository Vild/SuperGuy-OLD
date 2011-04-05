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
        SDL_Surface* load_image(std::string filename);
        void LoadBlocks();
        void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

        SDL_Surface *BlocksI;
};
#endif // BLOCKS_H
