#include <stdio.h>
#include "structures.h"
#include "stack.h"
#include "tree.h"


Node* createTree(Token *postfixHead) {
    if (!postfixHead) return NULL;

    Stack s;
    initStack(&s);

    Token *curToken = postfixHead;
    while (curToken) {
        if (curToken->type == TOK_NUM) {
            push(&s, createNodeNum(curToken->data.value));
        }

        else if (curToken->type == TOK_VAR) {
            push(&s, createNodeVar(curToken->data.varName));
        }

        else if (curToken->type == TOK_OP && curToken->data.op == '~') {
            Node *operand = (Node*)pop(&s);
            if (!operand) {
                printf("Не хватает операндов для выполнения операции ~\n");
                return NULL;
            }

            push(&s, createNodeOp('~', NULL, operand));
        }

        else if (curToken->type == TOK_OP) {
            Node *operand1 = (Node*)pop(&s);
            Node *operand2 = (Node*)pop(&s);

            if (!operand1 || !operand2) {
                printf("Не хватает операндов для выполнения операции %c\n", curToken->data.op);
                return NULL;
            }

            push(&s, createNodeOp(curToken->data.op, operand2, operand1));
        }

        curToken = curToken->next;
    }

    Node *root = (Node*)pop(&s);

    if (!root || (!isEmpty(&s))) {
        printf("Обратная польская запись некорректна\n");
        return NULL;
    }

    return root;
}


Node *transformTree(Node *root) {
    if (!root) return NULL;

    root->left = transformTree(root->left);
    root->right = transformTree(root->right);

    if (root->type == NODE_OP && root->data.op == '/') {
        // 1. (a / b) / c -> a / (b * c)
        if (root->left && root->left->type == NODE_OP && root->left->data.op == '/') {
            Node *l = root->left;
            Node *a = l->left;
            Node *b = l->right;
            Node *c = root->right;

            root->left = a;
            l->data.op = '*';
            l->left = b;
            l->right = c;
            root->right = l;

            return root;
        }

        // 2. a / (b / c) -> (a / b) * c
        if (root->right && root->right->type == NODE_OP && root->right->data.op == '/') {
            Node *r = root->right;
            Node *a = root->left;
            Node *b = r->left;
            Node *c = r->right;

            root->data.op = '*';
            root->right = c;
            r->left = a;
            r->right = b;
            root->left = r;

            return root;
        }
    }


    return root;
}


void printPostfixTree(Node *root, int indent) {
    if (!root) return;

    printPostfixTree(root->right, indent + 1);

    for (int i = 0; i < indent; i++) printf("  ");

    if (root->type == NODE_NUM) {
        printf("%d\n", root->data.value);
    } else if (root->type == NODE_VAR) {
        printf("%s\n", root->data.varName);
    } else {
        printf("%c\n", root->data.op);
    }

    printPostfixTree(root->left, indent + 1);
}


void printInfix(Node *node) {
    if  (!node) return;

    if (node->type == NODE_OP) {
        printf("(");
    }

    if (node->type == NODE_OP && node->data.op == '~') {
        printf("-");
    } else {
        printInfix(node->left);
    }

    if (node->type == NODE_NUM) {
        printf("%d", node->data.value);
    } else if (node->type == NODE_VAR) {
        printf("%s", node->data.varName);
    } else {
        if (node->type == NODE_OP && node->data.op != '~') {
            printf("%c", node->data.op);
        }
    }

    printInfix(node->right);

    if (node->type == NODE_OP) {
        printf(")");
    }
}
