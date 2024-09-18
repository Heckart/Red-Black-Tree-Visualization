#ifndef UNIT_TESTS
#define UNIT_TESTS

/* NOTE: unit tests are for testing the Red-Black Tree itself, not the GUI. GUI elements should be commented from red_black_tree.c before running these tests. */

// ensure that the tree correctly maintains the minimum and maximum elements
void testInsertMaxMin();

// ensure that the tree correctly updates node colors when insertion requires a color change
void testInsertRequiringRecoloring();

// ensure that the tree remains properly balannced and updates to the correct colors after insertions
void testInsertionBalanceColor();

// ensure that the tree maintains properties after deleting the only node, nodes with one child, and nodes with two children 
void testBasicDeletion();

// ensure that the tree maintains properties after deleting the root with 1 and 2 children
void testRootDeletion();

// ensure search function can properly find values and returns nil when necessary
void testSearch();

// ensure the size() and height() functions return the correct values
void testSizeHeight();
#endif
