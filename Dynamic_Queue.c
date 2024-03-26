#include "Dynamic_Queue.h"
#include "stdlib.h"

Queue* createQueue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, const treeNode* treeNode)
{
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;

    if (q->rear == NULL)
    {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

const treeNode* dequeue(Queue* q)
{
    if (q->front == NULL)
    {
        return NULL;
    }

    QueueNode* temp = q->front;
    const treeNode* treeNode = temp->treeNode;
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    
    free(temp);
    return treeNode;
}

bool isQueueEmpty(Queue* q)
{
    return q->front == NULL;
}