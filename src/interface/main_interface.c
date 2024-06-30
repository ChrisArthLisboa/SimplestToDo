
#include <gtk-4.0/gtk/gtk.h>
#include "utils.h"



static void activate_main(GtkApplication *app, gpointer user_data) {

    GtkWidget *window;
    GtkWidget *header;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "SimplestTodo");

    header = create_header();
    
    gtk_window_set_titlebar( GTK_WINDOW(window), header);
    

    gtk_window_present(GTK_WINDOW( window ));

}
