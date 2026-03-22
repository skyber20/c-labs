#include <stdio.h>
#include <stdlib.h>
#include <_string.h>

typedef enum {
    TYPE_NUM,
    TYPE_VAR,
    TYPE_OR
} NodeType;

typedef struct Node {
    NodeType type;
    union {
        int value;
        char op;
        char* var_name;
    } data;
    struct Node *left, *right;
} Node;


Node* createNum(int value) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->type = TYPE_NUM;
    node->data.value = value;
    node->left = node->right = NULL;
    return node;
}


Node* createVar(char *var_name) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->type = TYPE_VAR;
    node->data.var_name = strdup(var_name);
    node->left = node->right = NULL;
    return node;
}


Node* createOp(char oper, Node* left, Node* right) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->type = TYPE_NUM;
    node->data.op = oper;
    node->left = left;
    node->right = right;
    return node;
}


