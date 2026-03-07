#include <stdio.h>
#include "logic.c"

int main() {
    Table table;
    initTable(&table);
    tableFromFile(&table, "data.txt");

    // Элементы расположены рандомно (случай 3)
    printf("СЛУЧАЙ 3\n\n");
    printf("Таблица до сортировки:\n");
    printTable(&table);
    printf("\n");

    shakerSort(&table);

    printf("Таблица после сортировки:\n");
    printTable(&table);
    printf("\n");


    // Элементы уже упорядоченны (случай 1)
    printf("СЛУЧАЙ 1\n");
    printf("Таблица до сортировки:\n");
    printTable(&table);
    printf("\n");

    shakerSort(&table);

    printf("Таблица после сортировки:\n");
    printTable(&table);
    printf("\n");


    // Элементы упорядоченной таблицы реверснуты (случай 2)
    printf("СЛУЧАЙ 2\n");
    reverseTable(&table);
    printf("Таблица до сортировки:\n");
    printTable(&table);
    printf("\n");

    shakerSort(&table);

    printf("Таблица после сортировки:\n");
    printTable(&table);
    printf("\n");

    // Дальше CLI для бин поиска (юзер вводит key, ему выдает value)
    printf("БИНАРНЫЙ ПОИСК\n");
    printf("Введите ключ для поиска в таблице\n");

    int key;
    printf(">: ");

    while (scanf("%d", &key) == 1) {
        int ind = binarySearch(&table, key);

        if (ind == -1) {
            printf("Не найден элемент с таким ключом\n");
        } else {
            printf("Элемент: %s\n", table.values[ind]);
        }

        printf(">: ");
    }

    printf("Bye Bye\n");
    freeTable(&table);

    return 0;
}
