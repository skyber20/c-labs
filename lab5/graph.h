#ifndef LAB5_GRAPH_H
#define LAB5_GRAPH_H

#include <stdio.h>

typedef struct {
    int from;
    int to;
    int weight;
} Edge;

typedef struct {
    Edge *edges;
    int numEdges;
    int numNodes;
    int capacity;
} Graph;

Graph *createGraph(int numNodes);
void freeGraph(Graph *g);
void upCapacity(Graph *g);
int addEdge(Graph *g, int from, int to, int weight);
Graph *readGraph(FILE *input);
int writeGraph(FILE *output, const Graph *g);

#endif
