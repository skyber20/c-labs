#ifndef RPN_H
#define RPN_H

#include "structures.h"

int getPriority(char oper);

int isRightAssoc(char oper);

void appendToExitQueue(Token *t, Token **postfixHead, Token **postfixTail);

Token *toRPN(Token *infixHead);

void printRPNLinear(Token *headPostfix);

#endif