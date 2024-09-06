#ifndef GTKBACKEND
#define GTKBACKEND

#include <gtk/gtk.h>
#include "red_black_tree.h"

extern GtkWidget *drawing_area; 

void draw_node(cairo_t *cr, redBlackTree *tree, treeNode *node, int x, int y, int x_offset, int depth);
void draw_tree(cairo_t *cr, redBlackTree *tree);

#endif
