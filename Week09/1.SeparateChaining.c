#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} Node;

Node **A;
int M;

int h(int);

void initBucketArray();
void insertItem(int);
int findElement(int);
int removeElement(int);
void printBucketArray();
void freeBucketArray();

int main() {
    char cmd;
    int k;
    scanf("%d", &M);
    getchar();
    initBucketArray();
    while (1) {
        scanf("%c", &cmd);
        getchar();
        if (cmd == 'i') {
            scanf("%d", &k);
            getchar();
            insertItem(k);
        } else if (cmd == 's') {
            scanf("%d", &k);
            getchar();
            printf("%d\n", findElement(k));
        } else if (cmd == 'd') {
            scanf("%d", &k);
            getchar();
            printf("%d\n", removeElement(k));
        } else if (cmd == 'p') {
            printBucketArray();
        } else {
            break;
        }
    }
    freeBucketArray();
    return 0;
}

int h(int x) {
    return x % M;
}

void initBucketArray() {
    A = (Node **)malloc(M * sizeof(Node *));
    for (int i = 0; i < M; i++) {
        A[i] = NULL;
    }
}

void insertItem(int k) {
    int v = h(k);
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = k;
    p->next = A[v];
    A[v] = p;
}

int findElement(int k) {
    int v = h(k);
    Node *p = A[v];
    int i = 1;
    while (p != NULL) {
        if (p->key == k) {
            return i;
        } else {
            p = p->next;
            i++;
        }
    }
    return 0;
}

int removeElement(int k) {
    int v = h(k);
    Node *p = A[v];
    Node *q = NULL;
    int i = 1;
    while (p != NULL) {
        if (p->key == k) {
            if (q == NULL) {
                A[v] = p->next;
            } else {
                q->next = p->next;
            }
            free(p);
            return i;
        } else {
            q = p;
            p = p->next;
            i++;
        }
    }
    return 0;
}

void printBucketArray() {
    for (int i = 0; i < M; i++) {
        Node *p = A[i];
        while (p != NULL) {
            printf("%d ", p->key);
            p = p->next;
        }
    }
    printf("\n");
}

void freeBucketArray() {
    for (int i = 0; i < M; i++) {
        Node *p = A[i];
        while (p != NULL) {
            Node *q = p->next;
            free(p);
            p = q;
        }
    }
    free(A);
}