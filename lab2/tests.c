#include <assert.h>
#include "logic.c"


int isSorted(Table *table) {
    for (int i = 0; i < table->cnt - 1; i++) {
        if (table->keys[i] > table->keys[i + 1]) return 0;
    }
    return 1;
}


void createTable(Table *table) {
    table->cnt = 5;
    table->keys = (int*)malloc(5 * sizeof(int));
    table->values = (char**)malloc(5 * sizeof(char*));

    table->keys[0] = 30; table->values[0] = strdup("Тридцать");
    table->keys[1] = 10; table->values[1] = strdup("Десять");
    table->keys[2] = 50; table->values[2] = strdup("Пятьдесят");
    table->keys[3] = 20; table->values[3] = strdup("Двадцать");
    table->keys[4] = 40; table->values[4] = strdup("Сорок");
}


void testInitTable() {
    Table table;
    initTable(&table);

    assert(table.cnt == 0 && "Должно было быть 0 элементов");
    assert(table.keys == NULL && "Поле keys должно было быть NULL");
    assert(table.values == NULL && "Поле values должно было быть NULL");

    createTable(&table);
    assert(table.cnt == 5 && "Должно было быть 5 элементов");

    freeTable(&table);
    assert(table.cnt == 0 && "Должно было быть 0 элементов");
    assert(table.keys == NULL && "Поле keys должно было быть NULL");
    assert(table.values == NULL && "Поле values должно было быть NULL");

    printf("Тест на инициализацию и очистку таблицы пройден успешно\n");
}


void testShakerSort() {
    Table table;
    initTable(&table);
    createTable(&table);

    // Тест случая 3 (все данные в рандом порядке)
    shakerSort(&table);
    assert(isSorted(&table) && "Сортировка в третьем случае сраболтала некорректно");

    // Тест случая 1 (все данные упорядочены)
    shakerSort(&table);
    assert(isSorted(&table) && "Сортировка во втором случае сраболтала некорректно");

    // Тест случая 2 (все данные в реверснутом порядке)
    reverseTable(&table);
    assert(!isSorted(&table) && "Таблица реверснута, а показывает, что она отсортирована...");
    shakerSort(&table);
    assert(isSorted(&table) && "Сортировка в третьем случае сраболтала некорректно");

    freeTable(&table);
    printf("Тест на сортировки всех 3 случаев из условия пройден успешно\n");
}


void testBinarySearch() {
    Table table;
    initTable(&table);
    createTable(&table);
    shakerSort(&table);

    int ind = binarySearch(&table, 20);
    assert(ind == 1 && "Индекс должен был быть равен 1");
    assert(strcmp("Двадцать", table.values[ind]) == 0 && "Строки не равны, а должны бы быть");

    ind = binarySearch(&table, 42);
    assert(ind == -1 && "Индекс должен был быть равен -1");

    freeTable(&table);
    printf("Тест на бин поиск пройден успешно\n");
}


int main() {
    printf("Тесты стартуют\n");

    testInitTable();
    testShakerSort();
    testBinarySearch();

    printf("Все тесты завершены\n");
}
