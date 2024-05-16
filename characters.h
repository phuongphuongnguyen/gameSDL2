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

    init ()
    { x=location[2],y=600;
     dx = 0, dy = 0;
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

    void renderMain(const Character& character,  Graphics& graphics)
    {
        rect.x = character.x;
        rect.y = character.y;
        rect.w = CAR_WIDTH;
        rect.h = CAR_HEIGHT;
        texture = graphics.loadTexture(main_character);
        graphics.renderTexture(texture,rect.x,rect.y,rect.w,rect.h);
    }

};
struct Object1
{       SDL_Rect rect;
        SDL_Texture *texture_o1;
        int scrolling,x;
        init()
        { scrolling=350;
         x=location[rand()%5];}
        //int temp=rand()%Object.size();
        void scroll( int speedObject)
        {
            scrolling+=speedObject;
        }
        bool checkend()
        {
            if(scrolling> STREET_HEIGHT)
            {
                scrolling=-CAR_HEIGHT;
                //temp=rand()%Object.size();
                x=location[rand()%5];
                return true;}
            return false;
        }
        void renderO1(Graphics& graphics)
        {
             texture_o1=graphics.loadTexture("barrier.png");
             graphics.renderTexture(texture_o1,x,scrolling,80,30);
             rect.x=x;
             rect.y=scrolling;
             rect.w=80;
             rect.h=30;

        }
};

struct Object2
{
    SDL_Rect rect;
        SDL_Texture *texture_o2;
        int scrolling,x,temp;
        init()
        {

        scrolling=200;
         x=location[rand()%5];
         temp=rand()%Coin.size();
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
                return true;}
            return false;
        }
        void renderO2(Graphics& graphics)
        {
             texture_o2=graphics.loadTexture(Coin[temp]);
             graphics.renderTexture(texture_o2,x,scrolling,80,80);
             rect.x=x;
             rect.y=scrolling;
             rect.w=80;
             rect.h=80;


        }
};
struct Object3
{
    SDL_Rect rect;
        SDL_Texture *texture_o3;
                int scrolling,x,temp;
        init ()
        {
            scrolling=0;
         x=location[rand()%5];
         temp=rand()%Object.size();
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
                return true;}
            return false;
        }
        void renderO3(Graphics& graphics)
        {
             texture_o3=graphics.loadTexture(Object[temp]);
             graphics.renderTexture(texture_o3,x,scrolling,CAR_WIDTH,CAR_HEIGHT);
             rect.x=x;
             rect.y=scrolling;
             rect.w=CAR_WIDTH;
             rect.h=CAR_HEIGHT;

        }
};
struct Object4
{
    SDL_Rect rect;
        SDL_Texture *texture_o4;
                int scrolling,x,temp;
        init ()
        {

        scrolling=-CAR_HEIGHT-50;
        x=location[rand()%5];
        temp=rand()%Object.size();
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
                return true;}
            return false;
        }
        void renderO4(Graphics& graphics)
        {
             texture_o4=graphics.loadTexture(Object[temp]);
             graphics.renderTexture(texture_o4,x,scrolling,CAR_WIDTH,CAR_HEIGHT);
             rect.x=x;
             rect.y=scrolling;
             rect.w=CAR_WIDTH;
             rect.h=CAR_HEIGHT;

        }
};
struct Object5
{
    SDL_Rect rect;
        SDL_Texture *texture_o5;
                int scrolling,x,temp;
        init()
        {
         scrolling=-2*CAR_HEIGHT-100;
         x=location[rand()%5];
        temp=rand()%Object.size();
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
                return true;}
            return false;
        }
        void renderO5(Graphics& graphics)
        {
             texture_o5=graphics.loadTexture(Object[temp]);
             graphics.renderTexture(texture_o5,x,scrolling,CAR_WIDTH,CAR_HEIGHT);
             rect.x=x;
             rect.y=scrolling;
             rect.w=CAR_WIDTH;
             rect.h=CAR_HEIGHT;

        }

};



#endif // CHARACTERS_H_INCLUDED
