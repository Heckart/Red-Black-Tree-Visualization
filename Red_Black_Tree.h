#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

#include "stdbool.h"
#include "stddef.h"

typedef enum Color {RED, BLACK} Color;

typedef struct treeNode 
{
    int data;
    Color color;
    struct treeNode *left;
    struct treeNode *right;
    struct treeNode *parent;
} treeNode;

typedef struct redBlackTree
{
    treeNode *root;
    
    /*
    * having a redBlackTree struct allows us to store more metadata
    * that we may want to have quick access (O(1)) to in the future, 
    * such as a treeSize variable
    */
} redBlackTree;

// Utility functions


treeNode* getSuccessor(const treeNode *node)

// Returns true if the given node is red.
bool isRed(const treeNode *node);

// Returns true if the given node is black.
bool isBlack(const treeNode *node);

// Returns the color of the given node.
Color getColor(const treeNode *node);

// Additional features

// Returns true if tree is empty
bool isEmpty(const redBlackTree *tree)

#endif