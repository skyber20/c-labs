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
void rbTransplant(RBTree *tree, Node *u, Node *v);
Node* treeMinimum(RBTree *tree, Node *node);
void deleteFixup(RBTree *tree, Node *x);
int deleteNode(RBTree *tree, const char *key);
void printTreeHelper(RBTree *tree, Node *node, int depth, FILE *outputFile);
void printTree(RBTree *tree, FILE *outputFile);
Node* searchNode(RBTree *tree, const char *key);
void searchValue(RBTree *tree, const char *key);
void freeNodes(RBTree *tree, Node *node);
void destroyRBTree(RBTree *tree);

#endif