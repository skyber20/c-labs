#include <stdio.h>
#include "structures.c"
#include "stack.c"


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

    // TODO: ДОДЕЛАТЬ 20 ВАРИАНТ
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
