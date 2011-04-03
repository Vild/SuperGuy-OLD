#ifndef ENGINE_H
#define ENGINE_H

enum Direction {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3};

class Engine
{
    public:
        Engine();
        virtual ~Engine();
        SDL_Surface* GetCurrentScreen();
        bool CheckCollision(SDL_Rect A, SDl_Rect B);
        void Update();

        void AddBlock(char Type, int X, int Y);
        void RemoveBlock(int X, int Y);

        int AddEnemy(char Type, int X, int Y);
        bool RemoveEnemy(int ID);

        bool LoadLevel(char** level);

        void MovePlayer(Direction direction);
    protected:
    private:

        SDL_Surface *player = NULL;
        SDL_Surface *blocks = NULL;
        SDL_Surface *coins = NULL;
        SDL_Surface *screen = NULL;
        SDL_Surface *level = NULL;

        SDL_Rect rPlayer[3];
        SDL_Rect rBlocks[2];

        SDL_Rect pPlayer;

        int score = 0;
        int live = 3;

        char** curLevel;

        bool LoadImages();

        void UpdatePlayer();
        void UpdateBlocks();
        void UpdateEnemy();

        SDL_Surface Render();
        SDL_Surface RenderBackground();
        SDL_Surface RenderLevel();
        SDL_Surface RenderPlayer();

        bool CheckWallCollision(SDL_Pos obj);

        SDL_Surface *load_image(std::string filename);
        void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
};

#endif // ENGINE_H
