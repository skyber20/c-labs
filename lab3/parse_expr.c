#include <ctype.h>
#include <stdio.h>
#include "structures.c"


char *ReadInput() {
    char *line = NULL;
    size_t len = 0;

    int chars = getline(&line, &len, stdin);

    if (chars == -1) {
        fprintf(stderr, "getline ошибка\n");
        free(line);
        exit(1);
    }

    if (chars > 0 && line[chars-1] == '\n') {
        line[chars-1] = '\0';
    }

    return line;
}


int isOp(char oper) {
    return (oper == '+' || oper == '-' || oper == '*' || oper == '/' || oper == '^');
}


Token *tokenize(char *input) {
    Token *head = NULL;
    Token *tail = NULL;
    TokenType lastTokenType = TOK_LBRACKET;
    int i = 0;

    while (input[i] != '\0') {
        if (isspace(input[i])) {
            i++;
            continue;
        }

        Token *newToken = NULL;

        if (isdigit(input[i])) {
            int num = 0;
            while (isdigit(input[i])) {
                num = num * 10 + (input[i] - '0');
                i++;
            }
            newToken = createTokenNum(num);
            lastTokenType = TOK_NUM;
        }

        else if (isalpha(input[i])) {
            int start = i;
            while (isalpha(input[i])) {
                i++;
            }
            int len = i - start;

            char *varName = strndup(input + start, len);
            if (!varName) {
                fprintf(stderr, "strndup ошибка\n");
                free(varName);
                exit(1);
            }

            newToken = createTokenVar(varName);
            lastTokenType = TOK_VAR;
            free(varName);
        }

        else if (input[i] == '(') {
            newToken = createTokenOp(TOK_LBRACKET, '(');
            lastTokenType = TOK_LBRACKET;
            i++;
        }

        else if (input[i] == ')') {
            newToken = createTokenOp(TOK_RBRACKET, ')');
            lastTokenType = TOK_RBRACKET;
            i++;
        }

        else if (isOp(input[i])) {
            char oper = input[i];

            if (oper == '-' && (lastTokenType == TOK_LBRACKET || lastTokenType == TOK_OP)) {
                newToken = createTokenOp(TOK_OP, '~');
            } else if (oper == '+' && (lastTokenType == TOK_LBRACKET || lastTokenType == TOK_OP)) {
                i++;
                continue;
            } else {
                newToken = createTokenOp(TOK_OP, oper);
            }

            lastTokenType = TOK_OP;
            i++;
        }

        else {
            printf("Недопустимый символ: %c\n", input[i]);
            freeTokens(head);
            return NULL;
        }

        if (!head) {
            head = tail = newToken;
        } else {
            tail->next = newToken;
            tail = newToken;
        }
    }

    return head;
}
