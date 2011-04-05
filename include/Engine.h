#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>
#include "include/Blocks.h"
#include "include/Player.h"

#ifndef ENGINE_H
#define ENGINE_H

enum Direction {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3};

class Engine
{
    public:
        Engine();
        virtual ~Engine();
        SDL_Surface* GetCurrentScreen();
        bool CheckCollision(SDL_Rect A, SDL_Rect B);
        void Update();

        void AddBlock(char Type, int X, int Y);
        void RemoveBlock(int X, int Y);

        int AddEnemy(char Type, int X, int Y);
        bool RemoveEnemy(int ID);

        bool LoadLevel(char** level, int XLenght, int YLenght);

        void MovePlayer(Direction direction);
    protected:
    private:
        SDL_Surface *coins;
        SDL_Surface *screen;
        SDL_Surface *level;

        Blocks block;
        Player player;

        SDL_Rect rPlayer[3];
        SDL_Rect rBlocks[2];

        int playerx;
        int playery;

        int posPlayer;

        int score;
        int live;

        int levelX;
        int levelY;
        char** curLevel;

        void UpdatePlayer();
        void UpdateBlocks();
        void UpdateEnemy();

        SDL_Surface* Render();
        SDL_Surface* RenderBackground();
        SDL_Surface* RenderLevel();
        SDL_Surface* RenderPlayer();

        bool CheckWallCollision(SDL_Rect obj);

        SDL_Surface* load_image(std::string filename);
        void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
};

#endif // ENGINE_H
