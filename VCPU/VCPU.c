//
// Created by Yngeborga on 19.12.2019.
//

#include "VCPU.h"

char read_cmd ()
{
    if (instr[edi++] != CMD)
        return 1;

    ((char*) &cs)[0] = instr[edi++];
    ((char*) &cs)[1] = instr[edi++];

    if (cs == HLT)
        return 1;

    execute();
    return 0;
}

void execute ()
{
    switch (cs)
    {
        case PUSH1:
        {
            StackPush(&Stack, pick_arg());
            break;
        }

        case POP0:
        {
            StackPop(&Stack);
            break;
        }

        case POP1:
        {
            StackTop(&Stack, pick_addr());
            StackPop(&Stack);
            break;
        }

        case ADD0:
        {
            short arg1, arg2;

            StackTop(&Stack, &arg2);
            StackPop(&Stack);

            StackTop(&Stack, &arg1);
            StackPop(&Stack);

            StackPush(&Stack, arg1 + arg2);
            break;
        }

        case SUB0:
        {
            short arg1, arg2;

            StackTop(&Stack, &arg2);
            StackPop(&Stack);

            StackTop(&Stack, &arg1);
            StackPop(&Stack);

            StackPush(&Stack, arg1 - arg2);
            break;
        }

        case MUL0:
        {
            short arg1, arg2;

            StackTop(&Stack, &arg2);
            StackPop(&Stack);

            StackTop(&Stack, &arg1);
            StackPop(&Stack);

            StackPush(&Stack, arg1 * arg2);
            break;
        }

        case DIV0:
        {
            short arg1, arg2;

            StackTop(&Stack, &arg2);
            StackPop(&Stack);

            StackTop(&Stack, &arg1);
            StackPop(&Stack);

            StackPush(&Stack, arg1 / arg2);
            break;
        }

        case MOV2:
        {
            short *dst = pick_addr();
            *dst = pick_arg();
            break;
        }

        case CMP2:
        {
            short d = pick_arg();
            d -= pick_arg();

            if (d > 0)
                cmp = 1;
            else if (d == 0)
                cmp = 0;
            else
                cmp = -1;

            break;
        }

        case IN1:
        {
            *(pick_addr()) = getchar();
            break;
        }

        case IN0:
        {
            short in = getchar();

            StackPush(&Stack, in);

            break;
        }

        case OUT0:
        {
            short out;

            StackTop(&Stack, &out);
            StackPop(&Stack);

            putchar(out);
            break;
        }

        case OUT1:
        {
            putchar(pick_arg());
            break;
        }

        case JMP:
        {
            edi = (unsigned short) pick_arg();
            break;
        }

        case JE:
        {
            if (cmp == 0)
                edi = (unsigned short) pick_arg();
            else
                edi += 3;

            break;
        }

        case JA:
        {
            if (cmp == 1)
                edi = (unsigned short) pick_arg();
            else
                edi += 3;

            break;
        }

        case JB:
        {
            if (cmp == -1)
                edi = (unsigned short) pick_arg();
            else
                edi += 3;

            break;
        }

        default:
            return;
    }
}

short pick_arg()
{
    switch (instr[edi])
    {
        case REG:
        {
            return *pick_addr();
        }

        case INT:
        {
            edi++;

            short arg = 0;

            *(((char*) &arg) + 0) = instr[edi++];
            *(((char*) &arg) + 1) = instr[edi++];

            return arg;
        }

        case LBL:
        {
            edi++;

            short arg = 0;

            *(((char*) &arg) + 0) = instr[edi++];
            *(((char*) &arg) + 1) = instr[edi++];

            return arg;
        }
        default:
            return 0;
    }
}

short* pick_addr()
{
    if (instr[edi++] != REG)
        return NULL;

    short reg_n = 0;

    *(((char*) &reg_n) + 0) = instr[edi++];
    *(((char*) &reg_n) + 1) = instr[edi++];

    switch (reg_n)
    {
        case 1:
            return &ax;

        case 2:
            return &bx;

        case 3:
            return &cx;

        case 4:
            return &dx;

        default:
            return NULL;
    }
}

void run (char* code)
{
    instr = code;

    StackInit(&Stack, 4096);

    ax = cx = bx = dx = 0;
    cmp = 0;
    cs = 0;
    edi = 0;

    while (!read_cmd())
        ;

    StackDestroy(&Stack);
}