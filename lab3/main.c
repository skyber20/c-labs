#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "parse_expr.h"
#include "rpn.h"
#include "tree.h"


void help() {
    printf("\n");
    printf("Введите арифметическое выражение в инфиксной форме записи\n");
    printf("Поддерживаются: +, -, *, /, ^, ()\n");
    printf("Команды:\n");
    printf("help - показать это сообщение\n");
    printf("q - выход из программы\n");
    printf("\n");
}


int main() {
    printf("Введите help для справки или q для выхода\n");

    while (1) {
        printf("\n> ");
        char *input = readInput();

        if (input == NULL || strlen(input) == 0) {
            if (input) free(input);
            continue;
        }

        if (strcmp(input, "q") == 0) {
            free(input);
            printf("Bye Bye\n");
            break;
        }

        if (strcmp(input, "help") == 0) {
            help();
            free(input);
            continue;
        }

        Token *tokens = tokenize(input);
        if (!tokens) {
            free(input);
            continue;
        }

        Token *postfixTokens = toRPN(tokens);
        if (!postfixTokens) {
            freeTokens(tokens);
            free(input);
            continue;
        }

        printf("Функция перевода в ОПН: ");
        printRPNLinear(postfixTokens);

        Node *root = createTree(postfixTokens);
        if (!root) {
            freeTokens(postfixTokens);
            free(input);
            continue;
        }

        printf("\nФункция вывода дерева:\n");
        printPostfixTree(root, 0);

        root = transformTree(root);

        printf("\nФункция из варианта (после трансформации):\n");
        printPostfixTree(root, 0);

        freeTokens(postfixTokens);
        freeTree(root);
        free(input);

        printf("\n");
    }

    return 0;
}
