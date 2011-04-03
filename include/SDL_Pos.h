#ifndef SDL_POS_H
#define SDL_POS_H


class SDL_Pos
{
    public:
        SDL_Pos();
        virtual ~SDL_Pos();
        int X;
        int Y;
        int getX();
        int getY();
        void setX(int value);
        void setY(int value);
    protected:
    private:
};

#endif // SDL_POS_H
