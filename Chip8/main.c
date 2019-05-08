#include "cpu.h"
#include "graphics.h"
#include "input.h"
#include <SDL_timer.h>


int main(int argc, char **argv) {
    if (!init_graphics()) {
        return 0;
    }
    init_cpu();
    load_rom("TETRIS");
    while(1){
        render();
        handle_input();
        cycle();
        SDL_Delay(4);  // delay to simulate 60Hz
    }
    
    return 0;
}