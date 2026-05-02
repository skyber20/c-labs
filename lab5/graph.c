#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


Graph *createGraph(int numNodes) {
    if (numNodes <= 0) {
        printf("Кол-во узлов должно быть положительным целым числом");
        return NULL;
    }

    Graph *g = (Graph*)malloc(sizeof(Graph));
    if (!g) {
        fprintf(stderr, "Ошибка при выделении памяти\n");
        exit(1);
    }

    g->numEdges = g->capacity = 0;
    g->numNodes = numNodes;
    g->edges = NULL;

    return g;
}


void upCapacity(Graph *g) {
    int newCapacity = g->capacity == 0 ? 2 : g->capacity * 2;
    Edge *newEdges = realloc(g->edges, newCapacity * sizeof(Edge));

    if (!newEdges) {
        fprintf(stderr, "Ошибка при выделении памяти\n");
        exit(1);
    }

    g->edges = newEdges;
    g->capacity = newCapacity;
}


int addEdge(Graph *g, int from, int to, int weight) {
    if (!g || from < 1 || from > g->numNodes || to < 1 || to > g->numNodes || weight < 0) {
        return 0;
    }

    if (g->numEdges == g->capacity) {
        upCapacity(g);
    }

    g->edges[g->numEdges].from = from;
    g->edges[g->numEdges].to = to;
    g->edges[g->numEdges].weight = weight;
    g->numEdges++;

    return 1;
}


Graph *readGraph(FILE *input) {
    if (!input) {
        return NULL;
    }

    int numNodes, numEdges;

    if (fscanf(input, "%d %d", &numNodes, &numEdges) != 2 || numNodes <= 0 || numEdges < 0) {
        return NULL;
    }

    Graph *g = createGraph(numNodes);
    if (!g) {
        return NULL;
    }

    for (int i = 0; i < numEdges; i++) {
        int from, to, weight;

        if (fscanf(input, "%d %d %d", &from, &to, &weight) != 3 || !addEdge(g, from, to, weight)) {
            freeGraph(g);
            return NULL;
        }
    }

    return g;
}


int writeGraph(FILE *output, const Graph *g) {
    if (!output || !g) {
        return 0;
    }

    if (fprintf(output, "%d %d\n", g->numNodes, g->numEdges) < 0) {
        return 0;
    }

    for (int i = 0; i < g->numEdges; i++) {
        Edge edge = g->edges[i];
        if (fprintf(output, "%d %d %d\n", edge.from, edge.to, edge.weight) < 0) {
            return 0;
        }
    }

    return 1;
}


void freeGraph(Graph *g) {
    if (!g) {
        return;
    }

    free(g->edges);
    free(g);
}
