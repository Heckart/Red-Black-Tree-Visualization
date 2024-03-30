#ifndef UNIT_TESTS
#define UNIT_TESTS

// insertion tests

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
#endif
