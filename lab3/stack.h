#ifndef STACK_H
#define STACK_H

typedef struct StackNode {
    void *data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} Stack;


void initStack(Stack *s);


int isEmpty(Stack *s);


void push(Stack *s, void *data);


void* pop(Stack *s);


void *peek(Stack *s);


void freeStack(Stack *s);

#endif
