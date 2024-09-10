#include "red_black_tree.h"
#include "stdio.h"
#include <gtk/gtk.h>
#include "gtkBackend.h"
#include "stdbool.h"

GtkWidget *drawing_area;
GtkWidget *entry;
redBlackTree *tree;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, const gpointer USER_DATA) { 
  redBlackTree *tree = (redBlackTree *)USER_DATA; // Pass the tree as user_data
  draw_tree(cr, tree);
  return FALSE;
}

static void on_entry_activate(GtkEntry *entry, const gpointer USER_DATA) {
    const gchar *text = gtk_entry_get_text(entry);
    int input = safe_stoi(text); // convert text input to integer 

    rbInsert(tree, input);

    gtk_widget_queue_draw(drawing_area);

    gtk_entry_set_text(entry, "");
}

int main(int argc, char* argv[])
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Red-Black Tree Visualization");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    drawing_area = gtk_drawing_area_new();
    gtk_box_pack_start(GTK_BOX(vbox), drawing_area, TRUE, TRUE, 0);

    // Create the widget for input
    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0); 
    
    tree = initializeTree();

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), tree);

    g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(on_entry_activate), NULL);
    
    gtk_widget_show_all(window);
    
    // start the GTK main loop
    gtk_main();

    destroyTree(tree); 
    
    return 0;
}
