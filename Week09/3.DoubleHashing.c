#include <stdio.h>
#include <stdlib.h>

int *A, M, n, q;

int h1(int);
int h2(int);
int getNextBucket(int, int, int);

void initBucketArray();
int insertItem(int);
int findElement(int);
void printBucketArray();
void freeBucketArray();

int main() {
    char cmd;
    int k, b;
    scanf("%d %d %d", &M, &n, &q);
    getchar();
    initBucketArray();
    while (1) {
        scanf("%c", &cmd);
        getchar();
        if (cmd == 'i') {
            scanf("%d", &k);
            getchar();
            printf("%d\n", insertItem(k));
        } else if (cmd == 's') {
            scanf("%d", &k);
            getchar();
            b = findElement(k);
            if (b == -1) {
                printf("-1\n");
            } else {
                printf("%d %d\n", b, A[b]);
            }
        } else if (cmd == 'p') {
            printBucketArray();
        } else {
            printBucketArray();
            break;
        }
    }
    freeBucketArray();
    return 0;
}

int h1(int x) {
    return x % M;
}

int h2(int x) {
    return q - (x % q);
}

int getNextBucket(int v, int k, int i) {
    return (v + i * h2(k)) % M;
}

void initBucketArray() {
    A = (int *)malloc(M * sizeof(int));
    for (int i = 0; i < M; i++) {
        A[i] = 0;
    }
}

int insertItem(int k) {
    int v = h1(k);
    int i = 0;
    while (i < M) {
        int b = getNextBucket(v, k, i);
        if (A[b] == 0) {
            A[b] = k;
            return b;
        } else {
            printf("C");
            i++;
        }
    }
    return -1;
}

int findElement(int k) {
    int v = h1(k);
    int i = 0;
    while (i < M) {
        int b = getNextBucket(v, k, i);
        if (A[b] == 0) {
            return -1;
        } else if (A[b] == k) {
            return b;
        } else {
            i++;
        }
    }
    return -1;
}

void printBucketArray() {
    for (int i = 0; i < M; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void freeBucketArray() {
    free(A);
}