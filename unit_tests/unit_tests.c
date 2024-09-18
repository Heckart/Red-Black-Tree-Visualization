#include "red_black_tree.h"
#include "unit_tests.h"
#include "assert.h"
#include "stdio.h"

void testInsertMaxMin() {
    redBlackTree* tree = initializeTree();

    // basic tests
    rbInsert(tree, 15);
    rbInsert(tree, 10);
    rbInsert(tree, 20);
    rbInsert(tree, 5);
    rbInsert(tree, 25);

    treeNode* minNode = rbMinimum(tree, tree->root);
    treeNode* maxNode = rbMaximum(tree, tree->root);

    assert(minNode->key == 5);
    assert(maxNode->key == 25);

    // testing larger number after smaller number
    rbInsert(tree, 4);
    rbInsert(tree, 554);

    minNode = rbMinimum(tree, tree->root);
    maxNode = rbMaximum(tree, tree->root);

    assert(minNode->key == 4);
    assert(maxNode->key == 554);

    // testing negative number
    rbInsert(tree, -100);
    minNode = rbMinimum(tree, tree->root);

    assert(minNode->key == -100);

    destroyTree(tree);


    printf("testInsertMinMax passed.\n");
}

void testInsertRequiringRecoloring() {
    redBlackTree* tree = initializeTree();

    rbInsert(tree, 3);
    rbInsert(tree, 2);
    rbInsert(tree, 4);

    assert(tree->root->color == BLACK);
    assert(tree->root->left->color == RED);
    assert(tree->root->right->color == RED);

    // 1 becomes left child of 2. 2 and 4 should change colors
    rbInsert(tree, 1);

    assert(tree->root->color == BLACK);
    assert(tree->root->left->color == BLACK);
    assert(tree->root->right->color == BLACK);
    assert(tree->root->left->left->color == RED);

    destroyTree(tree);

    printf("testInsertRequireingRecoloring passed.\n");
}

void testInsertionBalanceColor() {
    redBlackTree* tree = initializeTree();

    rbInsert(tree, 15);
    rbInsert(tree, 10);
    rbInsert(tree, 20);
    rbInsert(tree, 5);
    rbInsert(tree, 25);
    rbInsert(tree, 4);
    rbInsert(tree, 554);
    rbInsert(tree, -100);

    assert(tree->root->key == 15);
    assert(tree->root->color == BLACK);
    assert(tree->root->left->right->key == 10);
    assert(tree->root->left->right->color == BLACK);
    assert(tree->root->right->left->color == RED);

    destroyTree(tree);

    printf("testInsertionBalanceColor passed.\n");
}

void testBasicDeletion() {
    redBlackTree *tree = initializeTree();

    // insert one element and delete it
    assert(tree->root == tree->nil);
    rbInsert(tree, 10);
    rbDelete(tree, tree->root);
    assert(tree->root == tree->nil);

    // ensure new elements can still be inserted
    rbInsert(tree, 100);
    assert(tree->root->key == 100);
    assert(tree->root->color == BLACK);

    // delete a node with one child
    rbInsert(tree, 50);
    rbInsert(tree, 200);
    rbInsert(tree, 25);
    rbDelete(tree, tree->root->left);
    assert(tree->root->left->key == 25);
    assert(tree->root->left->color == BLACK);

    rbInsert(tree, 10);
    rbInsert(tree, 50);
    rbInsert(tree, 150);
    rbInsert(tree, 1000);
    rbInsert(tree, 30);
    rbDelete(tree, tree->root->left);
    rbInsert(tree, 1);
    assert(tree->root->left->key == 30);
    assert(tree->root->right->color == BLACK);
    assert(tree->root->left->left->key == 10);
    assert(tree->root->left->left->color == BLACK);

    destroyTree(tree);


    printf("testBasicDeletion passed.\n");
}

void testRootDeletetion() {
    redBlackTree *tree = initializeTree();

    // deleting root with 1 child
    rbInsert(tree, 50);
    rbInsert(tree, 30);
    rbDelete(tree, tree->root);
    assert(tree->root->key == 30);
    assert(tree->root->color == BLACK);

    // deleting root with mutliple children
    rbInsert(tree, -352);
    rbInsert(tree, 31);
    rbInsert(tree, 20);
    rbDelete(tree, tree->root);
    assert(tree->root->key == 20);
    assert(tree->root->color == BLACK);

    destroyTree(tree);

    printf("testRootDeletion passed.\n");
}

void testSearch() {
    redBlackTree *tree = initializeTree();

    rbInsert(tree, 42);
    rbInsert(tree, 77);
    rbInsert(tree, 13);
    rbInsert(tree, 5);
    rbInsert(tree, 100);

    treeNode* valid = rbTreeSearch(tree, 77);
    assert(valid->key == 77); 
    treeNode* invalid = rbTreeSearch(tree, 78);
    assert(invalid == tree->nil);

    destroyTree(tree);

    printf("testSearch passed.\n");
}

void testSizeHeight() {
    redBlackTree *tree = initializeTree();

    int treeHeight = height(tree, tree->root);
    int treeSize = size(tree, tree->root);

    assert(isEmpty(tree));
    assert(treeHeight == -1);
    assert(treeSize == 0);
    
    rbInsert(tree, 1);

    treeHeight = height(tree, tree->root);
    treeSize = size(tree, tree->root);

    assert(!isEmpty(tree));
    assert(treeHeight == 0);
    assert(treeSize == 1);

    rbInsert(tree, 2);
    rbInsert(tree, 3);
    rbInsert(tree, 4);
    rbInsert(tree, 5);
    rbInsert(tree, 6);
    rbInsert(tree, 7);

    treeHeight = height(tree, tree->root);
    treeSize = size(tree, tree->root);

    assert(treeHeight == 3);
    assert(treeSize == 7);

    destroyTree(tree);

    printf("testSizeHeight passed.\n");
}

int main()
{
    // insertion tests
    testInsertMaxMin();
    testInsertRequiringRecoloring();
    testInsertionBalanceColor();
    // deletion tests
    testBasicDeletion();
    testRootDeletetion();
    // auxiliary test
    testSearch();
    testSizeHeight(); 
    return 0;
}
