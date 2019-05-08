#ifndef INPUT_H
#define INPUT_H

#include "cpu.h"

/* polls through an event queue to set the state of a key if its pressed or released */
void handle_input();

/* loops through the state of all the keys to check if a key is pressed and return the index for that key */
int wait_key();


#endif // !1

