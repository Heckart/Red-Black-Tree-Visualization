#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

#include "Dynamic_Queue.h"

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


// Traversal functions

// traverses the tree in-order (left, root, right)
void inOrderTraversal(const treeNode* root);

// traverses the tree pre-order (root, left, right)
void preOrderTraversal(const treeNode* root);

// traverses the tree post-order (left, right, root)
void postOrderTraversal(const treeNode* root);

// traverses the tree level by level (esssentially a BFS). Uses a queue under the hood.
void levelOrderTraversal(const treeNode* root);

// Utility functions

// returns the in-order successor of the given node
treeNode* getSuccessor(const treeNode *node);

// returns the in-order predecessor of the given node
treeNode* getPredecessor(const treeNode *node);

// Returns true if the given node is red.
bool isRed(const treeNode *node);

// Returns true if the given node is black.
bool isBlack(const treeNode *node);

// Returns the color of the given node.
Color getColor(const treeNode *node);

// Additional features

// Returns true if tree is empty
bool isEmpty(const redBlackTree *tree);

#endif