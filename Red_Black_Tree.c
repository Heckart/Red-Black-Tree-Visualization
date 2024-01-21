#include "Red_Black_Tree.h"

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