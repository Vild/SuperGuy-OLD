#include "Engine.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>
#include "Player.h"
#include "Blocks.h"
#include "Load.h"

Engine::Engine()
{
    pPlayer.x = 50;
    pPlayer.y = 50;

    posPlayer = 0;

    score = 0;
    live = 3;

    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
}

Engine::~Engine()
{
    //dtor

}
SDL_Surface* Engine::Render()
{
    apply_surface(0, 0, RenderBackground(), world);
    apply_surface(0, 0, RenderWorld(), world);
    apply_surface(0, 0, RenderPlayer(), world);

    apply_surface(0, 0, world, screen);
    return screen;
}

SDL_Surface* Engine::RenderBackground()
{
    return load_image("gfx\\splash.png");
}

SDL_Surface* Engine::RenderWorld()
{
    SDL_Surface *tmp = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    for(int x = 0; x > worldX; x++)
    {
        for(int y = 0; y > worldY; y++)
        {
            switch(curWorld[x][y])
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

SDL_Surface* Engine::RenderPlayer()
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
    return player.Left();
}

SDL_Surface* Engine::GetCurrentScreen()
{
    return Render();
}
bool Engine::CheckCollision(SDL_Rect A, SDL_Rect B)
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

void Engine::AddBlock(char Type, int X, int Y){    curWorld[X][Y] = Type;}

void Engine::RemoveBlock(int X, int Y){    curWorld[X][Y] = 0;}

int Engine::AddEnemy(char Type, int X, int Y){    return 0;}
bool Engine::RemoveEnemy(int ID)
{
    return true;
}

bool Engine::LoadWorld(char** newWorld, int XLenght, int YLenght){
    worldX = XLenght;
    worldY = YLenght;    curWorld = newWorld;
    world = SDL_SetVideoMode(worldX * 16, worldY * 16, 32, SDL_SWSURFACE);
    return true;
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
            if(!CheckWallCollision(pPlayer))
                pPlayer.y--;
            posPlayer = 2;
        case LEFT:
            pPlayer.x--;
            if(!CheckWallCollision(pPlayer))
                pPlayer.x++;
            posPlayer = 0;
        case RIGHT:
            pPlayer.x++;
            if(!CheckWallCollision(pPlayer))
                pPlayer.x--;
            posPlayer = 1;
    }}


void Engine::UpdatePlayer(){}
void Engine::UpdateBlocks(){}
void Engine::UpdateEnemy(){//TODO: Add enemy AI}

bool Engine::CheckWallCollision(SDL_Rect A)
{
    //TODO: Optimize the CheckWallCollision function
    for(int x = 0; x < worldX; x++)
    {
        for(int y = 0; y < worldY; y++)
        {
            if(curWorld[x][y] == 0x01) //0x01 == stone
            {
                SDL_Rect B;
                B.x = x;
                B.y = y;
                if(CheckCollision(A,B))
                    return true;
            }
        }
    }
    return false;
}
