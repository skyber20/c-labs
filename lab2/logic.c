#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *keys;
    char **values;
    int cnt;
} Table;

void initTable(Table *table);

void tableFromFile(Table *table, const char *filename);

void swap(Table *table, int i1, int i2);

void shakerSort(Table *table);

int binarySearch(Table *table, int keyValue);

void reverseTable(Table *table);


void initTable(Table *table) {
    table->keys = NULL;
    table->values = NULL;
    table->cnt = 0;
}


void tableFromFile(Table *table, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Файл не открылся\n");
        exit(1);
    }

    if (fscanf(file, "%d", &table->cnt) != 1) {
        fprintf(stderr, "Файл пуст или неверный формат\n");
        fclose(file);
        exit(1);
    }

    table->keys = (int*)malloc(table->cnt * sizeof(int));
    table->values = (char**)malloc(table->cnt * sizeof(char*));

    if (!table->keys || !table->values) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        fclose(file);
        exit(1);
    }

    char buffer[256];
    for (int i = 0; i < table->cnt; i++) {
        fscanf(file, "%d", &table->keys[i]);
        fscanf(file, "%s", buffer);

        table->values[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        if (!table->values[i]) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            fclose(file);
            exit(1);
        }

        strcpy(table->values[i], buffer);
    }

    fclose(file);
}


void swap(Table *table, int i1, int i2) {
    int tempKey = table->keys[i1];
    char *tempValue = table->values[i1];

    table->keys[i1] = table->keys[i2];
    table->keys[i2] = tempKey;

    table->values[i1] = table->values[i2];
    table->values[i2] = tempValue;
}


void shakerSort(Table *table) {
    int left = 0;
    int right = table->cnt - 1;

    while (left < right) {
        int lastSwapped = -1;

        for (int i = left; i < right; i++) {
            if (table->keys[i] > table->keys[i+1]) {
                swap(table, i, i + 1);
                lastSwapped = i;
            }
        }

        if (lastSwapped == -1) {
            break;
        }

        right = lastSwapped;
        lastSwapped = -1;

        for (int i = right; i > left; i--) {
            if (table->keys[i] < table->keys[i-1]) {
                swap(table, i - 1, i);
                lastSwapped = i;
            }
        }

        if (lastSwapped == -1) {
            break;
        }

        left = lastSwapped;
    }
}


int binarySearch(Table *table, int keyValue) {
    int l = 0;
    int r = table->cnt - 1;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (table->keys[mid] > keyValue) {
            r = mid - 1;
        } else if (table->keys[mid] < keyValue) {
            l = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}


void reverseTable(Table *table) {
    for (int i = 0; table->cnt / 2; i++) {
        swap(table, i, table->cnt - i - 1);
    }
}


void printTable(Table *table) {
    for (int i = 0; i < table->cnt; i++) {
        printf("%d  %s\n", table->keys[i], table->values[i]);
    }
}
