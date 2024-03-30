#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

typedef enum Color {RED, BLACK} Color;

typedef struct treeNode {
    Color color;
    int key;
    struct treeNode *left;
    struct treeNode *right;
    struct treeNode *parent;
} treeNode;

typedef struct redBlackTree {
    treeNode *root;
    treeNode *nil;

} redBlackTree;

/**
 * @brief Initializes a redBlackTree with the sentinel nil node and the root poiting to nil.
 * 
 * Runs in O(1).
 *
 * @return Returns a pointer to a redBlackTree struct, unless memory allocation failed
 * in whcih case an error message is printed and NULL is returned.
*/
redBlackTree *initializeTree();

/**
 * @brief Transforms the configuration of two treeNodes by swapping treeNode x with a child treeNode y such 
 * that Red-Black properties are maintined.
 * 
 * treeNode x has a right child y. This function turns x into the left child of y.
 * 
 * Runs in O(1).
 * 
 * @note This function should run automatically as a part of rbInsertFixup() or rbDeleteFixup(). 
 * It should not be called on its own.
 * 
 * @param *tree The redBlackTree struct which node x belongs to.
 * @param *x The treeNode to be rotated.
 * 
 * @return Nothing.
*/
void leftRotate(redBlackTree *tree, treeNode *x);

/**
 * @brief Transforms the configuration of two treeNodes by swapping treeNode x with a child treeNode y such 
 * that Red-Black properties are maintined.
 * 
 * treeNode x has a left child y. This function turns x into the right child of y.
 * 
 * Runs in O(1).
 * 
 * @note This function should run automatically as a part of rbInsertFixup() or rbDeleteFixup().
 * It should not be called on its own.
 * 
 * @param *tree The redBlackTree which treeNode x belongs to.
 * @param *x The treeNode to be rotated.
 * 
 * @return Nothing.
*/
void rightRotate(redBlackTree *tree, treeNode *x);

/**
 * @brief Internally creates a RED node for the tree with data param as key. Inserts as a regular BST
 * would, then calls rbInsertFixup() to maintain Red-Black properties.
 * 
 * Runs in O(log(n)).
 * 
 * @param *tree The redBlackTree the treeNode is inserted into.
 * @param data The key of the new treeNode.
 * 
 * @return Nothing. If a memory allocation fails, an error message is printed and the node is not inserted.
*/
void rbInsert(redBlackTree *tree, int data);

/**
 * @brief Auxiliary function for rbInsert(). Maintains Red-Black properties after insertion. 
 * 
 * This function specifically enforces the properties of the root being BLACK and a RED node not having a
 * RED child. The other properties (nodes being RED or BLACK, every leaf being black, and the number of BLACK
 * nodes being the same on every simple path) do not need to be enforced because rbInsert() cannot cause their
 * violations.
 * 
 * Runs in O(log(n)).
 * 
 * @note This function should run automatically as a part of rbInsert(). It should not be called individually.
 *  
 * @param *tree The redBlackTree that is being maintained.
 * @param *z The treeNode which was just inserted.
 * 
 * @return Nothing.
*/
void rbInsertFixup(redBlackTree *tree, treeNode *z);

/**
 * @brief Finds and returns the treeNode in a redBlackTree subtree rooted at *node with the max value.
 * 
 * Runs in O(log(n)).
 * 
 * @note Make *node the root in order to find the overall max value.
 *
 * @param *tree The redBlackTree being searched in. Used to identify nil treeNode.
 * @param *node The branch to begin searching from.
 * 
 * @return A pointer to the treeNode with the maximum value.
*/
treeNode *rbMaximum(redBlackTree *tree, treeNode *node);

/**
 * @brief Finds and returns the treeNode in a redBlackTree subtree rooted at *node with the min value.
 * 
 * Runs in O(log(n)).
 * 
 * @note Make *node the root in order to find the overall min value.
 * 
 * @param *tree The redBlackTree being searched in. Used to identify nil treeNode.
 * @param *node The branch to begin searching from.
 * 
 * @return A pointer to the treeNode with the minimum value.
*/
treeNode *rbMinimum(redBlackTree *tree, treeNode *node);

/**
 * @brief Replaces the subtree rooted at *u with the subtree rooted at *v.
 * 
 * Runs in O(1)
 * 
 * @note This function should be run automatically as a part of rbDelete(). It should not be called individually.
 * 
 * @param *tree The redBlackTree the transplant occurs in.
 * @param *u The subtree being replaced.
 * @param *v *u's new subtree.
 * 
 * @return Nothing.
*/
void rbTransplant(redBlackTree *tree, treeNode *u, treeNode *v);

/**
 * @brief Deletes as a regular BST would, with some additional lines to manage Red-Black properties. Also
 * calls rbDeleteFixup() to enfore Red-Black properties.
 * 
 * Runs in O(log(n)).
 * 
 * @param *tree The redBlackTree being deleted from.
 * @param *z The treeNode to be deleted.
 * 
 * @return Nothing.
*/
void rbDelete(redBlackTree *tree, treeNode *z);

/**
 * @brief Auxilliary function for rbDelete(). Maintains Red-Black properties after deletion.
 * 
 * This is more complicated than rbInertFixup() because there are more properties that can be violated from
 * deletion. This function covers four cases (eight total with symmetry), which is too much to describe in a
 * function comment. CLRS's (4th ed.) treatment of this function is very detailed and is a good read.
 * 
 * Runs in O(log(n)).
 * 
 * @note This function should run automatically as a part of rbDelete(). It should not be called individually.
 * 
 * @param *tree The redBlackTree that is being maintained.
 * @param *x Subtree to begin fixup from (determined automatically from rbDelete).
 * 
 * @return Nothing.
*/
void rbDeleteFixup(redBlackTree *tree, treeNode *x);

/**
 * @brief Auxilliary function for destroyTree(). Recursively frees all treeNodes.
 * 
 * Runs in O(n).
 * 
 * @note This function should run automatically as a part of destroyTree(). It should not be called individually,
 * as doing so could cause a memory leak.
 * 
 * @param *node  The node to be freed or recursed from.
 * @param *nil The nil node of the redBlackTree being freed.
 * 
 * @returns Nothing.
*/
void destroyTreeHelper(treeNode *node, treeNode *nil);

/**
 * @brief Frees all nodes in the redBlackTree, including nil, so it can no longer be used.
 * 
 * Runs in O(n).
 * 
 * @param *tree The redBlackTree being destroyed.
 * 
 * @returns Nothing.
*/
void destroyTree(redBlackTree *tree);

#endif