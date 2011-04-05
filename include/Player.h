#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>

#ifndef PLAYER_H
#define PLAYER_H


class Player
{
    public:
        Player();
        virtual ~Player();

        SDL_Surface* Left();
        SDL_Surface* Right();
        SDL_Surface* Down();
    protected:
    private:
        SDL_Surface* load_image(std::string filename);
        void LoadPlayer();
        void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

        SDL_Surface *PlayerI;
};

#endif // PLAYER_H
