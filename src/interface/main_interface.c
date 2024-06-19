
#include <gtk-4.0/gtk/gtk.h>

static void activate_main(GtkApplication *app, gpointer user_data) {

    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Teste");
    
    gtk_window_present(GTK_WINDOW( window ));

}
