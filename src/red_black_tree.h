#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

typedef enum Color {RED, BLACK} Color;

typedef struct treeNode {
    Color color;
    int key;
    struct treeNode *left;
    struct treeNode *right;
    struct treeNode *parent;
} treeNode;

typedef struct redBlackTree {
    treeNode *root;
    treeNode *nil;

} redBlackTree;

redBlackTree *initializeTree();

void leftRotate(redBlackTree *tree, treeNode *x);

void rightRotate(redBlackTree *tree, treeNode *x);

void rbInsert(redBlackTree *tree, int data);

void rbInsertFixup(redBlackTree *tree, treeNode *z);

treeNode *rbMaximum(redBlackTree *tree, treeNode *node);

treeNode *rbMinimum(redBlackTree *tree, treeNode *node);

void rbTransplant(redBlackTree *tree, treeNode *u, treeNode *v);

void rbDelete(redBlackTree *tree, treeNode *t);

void rbDeleteFixup(redBlackTree *tree, treeNode *x);

void destroyTreeHelper(treeNode *node, treeNode *nil);

void destroyTree(redBlackTree *tree);

#endif
