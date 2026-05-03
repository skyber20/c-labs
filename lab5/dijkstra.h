#ifndef LAB5_DIJKSTRA_H
#define LAB5_DIJKSTRA_H

#include <stdio.h>
#include "graph.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INF 1000000000

typedef struct {
    int start;
    int numNodes;
    int *dist;
    int *prev;
} DRes;

typedef struct {
    int *nodes;
    int len;
    int totalWeight;
} Path;

DRes *dijkstra(Graph *g, int start);
Path *restorePath(DRes *result, int target);
int writeDRes(FILE *output, DRes *result);
void freePath(Path *path);
void freeDRes(DRes *result);

#ifdef __cplusplus
}
#endif

#endif
