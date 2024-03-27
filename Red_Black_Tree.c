#include "Red_Black_Tree.h"

#include "stdio.h"
#include "stdlib.h"
// Initialization
redBlackTree* initializeTree()
{
    redBlackTree* tree = (redBlackTree*)malloc(sizeof(redBlackTree));
    if (tree == NULL) // if there is a memory allocation failure
    {
        return NULL;
    }
    tree->root = NULL;
    return tree;
}



// Node management
treeNode* createNode(int data)
{
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
    if (newNode == NULL)
    {
        return NULL;
    }
    
    newNode->data = data;
    newNode->color = RED; // new nodes are typically red by convention
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    
    return newNode;
}



// Insertion fuctions
void insert(redBlackTree* tree, int data)
{
    treeNode* newNode = createNode(data);
    if (tree->root == NULL)
    {
        tree->root = newNode;
    } 
    else
    {
        treeNode* current = tree->root;
        treeNode* parent = NULL;
        while (current != NULL)
        {
            parent = current;
            if (newNode->data < current->data)
            {
                current = current->left;
            } 
            else
            {
                current = current->right;
            }
        }
        
        newNode->parent = parent;
        
        if (parent != NULL) // Check if parent is not NULL to satisfy a cppcheck warning. In practice, this condition should always be true.
        {
            if (newNode->data < parent->data)
            {
                parent->left = newNode;
            } 
            else
            {
                parent->right = newNode;
            }   
        }
    }
    
    newNode->color = RED;
    fixViolationsAfterInsertion(tree, newNode);
}

void fixViolationsAfterInsertion(redBlackTree* tree, treeNode* node)
{
    treeNode* parent = NULL;
    treeNode* grandparent = NULL;
    while ((node != tree->root) && (node->color != BLACK) && (node->parent->color == RED))
    {
        parent = node->parent;
        grandparent = node->parent->parent;

        // if parent is left child of grandparent
        if (parent == grandparent->left)
        {
            treeNode* uncle = grandparent->right;
            // if uncle of node is also red
            if (uncle != NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } 
            else
            {
                // Left-right
                if (node == parent->right)
                {
                    leftRotate(&tree->root, parent);
                    node = parent;
                    parent = node->parent;
                }
                // Left-left
                rightRotate(&tree->root, grandparent);
                Color tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                node = parent;
            }
        } 
        else
        {
            treeNode* uncle = grandparent->left;
            // if uncle is red, only recolor
            if (uncle != NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } 
            else
            {
                // Right-left
                if (node == parent->left)
                {
                    rightRotate(&tree->root, parent);
                    node = parent;
                    parent = node->parent;
                }
                // Right-right
                leftRotate(&tree->root, grandparent);
                Color tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                node = parent;
            }
        }  
    }
}

// Rotation functions
void leftRotate(treeNode** root, treeNode* x)
{
    // set y and turn y's left subtree into x's right subtree
    treeNode *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
    {
        y->left->parent = x;
    }
    
    y->parent = x->parent; // link x's parent to y

    if (x->parent == NULL) // if x is root
    {
        *root = y;
    } 
    else if (x == x->parent->left) // if x is left child
    {
        x->parent->left = y;
    } 
    else // if x is right child
    {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;   
}

void rightRotate(treeNode** root, treeNode* y)
{
    // set x and turn x's left subtree into y's rught subtree
    treeNode* x = y->left;
    y->left = x->right;

    if (x->right != NULL)
    {
        x->right->parent = y;
    }

    x->parent = y->parent; // link y's parent to x

    if (y->parent == NULL) // if y is root
    {
        *root = x;
    } 
    else if (y == y->parent->left) // if y is left child
    {
        y->parent->right = x;
    } 
    else // if y is right child
    {
        y->parent->right = x;
    }
    
   x->parent = y;
   y->parent = x; 
}



// Traversal functions
void inOrderTraversal(const treeNode* root)
{
    // base case
    if (root == NULL)
    {
        printf("The Red-Black tree is empty!\n");
        return;
    }

    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

void preOrderTraversal(const treeNode* root)
{
    // base case
    if (root == NULL)
    {
        printf("The Red-Black tree is empty!\n");
        return;
    }
    
    printf("%d ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void postOrderTraversal(const treeNode* root)
{
    // base case
    if (root == NULL)
    {
        printf("The Red-Black tree is empty!\n");
        return;
    }

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->data);
    
}

void levelOrderTraversal(const treeNode* root)
{
    if (root == NULL)
    {
        printf("The Red-Black tree is empty!\n");
        return;
    }

    Queue* q = createQueue();
    enqueue(q, root);

    while (!isQueueEmpty(q))
    {
        const treeNode* current = dequeue(q);
        printf("%d ", current->data);

        if (current->left != NULL)
        {
            enqueue(q, current->left);
        }
        if (current->right != NULL)
        {
            enqueue(q, current->right);
        }   
    }
    
    free(q); // all nodes need to be dequeud to prevent memory leaks
}



// Utility functions
treeNode* getSuccessor(const treeNode* node)
{
    if (node == NULL) return NULL;

    // If the node has a right subtree
    if (node->right != NULL)
    {
        treeNode* temp = node->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
    
    // If there is no right subtree
    const treeNode* temp = node;
    const treeNode* parent = temp->parent;
    while (parent != NULL && temp == parent->right)
    {
        temp = parent;
        parent = parent->parent;
    }
    return (treeNode*)parent; // convert from const treeNode* to treeNode*
}

treeNode* getPredecessor(const treeNode* node)
{
    if (node == NULL) return NULL;

    // If the node has a left subtree
    if (node->left != NULL)
    {
        treeNode* temp = node->left;
        while (temp->right != NULL)
        {
            temp = temp->right;
        }
        return temp;
    }
    
    // If there is not left subtree
    const treeNode* temp = node;
    const treeNode* parent = temp->parent;
    while (parent != NULL && temp == parent->left)
    {
        temp = parent;
        parent = parent->parent;
    }
    return (treeNode*)parent; // convert from const treeNode* to treeNode*
}

bool isRed(const treeNode *node)
{
    if (node == NULL)
    {
        // in a Red-Black tree, a NULL node is typically considered black
        return false;
    }
    
    return node->color == RED;
}

bool isBlack(const treeNode *node)
{
    if (node == NULL)
    {
        // in a Red-Black tree, a NULL node is typically considered black
        return true;
    }
    
    return node->color == BLACK;
}

Color getColor(const treeNode *node)
{
    if (node == NULL)
    {
        // in a Red-Black tree, a NULL node is typically considered black
        return BLACK;
    } 
    else
    {
        return node->color;
    }     
}

// Additional features
bool isEmpty(const redBlackTree *tree)
{
    if (tree->root == NULL)
    {
        return true;
    } 
    else return false;
}



// Queue functions
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
