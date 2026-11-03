#include <stdio.h>
#include <stdlib.h>

#define FRESH 0
#define VISITED 1
#define TREE 2
#define BACK 3

typedef struct Vertex Vertex;
typedef struct Edge Edge;
typedef struct List List;
typedef struct Graph Graph;

struct Vertex {
    int label;
    List *lHead;
};

struct Edge {
    int label;
    int vertex1, vertex2;
};

struct List {
    int edge;
    List *next;
};

struct Graph {
    Vertex *vArray;
    Edge *eArray;
    int n, m, i;
};

void initGraph();
int opposite(int, int);
void insertEdge(int, int);
void DFS(int);
void freeGraph();

Graph G;

int main() {
    int s, v1, v2;
    scanf("%d %d %d", &G.n, &G.m, &s);
    initGraph();
    for (int i = 0; i < G.m; i++) {
        scanf("%d %d", &v1, &v2);
        insertEdge(v1, v2);
    }
    DFS(s);
    freeGraph();
    return 0;
}

void initGraph() {
    G.vArray = (Vertex *)malloc((G.n + 1) * sizeof(Vertex));
    for (int i = 1; i <= G.n; i++) {
        G.vArray[i].label = FRESH;
        List *p = (List *)malloc(sizeof(List));
        p->next = NULL;
        G.vArray[i].lHead = p;
    }
    G.eArray = (Edge *)malloc((G.m + 1) * sizeof(Edge));
    for (int i = 1; i <= G.m; i++) {
        G.eArray[i].label = FRESH;
        G.eArray[i].vertex1 = 0;
        G.eArray[i].vertex2 = 0;
    }
    G.i = 1;
}

int opposite(int v, int e) {
    if (G.eArray[e].vertex1 == v) {
        return G.eArray[e].vertex2;
    } else {
        return G.eArray[e].vertex1;
    }
}

void insertEdge(int v1, int v2) {
    G.eArray[G.i].vertex1 = v1;
    G.eArray[G.i].vertex2 = v2;
    List *p = (List *)malloc(sizeof(List));
    p->edge = G.i;
    p->next = NULL;
    List *q = G.vArray[v1].lHead;
    while (q->next != NULL && opposite(v1, q->next->edge) < v2) {
        q = q->next;
    }
    p->next = q->next;
    q->next = p;
    p = (List *)malloc(sizeof(List));
    p->edge = G.i;
    q = G.vArray[v2].lHead;
    while (q->next != NULL && opposite(v2, q->next->edge) < v1) {
        q = q->next;
    }
    p->next = q->next;
    q->next = p;
    G.i++;
}

void DFS(int v1) {
    printf("%d\n", v1);
    G.vArray[v1].label = VISITED;
    List *p = G.vArray[v1].lHead->next;
    while (p != NULL) {
        if (G.eArray[p->edge].label == FRESH) {
            int v2 = opposite(v1, p->edge);
            if (G.vArray[v2].label == FRESH) {
                G.eArray[p->edge].label = TREE;
                DFS(v2);
            } else {
                G.eArray[p->edge].label = BACK;
            }
        }
        p = p->next;
    }
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
}