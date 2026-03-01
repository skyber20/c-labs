#include <assert.h>
#include "tree.c"


void test1() {
    printf("Test 1 (создание дерева и вставка элементов в него)\n");
    int res;

    Node *tree = createNode(10);
    assert(tree->data == 10);
    assert(tree->firstChild == NULL);
    assert(tree->nextSibling == NULL);

    res = insertNode(tree, 10, 6);
    assert(res == 1);
    assert(tree->firstChild->data == 6);

    res = insertNode(tree, 10, 7);
    assert(res == 1);
    assert(tree->firstChild->nextSibling->data == 7);

    printf("OK\n\n");
}


void test2() {
    printf("Test 2 (поиск глубины дерева)\n");
    int dep;

    Node *tree = createNode(10);
    insertNode(tree, 10, 12);
    insertNode(tree, 10, 15);

    dep = findDepth(tree);
    assert(dep == 1);

    insertNode(tree, 15, 5);
    dep = findDepth(tree);
    assert(dep == 2);

    freeSubTree(tree);
    printf("OK\n\n");
}


void test3() {
    printf("Test 3 (удаление элементов)\n");
    int res;

    Node *tree = createNode(10);
    insertNode(tree, 10, 12);
    insertNode(tree, 10, 2);
    insertNode(tree, 12, 8);

    assert(tree->firstChild->firstChild->data == 8);
    res = deleteNode(&tree, 8);
    assert(res == 1);
    assert(tree->firstChild->firstChild == NULL);

    assert(tree->firstChild->data == 12);
    res = deleteNode(&tree, 12);
    assert(res == 1);
    assert(tree->firstChild->data == 2);

    insertNode(tree, 2, 4);
    insertNode(tree, 2, 6);
    assert(tree->firstChild->firstChild->data == 4);
    assert(tree->firstChild->firstChild->nextSibling->data == 6);

    res = deleteNode(&tree, 2);
    assert(res == 1);
    assert(tree->firstChild == NULL);

    freeSubTree(tree);
    printf("OK\n\n");
}


void test4() {
    printf("Test 4 (проверка на ошибки)\n");

    Node *tree = createNode(100);
    insertNode(tree, 100, 50);

    int res = insertNode(tree, 999, 1);
    assert(res == 0);
    assert(findNode(tree, 1) == NULL);

    res = deleteNode(&tree, 999);
    assert(res == 0);

    assert(findNode(tree, 777) == NULL);

    assert(tree->data == 100);
    assert(tree->firstChild->data == 50);

    freeSubTree(tree);
    printf("OK\n\n");
}


void test5() {
    printf("Test 5 (работа с пустым деревом)\n");

    Node *tree = createNode(5);
    insertNode(tree, 5, 1);

    int res = deleteNode(&tree, 5);
    assert(res == 1);
    assert(tree == NULL);

    res = deleteNode(&tree, 5);
    assert(res == 0);

    res = insertNode(tree, 5, 1);
    assert(res == 0);

    int dep = findDepth(tree);
    assert(dep == -1);

    printf("OK\n\n");
}


int main() {
    printf("Тесты начинаются\n");
    test1();
    test2();
    test3();
    test4();
    test5();

    printf("Все тесты завершены успешно\n");
    return 0;
}
