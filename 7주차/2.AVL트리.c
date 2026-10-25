#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NoSuchKey -1

typedef struct node {
    int key;
    int height;
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

void updateHeight(Node *v);
bool isBalanced(Node *v);
Node *tallerChild(Node *v);
Node *restructure(Node *x, Node *y, Node *z);

Node *treeSearch(Node *v, int k);
Node *inOrderSucc(Node *w);
int findElement(int k);

void insertItem(int k);
void searchAndFixAfterInsertion(Node *w);
int removeElement(int k);
void searchAndFixAfterRemoval(Node *w);

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
    v->height = 0;
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
    w->height = 1;
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

void updateHeight(Node *v) {
    int l = v->left->height;
    int r = v->right->height;
    if (l > r) {
        v->height = l + 1;
    } else {
        v->height = r + 1;
    }
}

bool isBalanced(Node *v) {
    int diff = v->left->height - v->right->height;
    return -1 <= diff && diff <= 1;
}

Node *tallerChild(Node *v) {
    if (v->left->height > v->right->height) {
        return v->left;
    } else {
        return v->right;
    }
}

Node *restructure(Node *x, Node *y, Node *z) {
    Node *a, *b, *c;
    Node *t0, *t1, *t2, *t3;

    if (z->key < y->key && y->key < x->key) {
        a = z;
        b = y;
        c = x;
        t0 = a->left;
        t1 = b->left;
        t2 = c->left;
        t3 = c->right;
    } else if (x->key < y->key && y->key < z->key) {
        a = x;
        b = y;
        c = z;
        t0 = a->left;
        t1 = a->right;
        t2 = b->right;
        t3 = c->right;
    } else if (z->key < x->key && x->key < y->key) {
        a = z;
        b = x;
        c = y;
        t0 = a->left;
        t1 = b->left;
        t2 = b->right;
        t3 = c->right;
    } else {
        a = y;
        b = x;
        c = z;
        t0 = a->left;
        t1 = b->left;
        t2 = b->right;
        t3 = c->right;
    }

    if (isRoot(z)) {
        root = b;
        b->parent = NULL;
    } else {
        Node *g = z->parent;
        if (z == g->left) {
            g->left = b;
        } else {
            g->right = b;
        }
        b->parent = g;
    }

    a->left = t0;
    t0->parent = a;
    a->right = t1;
    t1->parent = a;
    updateHeight(a);

    c->left = t2;
    t2->parent = c;
    c->right = t3;
    t3->parent = c;
    updateHeight(c);

    b->left = a;
    a->parent = b;
    b->right = c;
    c->parent = b;
    updateHeight(b);

    return b;
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
    searchAndFixAfterInsertion(w);
}

void searchAndFixAfterInsertion(Node *w) {
    Node *z = w;
    while (isBalanced(z)) {
        if (isRoot(z)) {
            return;
        }
        z = z->parent;
        updateHeight(z);
    }

    Node *y = tallerChild(z);
    Node *x = tallerChild(y);
    restructure(x, y, z);
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

    Node *zs;
    if (isExternal(z)) {
        zs = reduceExternal(z);
    } else {
        Node *y = inOrderSucc(w);
        z = y->left;
        w->key = y->key;
        zs = reduceExternal(z);
    }

    searchAndFixAfterRemoval(zs->parent);
    return e;
}

void searchAndFixAfterRemoval(Node *w) {
    if (w == NULL) {
        return;
    }

    Node *z = w;
    updateHeight(z);
    while (isBalanced(z)) {
        if (isRoot(z)) {
            return;
        }
        z = z->parent;
        updateHeight(z);
    }

    Node *y = tallerChild(z);
    Node *x;
    if (y->left->height > y->right->height) {
        x = y->left;
    } else if (y->left->height < y->right->height) {
        x = y->right;
    } else if (y == z->left) {
        x = y->left;
    } else {
        x = y->right;
    }

    Node *b = restructure(x, y, z);
    searchAndFixAfterRemoval(b->parent);
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