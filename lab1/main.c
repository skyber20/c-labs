#include <stdio.h>
#include "tree.c"

int main() {
    Node *root = NULL;
    int cmd, val, p_val;

    while (1) {
        printf("\n1-Add\n2-Print\n3-Del\n4-Depth\n0-Exit:\n");
        scanf("%d", &cmd);

        if (cmd == 0) {
            freeSubTree(root);
            break;
        }

        switch (cmd) {
            case 1:
                printf("Value: ");
                scanf("%d", &val);

                if (!root) {
                    root = createNode(val);
                } else {
                    printf("Parent: ");
                    scanf("%d", &p_val);

                    if (!insertNode(root, p_val, val))
                        printf("Error: Parent not found\n");
                }
                break;

            case 2:
                printTree(root, 0);
                break;

            case 3:
                printf("Value to delete: ");
                scanf("%d", &val);

                if (!deleteNode(&root, val))
                    printf("Error: Not found a value\n");
                break;

            case 4:
                printf("Depth: %d\n", findDepth(root));
                break;

            default:
                printf("Unknown command\n");
        }
    }
    return 0;
}
