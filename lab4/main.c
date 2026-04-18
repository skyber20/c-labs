#include <stdio.h>
#include "tree.h"


int main() {
    RBTree *tree = createRBTree();

    int op;
    char key[7];
    float value;

    printf("Тестовый режим КЧД\n");
    printf("Введите команды (0 - для выхода):\n");

    while (scanf("%d", &op) == 1) {

        if (op == 0) {
            printf("Выход из программы.\n");
            break;
        }

        if (op == 1) {
            scanf("%6s %f", key, &value);
            printf("> 1 %s %.2f\n", key, value);

            insert(tree, key, value);
            printf("Результат: Узел добавлен.\n");

        } else if (op == 2) {
            scanf("%6s", key);
            printf("> 2 %s\n", key);

            printf("Результат: Удаление пока в разработке!\n");

        } else if (op == 3) {
            printf("> 3\n");
            printTree(tree);

        } else if (op == 4) {
            scanf("%6s", key);
            printf("> 4 %s\n", key);

            searchValue(tree, key);

        } else {
            printf("Ошибка: Неизвестная операция %d\n", op);
        }
    }

    return 0;
}
