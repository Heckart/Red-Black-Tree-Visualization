#ifndef DYNAMIC_QUEUE
#define DYNAMIC_QUEUE

#include "Red_Black_Tree.h"
#include "stdbool.h"

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