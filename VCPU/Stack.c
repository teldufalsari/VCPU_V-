//
// Created by Yngeborga on 19.12.2019.
//

#include "Stack.h"

char StackPush (struct stack_t *st_ptr, ElemT value) {
    if (st_ptr == NULL)
        return ST_NULLPTR;

    if (st_ptr->size >= CAP)
        return ST_FULL;

    st_ptr->data[st_ptr->size++] = value;
    return SUCCESS;
}

char StackPop (struct stack_t *st_ptr) {
    if (st_ptr == NULL)
        return ST_NULLPTR;

    if (st_ptr->size == 0)
        return ST_EMPTY;

    st_ptr->size--;
    return SUCCESS;
}

char StackTop (struct stack_t *st_ptr, ElemT * value) {
    if (st_ptr == NULL)
        return ST_NULLPTR;

    if (st_ptr->size == 0)
        return ST_EMPTY;

    *value = st_ptr->data[st_ptr->size - 1];
    return SUCCESS;
}

char StackInit(struct stack_t *st_ptr, size_t capacity) {
    if (st_ptr == NULL)
        return ST_NULLPTR;
    if (capacity == 0)
        return ST_EMPTY;

    st_ptr->cap = capacity;
    st_ptr->data = calloc(capacity, sizeof(ElemT));
    st_ptr->size = 0;
    return SUCCESS;
}

char StackDestroy(struct stack_t *st_ptr) {
    if (st_ptr == NULL)
        return ST_NULLPTR;

    free(st_ptr->data);
    st_ptr->size = 0;
    st_ptr->cap = 0;
    return SUCCESS;
}
