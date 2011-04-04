#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>
#include "Blocks.h"
#include "Player.h"

#ifndef ENGINE_H
#define ENGINE_H

enum Direction {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3};

class Engine
{
    public:
        Engine();
        virtual ~Engine();
        SDL_Surface *GetCurrentScreen();
        bool CheckCollision(SDL_Rect A, SDl_Rect B);
        void Update();

        void AddBlock(char Type, int X, int Y);
        void RemoveBlock(int X, int Y);

        int AddEnemy(char Type, int X, int Y);
        bool RemoveEnemy(int ID);

        bool LoadLevel(char** level, int XLenght, int YLenght);

        void MovePlayer(Direction direction);
    protected:
    private:
        SDL_Surface *coins = NULL;
        SDL_Surface *screen = NULL;
        SDL_Surface *level = NULL;

        Blocks block;
        Player player;

        SDL_Rect rPlayer[3];
        SDL_Rect rBlocks[2];

        int playerx = 50;
        int playery = 50;

        int posPlayer = 0;

        int score = 0;
        int live = 3;

        int levelX;
        int levelY;
        char** curLevel;

        void UpdatePlayer();
        void UpdateBlocks();
        void UpdateEnemy();

        SDL_Surface *Render();
        SDL_Surface *RenderBackground();
        SDL_Surface *RenderLevel();
        SDL_Surface *RenderPlayer();

        bool CheckWallCollision(SDL_Pos obj);

        SDL_Surface *load_image(std::string filename);
        void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
};

#endif // ENGINE_H
