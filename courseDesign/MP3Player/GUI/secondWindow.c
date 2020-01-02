#include <gtk/gtk.h>
int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);

    //creat window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //set a title
    gtk_window_set_title(GTK_WINDOW(window), "test");
    //center
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    //size
    gtk_widget_set_size_request(window, 400, 300);
    //resizable
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    //destroy process while close the window
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit),NULL);

    //show window
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}