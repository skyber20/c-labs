#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void initStack(Stack *s) {
    s->top = NULL;
}


int isEmpty(Stack *s) {
    return s->top == NULL;
}


void push(Stack *s, void *data) {
    StackNode *newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
}


void* pop(Stack *s) {
    if (!s->top) return NULL;
    StackNode *curTop = s->top;
    void *poppedData = curTop->data;
    s->top = s->top->next;
    free(curTop);
    return poppedData;
}


void *peek(Stack *s) {
    if (!s->top) return NULL;
    return s->top->data;
}


void freeStack(Stack *s) {
    if (!s) return;

    while (s->top) {
        StackNode *tmp = s->top;
        s->top = s->top->next;
        free(tmp);
    }
}
