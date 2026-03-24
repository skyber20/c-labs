#ifndef TREE_H
#define TREE_H
#include "structures.h"
#include "stack.h"

Node* createTree(Token *postfixHead);

Node *transformTree(Node *root);

void printPostfixTree(Node *root, int indent);

void printInfix(Node *node);

#endif
