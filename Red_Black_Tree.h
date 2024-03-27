#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

#include "stdbool.h"
#include "stddef.h"

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
    * such as a treeSize variable
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



// Utility functions

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



// Additional features

// Returns true if tree is empty
bool isEmpty(const redBlackTree* tree);



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
