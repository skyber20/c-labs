#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "dijkstra.h"


static void printHelp(void) {
    printf("Команды:\n");
    printf("0 - выйти\n");
    printf("1 <filename> - загрузить граф из файла\n");
    printf("2 <from> <to> <weight> - добавить ребро\n");
    printf("3 <start> - запустить Дейкстру и вывести результат в консоль\n");
    printf("4 <start> <filename> - запустить Дейкстру и записать результат в файл\n");
    printf("5 <filename> - выгрузить текущий граф в файл\n");
    printf("help - показать список команд\n\n");
}


int main(void) {
    Graph *g = NULL;
    char cmd[32];
    char filename[256];
    int from, to, weight, start;

    printHelp();

    while (scanf("%31s", cmd) == 1) {
        if (strcmp(cmd, "0") == 0) {
            printf("Bye Bye\n");
            break;
        }

        if (strcmp(cmd, "help") == 0) {
            printHelp();
            continue;
        }

        if (strcmp(cmd, "1") == 0) {
            if (scanf("%255s", filename) != 1) {
                printf("Ошибка: укажите имя файла\n");
                break;
            }

            FILE *file = fopen(filename, "r");
            if (!file) {
                printf("Не удалось открыть файл\n");
                continue;
            }

            Graph *newGraph = readGraph(file);
            fclose(file);

            if (!newGraph) {
                printf("Не удалось прочитать граф\n");
                continue;
            }

            freeGraph(g);
            g = newGraph;
            printf("Граф загружен\n");
        } else if (strcmp(cmd, "2") == 0) {
            if (!g || scanf("%d %d %d", &from, &to, &weight) != 3) {
                printf("Ошибка синтаксива: 2 <from> <to> <weight>\n");
                break;
            }

            printf(addEdge(g, from, to, weight) ? "Ребро добавлено\n" : "Ошибка: ребро не добавлено\n");
        } else if (strcmp(cmd, "3") == 0) {
            if (!g || scanf("%d", &start) != 1) {
                printf("Ошибка синтаксиса: 3 <start>\n");
                break;
            }

            DRes *res = dijkstra(g, start);
            if (!res) {
                printf("Инвалидная стартовая вершина\n");
                continue;
            }

            writeDRes(stdout, res);
            freeDRes(res);
        } else if (strcmp(cmd, "4") == 0) {
            if (!g || scanf("%d %255s", &start, filename) != 2) {
                printf("Ошибка синтаксиса: 4 <start> <filename>\n");
                break;
            }

            DRes *res = dijkstra(g, start);
            FILE *file = fopen(filename, "w");
            if (!res || !file) {
                printf("Не удалось выполнить команду\n");
                freeDRes(res);
                if (file) fclose(file);
                continue;
            }

            writeDRes(file, res);
            fclose(file);
            freeDRes(res);
            printf("Результат записан\n");
        } else if (strcmp(cmd, "5") == 0) {
            if (!g || scanf("%255s", filename) != 1) {
                printf("Ошибка синтаксиса: 5 <filename>\n");
                break;
            }

            FILE *file = fopen(filename, "w");
            if (!file) {
                printf("Не удалось создать файл\n");
                continue;
            }

            writeGraph(file, g);
            fclose(file);
            printf("Граф выгружен\n");
        } else {
            printf("Была введена неизвестная команда\n");
        }
    }

    freeGraph(g);
    return 0;
}
