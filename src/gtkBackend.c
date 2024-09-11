#include "gtkBackend.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

void draw_node(cairo_t *cr, redBlackTree *tree, treeNode *node, const int x, const int y, const int x_offset, const int depth) {
    if (node == NULL || node == tree->nil) return;

    // Set the color based on the node's color
    if (node->color == RED) {
        cairo_set_source_rgb(cr, 1.0, 0.0, 0.0); // Red
    } else {
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0); // Black
    }

    // Draw the node as a circle
    cairo_arc(cr, x, y, 30, 0, 2 * G_PI); // 30 is the radius of the node
    cairo_fill(cr);

    // Prepare the text for the node's key
    char key_str[12]; // flawfinder: ignore (snprintf is protecting against buffer overflows) 
    snprintf(key_str, sizeof(key_str), "%d", node->key);

    // measure the text to center it
    cairo_text_extents_t extents;
    cairo_text_extents(cr, key_str, &extents);

    // Draw the node's key inside the circle
    cairo_set_source_rgb(cr, 0.0, 1.0, 0.0); // Green text
    cairo_set_font_size(cr, 15);
    // Move the text position so it is centered
    cairo_move_to(cr, x - extents.width / 2, y + extents.height / 2);
    cairo_show_text(cr, key_str); 

    // Calculate positions for left and right children
    const int child_y = y + 70;                    // Vertical distance between levels
    const int left_x = x - x_offset;               // Horizontal offset for left child
    const int right_x = x + x_offset;              // Horizontal offset for right child

    // Draw lines connecting to the left and right children
    if (node->left != tree->nil) {
        cairo_move_to(cr, x, y+10);
        cairo_line_to(cr, left_x, child_y);
        cairo_stroke(cr);
        draw_node(cr, tree, node->left, left_x, child_y, x_offset / 2, depth + 1);
    }

    if (node->right != tree->nil) {
        cairo_move_to(cr, x, y+10);
        cairo_line_to(cr, right_x, child_y);
        cairo_stroke(cr);
        draw_node(cr, tree, node->right, right_x, child_y, x_offset / 2, depth + 1);
    }
}

void draw_tree(cairo_t *cr, redBlackTree *tree) {
    // Start drawing from the root of the tree
    if (tree->root == tree->nil) return; // Tree is empty

    // Initial position and offset for the root node
    const int initial_x = 400;    // Start drawing in the middle of the canvas
    const int initial_y = 50;     // Start drawing from the top of the canvas
    const int x_offset = 200;     // Initial horizontal offset between child nodes

    draw_node(cr, tree, tree->root, initial_x, initial_y, x_offset, 0);
}

int safe_stoi(const char *str) {
    char* endptr;
    const int BASE = 10;
    
    const long long val = strtoll(str, &endptr, BASE);

    // overflow check
    if (val > INT_MAX || val < INT_MIN) {
      fprintf(stderr, "Integer overflow, value inserted as a 0\n");
      return 0;
    }

    return (int)val;
}
