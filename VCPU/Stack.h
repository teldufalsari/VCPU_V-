//
// Created by Yngeborga on 19.12.2019.
//

#ifndef ZION_VCPU_STACK_H
#define ZION_VCPU_STACK_H

#include <stdlib.h>

#define CAP 12
#define ST_FULL 5
#define ST_NULLPTR 4
#define ST_EMPTY 3
#define SUCCESS 1

#ifndef ElemT
#define ElemT short
#endif

struct stack_t
{
    ElemT * data;
    size_t size;
    size_t cap;
};

char StackPush (struct stack_t *st_ptr, ElemT value);

char StackPop (struct stack_t *st_ptr);

char StackTop (struct stack_t *st_ptr, ElemT * value);

char StackInit(struct stack_t *st_ptr, size_t capacity);

char StackDestroy(struct stack_t *st_ptr);

#endif //ZION_VCPU_STACK_H
