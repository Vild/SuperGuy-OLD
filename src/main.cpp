#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Timer.h"

#include "Engine.h"

#include "Load.h"

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//Screen surfaces
SDL_Surface *screen = NULL;
SDL_Surface *splash = NULL;

SDL_Event event;

int frame = 0;

Timer fps;

Timer update;

bool init() {
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}

	//Set up the screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
			SDL_SWSURFACE);

	//If there was an error in setting up the screen
	if (screen == NULL) {
		return false;
	}

	//Set the window caption
	SDL_WM_SetCaption("SuperGuy", NULL);

	//If everything initialized fine
	return true;
}

bool load_splash() {
	//Load the image
	splash = load_image("gfx\\splash.png");

	//If there was an error in loading the immage
	if (splash == NULL) {
		return false;
	}

	//If everything loaded fine
	return true;
}

void clean_up() {
	//Free the image
	SDL_FreeSurface(splash);

	//Quit SDL
	SDL_Quit();
}

int main(int argc, char* args[]) {

	Engine engine;
	//Make sure the program waits for a quit
	bool quit = false;

	//Initialize
	if (init() == false)
		return 1;

	//Load the files
	if (load_splash() == false)
		return 1;

	//Apply the background to the screen
	apply_surface(0, 0, splash, screen);

	//Update the screen
	if (SDL_Flip(screen) == -1) {
		return 1;
	}

	const int tmp[32][32] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01, 0x01,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0x01, 0x01, 0, 0, 0x02, 0x02, 0x02, 0x02,
			0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01, 0, 0, 0x01, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0x01, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01,
			0x01, 0x01, 0, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01, 0, 0, 0, 0,
			0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01, 0x02, 0x02, 0x02,
			0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0, 0, 0, 0x01, 0, 0,
			0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01, 0, 0, 0, 0x01,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0x01, 0, 0, 0, 0, 0x01, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0x01, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01,
			0, 0, 0, 0, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0x01, 0x01, 0x02, 0x02,
			0x02, 0x02, 0, 0 }, { 0, 0, 0, 0, 0, 0x01, 0x01, 0, 0, 0, 0x01,
			0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01, 0x01, 0x01, 0, 0, 0, 0, 0,
			0, 0 }, { 0, 0, 0, 0, 0x01, 0x01, 0x01, 0x01, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0x01, 0x01, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0,
			0, 0, 0, 0x01, 0, 0, 0x01, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01,
			0x01, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0x01, 0, 0,
			0, 0, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
			0x01, 0x01, 0, 0x01, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0,
			0x01, 0x01, 0, 0, 0, 0, 0x01, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0x01, 0x01, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0x01, 0, 0, 0, 0,
			0, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01, 0, 0, 0, 0,
			0, 0, 0, 0 },
			{ 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
					0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
					0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0, 0, 0 }, {
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

	engine.LoadWorld((char**) &tmp, 32, 32);

	update.start();
	fps.start();

	//While the user hasn't quit
	while (quit == false) {
		//While there's an event to handle
		while (SDL_PollEvent(&event)) {
			//If the user has Xed out the window
			if (event.type == SDL_QUIT) {
				//Quit the program
				quit = true;
			}

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
				}

				if (event.key.keysym.sym == SDLK_SPACE) {
					engine.MovePlayer(UP);
				}

				if (event.key.keysym.sym == SDLK_DOWN) {
					engine.MovePlayer(DOWN);
				}

				if (event.key.keysym.sym == SDLK_LEFT) {
					engine.MovePlayer(LEFT);
				}

				if (event.key.keysym.sym == SDLK_RIGHT) {
					engine.MovePlayer(RIGHT);
				}

			}

		}

		//Update Screen
		apply_surface(0, 0, engine.GetCurrentScreen(), screen);
		if (SDL_Flip(screen) == -1)
			return 1;
		frame++;
		//If a second has passed since the caption was last updated
		if (update.get_ticks() > 1000) {
			//The frame rate as a string
			std::stringstream caption;

			//Calculate the frames per second and create the string
			caption << "SuperGuy" << " FPS: "
					<< frame / (fps.get_ticks() / 1000.f);

			//Reset the caption
			SDL_WM_SetCaption(caption.str().c_str(), NULL);

			//Restart the update timer
			update.start();
		}
	}

	//Free the surface and quit SDL
	clean_up();

	return 0;
}
