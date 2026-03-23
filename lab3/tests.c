#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "structures.h"
#include "parse_expr.h"
#include "rpn.h"
#include "tree.h"


typedef struct {
    char *input;
    char *expected;
} TestCase;


char *toString(Token *head) {
    size_t size = 128;
    char *buffer = (char*)malloc(size * sizeof(char));
    if (!buffer) {
        fprintf(stderr,"Ошибка выделения памяти\n");
        exit(1);
    }
    buffer[0] = '\0';

    Token *cur = head;
    while (cur) {
        char temp[64];

        if (cur->type == TOK_NUM) sprintf(temp, "%d ", cur->data.value);
        else if (cur->type == TOK_VAR) sprintf(temp, "%s ", cur->data.varName);
        else sprintf(temp, "%c ", cur->data.op);

        if (strlen(temp) + strlen(buffer) + 1 >= size) {
            size *= 2;
            char *newPtr = (char*)realloc(buffer, size * sizeof(char));

            if (!newPtr) {
                fprintf(stderr,"Ошибка выделения памяти\n");
                free(buffer);
                exit(1);
            }
            buffer = newPtr;
        }

        strcat(buffer, temp);
        cur = cur->next;
    }

    return buffer;
}


void treeToInfix(Node *node, char *buffer) {
    if (!node) return;

    if (node->type == NODE_OP) strcat(buffer, "(");

    treeToInfix(node->left, buffer);

    char temp[64];
    if (node->type == NODE_NUM) sprintf(temp, "%d", node->data.value);
    else if (node->type == NODE_VAR) sprintf(temp, "%s", node->data.varName);
    else sprintf(temp, "%c", node->data.op);
    strcat(buffer, temp);

    treeToInfix(node->right, buffer);

    if (node->type == NODE_OP) strcat(buffer, ")");
}


void testTokenize() {
    TestCase data[] = {
        {"1 + 2", "1 + 2 "},
        {"(1 * 2) * ((1 + 2) - (-1)) ^ 3", "( 1 * 2 ) * ( ( 1 + 2 ) - ( ~ 1 ) ) ^ 3 "},
        {"abcd ^ (10 ^ b)", "abcd ^ ( 10 ^ b ) "},
        {"1 + 100 * a ^ 10", "1 + 100 * a ^ 10 "}
    };

    for (int i = 0; i < 4; i++) {
        Token *tokens = tokenize(data[i].input);
        char *res= toString(tokens);

        assert(strcmp(res, data[i].expected) == 0 && "Ошибочка в распарсивании данных");

        free(res);
        freeTokens(tokens);
        printf("Тест вспомогательной функции toString %d пройден успешно\n", i + 1);
    }
}


void testRPN() {
    TestCase data[] = {
        {"1 + 2", "1 2 + "},
        {"-okok + 2", "okok ~ 2 + "},
        {"(1 * 2) * ((1 + 2) - (-1)) ^ 3", "1 2 * 1 2 + 1 ~ - 3 ^ * "},
        {"abcd ^ (10 ^ b)", "abcd 10 b ^ ^ "},
        {"1 + 100 * a ^ 10", "1 100 a 10 ^ * + "}
    };

    for (int i = 0; i < 5; i++) {
        Token *tokens = tokenize(data[i].input);
        Token *rpn = toRPN(tokens);
        char *res = toString(rpn);

        assert(strcmp(res, data[i].expected) == 0 && "Ошибочка в RPN");

        free(res);
        freeTokens(rpn);
        printf("Тест RPN %d пройден успешно\n", i + 1);
    }
}


void testTransform() {
    TestCase data[] = {
        {"(a / b) / c", "(a/(b*c))"},
        {"a / (b / c)", "((a/b)*c)"},
        {"((a / b) / c) / d", "(a/((b*c)*d))"}
    };

    for (int i = 0; i < 3; i++) {
        Token *t = tokenize(data[i].input);
        Token *r = toRPN(t);
        Node *root = createTree(r);

        root = transformTree(root);

        char res[256] = "";
        treeToInfix(root, res);

        assert(strcmp(res, data[i].expected) == 0 && "Ошибочка в Transform");

        freeTree(root);
        freeTokens(r);
        printf("Тест Transform %d пройден успешно\n", i + 1);
    }
}


int main() {
    printf("Тесты начинаются\n");

    testTokenize();
    testRPN();
    testTransform();

    printf("\nТесты успешно завершены\n");
    return 0;
}
