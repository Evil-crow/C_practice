#ifndef _STACK_H
#define _STACK_H
#define MAXLEN 20

typedef struct {
    int data[MAXLEN];
    int top;
}Stack;

void stack_init(Stack *S);

int stack_empty(Stack *S);

void stack_push_in(Stack *S, int data);

void stack_pop_out(Stack *S, int *dest);

#endif
