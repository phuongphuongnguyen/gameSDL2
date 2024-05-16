#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "graphics.h"
#include "defs.h"
#include "characters.h"

using namespace std;
void getHighscore(int point, int &best)
{
	if (point> best)
	{
		best = point;
	}
	fstream file("Poin.txt");
	file<<best;
	file.close();
}
void Highscore(int &best)
{
	fstream file("Poin.txt");
	file >> best;
	file.close();
}

int main(int argc, char *argv[])
{

    srand(time(NULL));
    Graphics graphics;
    graphics.init();

    ScrollingBackground background;
    background.texture=graphics.loadTexture(BACKGROUND_IMG);
    Character character;
    Object1 object1;
    Object2 object2;
    Object3 object3;
    Object4 object4;
    Object5 object5;
    TTF_Font* font = graphics.loadFont("font.ttf", 100);
    graphics.playMusic();

    SDL_Color color = {255, 255, 255, 255};




    bool quit = false;
    SDL_Event e;
    srand(time(NULL));
    int point;
    int best=0;
    Highscore(best);
    bool play=false;
    bool menu=true;
    int x,y;

    while( !quit ) {
            while (menu)
            {
                point=0;
                character.init();
                object1.init();
                object2.init();
                object3.init();
                object4.init();
                object5.init();
                background.scroll(1);
                graphics.render(background);

                character.renderMain(character,graphics);
                graphics.renderTexture(graphics.play_button,playButton.x,
                                       playButton.y,playButton.w,playButton.h);
                graphics.renderTexture(graphics.quit_button,quitButton.x,
                                       quitButton.y,quitButton.w,quitButton.h);
                 graphics.presentScene();
                 if(SDL_PollEvent(&e)){
                 switch (e.type)

           {
           case SDL_QUIT:
               menu=false;
               quit=true;
               break;
           case SDL_MOUSEBUTTONDOWN:
               SDL_GetMouseState(&x, &y);
               cerr << "Mouse-down at (" << x << ", " << y << ")\n";
               if (inside(x,y,playButton))
                 {
                     SDL_RenderClear(graphics.renderer);
                     menu=false;
                     play=true;

                 }
                if (inside(x,y,quitButton))
                {
                    menu=false;
                    quit=true;
                }
                 break;
           }}



            }

    while(play)
     {
                background.scroll(10);
                graphics.render(background);
         while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_KEYDOWN:
                    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                    if (character.dx==0)
                   {

                    if (currentKeyStates[SDL_SCANCODE_LEFT]) character.turnLeft();
                    if (currentKeyStates[SDL_SCANCODE_RIGHT]) character.turnRight();
                   }
                   if (currentKeyStates[SDL_SCANCODE_SPACE])
                    {
                        bool pause=true;
                        while(pause)
                        {
                        object5.renderO5(graphics);
                        object4.renderO4(graphics);
                        object3.renderO3(graphics);
                        object2.renderO2(graphics);
                        object1.renderO1(graphics);
                        character.renderMain(character,graphics);
                        graphics.renderTexture(graphics.continue_button,continueButton.x,continueButton.y,
                                               continueButton.w,continueButton.h);
                        graphics.presentScene();
                        SDL_Event event;

                        if(SDL_PollEvent(& event) && event.type==SDL_KEYDOWN &&currentKeyStates[SDL_SCANCODE_SPACE]) pause=false;
                        if(SDL_PollEvent(&event) && event.type==SDL_QUIT) exit(0);
                        if(SDL_PollEvent(&event)&& event.type==SDL_MOUSEBUTTONDOWN)
                        {
                            SDL_GetMouseState(&x, &y);
                            if (inside(x,y,continueButton)) pause=false;
                            SDL_RenderClear(graphics.renderer);


                        }
                        }
                    }

                   break;
            }

        }

        if(!object1.checkend())
        {

        object1.renderO1(graphics);
        object1.scroll(10);
        if(overlap(character.rect,object1.rect))
        {
            play=false;
            menu=true;
        }
        }

        if(!object2.checkend())
        {

        object2.renderO2(graphics);
        object2.scroll(10);
        if(overlap(character.rect,object2.rect))
        {
            graphics.playSound();
            if(object2.temp==0) point+=1;
            else if(object2.temp==1) point+=5;
            else point+=10;
            object2.scrolling=STREET_HEIGHT;
        }


        }
        if(!object3.checkend())
        {

        object3.renderO3(graphics);
        object3.scroll(10);
        if(overlap(character.rect,object3.rect)) {play=false;menu=true;}
        }
        if(!object4.checkend())
        {

        object4.renderO4(graphics);
        object4.scroll(10);
        if(overlap(character.rect,object4.rect)) {play=false; menu=true;}
        }
         if(!object5.checkend())
        {

        object5.renderO5(graphics);
        object5.scroll(10);
        if(overlap(character.rect,object5.rect)) {play=false;menu=true;}
        }


        character.moved();
        character.renderMain(character,graphics);

        const char * Text=to_string(point).c_str();

        SDL_Texture* pointText= graphics.renderText(Text, font, color);
        graphics.renderTexture(pointText, 0, 0,100,100);
        getHighscore(point,best);
        Highscore(best);
        const char* Best= to_string(best).c_str();

        SDL_Texture* bestPoint= graphics.renderText(Best,font,color);
        graphics.renderTexture(bestPoint, 0,200,100,100);
        SDL_DestroyTexture(bestPoint);
        SDL_DestroyTexture(pointText);
        graphics.presentScene();
        SDL_RenderClear(graphics.renderer);
        SDL_Delay(20);
     }

    }

    SDL_DestroyTexture(background.texture );
    SDL_DestroyTexture(object1.texture_o1);
    SDL_DestroyTexture(object2.texture_o2);
    SDL_DestroyTexture(object3.texture_o3);
    SDL_DestroyTexture(object4.texture_o4);
    SDL_DestroyTexture(object5.texture_o5);

    TTF_CloseFont( font );
    graphics.quit();
    return 0;
}
