#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Vertex Vertex;
typedef struct Edge Edge;
typedef struct List List;
typedef struct Graph Graph;

struct Vertex {
    int distance;
    int locator;
    int parent;
    List *lHead;
};

struct Edge {
    int weight;
    int vertex1, vertex2;
};

struct List {
    int edge;
    List *next;
};

struct Graph {
    Vertex *vArray;
    Edge *eArray;
    int *heap;
    int n, m, i, heapSize;
};

void initGraph();
void insertEdge(int, int, int);
void upHeap(int);
void downHeap(int);
int removeMin();
int opposite(int, int);
void primJarnikMST();
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
    primJarnikMST();
    freeGraph();
    return 0;
}

void initGraph() {
    G.vArray = (Vertex *)malloc((G.n + 1) * sizeof(Vertex));
    G.eArray = (Edge *)malloc((G.m + 1) * sizeof(Edge));
    G.heap = (int *)malloc((G.n + 1) * sizeof(int));
    for (int i = 1; i <= G.n; i++) {
        G.vArray[i].distance = INT_MAX;
        G.vArray[i].locator = i;
        G.vArray[i].parent = 0;
        List *p = (List *)malloc(sizeof(List));
        p->next = NULL;
        G.vArray[i].lHead = p;
        G.heap[i] = i;
    }
    G.vArray[1].distance = 0;
    for (int i = 1; i <= G.m; i++) {
        G.eArray[i].vertex1 = 0;
        G.eArray[i].vertex2 = 0;
    }
    G.heapSize = G.n;
    G.i = 1;
}

void insertEdge(int v1, int v2, int w) {
    G.eArray[G.i].vertex1 = v1;
    G.eArray[G.i].vertex2 = v2;
    G.eArray[G.i].weight = w;
    List *p = (List *)malloc(sizeof(List));
    List *q = G.vArray[v1].lHead;
    p->edge = G.i;
    p->next = q->next;
    q->next = p;
    p = (List *)malloc(sizeof(List));
    q = G.vArray[v2].lHead;
    p->edge = G.i;
    p->next = q->next;
    q->next = p;
    G.i++;
}

void upHeap(int i) {
    int parent = i / 2;
    if (parent == 0) {
        return;
    }
    if (G.vArray[G.heap[parent]].distance <= G.vArray[G.heap[i]].distance) {
        return;
    }
    int tmp = G.heap[i];
    G.heap[i] = G.heap[parent];
    G.heap[parent] = tmp;
    G.vArray[G.heap[i]].locator = i;
    G.vArray[G.heap[parent]].locator = parent;
    upHeap(parent);
}

void downHeap(int i) {
    int left = i * 2;
    int right = i * 2 + 1;
    if (left > G.heapSize) {
        return;
    }
    int smaller = left;
    if (right <= G.heapSize) {
        if (G.vArray[G.heap[right]].distance <
            G.vArray[G.heap[left]].distance) {
            smaller = right;
        }
    }
    if (G.vArray[G.heap[smaller]].distance >= G.vArray[G.heap[i]].distance) {
        return;
    }
    int tmp = G.heap[i];
    G.heap[i] = G.heap[smaller];
    G.heap[smaller] = tmp;
    G.vArray[G.heap[i]].locator = i;
    G.vArray[G.heap[smaller]].locator = smaller;
    downHeap(smaller);
}

int removeMin() {
    int min = G.heap[1];
    G.heap[1] = G.heap[G.heapSize];
    G.vArray[G.heap[1]].locator = 1;
    G.vArray[min].locator = 0;
    G.heapSize--;
    downHeap(1);
    return min;
}

int opposite(int v, int e) {
    if (G.eArray[e].vertex1 == v) {
        return G.eArray[e].vertex2;
    } else {
        return G.eArray[e].vertex1;
    }
}

void primJarnikMST() {
    int sum = 0;
    while (G.heapSize != 0) {
        int v1 = removeMin();
        printf("%d ", v1);
        sum += G.vArray[v1].distance;
        List *p = G.vArray[v1].lHead->next;
        while (p != NULL) {
            int v2 = opposite(v1, p->edge);
            if (G.vArray[v2].locator != 0 &&
                G.eArray[p->edge].weight < G.vArray[v2].distance) {
                G.vArray[v2].distance = G.eArray[p->edge].weight;
                G.vArray[v2].parent = p->edge;
                upHeap(G.vArray[v2].locator);
            }
            p = p->next;
        }
    }
    printf("\n%d\n", sum);
}

void freeGraph() {
    for (int i = 1; i <= G.n; i++) {
        List *p = G.vArray[i].lHead;
        while (p != NULL) {
            List *q = p->next;
            free(p);
            p = q;
        }
    }
    free(G.vArray);
    free(G.eArray);
    free(G.heap);
}