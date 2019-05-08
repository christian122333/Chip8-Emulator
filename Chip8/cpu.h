#ifndef CPU_H
#define CPU_H

typedef unsigned char BYTE;		
typedef unsigned short WORD;

extern BYTE memory[4096];
extern BYTE V[16];
extern BYTE key[16];
extern WORD I;  // Index register

/* initalize various variables of the cpu, clears screen, stack and key, and loads chip8 font data into memory at 0x00 */
void init_cpu(void);

/* loads each byte of the game program into memory starting at 0x200 */
void load_rom(char *filename);

/* emulate one cycle of the Chip 8 CPU */
void cycle(void); 

/* retrieves two bytes from two consecutive addresses and increments pc by 2 */
void fetch(void);

/* decodes the opcode and then executes it */
void execute(void);


typedef void(*functionPointers[16])(void);

/*op code functions */
void Opcode0();
void Opcode1();
void Opcode2();
void Opcode3();
void Opcode4();
void Opcode5();
void Opcode6();
void Opcode7();
void Opcode8();
void Opcode9();
void OpcodeA();
void OpcodeB();
void OpcodeC();
void OpcodeD();
void OpcodeE();
void OpcodeF();
#endif // !1