#include <gtk/gtk.h>
#include <string.h>
#include <math.h>
GtkWidget* entry;
char buf[100] = "";
void deal_pressed(GtkButton *button, gpointer user_data)
{
	// 获得按钮的文本信息
	const char *text = gtk_button_get_label( button );
	// g_print() 相当于C语言的 printf(), gchar相当于char
	g_print("button_text = %s; user_data = %s\n", text, (gchar *)user_data);
    if(strcmp("C", text) == 0){
        buf[strlen(buf) - 1] = 0;
    }
    else{
        double a = 0, b = 0;
        char c;
        strcat(buf, text);
        if(strcmp("=", text) == 0){
            sscanf(buf, "%lf%c%lf", &a, &c, &b);
            printf("a = %lf, c = %c, b = %lf\n", a, c, b);
            if(c == '+'){
                sprintf(buf, "%.2lf", a+b);
            }
            if(c == '-'){
                sprintf(buf, "%.2lf", a-b);
            }
            if(c == '*'){
                sprintf(buf, "%.2lf", a*b);
            }
            if(c == '/'){
                sprintf(buf, "%.2lf", (double)a/(double)b);
            }
        }
    }
    gtk_entry_set_text(GTK_ENTRY(entry), buf);
}

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);

    //creat window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//main window
    gtk_window_set_title(GTK_WINDOW(window), "测试");//title
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);//position
    gtk_widget_set_size_request(window, 300, 400);//size
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);//
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit),NULL);//close

    //create a table layout
    GtkWidget *table = gtk_table_new(5, 5, TRUE);
    gtk_container_add(GTK_CONTAINER(window), table);

    //entry
    entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry), "");
    gtk_table_attach_defaults(GTK_TABLE(table), entry, 0, 5, 0, 1);

    //button
    GtkWidget *button = gtk_button_new_with_label("7");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "7");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 1, 1, 2);
    //button2
    button = gtk_button_new_with_label("8");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "8");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 1, 2, 1, 2);
    //button3
    button = gtk_button_new_with_label("9");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "9");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 2, 3, 1, 2);
    //button4
    button = gtk_button_new_with_label("+");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "+");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 3, 4, 1, 2);

    //button5
    button = gtk_button_new_with_label("4");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "4");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 1, 2, 3);
    //button6
    button = gtk_button_new_with_label("5");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "5");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 1, 2, 2, 3);
    //button7
    button = gtk_button_new_with_label("6");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "6");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 2, 3, 2, 3);
    //button8
    button = gtk_button_new_with_label("-");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "-");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 3, 4, 2, 3);

    //butto9
    button = gtk_button_new_with_label("1");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "1");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 1, 3, 4);
    //button10
    button = gtk_button_new_with_label("2");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "2");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 1, 2, 3, 4);
    //button11
    button = gtk_button_new_with_label("3");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "3");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 2, 3, 3, 4);
    //button12
    button = gtk_button_new_with_label("*");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "*");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 3, 4, 3, 4);
    button = gtk_button_new_with_label("/");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "/");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 3, 4, 4, 5);

    //button13
    button = gtk_button_new_with_label("C");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "clear");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 1, 4, 5);
    //button14
    button = gtk_button_new_with_label("0");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "0");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 1, 2, 4, 5);
    //button15
    button = gtk_button_new_with_label(".");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), ".");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 2, 3, 4, 5);
    //button16
    button = gtk_button_new_with_label("=");
    g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "=");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 4, 5, 3, 5);
    //button16
    //button = gtk_button_new_with_label("π");
    //g_signal_connect(button, "pressed", G_CALLBACK(deal_pressed), "PI");
    //gtk_table_attach_defaults(GTK_TABLE(table), button, 4, 5, 2, 3);
    
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}