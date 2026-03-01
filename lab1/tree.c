#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *firstChild;
    struct Node *nextSibling;
} Node;

Node* createNode(int value);

Node* findNode(Node *root, int value);

int insertNode(Node *root, int parent_value, int value);

int deleteNode(Node **root, int value);

Node* findParent(Node *root, int value);

void freeSubTree(Node *node);

int findDepth(Node *node);

void printTree(Node *node, int level);


Node* createNode(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Error: malloc error");
        exit(1);
    }

    new_node->data = value;
    new_node->firstChild = NULL;
    new_node->nextSibling = NULL;

    return new_node;
}


Node* findNode(Node *root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    Node *found_in_depth = findNode(root->firstChild, value);

    if (found_in_depth) {
        return found_in_depth;
    }

    return findNode(root->nextSibling, value);
}


int insertNode(Node *root, int parent_value, int value) {
    if (!root) {
        return 0;
    }

    Node *parent = findNode(root, parent_value);
    if (!parent) {
        return 0;
    }

    Node *new_child = createNode(value);
    if (!parent->firstChild) {
        parent->firstChild = new_child;
    } else {
        Node* child = parent->firstChild;
        while (child->nextSibling) {
            child = child->nextSibling;
        }
        child->nextSibling = new_child;
    }
    return 1;
}


Node* findParent(Node *root, int value) {
    if (!root) {
        return NULL;
    }

    Node *child = root->firstChild;
    while (child) {
        if (child->data == value) {
            return root;
        }
        child = child->nextSibling;
    }

    child = root->firstChild;
    while (child) {
        Node *inChild = findParent(child,  value);
        if (inChild) {
            return inChild;
        }
        child = child->nextSibling;
    }

    return NULL;
}


void freeSubTree(Node *node) {
    if (!node) {
        return;
    }

    freeSubTree(node->firstChild);
    freeSubTree(node->nextSibling);

    free(node);
}


int deleteNode(Node **rootPtr, int value) {
    Node *root = *rootPtr;
    if (!root) {
        printf("Tree is empty\n");
        return 0;
    }

    if (root->data == value) {
        freeSubTree(root);
        *rootPtr = NULL;
        return 1;
    }

    Node *parent = findParent(root, value);
    if (!parent) {
        printf("Не был найден такой элемент\n");
        return 0;
    }

    Node *child = parent->firstChild;
    if (child->data == value) {
        parent->firstChild = child->nextSibling;
        child->nextSibling = NULL;
        freeSubTree(child);
        return 1;
    }

    while (child->nextSibling) {
        Node *target = child->nextSibling;
        if (target->data == value) {
            child->nextSibling = target->nextSibling;
            target->nextSibling = NULL;
            freeSubTree(target);
            return 1;
        }
        child = child->nextSibling;
    }

    return 0;
}


int findDepth(Node *node) {
    if (!node) {
        return -1;
    }

    if (!node->firstChild) {
        return 0;
    }

    int max_d = -1;
    Node *child = node->firstChild;

    while (child) {
        int d = findDepth(child);
        if (d > max_d) {
            max_d = d;
        }
        child = child->nextSibling;
    }

    return max_d + 1;
}


void printTree(Node *node, int level) {
    if (!node) {
        return;
    }

    for (int i = 0; i < level * 2; i++) {
        printf(" ");
    }

    printf("%d\n", node->data);

    printTree(node->firstChild, level + 1);
    printTree(node->nextSibling, level);
}
