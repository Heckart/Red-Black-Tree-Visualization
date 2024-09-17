#ifndef GTKBACKEND
#define GTKBACKEND

#include <gtk/gtk.h>
#include "red_black_tree.h"

extern GtkWidget *drawing_area; 

/**
 * @brief Handles drawing individual nodes in the GUI.
 *
 * Runs in O(n).
 *
 * @param *cr The cairo drawing object.  
 * @oaram *tree The redBlacktree being drawn.
 * @param *node The node being drawn.
 * @param x The horizontal coordinate of the node. 
 * @param y The vertical coordinate of the node.
 * @param x_offset The horizontal spacing of the node.
 * @param depth The depth of the node being drawn.
 *
 * @returns Nothing. A new node is drawn in the GUI after execution.
*/
void draw_node(cairo_t *cr, redBlackTree *tree, treeNode *node, const int x, const int y, const int x_offset, const int depth);

/**
 * @brief Calls draw_node() after setting the gui size.
 *
 * Runs in O(n).
 *
 * @param *cr The cairo drawing object. 
 * @param *tree The redBlackTree being drawn.
 *
 * @returns Nothing. A new tree has been drawn in the GUI after execution.
*/
void draw_tree(cairo_t *cr, redBlackTree *tree);

/**
 * @brief Converts a string to an integer in a safe manner.
 *
 * Runs in O(1).
 *
 * @param *str The string to be converted to an integer
 *
 * @returns *str as an integer is no overflow, else returns a 0.
 */
int safe_stoi(const char *str);

#endif
