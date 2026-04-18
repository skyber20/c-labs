#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


RBTree* createRBTree() {
    RBTree *tree = (RBTree*)malloc(sizeof(RBTree));
    if (!tree) {
        fprintf(stderr,"Ошибка при выделении памяти\n");
        exit(1);
    }

    tree->NIL = (Node*)malloc(sizeof(Node));
    if (!tree->NIL) {
        fprintf(stderr,"Ошибка при выделении памяти\n");
        exit(1);
    }

    tree->NIL->color = BLACK;
    tree->NIL->left = tree->NIL->right = tree->NIL->parent = tree->NIL;
    tree->root = tree->NIL;

    return tree;
}


Node* grandparent(Node *n) {
    return n->parent->parent;
}


Node* uncle(Node *n) {
    Node *g = grandparent(n);

    if (n->parent == g->left) {
        return g->right;
    }
    return g->left;
}


void leftRotate(RBTree *tree, Node *x) {
    Node *y = x->right;

    if (y->left != tree->NIL) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == tree->root) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}


void rightRotate(RBTree *tree, Node *x) {
    Node *y = x->left;

    if (y->right != tree->NIL) {
        y->right->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == tree->root) {
        tree->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}


void insertFixup(RBTree *tree, Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;

            // case 1
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                // case 2
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }

                // case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        }
        else {
            Node *y = z->parent->parent->left;

            // case 1
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                // case 2
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }

                // case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }

    tree->root->color = BLACK;
}


void insert(RBTree *tree, const char *key, float value) {
    Node *z = (Node*)malloc(sizeof(Node));
    if (!z) {
        fprintf(stderr,"Ошибка при выделении памяти\n");
        exit(1);
    }

    strncpy(z->key, key, 6);
    z->key[6] = '\0';
    z->value = value;
    z->color = RED;
    z->left = z->right = tree->NIL;

    Node *y = tree->NIL;
    Node *x = tree->root;

    while (x != tree->NIL) {
        y = x;
        if (strcmp(z->key, x->key) < 0) {
            x = x->left;
        } else if (strcmp(z->key, x->key) > 0) {
            x = x->right;
        } else {
            x->value = z->value;
            free(z);
            return;
        }
    }

    z->parent = y;
    if (y == tree->NIL) {
        tree->root = z;
    } else if (strcmp(z->key, y->key) < 0) {
        y->left = z;
    } else {
        y->right = z;
    }

    insertFixup(tree, z);
}


void printTreeHelper(RBTree *tree, Node *node, int depth) {
    if (node == tree->NIL) {
        return;
    }

    printTreeHelper(tree, node->right, depth + 1);

    for (int i = 0; i < depth; i++) {
        printf("    ");
    }

    char c = (node->color == RED) ? 'R' : 'B';
    printf("%s %.2f (%c)\n", node->key, node->value, c);

    printTreeHelper(tree, node->left, depth + 1);
}


void printTree(RBTree *tree) {
    if (tree->root == tree->NIL) {
        printf("Дерево пустое\n");
        return;
    }

    printf("Вывод дерева:\n");
    printTreeHelper(tree, tree->root, 0);
    printf("Конец вывода дерева\n");
}


Node* searchNode(RBTree *tree, const char *key) {
    Node *cur = tree->root;

    while (cur != tree->NIL) {
        if (strcmp(cur->key, key) == 0) {
            return cur;
        } else if (strcmp(cur->key, key) < 0) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }

    return tree->NIL;
}


void searchValue(RBTree *tree, const char *key) {
    if (tree->root == tree->NIL) {
        printf("Дерево пустое\n");
        return;
    }

    Node *res = searchNode(tree, key);

    if (res == tree->NIL) {
        printf("%s нет в дереве\n", key);
    } else {
        printf("Ключу %s соотвествует значение %.2f\n", key, res->value);
    }
}
