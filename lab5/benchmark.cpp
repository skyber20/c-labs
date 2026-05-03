#include <benchmark/benchmark.h>

#include "graph.h"
#include "dijkstra.h"


static Graph *createBenchmarkGraph(int vertices, int edges) {
    Graph *g = createGraph(vertices);
    if (!g) {
        return nullptr;
    }

    for (int i = 1; i < vertices && g->numEdges < edges; i++) {
        addEdge(g, i, i + 1, 1);
    }

    for (int from = 1; from <= vertices && g->numEdges < edges; from++) {
        for (int to = 1; to <= vertices && g->numEdges < edges; to++) {
            if (from != to) {
                int weight = (from * 11 + to * 10) % 100 + 1;
                addEdge(g, from, to, weight);
            }
        }
    }

    return g;
}


static void BM_Dijkstra(benchmark::State& state) {
    int vertices = state.range(0);
    int edges = state.range(1);

    Graph *g = createBenchmarkGraph(vertices, edges);

    for (auto _ : state) {
        dijkstra(g, 1);
    }

    freeGraph(g);
}


BENCHMARK(BM_Dijkstra)
    ->Args({10, 50})
    ->Args({50, 250})
    ->Args({100, 500})
    ->Args({250, 1250})
    ->Args({500, 2500})
    ->Args({1000, 5000})
    ->Args({5000, 25000})
    ->Args({10000, 50000})
    ->Args({20000, 100000})
    ->ArgNames({"vertices", "edges"});


BENCHMARK_MAIN();
