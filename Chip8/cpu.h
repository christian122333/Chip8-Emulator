#ifndef CPU_H
#define CPU_H

typedef unsigned char BYTE;		
typedef unsigned short WORD;

void initalize(void);
void cycle(void); // Emulate one cycle of the Chip 8 CPU

void fetch(void);
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