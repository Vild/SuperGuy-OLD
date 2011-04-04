#include "Engine.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>

Engine::Engine()
{
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
}

Engine::~Engine()
{
    //dtor
}

SDL_Surface Engine::*Render()
{
    apply_surface(0, 0, RenderBackground(), level)
    apply_surface(0, 0, RenderLevel(), level);
    apply_surface(0, 0, RenderPlayer(), level);

    apply_surface(0, 0, level, screen);
    return screen;
}

SDL_Surface Engine::*RenderBackground()
{
    return load_image("gfx\\splash.png")
}

SDL_Surface Engine::*RenderLevel()
{
    SDL_Surface *tmp = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    for(int x = 0; x > levelX; x++)
    {
        for(int y = 0; y > levelY; y++)
        {
            switch(curLevel[X][Y])
            {
                case 0x01:
                    apply_surface(x * 16, y * 16, block.Solid(), tmp);
                case 0x02:
                    apply_surface(x * 16, y * 16, block.QMarkBox(), tmp);
            }
        }

    }
    return tmp;
}

SDL_Surface Engine::*RenderPlayer()
{
    switch(posPlayer)
    {
        case 0:
            return player.Left();
        case 1:
            return player.Right();
        case 2:
            return player.Down();
    }
}

SDL_Surface Engine::*GetCurrentScreen()
{
    return Render();
}

bool Engine::CheckCollision(SDL_Pos obj1, SDl_Pos obj2)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if(bottomA <= topB)
    {
        return false;
    }

    if(topA >= bottomB)
    {
        return false;
    }

    if(rightA <= leftB)
    {
        return false;
    }

    if(leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void Engine::Update()
{    UpdateBlocks();
    UpdatePlayer();
    UpdateEnemy();}

void Engine::AddBlock(char Type, int X, int Y){    curLevel[X][Y] = Type;}

void Engine::RemoveBlock(int X, int Y){    curLevel[X][Y] = 0;}

int Engine::AddEnemy(char Type, int X, int Y){}
bool Engine::RemoveEnemy(int ID)
{

}

bool Engine::LoadLevel(char** level, int XLenght, int YLenght){
    levelX = XLenght;
    levelY = YLenght;    curLevel = level;
    level = SDL_SetVideoMode(levelX * 16, levelY * 16, 32, SDL_SWSURFACE);
}

void Engine::MovePlayer(Direction direction){    switch(direction)
    {
        case UP:
            //TODO: Add Real Jump
            pPlayer.y--;
            if(!CheckWallCollision(pPlayer))
                pPlayer.y++;
        case DOWN:
            pPlayer.y++;
            if(!CheckWallCollision(pPlayer)))
                pPlayer.y--;
            posPlayer = 2;
        case LEFT:
            pPlayer.x--;
            if(!CheckWallCollision(pPlayer)))
                pPlayer.x++;
            posPlayer = 0;
        case RIGHT:
            pPlayer.x++;
            if(!CheckWallCollision(pPlayer)))
                pPlayer.x--;
            posPlayer = 1;
    }}


void Engine::UpdatePlayer(){}
void Engine::UpdateBlocks(){}
void Engine::UpdateEnemy(){//TODO: Add enemy AI}

bool Engine::CheckWallCollision(SDL_Rect A)
{
    //TODO: Optimize the CheckWallCollision function
    for(int x = 0; x < strlen(curLevel); x++)
    {
        for(int y = 0; y < strlen(curLevel[strlen(curLevel)]); y++)
        {
            if(curLevel[x][y] == 0x01) //0x01 == stone
            {
                SDL_Rect B;
                B.x = x;
                B.y = y;
                CheckCollision(A,B);
            }
        }
    }
}

SDL_Surface Engine::*load_image(std::string filename){    //Temporary storage for the image that's loaded
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
    return optimizedImage;}

void Engine::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL){    //Holds offsets
    SDL_Rect offset;
    //Get offsets
    offset.x = x;
    offset.y = y;
    //Blit
    SDL_BlitSurface(source, clip, destination, &offset);}
