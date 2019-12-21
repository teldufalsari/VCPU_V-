//
// Created by Yngeborga on 19.12.2019.
//

#ifndef ZION_VCPU_VCPU_H
#define ZION_VCPU_VCPU_H

#include "Stack.h"
#include "stdio.h"

enum Commands {PUSH1 = 1, POP0, POP1,  MOV2, CMP2, ADD0, SUB0, MUL0, DIV0, IN0, IN1, OUT0, OUT1, JA, JB, JE, JMP, HLT};

enum Unit_types {CMD = 1, REG, INT, LBL};

char cmp;

short ax;
short bx;
short cx;
short dx;


short cs; // current command code
unsigned short edi; // current command index

struct stack_t Stack;

char* instr;

static char read_cmd ();
static void execute();
static short pick_arg();
static short* pick_addr();

void run(char* code);

#endif //ZION_VCPU_VCPU_H
