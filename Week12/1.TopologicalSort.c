#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex Vertex;
typedef struct Edge Edge;
typedef struct List List;
typedef struct Graph Graph;

struct Vertex {
    char name;
    int inDegree;
    List *lHead;
};

struct Edge {
    int origin, destination;
};

struct List {
    int edge;
    List *next;
};

struct Graph {
    Vertex *vArray;
    Edge *eArray;
    int n, m, i;
    int *topologicalOrder;
};

Graph G;

void initGraph();
int findIndex(char);
void insertEdge(char, char);
int topologicalSort();
void freeGraph();

int main() {
    char name1, name2;
    initGraph();
    for (int i = 0; i < G.m; i++) {
        scanf("%c %c", &name1, &name2);
        getchar();
        insertEdge(name1, name2);
    }
    int res = topologicalSort();
    if (res == 1) {
        for (int i = 1; i <= G.n; i++) {
            printf("%c ", G.vArray[G.topologicalOrder[i]].name);
        }
        printf("\n");
    } else {
        printf("0\n");
    }
    freeGraph();
    return 0;
}

void initGraph() {
    scanf("%d", &G.n);
    getchar();
    G.vArray = (Vertex *)malloc((G.n + 1) * sizeof(Vertex));
    for (int i = 1; i <= G.n; i++) {
        scanf("%c", &G.vArray[i].name);
        getchar();
        G.vArray[i].inDegree = 0;
        List *p = (List *)malloc(sizeof(List));
        p->next = NULL;
        G.vArray[i].lHead = p;
    }
    scanf("%d", &G.m);
    getchar();
    G.eArray = (Edge *)malloc((G.m + 1) * sizeof(Edge));
    for (int i = 1; i <= G.m; i++) {
        G.eArray[i].origin = 0;
        G.eArray[i].destination = 0;
    }
    G.topologicalOrder = (int *)malloc((G.n + 1) * sizeof(int));
    G.i = 1;
}

int findIndex(char name) {
    for (int i = 1; i <= G.n; i++) {
        if (G.vArray[i].name == name) {
            return i;
        }
    }
    return -1;
}

void insertEdge(char name1, char name2) {
    int v1 = findIndex(name1);
    int v2 = findIndex(name2);
    G.eArray[G.i].origin = v1;
    G.eArray[G.i].destination = v2;
    List *p = (List *)malloc(sizeof(List));
    List *q = G.vArray[v1].lHead;
    p->edge = G.i;
    p->next = q->next;
    q->next = p;
    G.vArray[v2].inDegree++;
    G.i++;
}

int topologicalSort() {
    int *Q = (int *)malloc(G.n * sizeof(int));
    int front = 0, rear = 0;
    for (int i = 1; i <= G.n; i++) {
        if (G.vArray[i].inDegree == 0) {
            Q[rear++] = i;
        }
    }
    int i = 1;
    while (front < rear) {
        int v1 = Q[front++];
        G.topologicalOrder[i] = v1;
        i++;
        List *p = G.vArray[v1].lHead->next;
        while (p != NULL) {
            int v2 = G.eArray[p->edge].destination;
            G.vArray[v2].inDegree--;
            if (G.vArray[v2].inDegree == 0) {
                Q[rear++] = v2;
            }
            p = p->next;
        }
    }
    free(Q);
    if (i <= G.n) {
        return 0;
    } else {
        return 1;
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
    free(G.topologicalOrder);
}