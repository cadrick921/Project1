#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NoSuchKey -1

typedef struct node {
    int key;
    struct node *parent, *left, *right;
} Node;

Node *root;

Node *getnode(Node *parent);
bool isInternal(Node *v);
bool isExternal(Node *v);
bool isRoot(Node *v);
Node *sibling(Node *v);

void initializeTree();
void expandExternal(Node *w);
Node *reduceExternal(Node *z);

Node *treeSearch(Node *v, int k);
Node *inOrderSucc(Node *w);
int findElement(int k);

void insertItem(int k);
int removeElement(int k);

void printTree(Node *v);
void deleteTree(Node *v);

int main() {
    char cmd;
    int k, e;

    initializeTree();

    while (scanf(" %c", &cmd) == 1) {
        if (cmd == 'i') {
            scanf("%d", &k);
            insertItem(k);
        } else if (cmd == 'd') {
            scanf("%d", &k);
            e = removeElement(k);
            if (e == NoSuchKey) {
                printf("X\n");
            } else {
                printf("%d\n", e);
            }
        } else if (cmd == 's') {
            scanf("%d", &k);
            e = findElement(k);
            if (e == NoSuchKey) {
                printf("X\n");
            } else {
                printf("%d\n", e);
            }
        } else if (cmd == 'p') {
            printTree(root);
            printf("\n");
        } else if (cmd == 'q') {
            break;
        }
    }

    deleteTree(root);
    root = NULL;
    return 0;
}

Node *getnode(Node *parent) {
    Node *v = (Node *)malloc(sizeof(Node));
    v->key = 0;
    v->parent = parent;
    v->left = NULL;
    v->right = NULL;
    return v;
}

bool isInternal(Node *v) { return v->left != NULL && v->right != NULL; }

bool isExternal(Node *v) { return v->left == NULL && v->right == NULL; }

bool isRoot(Node *v) { return v->parent == NULL; }

Node *sibling(Node *v) {
    Node *p = v->parent;
    if (p->left == v) {
        return p->right;
    } else {
        return p->left;
    }
}

void initializeTree() { root = getnode(NULL); }

void expandExternal(Node *w) {
    w->left = getnode(w);
    w->right = getnode(w);
}

Node *reduceExternal(Node *z) {
    Node *w = z->parent;
    Node *zs = sibling(z);

    if (isRoot(w)) {
        root = zs;
        zs->parent = NULL;
    } else {
        Node *g = w->parent;
        zs->parent = g;
        if (w == g->left) {
            g->left = zs;
        } else {
            g->right = zs;
        }
    }

    free(z);
    free(w);
    return zs;
}

Node *treeSearch(Node *v, int k) {
    if (isExternal(v)) {
        return v;
    }
    if (k == v->key) {
        return v;
    } else if (k < v->key) {
        return treeSearch(v->left, k);
    } else {
        return treeSearch(v->right, k);
    }
}

Node *inOrderSucc(Node *w) {
    w = w->right;
    while (isInternal(w->left)) {
        w = w->left;
    }
    return w;
}

int findElement(int k) {
    Node *w = treeSearch(root, k);
    if (isExternal(w)) {
        return NoSuchKey;
    } else {
        return w->key;
    }
}

void insertItem(int k) {
    Node *w = treeSearch(root, k);
    if (isInternal(w)) {
        return;
    }
    w->key = k;
    expandExternal(w);
}

int removeElement(int k) {
    Node *w = treeSearch(root, k);
    if (isExternal(w)) {
        return NoSuchKey;
    }

    int e = w->key;
    Node *z = w->left;
    if (!isExternal(z)) {
        z = w->right;
    }

    if (isExternal(z)) {
        reduceExternal(z);
    } else {
        Node *y = inOrderSucc(w);
        z = y->left;
        w->key = y->key;
        reduceExternal(z);
    }
    return e;
}

void printTree(Node *v) {
    if (isExternal(v)) {
        return;
    }
    printf(" %d", v->key);
    printTree(v->left);
    printTree(v->right);
}

void deleteTree(Node *v) {
    if (v == NULL) {
        return;
    }
    if (isInternal(v)) {
        deleteTree(v->left);
        deleteTree(v->right);
    }
    free(v);
}