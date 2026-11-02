#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex Vertex;
typedef struct Edge Edge;
typedef struct Matrix Matrix;
typedef struct Graph Graph;

struct Vertex {
    int number;
    Vertex *next;
};

struct Edge {
    int weight;
    Vertex *v1, *v2;
    Edge *next;
};

struct Matrix {
    Edge *e[6][6];
};

struct Graph {
    Vertex *vHead, *vTail;
    Edge *eHead, *eTail;
    Matrix m;
};

void initGraph();
void insertVertex(int);
void insertEdge(int, int, int);
void adjacentVertices(int);
void modifyEdge(int, int, int);
void freeGraph();

Graph g;

int main() {
    char c;
    int n, n1, n2, w;
    initGraph();
    while (1) {
        scanf("%c", &c);
        getchar();
        if (c == 'a') {
            scanf("%d", &n);
            getchar();
            adjacentVertices(n);
        } else if (c == 'm') {
            scanf("%d %d %d", &n1, &n2, &w);
            getchar();
            modifyEdge(n1, n2, w);
        } else {
            break;
        }
    }
    freeGraph();
    return 0;
}

void initGraph() {
    g.vHead = NULL;
    g.vTail = NULL;
    g.eHead = NULL;
    g.eTail = NULL;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            g.m.e[i][j] = NULL;
        }
    }
    insertVertex(1);
    insertVertex(2);
    insertVertex(3);
    insertVertex(4);
    insertVertex(5);
    insertVertex(6);
    insertEdge(1, 2, 1);
    insertEdge(1, 3, 1);
    insertEdge(1, 4, 1);
    insertEdge(1, 6, 2);
    insertEdge(2, 3, 1);
    insertEdge(3, 5, 4);
    insertEdge(5, 5, 4);
    insertEdge(5, 6, 3);
}

void insertVertex(int n) {
    Vertex *v = (Vertex *)malloc(sizeof(Vertex));
    v->number = n;
    v->next = NULL;
    if (g.vHead == NULL) {
        g.vHead = v;
    } else {
        g.vTail->next = v;
    }
    g.vTail = v;
}

void insertEdge(int n1, int n2, int w) {
    Vertex *u = g.vHead;
    while (u != NULL) {
        if (u->number == n1) {
            break;
        }
        u = u->next;
    }
    Vertex *v = g.vHead;
    while (v != NULL) {
        if (v->number == n2) {
            break;
        }
        v = v->next;
    }
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->weight = w;
    e->v1 = u;
    e->v2 = v;
    e->next = NULL;
    if (g.eHead == NULL) {
        g.eHead = e;
    } else {
        g.eTail->next = e;
    }
    g.eTail = e;
    g.m.e[n1 - 1][n2 - 1] = e;
    g.m.e[n2 - 1][n1 - 1] = e;
}

void adjacentVertices(int n) {
    Vertex *u = g.vHead;
    while (u != NULL) {
        if (u->number == n) {
            break;
        }
        u = u->next;
    }
    if (u == NULL) {
        printf("-1\n");
        return;
    }
    for (int i = 0; i < 6; i++) {
        Edge *e = g.m.e[n - 1][i];
        if (e != NULL) {
            if (e->v1 == u) {
                printf("%d %d ", e->v2->number, e->weight);
            } else {
                printf("%d %d ", e->v1->number, e->weight);
            }
        }
    }
    printf("\n");
}

void modifyEdge(int n1, int n2, int w) {
    Vertex *u = g.vHead;
    while (u != NULL) {
        if (u->number == n1) {
            break;
        }
        u = u->next;
    }
    Vertex *v = g.vHead;
    while (v != NULL) {
        if (v->number == n2) {
            break;
        }
        v = v->next;
    }
    if (u == NULL || v == NULL) {
        printf("-1\n");
        return;
    }
    Edge *e = g.m.e[n1 - 1][n2 - 1];
    if (e == NULL) {
        insertEdge(n1, n2, w);
    } else if (w == 0) {
        g.m.e[n1 - 1][n2 - 1] = NULL;
        g.m.e[n2 - 1][n1 - 1] = NULL;
        Edge *prev = NULL;
        Edge *cur = g.eHead;
        while (cur != e) {
            prev = cur;
            cur = cur->next;
        }
        if (prev == NULL) {
            g.eHead = e->next;
        } else {
            prev->next = e->next;
        }
        if (g.eTail == e) {
            g.eTail = prev;
        }
        free(e);
    } else {
        e->weight = w;
    }
}

void freeGraph() {
    Vertex *v = g.vHead;
    while (v != NULL) {
        Vertex *vNext = v->next;
        free(v);
        v = vNext;
    }
    Edge *e = g.eHead;
    while (e != NULL) {
        Edge *eNext = e->next;
        free(e);
        e = eNext;
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            g.m.e[i][j] = NULL;
        }
    }
    g.vHead = NULL;
    g.vTail = NULL;
    g.eHead = NULL;
    g.eTail = NULL;
}