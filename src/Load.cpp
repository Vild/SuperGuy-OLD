#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>

SDL_Surface *load_image(std::string filename) {
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load(filename.c_str());

	//If nothing went wrong in loading the image
	std::cout << "loadedImage = " << loadedImage << std::endl;
	if (loadedImage == NULL) {
		std::cout << "loadedImage == NULL" << std::endl;
		return NULL;
	}

	//Create an optimized image
	optimizedImage = SDL_DisplayFormat(loadedImage);

	if (optimizedImage == NULL) {
		std::cout << "1 optimizedImage == NULL" << std::endl;
		return loadedImage;
	}

	//Free the old image
	SDL_FreeSurface(loadedImage);

	//If the image was optimized just fine
	if (optimizedImage == NULL) {
		std::cout << "2 optimizedImage == NULL" << std::endl;
		return NULL;
	}
	//Map the color key
	Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0, 0xFF);

	//Set all pixels of color R 0xFF, G 0, B 0xFF to be transparent
	SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);

	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination,
		SDL_Rect* clip = NULL) {
//Holds offsets
	SDL_Rect offset;
//Get offsets
	offset.x = x;
	offset.y = y;
//Blit
	SDL_BlitSurface(source, clip, destination, &offset);
}
