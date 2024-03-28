#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

#include "stdbool.h"
#include "stddef.h"

// treeNode and root struct

typedef enum Color {RED, BLACK} Color;

typedef struct treeNode 
{
    int data;
    Color color;
    struct treeNode* left;
    struct treeNode* right;
    struct treeNode* parent;
} treeNode;

typedef struct redBlackTree
{
    treeNode* root;
    
    /*
    * having a redBlackTree struct allows us to store more metadata
    * that we may want to have quick access (O(1)) to in the future, 
    * such as a treeSize variable, max, or min.
    */
} redBlackTree;



// Initialization

// set up an empty tree
redBlackTree* initializeTree();



// Node management

// kind of stunted...just creates a new node with given data
treeNode* createNode(int data);



// Insertion

// insert a new node into the tree
void insert(redBlackTree* tree, int data);

// fix color and strucutral violations after insertion
void fixViolationsAfterInsertion(redBlackTree* tree, treeNode* node);


// Deletion

// search for a node with given value and delete it
void deleteNode(redBlackTree* tree, int data);

// fix color and structural violations after deletion
void fixViolationsAfterDeletion(redBlackTree* tree, treeNode* x);

// maintain binary tree structure during deletions
void rbTransplant(redBlackTree* tree, treeNode* u, treeNode* v);



// Rotation functions (should only be used as a part of insert & delete functions)

// performs a left rotation on the given node
void leftRotate(treeNode** root, treeNode* x);

// performs a right rotation on the given node
void rightRotate(treeNode** root, treeNode* y);



// Traversal functions

// traverses the tree in-order (left, root, right)
void inOrderTraversal(const treeNode* root);

// traverses the tree pre-order (root, left, right)
void preOrderTraversal(const treeNode* root);

// traverses the tree post-order (left, right, root)
void postOrderTraversal(const treeNode* root);

// traverses the tree level by level (esssentially a BFS). Uses a queue under the hood.
void levelOrderTraversal(const treeNode* root);



// search function

// standard BST search algorithm
treeNode* search(treeNode* root, int data);



// Utility functions

// returns the node with the minimum element
treeNode* getMinimum(treeNode* root);

// returns the node with the maximum element
treeNode* getMaximum(treeNode* root);

// returns the in-order successor of the given node
treeNode* getSuccessor(const treeNode* node);

// returns the in-order predecessor of the given node
treeNode* getPredecessor(const treeNode* node);

// Returns true if the given node is red.
bool isRed(const treeNode* node);

// Returns true if the given node is black.
bool isBlack(const treeNode* node);

// Returns the color of the given node.
Color getColor(const treeNode* node);



// Destruction functions

// helper function for freeTree() that recursively frees all nodes
void freeTreeNodes(treeNode* node);

// frees all nodes and destroys the tree
void freeTree(redBlackTree* tree);



// Additional features

// Returns the height of the tree
int height(const treeNode* node);

// Returns the number of nodes in the tree
int size(const treeNode* node);

// Returns true if tree is empty
bool isEmpty(const redBlackTree* tree);

// helper fuction for printTree
void printTreeHelper(const treeNode* node, int space);

// pretty prints the Red-Black tree top down
void printTree(const redBlackTree* tree);



// Queue functions

typedef struct QueueNode 
{
    const treeNode* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue 
{
    QueueNode* front;
    QueueNode* rear;
} Queue;

// initialize a queue
Queue* createQueue();

// enqueue a treeNode
void enqueue(Queue* q, const treeNode* treeNode);

// dequeue a treeNode and return it
const treeNode* dequeue(Queue* q);

// check if the queue is empty
bool isQueueEmpty(Queue* q);

#endif
