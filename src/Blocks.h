#ifndef BLOCKS_H
#define BLOCKS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>

class Blocks {
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
