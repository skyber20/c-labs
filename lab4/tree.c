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


void leftRotate(RBTree *tree, Node *x) {
    Node *y = x->right;
    x->right = y->left;

    if (y->left != tree->NIL) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == tree->NIL) {
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
    x->left = y->right;

    if (y->right != tree->NIL) {
        y->right->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == tree->NIL) {
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


void rbTransplant(RBTree *tree, Node *u, Node *v) {
    if (u->parent == tree->NIL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}


Node* treeMinimum(RBTree *tree, Node *node) {
    while (node->left != tree->NIL) {
        node = node->left;
    }
    return node;
}


void deleteFixup(RBTree *tree, Node *x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            // case 1
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            // case 2
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                // case 3
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                // case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            Node *w = x->parent->left;
            // case 1
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            // case 2
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                // case 3
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                // case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}


int deleteNode(RBTree *tree, const char *key) {
    Node *z = searchNode(tree, key);
    if (z == tree->NIL) return 0;

    Node *y = z;
    Node *x;
    Color y_original_color = y->color;

    if (z->left == tree->NIL) {
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->NIL) {
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {
        y = treeMinimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (y_original_color == BLACK) {
        deleteFixup(tree, x);
    }
    return 1;
}


void printTreeHelper(RBTree *tree, Node *node, int depth, FILE *outputFile) {
    if (node == tree->NIL) {
        return;
    }

    printTreeHelper(tree, node->right, depth + 1, outputFile);

    for (int i = 0; i < depth; i++) {
        fprintf(outputFile, "    ");
    }

    char c = (node->color == RED) ? 'R' : 'B';
    fprintf(outputFile, "%s %g (%c)\n", node->key, node->value, c);

    printTreeHelper(tree, node->left, depth + 1, outputFile);
}


void printTree(RBTree *tree, FILE *outputFile) {
    if (tree->root == tree->NIL) {
        fprintf(outputFile, "Дерево пустое\n\n");
        return;
    }

    fprintf(outputFile, "Вывод дерева:\n");
    printTreeHelper(tree, tree->root, 0, outputFile);
    fprintf(outputFile, "Конец вывода дерева\n\n");
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
        printf("Ключу %s соотвествует значение %g\n", key, res->value);
    }
}


void freeNodes(RBTree *tree, Node *node) {
    if (node == tree->NIL) {
        return;
    }
    
    freeNodes(tree, node->left);
    freeNodes(tree, node->right);
    free(node);
}


void destroyRBTree(RBTree *tree) {
    freeNodes(tree, tree->root);
    free(tree->NIL);
    free(tree);
}
