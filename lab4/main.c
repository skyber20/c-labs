#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


int main(int argc, char *argv[]) {
    FILE *inputFile = stdin;
    FILE *outputFile = stdout;

    if (argc == 3) {
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            fprintf(stderr, "Ошибка: не удалось открыть файл %s\n", argv[1]);
            return 1;
        }

        outputFile = fopen(argv[2], "w");
        if (outputFile == NULL) {
            fprintf(stderr, "Ошибка: не удалось создать файл %s\n", argv[2]);
            fclose(inputFile);
            return 1;
        }
        printf("Все ок");
    }
    else {
        printf("Консольный CLI\n");
        printf("0 - для выхода\n");
        printf("1 <ключ> <значение> - добавить узел\n");
        printf("2 <ключ> - удалить узел\n");
        printf("3 - показать дерево\n");
        printf("4 <ключ> - поиск узла\n\n");
    }

    RBTree *tree = createRBTree();
    int op;
    char key[7];
    float value;

    while (fscanf(inputFile, "%d", &op) == 1) {
        if (op == 0) {
            fprintf(outputFile, "Bye bye\n\n");
            break;
        }

        if (op == 1) {
            fscanf(inputFile, "%6s %f", key, &value);
            fprintf(outputFile, "1 %s %g\n", key, value);
            insert(tree, key, value);
            fprintf(outputFile, "Узел добавлен\n\n");
            
        } else if (op == 2) {
            fscanf(inputFile, "%6s", key);
            fprintf(outputFile, "2 %s\n", key);
            if (deleteNode(tree, key)) {
                fprintf(outputFile, "Узел удален\n\n");
            } else {
                fprintf(outputFile, "Узел не найден\n\n");
            }
            
        } else if (op == 3) {
            fprintf(outputFile, "3\n");
            printTree(tree, outputFile);
            
        } else if (op == 4) {
            fscanf(inputFile, "%6s", key);
            fprintf(outputFile, "4 %s\n", key);
            Node *res = searchNode(tree, key);
            if (res == tree->NIL) {
                fprintf(outputFile, "%s нет в дереве\n\n", key);
            } else {
                fprintf(outputFile, "Ключу %s соотвествует значение %g\n\n", key, res->value);
            }
        } else {
            fprintf(outputFile, "Ошибка: низвестная операция %d\n\n", op);
        }
    }

    destroyRBTree(tree);
    
    if (inputFile != stdin) fclose(inputFile);
    if (outputFile != stdout) fclose(outputFile);

    return 0;
}
