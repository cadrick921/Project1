#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge Edge;
typedef struct Graph Graph;

struct Edge {
    int weight;
    int origin, destination;
};

struct Graph {
    Edge *eArray;
    int *distance;
    int n, m, i;
    int start;
};

void initGraph();
void insertEdge(int, int, int);
void bellmanFordShortestPaths();
void freeGraph();

Graph G;

int main() {
    int origin, destination, weight;
    scanf("%d %d %d", &G.n, &G.m, &G.start);
    initGraph();
    for (int i = 0; i < G.m; i++) {
        scanf("%d %d %d", &origin, &destination, &weight);
        insertEdge(origin, destination, weight);
    }
    bellmanFordShortestPaths();
    freeGraph();
    return 0;
}

void initGraph() {
    G.eArray = (Edge *)malloc((G.m + 1) * sizeof(Edge));
    G.distance = (int *)malloc((G.n + 1) * sizeof(int));
    for (int i = 1; i <= G.n; i++) {
        G.distance[i] = INT_MAX;
    }
    G.distance[G.start] = 0;
    G.i = 1;
}

void insertEdge(int o, int d, int w) {
    G.eArray[G.i].origin = o;
    G.eArray[G.i].destination = d;
    G.eArray[G.i].weight = w;
    G.i++;
}

void bellmanFordShortestPaths() {
    for (int i = 1; i < G.n; i++) {
        for (int j = 1; j <= G.m; j++) {
            int o = G.eArray[j].origin;
            int d = G.eArray[j].destination;
            if (G.distance[o] != INT_MAX && G.distance[o] + G.eArray[j].weight < G.distance[d]) {
                G.distance[d] = G.distance[o] + G.eArray[j].weight;
            }
        }
    }
    for (int i = 1; i <= G.n; i++) {
        if (i != G.start && G.distance[i] != INT_MAX) {
            printf("%d %d\n", i, G.distance[i]);
        }
    }
}

void freeGraph() {
    free(G.eArray);
    free(G.distance);
}