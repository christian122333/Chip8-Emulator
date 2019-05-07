#include "SDL.h"
#include <stdio.h>
#include "graphics.h"


const int SCREEN_BPP = 32;
BYTE screen[64][32];

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int init_graphics() {
    /* Initialize the various SDL subsystems */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 0;
    }

    /* Initialize the window */
    window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 240, 240, 0);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    /* Initialize the renderer */
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    for (int row = 0; row < 32; row++) {
        for (int column = 0; column < 64; column++) {
            if (screen[column][row] = 1) {
                SDL_RenderDrawPoint(renderer, column, row);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void screen_clear(){
    for (int row = 0; row < 32; row++) {
        for (int column = 0; column < 64; column++) {
            screen[column][row] = 0;
        }
    }
}

void screen_draw(int x, int y, int height) {
    BYTE data, shift, mask;
    V[15] = 0; // set carry flag to 0
    for (BYTE row = 0; row < height; row++) {
        data = memory[I + row];
        shift = 7;
        mask = 1;
        for (BYTE column = 0; column < 8; column++, shift--) {
            /* retrieve sprite BYTE data from address and mask each bit. If the bit is 1, then toggle to the pixel on the screen */
            mask = mask << shift;
            if (data & mask) {
                if (screen[x + column][y + row] == 1) {
                    V[15] = 1; // If there's a bit already set to 1 in the pixel then set the carry flag to 1 because a collision occured
                }
                screen[x + column][y + row] ^= 1;
            }
        }
    }
}
