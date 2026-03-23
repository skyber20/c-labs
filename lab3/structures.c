#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"


Token *createTokenNum(int value) {
    Token *token = (Token*)malloc(sizeof(Token));

    if (!token) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    token->type = TOK_NUM;
    token->data.value = value;
    token->next = NULL;

    return token;
}


Token *createTokenVar(char *varName) {
    Token *token = (Token*)malloc(sizeof(Token));

    if (!token) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    token->type = TOK_VAR;
    token->data.varName = strdup(varName);
    if (!token->data.varName) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        free(token);
        exit(1);
    }
    token->next = NULL;

    return token;
}


Token *createTokenOp(TokenType type, char oper) {
    Token *token = (Token*)malloc(sizeof(Token));

    if (!token) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    token->type = type;
    token->data.op = oper;
    token->next = NULL;

    return token;
}


Node *createNodeNum(int value) {
    Node *node = (Node*)malloc(sizeof(Node));

    if (!node) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    node->type = NODE_NUM;
    node->data.value = value;
    node->left = node->right = NULL;

    return node;
}


Node *createNodeVar(char *varName) {
    Node *node = (Node*)malloc(sizeof(Node));

    if (!node) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    node->type = NODE_VAR;
    node->data.varName = strdup(varName);
    if (!node->data.varName) {
        fprintf(stderr, "Ошибка выделения памяти\n");
    }
    node->left = node->right = NULL;

    return node;
}


Node *createNodeOp(char oper, Node *left, Node *right) {
    Node *node = (Node*)malloc(sizeof(Node));

    if (!node) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    node->type = NODE_OP;
    node->data.op = oper;
    node->left = left;
    node->right = right;

    return node;
}


void freeTokens(Token *head) {
    Token *current = head;
    while (current) {
        Token *next = current->next;

        if (current->type == TOK_VAR) {
            free(current->data.varName);
        }

        free(current);
        current = next;
    }
}


void freeTree(Node *root) {
    if (!root) return;

    freeTree(root->left);
    freeTree(root->right);

    if (root->type == NODE_VAR) {
        free(root->data.varName);
    }

    free(root);
}
