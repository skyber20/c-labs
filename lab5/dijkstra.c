#include <stdlib.h>
#include "dijkstra.h"


static int findMin(DRes *result, int *used) {
    int min = -1;

    for (int v = 0; v < result->numNodes; v++) {
        if (!used[v] && result->dist[v] < INF &&
            (min == -1 || result->dist[v] < result->dist[min])) {
            min = v;
        }
    }

    return min;
}


DRes *dijkstra(Graph *g, int start) {
    if (!g || start < 1 || start > g->numNodes) {
        return NULL;
    }

    DRes *result = (DRes*)malloc(sizeof(DRes));
    if (!result) {
        fprintf(stderr, "Ошибка при выделении памяти\n");
        exit(1);
    }

    result->start = start;
    result->numNodes = g->numNodes;
    result->dist = (int*)malloc(g->numNodes * sizeof(int));
    result->prev = (int*)malloc(g->numNodes * sizeof(int));
    int *used = (int*)calloc(g->numNodes, sizeof(int));

    if (!result->dist || !result->prev || !used) {
        fprintf(stderr, "Ошиька при выделении памяти\n");
        exit(1);
    }

    for (int v = 0; v < g->numNodes; v++) {
        result->dist[v] = INF;
        result->prev[v] = -1;
    }

    result->dist[start - 1] = 0;

    for (int step = 0; step < g->numNodes; step++) {
        int cur = findMin(result, used);
        if (cur == -1) {
            break;
        }

        used[cur] = 1;

        for (int i = 0; i < g->numEdges; i++) {
            Edge edge = g->edges[i];
            if (edge.from - 1 != cur) {
                continue;
            }

            int newDistance = result->dist[cur] + edge.weight;
            int to = edge.to - 1;
            if (newDistance < result->dist[to]) {
                result->dist[to] = newDistance;
                result->prev[to] = cur;
            }
        }
    }

    free(used);
    return result;
}


Path *restorePath(DRes *result, int target) {
    if (!result || target < 1 || target > result->numNodes) {
        return NULL;
    }

    if (result->dist[target - 1] == INF) {
        return NULL;
    }

    Path *path = (Path*)malloc(sizeof(Path));
    if (!path) {
        fprintf(stderr, "Ошибка при выделении памяти\n");
        exit(1);
    }

    path->nodes = (int*)malloc(result->numNodes * sizeof(int));
    if (!path->nodes) {
        free(path);
        fprintf(stderr, "Ошибка при выделении памяти\n");
        exit(1);
    }

    path->len = 0;
    path->totalWeight = result->dist[target - 1];

    int cur = target - 1;
    while (cur != -1) {
        path->nodes[path->len] = cur + 1;
        path->len++;
        cur = result->prev[cur];
    }

    for (int *l = path->nodes, *r = l + path->len - 1; l < r; l++, r--) {
        int tmp = *l;
        *l = *r;
        *r = tmp;
    }

    return path;
}


static int printPath(FILE *f, Path *path, int target) {
    fprintf(f, "%d\t%d\t\t", target, path->totalWeight);
    for (int i = 0; i < path->len; i++) {
        fprintf(f, "%d%s", path->nodes[i], (i + 1 < path->len) ? " -> " : "");
    }
    fprintf(f, "\n");

    return ferror(f) ? -1 : 1;
}


int writeDRes(FILE *output, DRes *result) {
    if (!output || !result) {
        return 0;
    }

    if (fprintf(output, "Стартовая вершина: %d\n\n", result->start) < 0 ||
        fprintf(output, "Вершина\tРасстояние\tПуть\n") < 0) {
        return 0;
    }

    for (int target = 1; target <= result->numNodes; target++) {
        Path *path = restorePath(result, target);

        if (!path) {
            if (fprintf(output, "%d\tINF\t\tпути нет\n", target) < 0) return 0;
            continue;
        }

        int status = printPath(output, path, target);
        freePath(path);

        if (status < 0) return 0;
    }

    return 1;
}


void freePath(Path *path) {
    if (!path) {
        return;
    }

    free(path->nodes);
    free(path);
}


void freeDRes(DRes *result) {
    if (!result) {
        return;
    }

    free(result->dist);
    free(result->prev);
    free(result);
}
