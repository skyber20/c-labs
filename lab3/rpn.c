#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "stack.h"


int getPriority(char oper) {
    switch (oper) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        case '~':
            return 4;
        default:
            return 0;
    }
}


int isRightAssoc(char oper) {
    return (oper == '^' || oper == '~');
}


void appendToExitQueue(Token *t, Token **postfixHead, Token **postfixTail) {
    t->next = NULL;
    if (!(*postfixHead)) {
        *postfixHead = *postfixTail = t;
    } else {
        (*postfixTail)->next = t;
        *postfixTail = t;
    }
}


Token *toRPN(Token *infixHead) {
    Token *postfixHead = NULL;
    Token *postfixTail = NULL;
    Stack OpStack;
    initStack(&OpStack);

    Token *curToken = infixHead;
    while (curToken) {
        Token *nextToken = curToken->next;

        if (curToken->type == TOK_NUM || curToken->type == TOK_VAR) {
            appendToExitQueue(curToken, &postfixHead, &postfixTail);
        }

        else if (curToken->type == TOK_LBRACKET) {
            push(&OpStack, curToken);
        }

        else if (curToken->type == TOK_RBRACKET) {
            while (1) {
                if (isEmpty(&OpStack)) {
                    printf("Была пропущена открывающая скобка");
                    freeTokens(postfixHead);
                    free(curToken);
                    return NULL;
                }

                Token *t = (Token*)pop(&OpStack);
                if (t->type == TOK_LBRACKET) {
                    free(t);
                    break;
                }

                appendToExitQueue(t, &postfixHead, &postfixTail);
            }
            free(curToken);
        }

        else if (curToken->type == TOK_OP) {
            Token *op1 = curToken;
            int p1 = getPriority(op1->data.op);

            while (!isEmpty(&OpStack)) {
                Token *op2 = peek(&OpStack);

                if (op2->type == TOK_LBRACKET) break;

                int p2 = getPriority(op2->data.op);

                if (p2 > p1 || (p2 == p1 && !isRightAssoc(op1->data.op))) {
                    appendToExitQueue((Token*)pop(&OpStack), &postfixHead, &postfixTail);
                } else break;
            }

            push(&OpStack, op1);
        }

        curToken = nextToken;
    }

    while (!isEmpty(&OpStack)) {
        Token *t = (Token*)pop(&OpStack);
        if (t->type == TOK_LBRACKET) {
            printf("Была пропущена открывающая скобка");
            freeTokens(postfixHead);
            return NULL;
        }
        appendToExitQueue(t, &postfixHead, &postfixTail);
    }

    freeStack(&OpStack);
    return postfixHead;
}


void printRPNLinear(Token *headPostfix) {
    Token *curToken = headPostfix;

    while (curToken) {
        if (curToken->type == TOK_NUM) {
            printf("%d ", curToken->data.value);
        } else if (curToken->type == TOK_VAR) {
            printf("%s ", curToken->data.varName);
        } else if (curToken->type == TOK_OP) {
            printf("%c ", curToken->data.op);
        }
        curToken = curToken->next;
    }

    printf("\n");
}
