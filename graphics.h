#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include <string>

struct ScrollingBackground {
    SDL_Texture* texture;
    int scrollingOffset = 0;

    void scroll(int distance) {
        scrollingOffset += distance;
        if( scrollingOffset > STREET_HEIGHT ) { scrollingOffset = 0; }
    }
};


struct Graphics {
    SDL_Renderer *renderer;
	SDL_Window *window;
    Mix_Chunk* sound = NULL;
	Mix_Music* music = NULL;
	SDL_Texture *play_button,*quit_button,*continue_button;
    bool loadMusic(const char* path)
{
	music = Mix_LoadMUS(path);
	if (music == NULL)
	{
		std::cout << "Load Error";
		return false;
	}

	return true;
}

bool loadSound(const char* path)
{
	sound = Mix_LoadWAV(path);
	if (sound == NULL)
	{
		return false;
	}

	return true;
}

void playMusic()
{
    loadMusic("music.mp3");
	if (music) Mix_PlayMusic(music,-1);
}

void playSound()
{
        loadSound("sound.mp3");
		if (sound) Mix_PlayChannel(-1, sound, 0);

}

void stopMusic()
{
	if (music) Mix_HaltMusic();
}
	void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                        "%s: %s", msg, error);
        SDL_Quit();
    }

	void init() {
	    if( Mix_OpenAudio( 40000, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
   logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                    Mix_GetError() );
}

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());
            //std::cout << "Error: " << SDL_GetError() << std::endl;
        if (TTF_Init() < 0) {
            std::cout << "HELLOO" << std::endl;
        }
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

        play_button=loadTexture("play_button.png");
        quit_button=loadTexture("quit_button.png");
        continue_button=loadTexture("continue_button.png");

    }

	void prepareScene(SDL_Texture * background = nullptr)
    {
        SDL_RenderClear(renderer);
        if (background != nullptr) SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char* filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y, int w, int h)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w=w;
        dest.h=h;

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }

    void quit()
    {
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void render(const ScrollingBackground& background) {
        renderTexture(background.texture,200, background.scrollingOffset,STREET_WIDTH,STREET_HEIGHT);
        renderTexture(background.texture,200, background.scrollingOffset - STREET_HEIGHT ,STREET_WIDTH,STREET_HEIGHT);

    }
    TTF_Font* loadFont(const char* path, int sized)
    {
        TTF_Font* gFont = TTF_OpenFont( path, sized );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
        }
    }
     SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, textColor );

        if( textSurface == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
            std::cerr << "NULL PTR surface" << std::endl;
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
            std::cerr << "NULL PTR TEXTURE" << std::endl;
        }

        SDL_FreeSurface( textSurface );
        return texture;
    }









};

#endif // GRAPHICS_H_INCLUDED
