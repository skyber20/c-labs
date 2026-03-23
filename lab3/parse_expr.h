#ifndef PARSE_EXPR_H
#define PARSE_EXPR_H

#include "structures.h"

char *readInput();

int isOp(char oper);

Token *tokenize(char *input);

#endif
