#include "Player.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>

Player::Player()
{
    LoadPlayer();
}

Player::~Player()
{
    SDL_FreeSurface(Player);
}

SDL_Surface Player::*load_image(std::string filename){
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load(filename.c_str());

    //If nothing went wrong in loading the image
    if(loadedImage != NULL)
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old image
        SDL_FreeSurface(loadedImage);

        //If the image was optimized just fine
        if(optimizedImage != NULL)
        {
            //Map the color key
            Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0, 0xFF);

            //Set all pixels of color R 0xFF, G 0, B 0xFF to be transparent
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
        }
    }

    //Return the optimized image
    return optimizedImage;
}

void LoadPlayer()
{
    Player = load_image("gfx\\Player.png");
}

SDL_Surface Player::*Left()
{
    SDL_Rect tmp;
    tmp.x = 0;
    tmp.y = 0;
    tmp.w = 16;
    tmp.h = 16;

    SDL_Surface *playGround = NULL;
    apply_surface(0, 0, Player, playGround, tmp);
    return playGround;
}

SDL_Surface Player::*Right()
{
    SDL_Rect tmp;
    tmp.x = 16;
    tmp.y = 0;
    tmp.w = 16;
    tmp.h = 16;

    SDL_Surface *playGround = NULL;
    apply_surface(0, 0, Player, playGround, tmp);
    return playGround;
}

SDL_Surface Player::*Down()
{
    SDL_Rect tmp;
    tmp.x = 16;
    tmp.y = 0;
    tmp.w = 16;
    tmp.h = 16;

    SDL_Surface *playGround = NULL;
    apply_surface(0, 0, Player, playGround, tmp);
    return playGround;
}

void Player::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL){    //Holds offsets
    SDL_Rect offset;
    //Get offsets
    offset.x = x;
    offset.y = y;
    //Blit
    SDL_BlitSurface(source, clip, destination, &offset);}
