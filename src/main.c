
#include <stdbool.h> 
#include <stdio.h>

#include <gtk-4.0/gtk/gtk.h>

#include "glib-object.h"
#include "libs/setup.h"
#include "interface/main_interface.h"


int main(int argc, char **argv) {

    if (checker()) {
        printf("Files already exists\n");
    } else {
        set_up();
        printf("creating files\n");
    }

    if (argc <= 2) {
        printf("Please run with a flag.\n");
        help_cmd();
        return 1;
    }

    GtkApplication *app;
    int status;

    app = gtk_application_new("org.lisboa.SimplestTodo", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK( activate_main ), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

