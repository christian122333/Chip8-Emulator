#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
const int SCREEN_WIDTH = 640;
const int SCEEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *surface = NULL;

bool Init() {
    /* Initialize the various SDL subsystems */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    /* Initialize the window */
    window = SDL_CreateWindow("Chip8", 100, 100, SCREEN_WIDTH, SCEEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    else {
        surface = SDL_GetWindowSurface(window);
    }

    /* Initialize the renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer = NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

int main(int argc, char **argv) {

    if (!Init()){

    }
    
    for (;;) {
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
}