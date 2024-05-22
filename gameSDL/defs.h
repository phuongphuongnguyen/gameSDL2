#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define WINDOW_TITLE "canh sat tuan tra"
#define INITIAL_SPEED 10

#define STREET_HEIGHT 800
#define STREET_WIDTH 800

#define CAR_HEIGHT 150
#define CAR_WIDTH 80
#define BACKGROUND_IMG "street.png"
#define main_character "police.png"
#define PLAY_BUTTON "play_button"
#define QUIT_BUTTON "quit_button"
const SDL_Rect playButton{450,300,300,100};
const SDL_Rect quitButton{450,420,300,100};
const SDL_Rect continueButton{450,350,300,100};
const SDL_Rect audioButton{200,0,50,50};
const int location[]={260,410,560,710,860};


const std::vector<const char*> Object={"car1.png","car2.png","car3.png","truck1.png","truck2.png"};
const std::vector<const char*> Coin={"coin1.png","coin5.png","coin10.png"};

const SDL_Color color = {255, 255, 255, 255};
const SDL_Color color_black={0,0,0,0};



#endif
