#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>

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

SDL_Surface *load_image(std::string filename)
{
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

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface(source, NULL, destination, &offset);
}

bool init()
{
    //Initialize all SDL subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    //If there was an error in setting up the screen
    if(screen == NULL)
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption("SuperGuy", NULL);

    //If everything initialized fine
    return true;
}

bool load_splash()
{
    //Load the image
    splas = load_image("gfx\\splash.png")

    //If there was an error in loading the immage
    if(image == NULL)
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the image
    SDL_FreeSurface(image);

    //Quit SDL
    SDL_Quit();
}

int main(int argc, char* args[])
{

    Engine engine();

    //Make sure the program waits for a quit
    bool quit = false;

    //Initialize
    if(init() == false)
        return 1;

    //Load the files
    if(load_splash() == false)
        return 1;

    //Apply the background to the screen
    apply_surface(0, 0, image, screen);

    //Update the screen
    if(SDL_Flip(screen) == -1)
    {
        return 1;
    }

    update.start();
    fps.start();

    //While the user hasn't quit
    while(quit == false)
    {
        //While there's an event to handle
        while(SDL_PollEvent(&event))
        {
            //If the user has Xed out the window
            if(event.type == SDL_QUIT)
            {
                //Quit the program
                quit = true;
            }

            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_SPACE)
                {
                    engine.MovePlayer(UP);
                }

                if(event.key.keysym.sym == SDLK_DOWN)
                {
                    engine.MovePlayer(DOWN);
                }

                if(event.key.keysym.sym == SDLK_LEFT)
                {
                    engine.MovePlayer(LEFT);
                }

                if(event.key.keysym.sym == SDLK_RIGHT)
                {
                    engine.MovePlayer(RIGHT);
                }


            }

        }

        //Update Screen
        apply_surface(0, 0, engine.GetCurrentScreen(), screen);
        if(SDL_Flip(screen) == -1)
            return 1;
        frame++;
        //If a second has passed since the caption was last updated
        if(update.get_ticks() > 1000)
        {
            //The frame rate as a string
            std::stringstream caption;

            //Calculate the frames per second and create the string
            caption << "SuperGuy" << " FPS: " << frame / ( fps.get_ticks() / 1000.f );

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
