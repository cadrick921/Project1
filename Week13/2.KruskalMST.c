#include <stdio.h>
#include <stdlib.h>

typedef struct Edge Edge;
typedef struct Graph Graph;

struct Edge {
    int weight;
    int vertex1, vertex2;
};

struct Graph {
    Edge *eArray;
    int *sack;
    int *size;
    int *heap;
    int n, m, i, heapSize;
};

void initGraph();
void insertEdge(int, int, int);
void downHeap(int);
void buildHeap();
int removeMin();
void unionSack(int, int);
void kruskalMST();
void freeGraph();

Graph G;

int main() {
    int vertex1, vertex2, weight;
    scanf("%d %d", &G.n, &G.m);
    initGraph();
    for (int i = 0; i < G.m; i++) {
        scanf("%d %d %d", &vertex1, &vertex2, &weight);
        insertEdge(vertex1, vertex2, weight);
    }
    kruskalMST();
    freeGraph();
    return 0;
}

void initGraph() {
    G.eArray = (Edge *)malloc((G.m + 1) * sizeof(Edge));
    G.sack = (int *)malloc((G.n + 1) * sizeof(int));
    G.size = (int *)malloc((G.n + 1) * sizeof(int));
    G.heap = (int *)malloc((G.m + 1) * sizeof(int));
    for (int i = 1; i <= G.n; i++) {
        G.sack[i] = i;
        G.size[i] = 1;
    }
    G.i = 1;
    G.heapSize = 0;
}

void insertEdge(int v1, int v2, int w) {
    G.eArray[G.i].vertex1 = v1;
    G.eArray[G.i].vertex2 = v2;
    G.eArray[G.i].weight = w;
    G.i++;
}

void downHeap(int i) {
    int left = i * 2;
    int right = i * 2 + 1;
    if (left > G.heapSize) {
        return;
    }
    int smaller = left;
    if (right <= G.heapSize) {
        if (G.eArray[G.heap[right]].weight < G.eArray[G.heap[left]].weight) {
            smaller = right;
        }
    }
    if (G.eArray[G.heap[smaller]].weight >= G.eArray[G.heap[i]].weight) {
        return;
    }
    int tmp = G.heap[i];
    G.heap[i] = G.heap[smaller];
    G.heap[smaller] = tmp;
    downHeap(smaller);
}

void buildHeap() {
    for (int i = 1; i <= G.m; i++) {
        G.heap[i] = i;
    }
    G.heapSize = G.m;
    for (int i = G.heapSize / 2; i >= 1; i--) {
        downHeap(i);
    }
}

int removeMin() {
    int min = G.heap[1];
    G.heap[1] = G.heap[G.heapSize];
    G.heapSize--;
    downHeap(1);
    return min;
}

void unionSack(int v1, int v2) {
    int a = G.sack[v1];
    int b = G.sack[v2];
    if (G.size[a] > G.size[b]) {
        for (int i = 1; i <= G.n; i++) {
            if (G.sack[i] == b) {
                G.sack[i] = a;
            }
        }
        G.size[a] += G.size[b];
    } else {
        for (int i = 1; i <= G.n; i++) {
            if (G.sack[i] == a) {
                G.sack[i] = b;
            }
        }
        G.size[b] += G.size[a];
    }
}

void kruskalMST() {
    int sum = 0, i = 0;
    buildHeap();
    while (i < G.n - 1) {
        int e = removeMin();
        int v1 = G.eArray[e].vertex1;
        int v2 = G.eArray[e].vertex2;
        if (G.sack[v1] != G.sack[v2]) {
            int w = G.eArray[e].weight;
            printf("%d ", w);
            sum += w;
            unionSack(v1, v2);
            i++;
        }
    }
    printf("\n%d\n", sum);
}

void freeGraph() {
    free(G.eArray);
    free(G.sack);
    free(G.size);
    free(G.heap);
}