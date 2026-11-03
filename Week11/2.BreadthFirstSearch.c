#include <stdio.h>
#include <stdlib.h>

#define FRESH 0
#define VISITED 1
#define TREE 2
#define CROSS 3

typedef struct Vertex Vertex;
typedef struct Edge Edge;
typedef struct Matrix Matrix;
typedef struct Graph Graph;

struct Vertex {
    int label;
};

struct Edge {
    int label;
    int vertex1, vertex2;
};

struct Matrix {
    int **edge;
};

struct Graph {
    Vertex *vArray;
    Edge *eArray;
    Matrix adj;
    int n, m, i;
};

Graph G;

void initGraph();
void insertEdge(int, int);
void BFS(int);
void freeGraph();

int main() {
    int s, v1, v2;
    scanf("%d %d %d", &G.n, &G.m, &s);
    initGraph();
    for (int i = 0; i < G.m; i++) {
        scanf("%d %d", &v1, &v2);
        insertEdge(v1, v2);
    }
    BFS(s);
    freeGraph();
    return 0;
}

void initGraph() {
    G.vArray = (Vertex *)malloc((G.n + 1) * sizeof(Vertex));
    for (int i = 1; i <= G.n; i++) {
        G.vArray[i].label = FRESH;
    }
    G.eArray = (Edge *)malloc((G.m + 1) * sizeof(Edge));
    for (int i = 1; i <= G.m; i++) {
        G.eArray[i].label = FRESH;
        G.eArray[i].vertex1 = 0;
        G.eArray[i].vertex2 = 0;
    }
    G.adj.edge = (int **)malloc((G.n + 1) * sizeof(int *));
    for (int i = 0; i <= G.n; i++) {
        G.adj.edge[i] = (int *)malloc((G.n + 1) * sizeof(int));
    }
    for (int i = 1; i <= G.n; i++) {
        for (int j = 1; j <= G.n; j++) {
            G.adj.edge[i][j] = -1;
        }
    }
    G.i = 1;
}

void insertEdge(int v1, int v2) {
    G.eArray[G.i].vertex1 = v1;
    G.eArray[G.i].vertex2 = v2;
    G.adj.edge[v1][v2] = G.i;
    G.adj.edge[v2][v1] = G.i;
    G.i++;
}

void BFS(int v) {
    int *Q = (int *)malloc(G.n * sizeof(int));
    int front = 0, rear = 0;
    printf("%d\n", v);
    G.vArray[v].label = VISITED;
    Q[rear++] = v;
    while (front < rear) {
        int v = Q[front++];
        for (int i = 1; i <= G.n; i++) {
            int e = G.adj.edge[v][i];
            if (e != -1 && G.eArray[e].label == FRESH) {
                if (G.vArray[i].label == FRESH) {
                    G.eArray[e].label = TREE;
                    G.vArray[i].label = VISITED;
                    printf("%d\n", i);
                    Q[rear++] = i;
                } else {
                    G.eArray[e].label = CROSS;
                }
            }
        }
    }
    free(Q);
}

void freeGraph() {
    for (int i = 0; i <= G.n; i++) {
        free(G.adj.edge[i]);
    }
    free(G.adj.edge);
    free(G.vArray);
    free(G.eArray);
}