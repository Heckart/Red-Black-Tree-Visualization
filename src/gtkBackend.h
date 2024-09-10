#ifndef GTKBACKEND
#define GTKBACKEND

#include <gtk/gtk.h>
#include "red_black_tree.h"

extern GtkWidget *drawing_area; 

void draw_node(cairo_t *cr, redBlackTree *tree, treeNode *node, const int x, const int y, const int x_offset, const int depth);
void draw_tree(cairo_t *cr, redBlackTree *tree);

int safe_stoi(const char *str);

#endif
