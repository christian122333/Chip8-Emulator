#include <stdlib.h>
#include "cpu.h"
#include "graphics.h"

BYTE memory[4096]; // Chip8 has 4KB of total memory
BYTE V[16];	// 15 8-bit general purpose registers from V0-VE. The 16th register is used for the 'carry flag'
WORD pc = 0x200; // Program counter
WORD opcode = 0;
WORD I = 0;
BYTE key[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
BYTE delay_timer = 0;
BYTE sound_timer = 0;
WORD stack[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
WORD sp = 0;

void (*chip8Table[16])() = {
    Opcode0, Opcode1, Opcode2, Opcode3,
    Opcode4, Opcode5, Opcode6, Opcode7,
    Opcode8, Opcode9, OpcodeA, OpcodeB,
    OpcodeC, OpcodeD, OpcodeE, OpcodeF,
};
/*	Memory Map
0x000-0x1FF - Chip 8 interpreter
*/

/*
void init_cpu() {
	pc = 0x200;  // Program counter starts at 0x200
	opcode = 0;  // Reset current opcode
	I = 0;       // Reset index register
	sp = 0;      // Reset stack pointer
    // Clear display
    screen_clear();
    // Clear stack
    for (int index = 0; index < 16; index++) {
        stack[index] = 0;
    }
    // Clear
}
*/

void fetch(){
	/* The opcode contains two bytes. Since each address contains one byte, we fetch two successive bytes and merge them to get the opcode */
	opcode = memory[pc] << 8 | memory[pc + 1];
    pc += 2;
}


/* Fetch opcode then decode and execute opcode using the array of function pointers*/
void execute() {
    fetch(); 
    chip8Table[(opcode & 0xF000) >> 12](); // Executes the function based on four most significant bits of the opcode
}

void cycle() {
    execute();
    sound_timer = (sound_timer + 1) % 60;
    delay_timer = (delay_timer + 1) % 60;
}

/* Opcode functions */

void Opcode0(){
    switch (opcode & 0x000F)
    {
    case 0x0000:    //0x00E0 clear the screen
        screen_clear();
        break;
    case 0x000E:    //0x00EE return from subroutine call
        sp--;
        pc = stack[sp];
        stack[sp] = 0;
        break;
    default:      /* Opcode not valid */
        break;
    }
};

void Opcode1(){
    /* 0x1NNN jump to address NNN */
    pc = opcode & 0x0FFF;
};

void Opcode2(){
    /* 0x2NNN jump to subroutine at address NNN */
    stack[sp] = pc;
    sp++;
    pc = opcode & 0x0FFF;
};

void Opcode3(){
    /* 0x3XNN skip next instruction if register V[X] == NN */
    if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
        pc += 2;
};

void Opcode4(){
    /* 0x4XNN skip next instruction if register V[X] != NN */
    if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
        pc += 2;
};

void Opcode5(){
    /* 0x5XY0 skip next instruction if V[X] == V[Y] */
    if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
        pc += 2;
};

void Opcode6(){
    /* 0x6XNN sets V[X] to NN */
    V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
};

void Opcode7(){
    /* 0x7XNN adds NN to V[X] */
    V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
};

void Opcode8(){
    int x, y = 0;
    switch (opcode & 0x000F)
    {   
    case 0x0000:  /* 0x8XY0 sets the V[X] to the value of V[Y] */
        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
        break;
    case 0x0001:  /* 0x8XY1  sets  V[X] to V[X] OR V[Y]*/
        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] | V[(opcode & 0x00F0) >> 4];
        break;
    case 0x0002:  /* 0x8XY2 sets V[X] to V[X] AND V[Y] */
        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] & V[(opcode & 0x00F0) >> 4];
        break;
    case 0x0003:  /* 0x8XY3 sets V[X] to V[X] XOR V[Y] */
        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] ^ V[(opcode & 0x00F0) >> 4];
        break;
    case 0x0004:  /* 0x8XY4 adds V[Y] to V[X]. V[15] is set to 1 when there's a carry, and to 0 when there isn't */
        x = V[(opcode & 0x0F00) >> 8];
        y = V[(opcode & 0x00F0) >> 4];
        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] + V[(opcode & 0x00F0) >> 4];
        if (x + y > 255)
            V[15] = 1;
        else
            V[15] = 0;
        break;
    case 0x0005:  /* 0x8XY5 V[Y] is subtracted from V[X]. V[15] is set to 0 when there's a borrow, and to 1 when there isn't  */
        x = V[(opcode & 0x0F00) >> 8];
        y = V[(opcode & 0x00F0) >> 4];
        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] - V[(opcode & 0x00F0) >> 4];
        if (y > x)
            V[15] = 1;
        else
            V[15] = 0;
        break;
    case 0x0006:  /* 0x8XY6 stores the least significant bit of V[X] in V[15] then shift V[X] to the right by 1*/
        V[15] = V[(opcode & 0x0F00) >> 8] & 0x0001;
        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] >> 1;
        break;
    case 0x0007:  /* 0x8XY7 sets V[X] to V[Y] minus V[X]. V[15] is set to 0 when there's a borrow, and 1 when there isn't */
        x = V[(opcode & 0x0F00) >> 8];
        y = V[(opcode & 0x00F0) >> 4];
        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
        if (x > y)
            V[15] = 1;
        else
            V[15] = 0;
        break;
    case 0x000E:  /* 0x8XYE stores the most significant bit of V[X] in V[15] then shift V[X] to the left by 1 */
        V[15] = V[(opcode & 0x0F00) >> 8] & 0x8000;
        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] << 1;
        break;
    default:      /* Opcode not valid */
        break;
    }
};

void Opcode9(){
    /* 0x9XY0 skips the next instruction if V[X] doesn't equal V[Y] */
    if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
        pc += 2;
};

void OpcodeA(){
    /* 0xANNN sets I to the address NNN */
    I = opcode & 0x0FFF;
};

void OpcodeB(){
    /* 0xBNNN jumps to the address NNN plus V[0] */
    pc = V[0] + (opcode & 0x0FFF);
};

void OpcodeC(){
    /* 0xCXNN sets V[X] to the result of a bitwise AND operation on random number(0 to 255) and NN */
    V[(opcode & 0x0F00) >> 8] = (rand() % 256) & (opcode & 0x00FF);
};

void OpcodeD(){
    /* 0xDXYN draws a sprite coordinate (V[X], V[Y]) that has the width of 8 pixels and a height of N pixels */
    screen_draw(V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4], opcode & 0x000F);
};

void OpcodeE(){
    switch (opcode & 0x000F) 
    {
    case 0x000E: /* 0xEX9E skips the next instruction if the key stores in V[X] is pressed */
        if (key[(opcode & 0x0F00) >> 8] == 1)
            pc += 2;
        break;
    case 0x0001: /* 0xEXA1 skips the next instruction if the key stored in V[X] isn't pressed */
        if (key[(opcode & 0x0F00) >> 8] == 0)
            pc += 2;
        break;
    }
};

void OpcodeF(){
    switch (opcode & 0x00FF)
    {
    case 0x0007: /* 0xFX07 sets V[X] to the value of the delay timer */
        V[(opcode & 0x0F00) >> 8] = delay_timer;
        break;
    case 0x000A: /* 0xFX0A a key press is awaited, and then stored in V[X] */
        waitKey((opcode & 0x0F00) >> 8);
        break;
    case 0x0015: /* 0xFX15 sets the delay timer to V[X] */
        delay_timer = V[(opcode & 0x0F00) >> 8];
        break;
    case 0x0018: /* 0xFX18 sets the sound timer to V[X] */
        sound_timer = V[(opcode & 0x0F00) >> 8];
        break;
    case 0x001E: /* 0xFX1E adds V[X] to I */
        I += V[(opcode & 0x0F00) >> 8];
        break;
    case 0x0029: /* 0xFX29 sets I to the location of the sprite for the character in V[X] */
        I = V[(opcode & 0x0F00) >> 8];
        break;
    case 0x0033: /* 0xFX33 stores the binary-coded decimal representation of V[X] */
        memory[I] = V[(opcode & 0x0F00) >> 8] / 100;           // hundrends
        memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10; // tens
        memory[I + 2] = V[(opcode & 0x0F00) >> 8] % 10;        // ones
        break;
    case 0x0055: /* 0xFX55 stores V[0] to V[X] in memory starting at address I */
        for (int n = 0; n <= (opcode & 0x0F00) >> 8; n++) {
            memory[I + n] = V[n];
        }
        break;
    case 0x0065: /* 0xFX65 fills V[0] to V[X] with values from memory starting at address I */
        for (int n = 0; n <= (opcode & 0x0F00) >> 8; n++) {
            V[n] = memory[I + n];
        }
        break;
    default:    /* Opcode not valid */
        break;
    }
};

