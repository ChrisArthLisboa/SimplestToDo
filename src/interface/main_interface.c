
#include <gtk-4.0/gtk/gtk.h>


static GtkWidget* create_header() {

    GtkWidget *header;
    GtkWidget *button;

    header = gtk_header_bar_new();

    button = gtk_toggle_button_new();
    gtk_widget_set_tooltip_text(button, "Configuration");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header), button);


    return header;

}


static void activate_main(GtkApplication *app, gpointer user_data) {

    GtkWidget *window;
    GtkWidget *header;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "SimplestTodo");

    header = create_header();
    
    gtk_window_set_titlebar( GTK_WINDOW(window), header);
    

    gtk_window_present(GTK_WINDOW( window ));

}
