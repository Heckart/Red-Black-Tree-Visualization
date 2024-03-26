#include "Red_Black_Tree.h"
#include "stdio.h"

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

        return node->color;
    }  
}

// Additional features
bool isEmpty(const redBlackTree *tree)
{
    if (tree->root == NULL)
    {
        return true;
    } else return false;
}