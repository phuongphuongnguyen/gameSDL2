#ifndef CHARACTERS_H_INCLUDED
#define CHARACTERS_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"

bool inside(int x, int y, SDL_Rect r) {
    return x >=r.x && x < r.x+r.w && y < r.y+r.h && y >r.y ;

}

bool overlap(const SDL_Rect& r1, const SDL_Rect& r2) {
    return inside(r1.x, r1.y, r2) || inside(r1.x + r1.w, r1.y, r2) ||
            inside(r1.x, r1.y+r1.h, r2) || inside(r1.x+r1.w, r1.y+r1.h, r2);
}
struct Character {
    SDL_Texture* texture;
    SDL_Rect rect;
    int y,x,dx,dy;

    void init ()
    { x=location[2],y=600;
     dx = 0, dy = 0;
     texture = loadTexture(main_character);
    }
    int speed = INITIAL_SPEED;
    void moved()
    {
       if(x>=location[0] && x<=location[4]) x+=dx;

       if(x<location[0]||x>location[4]) x-=dx;
        if(x==location[0]||
           x==location[1]||
           x==location[2]||
           x==location[3]||
           x==location[4])
           {
               dx=0;
           }
    }

    void turnLeft()
    {
        dy = 0;
        dx = -speed;
    }
    void turnRight()
    {
        dy = 0;
        dx = speed;
    }

    void renderMain(const Character& character)
    {
        rect.x = character.x;
        rect.y = character.y;
        rect.w = CAR_WIDTH;
        rect.h = CAR_HEIGHT;

        renderTexture(texture,rect.x,rect.y,rect.w,rect.h);
    }


};
struct Object1
{       SDL_Rect rect;
        SDL_Texture *texture;
        int scrolling,x;
        void init()
        { scrolling=-400;
         x=location[rand()%5];
        texture=loadTexture("barrier.png");
}
        void scroll( int speedObject)
        {
            scrolling+=speedObject;
        }
        bool checkend()
        {
            if(scrolling> STREET_HEIGHT)
            {
                scrolling=-CAR_HEIGHT;
                x=location[rand()%5];
                return true;}
            return false;
        }
        void render()
        {
             renderTexture(texture,x,scrolling,80,30);
             rect.x=x;
             rect.y=scrolling;
             rect.w=80;
             rect.h=30;

        }
};

struct Object2
{
    SDL_Rect rect;
        SDL_Texture *texture;
        int scrolling,x,temp;
         void init()
        {

        scrolling=-320;
         x=location[rand()%5];
         temp=rand()%Coin.size();
        texture=loadTexture(Coin[temp]);

        }
        void scroll( int speedCoin)
        {
            scrolling+=speedCoin;
        }
        bool checkend()
        {
            if(scrolling> STREET_HEIGHT)
            {
                scrolling=-CAR_HEIGHT;
                x=location[rand()%5];
                temp=rand()%Coin.size();
                texture=loadTexture(Coin[temp]);
                return true;}
            return false;
        }
        void render()
        {
             renderTexture(texture,x,scrolling,80,80);
             rect.x=x;
             rect.y=scrolling;
             rect.w=80;
             rect.h=80;


        }
};
struct Object3
{
    SDL_Rect rect;
    SDL_Texture *texture;
    int scrolling,x,temp;
    void init (int locate)
    {
        scrolling=locate;
        x=location[rand()%5];
        temp=rand()%Object.size();
        texture=loadTexture(Object[temp]);

    }
    void scroll( int speedObject)
    {
            scrolling+=speedObject;
    }
    bool checkend()
    {
        if(scrolling> STREET_HEIGHT)
            {
                scrolling=-CAR_HEIGHT;
                x=location[rand()%5];
                temp=rand()%Object.size();
                texture=loadTexture(Object[temp]);

                return true;}
            return false;
    }
    void render()
    {
        renderTexture(texture,x,scrolling,CAR_WIDTH,CAR_HEIGHT);
        rect.x=x;
        rect.y=scrolling;
        rect.w=CAR_WIDTH;
        rect.h=CAR_HEIGHT;

    }
};


#endif // CHARACTERS_H_INCLUDED
