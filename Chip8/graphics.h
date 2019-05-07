#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "cpu.h"
extern BYTE screen[64][32]; // stores the data of each pixel

/* initalize all the various SDL subsystems, window, and renderer */
int init_graphics();

/* render the data from the array onto scren */
void render();

/* set all the pixels in the screen to black */
void screen_clear();

/* retreive sprite data from memory and add to screen data */
void screen_draw(int x, int y, int height);
#endif