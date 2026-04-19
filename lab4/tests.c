#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "tree.h"


void test_create() {
    RBTree *tree = createRBTree();
    assert(tree->root == tree->NIL && "Корень нового дерева должен быть NIL");
    destroyRBTree(tree);
    printf("Тест 1 (создание) ок\n");
}

void test_insert() {
    RBTree *tree = createRBTree();
    insert(tree, "key1", 10.5f);
    Node *n = searchNode(tree, "key1");
    assert(n != tree->NIL && "Узел должен быть вставлен");
    assert(n->value == 10.5f && "Значение должно совпадать");
    destroyRBTree(tree);
    printf("Тест 2 (вставка) ок\n");
}

void test_search() {
    RBTree *tree = createRBTree();
    insert(tree, "a", 1.0f);
    assert(searchNode(tree, "a") != tree->NIL && "Должен найти 'a'");
    assert(searchNode(tree, "b") == tree->NIL && "Не должен найти 'b'");
    destroyRBTree(tree);
    printf("Тест 3 (поиск) ок\n");
}

void test_delete() {
    RBTree *tree = createRBTree();
    insert(tree, "del", 5.0f);
    deleteNode(tree, "del");
    assert(searchNode(tree, "del") == tree->NIL && "Узел должен быть удален");
    destroyRBTree(tree);
    printf("Тест 4 (удаление) ок\n");
}

void test_update() {
    RBTree *tree = createRBTree();
    insert(tree, "upd", 1.0f);
    insert(tree, "upd", 2.0f);
    Node *n = searchNode(tree, "upd");
    assert(n->value == 2.0f && "Значение должно обновиться");
    destroyRBTree(tree);
    printf("Тест 5 (обнова) ок\n");
}

int main() {
    test_create();
    test_insert();
    test_search();
    test_delete();
    test_update();
    printf("Все тесты пройдены\n");
    return 0;
}
