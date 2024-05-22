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
    background.texture=loadTexture(BACKGROUND_IMG);
    Character character;
    Object1 object1;
    Object2 object2;
    Object3 object3;
    Object3 object4;
    Object3 object5;
    TTF_Font* font = graphics.loadFont("times new roman.ttf", 75);

    bool quit = false;
    SDL_Event e;
    int point;
    int best=0;
    Highscore(best);
    bool play=false;
    int menu=1;
    int x,y;
    string yourscore,highscore;
    SDL_Rect pointTextRect, bestPointRect;
    clock_t start;

    double speed;
    while( !quit )
    {
        point=0;
        speed=0;
        character.init();
        object1.init();
        object2.init();
        object3.init(-240);
        object4.init(-600);
        object5.init(30);
        background.scroll(1);
        while (menu==1 or menu==2)
        {
            graphics.render(background);
            character.renderMain(character);
            renderTexture(graphics.play_button,playButton.x,
                                       playButton.y,playButton.w,playButton.h);
            renderTexture(graphics.quit_button,quitButton.x,
                                       quitButton.y,quitButton.w,quitButton.h);
            renderTexture(graphics.audio_button,200,0,50,50);

            if (menu==2)
            {


                pointTextRect = {450,200 ,300,70};
                graphics.renderText(yourscore.c_str(), font, color_black, &pointTextRect);
                bestPointRect = {450,130,300,70};
                graphics.renderText(highscore.c_str(),font,color_black,&bestPointRect);

            }
            graphics.presentScene();
            if(SDL_PollEvent(&e)){
                 switch (e.type)
           {
           case SDL_QUIT:
               {
               menu=0;
               quit=true;
               break;
               }
           case SDL_MOUSEBUTTONDOWN:
               {
               SDL_GetMouseState(&x, &y);
               cerr << "Mouse-down at (" << x << ", " << y << ")\n";
               if (inside(x,y,playButton))
                {
                    SDL_RenderClear(renderer);
                    menu=0;
                    play=true;
                    start = clock();
                }
                if (inside(x,y,quitButton))
                {
                    menu=0;
                    quit=true;
                }

                if (inside(x,y,audioButton))
                {
                   if(graphics.music==NULL)  graphics.playMusic();
                   else {graphics.stopMusic(); graphics.music=NULL;}

                }
                break;
               }
           }
        }
    }

    while(play)
    {
        background.scroll(10+speed);
        graphics.render(background);
        renderTexture(graphics.audio_button,200,0,50,50);

        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x, &y);
                    cerr << x << " " << y << "\n";
                    if (inside(x,y,audioButton))
                    {
                        if(graphics.music==NULL)  graphics.playMusic();
                        else { graphics.stopMusic();graphics.music=NULL;}
                    }
                    break;

                case SDL_KEYDOWN:
                {
                    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                    if (character.dx==0)
                    {

                    if (currentKeyStates[SDL_SCANCODE_LEFT]) character.turnLeft();
                    if (currentKeyStates[SDL_SCANCODE_RIGHT]) character.turnRight();
                    if (currentKeyStates[SDL_SCANCODE_UP]) speed+=2;
                    if (currentKeyStates[SDL_SCANCODE_DOWN]) {speed-=2; if (speed<-8) speed+=2;}
                    }
                    if (currentKeyStates[SDL_SCANCODE_SPACE])
                    {
                        bool pause=true;
                        while(pause)
                        {
                        graphics.render(background);
                        object5.render();
                        object4.render();
                        object3.render();
                        object2.render();
                        object1.render();
                        character.renderMain(character);
                        renderTexture(graphics.continue_button,continueButton.x,continueButton.y,
                                               continueButton.w,continueButton.h);

                        graphics.presentScene();
                        SDL_Event event;
                        SDL_PollEvent(&event);

                        if( event.type==SDL_KEYDOWN &&currentKeyStates[SDL_SCANCODE_SPACE]) pause=false;
                        if( event.type==SDL_QUIT) exit(0);
                        if(event.type== SDL_MOUSEBUTTONDOWN)
                        {
                            SDL_GetMouseState(&x, &y);
                            cerr<<x<<" "<<y<<endl;
                            if (inside(x,y,continueButton)) pause=false;
                            SDL_RenderClear(renderer);
                        }
                        }
                    }

                  break;
                }
            }

        }

        if(!object1.checkend())
        {
            object1.render();
            object1.scroll(10+speed-1);
            if(overlap(character.rect,object1.rect)){play=false; menu=2;}
        }

        if(!object2.checkend())
        {
            object2.render();
            object2.scroll(10+speed-1);
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
            object3.render();
            object3.scroll(10+speed-1);
            if(overlap(character.rect,object3.rect)) {play=false;menu=2;}
        }

        if(!object4.checkend())
        {
            object4.render();
            object4.scroll(10+speed-1);
            if(overlap(character.rect,object4.rect)) {play=false; menu=2;}
        }

         if(!object5.checkend())
        {
            object5.render();
            object5.scroll(10+speed-1);
            if(overlap(character.rect,object5.rect)) {play=false;menu=2;}
        }

        character.moved();
        character.renderMain(character);

        yourscore="Your score: "+to_string(point);
        pointTextRect = {0, 50,195,50};
        graphics.renderText(yourscore.c_str(), font, color, &pointTextRect);

        getHighscore(point,best);
        Highscore(best);
        highscore= "High score: "+ to_string(best);
        bestPointRect = {0,0,195,50};
        graphics.renderText(highscore.c_str(),font,color,&bestPointRect);

        graphics.presentScene();
        SDL_RenderClear(renderer);
        SDL_Delay(20);
        clock_t endtime = clock();
        if ((double)(endtime - start)/CLOCKS_PER_SEC>2) {speed+=0.5; start = clock();}
     }
    }


    SDL_DestroyTexture(background.texture );
    SDL_DestroyTexture(character.texture);
    SDL_DestroyTexture(object1.texture);
    SDL_DestroyTexture(object2.texture);
    SDL_DestroyTexture(object3.texture);
    SDL_DestroyTexture(object4.texture);
    SDL_DestroyTexture(object5.texture);

    TTF_CloseFont( font );
    graphics.quit();
    return 0;
}
