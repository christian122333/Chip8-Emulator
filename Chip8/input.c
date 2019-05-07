#include "input.h"
#include "SDL_events.h"

enum KeyPress {
    KEY_PRESS_1, KEY_PRESS_2, KEY_PRESS_3, KEY_PRESS_4,
    KEY_PRESS_Q, KEY_PRESS_W, KEY_PRESS_E, KEY_PRESS_R,
    KEY_PRESS_A, KEY_PRESS_S, KEY_PRESS_D, KEY_PRESS_F,
    KEY_PRESS_Z, KEY_PRESS_X, KEY_PRESS_C, KEY_PRESS_V,
};

SDL_Event e;

void handleInput() {
    while (SDL_PollEvent(&e)) {
        /* Key was pressed */
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym)
            {
            case SDLK_1:
                key[KEY_PRESS_1] = 1;
                break;
            case SDLK_2:
                key[KEY_PRESS_2] = 1;
                break;
            case SDLK_3:
                key[KEY_PRESS_3] = 1;
                break;
            case SDLK_4:
                key[KEY_PRESS_4] = 1;
                break;
            case SDLK_q:
                key[KEY_PRESS_Q] = 1;
                break;
            case SDLK_w:
                key[KEY_PRESS_W] = 1;
                break;
            case SDLK_e:
                key[KEY_PRESS_E] = 1;
                break;
            case SDLK_r:
                key[KEY_PRESS_R] = 1;
                break;
            case SDLK_a:
                key[KEY_PRESS_A] = 1;
                break;
            case SDLK_s:
                key[KEY_PRESS_S] = 1;
                break;
            case SDLK_d:
                key[KEY_PRESS_D] = 1;
                break;
            case SDLK_f:
                key[KEY_PRESS_F] = 1;
                break;
            case SDLK_z:
                key[KEY_PRESS_Z] = 1;
                break;
            case SDLK_x:
                key[KEY_PRESS_X] = 1;
                break;
            case SDLK_c:
                key[KEY_PRESS_C] = 1;
                break;
            case SDLK_v:
                key[KEY_PRESS_V] = 1;
                break;
            }
        }
        
        /* Key was released */
        if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym)
            {
            case SDLK_1:
                key[KEY_PRESS_1] = 0;
                break;
            case SDLK_2:
                key[KEY_PRESS_2] = 0;
                break;
            case SDLK_3:
                key[KEY_PRESS_3] = 0;
                break;
            case SDLK_4:
                key[KEY_PRESS_4] = 0;
                break;
            case SDLK_q:
                key[KEY_PRESS_Q] = 0;
                break;
            case SDLK_w:
                key[KEY_PRESS_W] = 0;
                break;
            case SDLK_e:
                key[KEY_PRESS_E] = 0;
                break;
            case SDLK_r:
                key[KEY_PRESS_R] = 0;
                break;
            case SDLK_a:
                key[KEY_PRESS_A] = 0;
                break;
            case SDLK_s:
                key[KEY_PRESS_S] = 0;
                break;
            case SDLK_d:
                key[KEY_PRESS_D] = 0;
                break;
            case SDLK_f:
                key[KEY_PRESS_F] = 0;
                break;
            case SDLK_z:
                key[KEY_PRESS_Z] = 0;
                break;
            case SDLK_x:
                key[KEY_PRESS_X] = 0;
                break;
            case SDLK_c:
                key[KEY_PRESS_C] = 0;
                break;
            case SDLK_v:
                key[KEY_PRESS_V] = 0;
                break;
            }
        }
    }
}


void waitKey(BYTE index) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym)
            {
            case SDLK_1:
                key[KEY_PRESS_1] = 1;
                V[index] = KEY_PRESS_1;
                return;
            case SDLK_2:
                key[KEY_PRESS_2] = 1;
                V[index] = KEY_PRESS_2;
                return;
            case SDLK_3:
                key[KEY_PRESS_3] = 1;
                V[index] = KEY_PRESS_3;
                return;
            case SDLK_4:
                key[KEY_PRESS_4] = 1;
                V[index] = KEY_PRESS_4;
                return;
            case SDLK_q:
                key[KEY_PRESS_Q] = 1;
                V[index] = KEY_PRESS_Q;
                return;
            case SDLK_w:
                key[KEY_PRESS_W] = 1;
                V[index] = KEY_PRESS_W;
                return;
            case SDLK_e:
                key[KEY_PRESS_E] = 1;
                V[index] = KEY_PRESS_E;
                return;
            case SDLK_r:
                key[KEY_PRESS_R] = 1;
                V[index] = KEY_PRESS_R;
                return;
            case SDLK_a:
                key[KEY_PRESS_A] = 1;
                V[index] = KEY_PRESS_A;
                return;
            case SDLK_s:
                key[KEY_PRESS_S] = 1;
                V[index] = KEY_PRESS_S;
                return;
            case SDLK_d:
                key[KEY_PRESS_D] = 1;
                V[index] = KEY_PRESS_D;
                return;
            case SDLK_f:
                key[KEY_PRESS_F] = 1;
                V[index] = KEY_PRESS_F;
                return;
            case SDLK_z:
                key[KEY_PRESS_Z] = 1;
                V[index] = KEY_PRESS_Z;
                return;
            case SDLK_x:
                key[KEY_PRESS_X] = 1;
                V[index] = KEY_PRESS_X;
                return;
            case SDLK_c:
                key[KEY_PRESS_C] = 1;
                V[index] = KEY_PRESS_C;
                return;
            case SDLK_v:
                key[KEY_PRESS_V] = 1;
                V[index] = KEY_PRESS_V;
                return;
            }
        }
    }
}