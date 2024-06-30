
#include <gtk-4.0/gtk/gtk.h>

static GtkWidget* create_header() {

    GtkWidget *header;
    GtkWidget *button;

    header = gtk_header_bar_new();

    button = gtk_button_new_from_icon_name("emblem-system-symbolic");
    gtk_widget_set_tooltip_text(button, "Configuration");


    gtk_header_bar_pack_end(GTK_HEADER_BAR(header), button);
    return header;

}

