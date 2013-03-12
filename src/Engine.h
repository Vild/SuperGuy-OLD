#ifndef ENGINE_H
#define ENGINE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>
#include "Blocks.h"
#include "Player.h"

enum Direction {
	UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
};

class Engine {
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

	bool LoadWorld(char** world, int XLenght, int YLenght);

	void MovePlayer(Direction direction);
protected:
private:
	SDL_Surface *coins;
	SDL_Surface *screen;
	SDL_Surface *world;

	Blocks *block;
	Player *player;

	SDL_Rect rPlayer[3];
	SDL_Rect rBlocks[2];

	SDL_Rect pPlayer;

	int posPlayer;

	int score;
	int live;

	int worldX;
	int worldY;
	char** curWorld;

	void UpdatePlayer();
	void UpdateBlocks();
	void UpdateEnemy();

	SDL_Surface* Render();
	SDL_Surface* RenderBackground();
	SDL_Surface* RenderWorld();
	SDL_Surface* RenderPlayer();

	bool CheckWallCollision(SDL_Rect obj);
	;
};

#endif // ENGINE_H
