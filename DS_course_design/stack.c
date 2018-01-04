#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void stack_init(Stack *S)
{
    S = (Stack *)malloc(sizeof(Stack));
    S->top = -1;
}

int stack_empty(Stack *S)
{
    if (S->top == -1)
        return 1;
    return 0;
}

void stack_push_in(Stack *S, int data)
{
    if (S->top == MAXLEN)
        return ;
    S->data[++S->top] = data;
}

void stack_pop_out(Stack *S, int *dest)
{
    if (stack_empty(S))
        return ;
    *dest = S->data[--S->top];
}
