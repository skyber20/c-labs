#ifndef LAB4_TREE_H
#define LAB4_TREE_H

typedef enum {
    BLACK,
    RED
} Color;

typedef struct Node {
    char key[7];
    float value;
    Color color;
    struct Node *left, *right, *parent;
} Node;

typedef struct {
    Node *root;
    Node *NIL;
} RBTree;


RBTree* createRBTree();
void leftRotate(RBTree *tree, Node *x);
void rightRotate(RBTree *tree, Node *y);
void insertFixup(RBTree *tree, Node *z);
void insert(RBTree *tree, const char *key, float value);
void printTreeHelper(RBTree *tree, Node *node, int depth);
void printTree(RBTree *tree);
Node* searchNode(RBTree *tree, const char *key);
void searchValue(RBTree *tree, const char *key);

#endif