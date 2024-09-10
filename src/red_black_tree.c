#include "red_black_tree.h"
#include "gtkBackend.h"

#include "stdlib.h"
#include "stdio.h"

redBlackTree* initializeTree() {
    redBlackTree *tree = (redBlackTree*)malloc(sizeof(redBlackTree));
    // handle memory allocation failure
    if (tree == NULL) {
        printf("tree was not allocated and the new tree was not created\n");
        return NULL;
    }
    
    treeNode *sentinel = (treeNode*)malloc(sizeof(treeNode));
    if (sentinel == NULL) {
        printf("sentinel was not allocated and the new tree was not created\n");
        free(tree);
        return NULL;
    }

    sentinel->color = BLACK; // the sentinel is black by convention
    sentinel->left = sentinel;
    sentinel->right = sentinel;
    sentinel->parent = sentinel;
    sentinel->key = -1; // placeholder value, we should never be checking the sentinel's key anyways

    tree->nil = sentinel;
    tree->root = sentinel; // in an empty tree, the root points to the sentinel

    return tree;
}

void leftRotate(redBlackTree *tree, treeNode *x) {
    treeNode *y = x->right;
    x->right = y->left; // turn y's left subtree into x's right subtree

    // if y's left subtree is not empty, x becomes the subtree's root
    if (y->left != tree->nil) {
        y->left->parent = x;
    }

    y->parent = x->parent; // x's parent becomes y's parent

    // if x was the root, y becomes the root
    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) { // else if x was a left child, y becomes left child
        x->parent->left = y;
    } else { // otherwise x was a right child, y becomes right child
        x->parent->right = y;
    }
    
    y->left = x; // make x y's left child
    x->parent = y;
}

void rightRotate(redBlackTree *tree, treeNode *x) {
    treeNode *y = x->left;
    x->left = y->right; // turn y's right subtree into x's right subtree

    // if y's right subtree is not empty, x becomes the subtree's root
    if (y->right != tree->nil) {
        y->right->parent = x;
    }
    
    y->parent = x->parent; // x's parent becomes y's parent

    if (x->parent == tree->nil) { // if x was the root, y becomes the root
        tree->root = y;
    } else if (x == x->parent->left) { // else if x was a left child, y becomes the left child
        x->parent->left = y;
    } else { // otherwise x was a right child, y becomes right child
        x->parent->right = y;
    }
    
    y->right = x; // make x y's left child
    x->parent = y;
}

void rbInsert(redBlackTree* tree, int data) {
    /* the structure of this red-black tree (NULL's pointing to a common sentinel) means
    *  a createNode function isn't useful, since we would still need to point right, left
    *  and parent toward tree->nil at the start of the rbInsert function; therefore, we are
    *  just creating a new node inside this function. 
    */

    treeNode *z = (treeNode*)malloc(sizeof(treeNode));
    // handle memory allocation failure
    if (z == NULL) {
        printf("The memory allocation failed. The value has not been inserted\n");
        return;
    }
    
    z->key = data;
    z->color = RED;
    z->parent = tree->nil;
    z->right = tree->nil;
    z->left = tree->nil;

    treeNode *x = tree->root; // node being compared with z
    treeNode *y = tree->nil; // y will be parent of z

    // descend until reaching the sentinel
    while (x != tree->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    z->parent = y; // found the location, insert z with parent y

    if (y == tree->nil) {// if tree is empty
        tree->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    z->left = tree->nil; // both of z's children are the sentinel
    z->right = tree->nil;
    z->color = RED;

    rbInsertFixup(tree, z);   

    gtk_widget_queue_draw(drawing_area);
}

void rbInsertFixup(redBlackTree *tree, treeNode *z) {
    while (z->parent->color == RED) {
        // if z's parent is a left child
        if (z->parent == z->parent->parent->left) {
            treeNode* y = z->parent->parent->right; // y is z's uncle

            // if z's parent and uncle are both red
            if (y->color == RED) {
                // case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // case 2
                    z = z->parent;
                    leftRotate(tree, z);
                }
                
                // case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }   
        } else { 
            treeNode *y = z->parent->parent->left;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

treeNode *rbMaximum(const redBlackTree *tree, treeNode *node)
{
    while (node->right != tree->nil) {
        node = node->right;
    }
    return node;
}

treeNode *rbMinimum(const redBlackTree *tree, treeNode *node) {
    while (node->left != tree->nil) {
        node = node->left;
    }
    return node;
}

void rbTransplant(redBlackTree *tree, treeNode *u, treeNode *v) {
    if (u->parent == tree->nil) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    
    v->parent = u->parent;
}

void rbDelete(redBlackTree *tree, treeNode *z) {
    int zOriginalKey = z->key;
    treeNode *y = z;
    Color yOriginalColor = y->color;
    treeNode *x;

    if (z->left == tree->nil) {
        x = z->right;
        rbTransplant(tree, z, z->right); // replace z by its right child
    } else if (z->right == tree->nil) {
        x = z->left;
        rbTransplant(tree, z, z->left); // replace z by its left child
    } else {
        y = rbMinimum(tree, z->right); // y is z's successor
        yOriginalColor = y->color;
        x = y->right;
        // if y is farther down the tree
        if (y != z->right) {
            rbTransplant(tree, y, y->right); // replace y by its right child
            y->right = z->right; // z's right child becomes y's right child
            y->right->parent = y;
        } else { // if x is tree->nil
            x->parent = y;
        }
        rbTransplant(tree, z, y); // replace z by its successor y
        y->left = z->left; // give z's left child to y, which had no left child
        y->left->parent = y;
        y->color = z->color;
    }
    
    // correct vilations if they occured
    if (yOriginalColor == BLACK) {
        rbDeleteFixup(tree, x);
    }

    // prevent memory leak
    // the node to be discarded could be different from z in certain scenarios
    // based on rotations
    if (z->key == zOriginalKey) {
        free(z);
    } else if (y->key == zOriginalKey) {
        free(y);
    } else if (x->key == zOriginalKey ) {
        free(x);
    }
}

void rbDeleteFixup(redBlackTree *tree, treeNode *x) {
    while (x != tree->root && x->color == BLACK) {
        // if x is a left child
        if (x == x->parent->left) {
            treeNode *w = x->parent->right; // w is x's sibling

            // case 1
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }

            // case 2
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                // case 3
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                
                // case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else { // same as above, but with right and left exchanged
            treeNode *w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

void destroyTreeHelper(treeNode *node, treeNode *nil) {
    // base case
    if (node == nil) {
        return;
    }
    
    // recurse on left and right sides
    destroyTreeHelper(node->left, nil);
    destroyTreeHelper(node->right, nil);

    free(node);
}

void destroyTree(redBlackTree *tree) {
    destroyTreeHelper(tree->root, tree->nil);

    // nil node is dynamically allocated, so it must be freed
    free(tree->nil);

    tree->root = NULL;

    // tree struct itself is dynamically allocated, so it must be freed
    free(tree);
}

treeNode* rbTreeSearch(redBlackTree *tree, int key) {
    treeNode *x = tree->root;

    while (x != tree->nil && key != x->key) {
        if (key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    return x;
}
