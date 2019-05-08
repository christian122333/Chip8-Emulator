#include "SDL.h"
#include <stdio.h>
#include "graphics.h"


const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 384;
BYTE screen[64][32];
extern BYTE draw_flag = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Rect rect;
int x_scale;
int y_scale;

BYTE chip8_font[80] = {
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

int init_graphics() {
    /* Initialize the various SDL subsystems */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 0;
    }

    /* Initialize the window */
    window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
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
   /* the chip8 is originally 64x32. To make the screen bigger, an x and y scale factor are initalized to determine where to place the pixels on the bigger screen */
    x_scale = SCREEN_WIDTH / 64;
    y_scale = SCREEN_HEIGHT / 32;
    /* the rect acts a bigger pixel. The width and height are increased by their respective scaling factor */
    rect.w = x_scale;
    rect.h = y_scale;

    return 1;
}

void render() {
    if (draw_flag) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        for (int row = 0; row < 32; row++) {
            for (int column = 0; column < 64; column++) {
                if (screen[column][row] == 1) {
                    rect.x = x_scale * column;
                    rect.y = y_scale * row;
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
    draw_flag = 0;
}

void screen_clear(){
    for (int row = 0; row < 32; row++) {
        for (int column = 0; column < 64; column++) {
            screen[column][row] = 0;
        }
    }
    draw_flag = 1;
}

void screen_draw(int x, int y, int height) {
    BYTE data, shift, mask;
    V[15] = 0; // set carry flag to 0
    for (BYTE row = 0; row < height; row++) {
        data = memory[I + row];
        shift = 7;
        for (BYTE column = 0; column < 8; column++, shift--) {
            /* retrieve sprite BYTE data from address and mask each bit. If the bit is 1, then toggle to the pixel on the screen */
            mask = 1 << shift;
            if (data & mask) {
                if (screen[x + column][y + row] == 1) {
                    V[15] = 1; // If there's a bit already set to 1 in the pixel then set the carry flag to 1 because a collision occured
                }
                screen[x + column][y + row] ^= 1;
            }
        }
    }
    draw_flag = 1;
}
