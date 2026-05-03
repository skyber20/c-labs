#include <gtest/gtest.h>

#include "graph.h"
#include "dijkstra.h"


TEST(GraphTest, CreateGraph) {
    Graph *g = createGraph(5);

    EXPECT_NE(g, nullptr);
    if (!g) return;

    EXPECT_EQ(g->numNodes, 5);
    EXPECT_EQ(g->numEdges, 0);
    EXPECT_EQ(g->capacity, 0);
    EXPECT_EQ(g->edges, nullptr);

    freeGraph(g);
}


TEST(GraphTest, RejectInvalidNodeCount) {
    EXPECT_EQ(createGraph(0), nullptr);
    EXPECT_EQ(createGraph(-3), nullptr);
}


TEST(GraphTest, AddEdge) {
    Graph *g = createGraph(3);

    EXPECT_EQ(addEdge(g, 1, 2, 10), 1);
    if (g->numEdges == 0) {
        freeGraph(g);
        return;
    }

    EXPECT_EQ(g->numEdges, 1);
    EXPECT_EQ(g->edges[0].from, 1);
    EXPECT_EQ(g->edges[0].to, 2);
    EXPECT_EQ(g->edges[0].weight, 10);

    freeGraph(g);
}


TEST(GraphTest, RejectBadEdges) {
    Graph *g = createGraph(3);

    EXPECT_EQ(addEdge(g, 0, 2, 10), 0);
    EXPECT_EQ(addEdge(g, 1, 4, 10), 0);
    EXPECT_EQ(addEdge(g, 1, 1, 10), 0);
    EXPECT_EQ(addEdge(g, 1, 2, -5), 0);
    EXPECT_EQ(g->numEdges, 0);

    freeGraph(g);
}


TEST(DijkstraTest, FindsShortestPaths) {
    Graph *g = createGraph(5);
    addEdge(g, 1, 2, 10);
    addEdge(g, 1, 3, 3);
    addEdge(g, 3, 2, 4);
    addEdge(g, 2, 4, 2);
    addEdge(g, 3, 5, 8);
    addEdge(g, 4, 5, 1);

    DRes *res = dijkstra(g, 1);

    EXPECT_NE(res, nullptr);
    if (!res) {
        freeGraph(g);
        return;
    }

    EXPECT_EQ(res->dist[0], 0);
    EXPECT_EQ(res->dist[1], 7);
    EXPECT_EQ(res->dist[2], 3);
    EXPECT_EQ(res->dist[3], 9);
    EXPECT_EQ(res->dist[4], 10);

    Path *path = restorePath(res, 5);
    EXPECT_NE(path, nullptr);
    if (!path) {
        freeDRes(res);
        freeGraph(g);
        return;
    }

    EXPECT_EQ(path->totalWeight, 10);
    EXPECT_EQ(path->len, 5);
    if (path->len == 5) {
        EXPECT_EQ(path->nodes[0], 1);
        EXPECT_EQ(path->nodes[1], 3);
        EXPECT_EQ(path->nodes[2], 2);
        EXPECT_EQ(path->nodes[3], 4);
        EXPECT_EQ(path->nodes[4], 5);
    }

    freePath(path);
    freeDRes(res);
    freeGraph(g);
}


TEST(DijkstraTest, RejectInvalidStart) {
    Graph *g = createGraph(3);

    EXPECT_EQ(dijkstra(g, 0), nullptr);
    EXPECT_EQ(dijkstra(g, 4), nullptr);
    EXPECT_EQ(dijkstra(nullptr, 1), nullptr);

    freeGraph(g);
}
