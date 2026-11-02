#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex Vertex;
typedef struct Edge Edge;
typedef struct List List;
typedef struct Graph Graph;

struct Vertex {
    int number;
    List *lHead, *lTail;
    Vertex *next;
};

struct Edge {
    int weight;
    Vertex *v1, *v2;
    Edge *next;
};

struct List {
    Edge *e;
    List *next;
};

struct Graph {
    Vertex *vHead, *vTail;
    Edge *eHead, *eTail;
};

void initGraph();
void insertVertex(int);
void insertEdge(int, int, int);
void removeEdge(int, int);
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
    v->lHead = NULL;
    v->lTail = NULL;
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
    List *l1 = (List *)malloc(sizeof(List));
    l1->e = e;
    List *cur = u->lHead, *prev = NULL;
    while (cur != NULL) {
        Vertex *o;
        if (cur->e->v1 == u) {
            o = cur->e->v2;
        } else {
            o = cur->e->v1;
        }
        if (o->number > v->number) {
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    l1->next = cur;
    if (prev == NULL) {
        u->lHead = l1;
    } else {
        prev->next = l1;
    }
    if (cur == NULL) {
        u->lTail = l1;
    }
    if (u == v) {
        return;
    }
    List *l2 = (List *)malloc(sizeof(List));
    l2->e = e;
    cur = v->lHead;
    prev = NULL;
    while (cur != NULL) {
        Vertex *o;
        if (cur->e->v1 == v) {
            o = cur->e->v2;
        } else {
            o = cur->e->v1;
        }
        if (o->number > u->number) {
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    l2->next = cur;
    if (prev == NULL) {
        v->lHead = l2;
    } else {
        prev->next = l2;
    }
    if (cur == NULL) {
        v->lTail = l2;
    }
}

void removeEdge(int n1, int n2) {
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
        return;
    }
    Edge *e = g.eHead, *ePrev = NULL;
    while (e != NULL) {
        if ((e->v1 == u && e->v2 == v) || (e->v1 == v && e->v2 == u)) {
            break;
        }
        ePrev = e;
        e = e->next;
    }
    if (e == NULL) {
        return;
    }
    List *l1 = u->lHead, *lPrev = NULL;
    while (l1 != NULL) {
        if (l1->e == e) {
            break;
        }
        lPrev = l1;
        l1 = l1->next;
    }
    if (l1 != NULL) {
        if (lPrev == NULL) {
            u->lHead = l1->next;
        } else {
            lPrev->next = l1->next;
        }
        if (u->lTail == l1) {
            u->lTail = lPrev;
        }
        free(l1);
    }
    if (u != v) {
        List *l2 = v->lHead;
        lPrev = NULL;
        while (l2 != NULL) {
            if (l2->e == e) {
                break;
            }
            lPrev = l2;
            l2 = l2->next;
        }
        if (l2 != NULL) {
            if (lPrev == NULL) {
                v->lHead = l2->next;
            } else {
                lPrev->next = l2->next;
            }
            if (v->lTail == l2) {
                v->lTail = lPrev;
            }
            free(l2);
        }
    }
    if (ePrev == NULL) {
        g.eHead = e->next;
    } else {
        ePrev->next = e->next;
    }
    if (g.eTail == e) {
        g.eTail = ePrev;
    }
    free(e);
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
    List *l = u->lHead;
    while (l != NULL) {
        if (l->e->v1 == u) {
            printf("%d ", l->e->v2->number);
        } else {
            printf("%d ", l->e->v1->number);
        }
        printf("%d ", l->e->weight);
        l = l->next;
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
    List *l = u->lHead;
    while (l != NULL) {
        if ((l->e->v1 == u && l->e->v2 == v) ||
            (l->e->v1 == v && l->e->v2 == u)) {
            break;
        }
        l = l->next;
    }
    if (l == NULL) {
        insertEdge(n1, n2, w);
    } else if (w == 0) {
        removeEdge(n1, n2);
    } else {
        l->e->weight = w;
    }
}

void freeGraph() {
    Vertex *v = g.vHead;
    while (v != NULL) {
        List *l = v->lHead;
        while (l != NULL) {
            List *lNext = l->next;
            free(l);
            l = lNext;
        }
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
    g.vHead = NULL;
    g.vTail = NULL;
    g.eHead = NULL;
    g.eTail = NULL;
}