#ifndef STRUCTURES_H
#define STRUCTURES_H


typedef enum {
    TOK_NUM,
    TOK_VAR,
    TOK_OP,
    TOK_LBRACKET,
    TOK_RBRACKET,
} TokenType;

typedef struct Token {
    TokenType type;
    union {
        int value;
        char* varName;
        char op;
    } data;
    struct Token* next;
} Token;

typedef enum {
    NODE_NUM,
    NODE_VAR,
    NODE_OP
} NodeType;

typedef struct Node {
    NodeType type;
    union {
        int value;
        char* varName;
        char op;
    } data;
    struct Node *left, *right;
} Node;


Token *createTokenNum(int value);

Token *createTokenVar(char *varName);

Token *createTokenOp(TokenType type, char oper);

Node *createNodeNum(int value);

Node *createNodeVar(char *varName);

Node *createNodeOp(char oper, Node *left, Node *right);

void freeTokens(Token *head);

void freeTree(Node *root);

#endif
