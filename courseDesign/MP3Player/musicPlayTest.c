#include <gtk/gtk.h>
#include <string.h>
#include <math.h>

GtkWidget *songName, *singerName;
GtkWidget *songProgress, *soundProgress;
GtkWidget *fixed;
static GdkColor black = {0, 0, 0, 0};//color init

//the active function when press the normal btn
void deal_pressed(GtkButton *button, gpointer user_data)
{
	// 获得按钮的文本信息
	const char *text = gtk_button_get_label( button );
	// g_print() 相当于C语言的 printf(), gchar相当于char
	g_print("button_text = %s; user_data = %s\n", text, (gchar *)user_data);
    
}

//toggle btn call back
void toggle_button_callback (GtkWidget *widget, gpointer data)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget))) 
    {
        /* 如果运行到这里，开关按钮是按下的 */
        printf("ON\n");
    
    } else {
        /* 如果运行到这里，开关按钮是弹起的 */
        printf("OFF\n");
    }
}

//volum control call back
void deal_pressed_vol(GtkButton *button, gpointer user_data)
{
	// 获得按钮的文本信息
    static double volDiff = 0;
	const char *text = gtk_button_get_label( button );
    if(strcmp(text, ">") == 0){
        volDiff += 0.1;
        if(volDiff > 0.5){
            volDiff = 0.5;
        }
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (soundProgress), 0.5 + volDiff);
        //gtk_fixed_put(GTK_FIXED(fixed), soundProgress,  45, 521);        
    }
    if(strcmp(text, "<") == 0){
        volDiff -= 0.1;
        if(volDiff < -0.5){
            volDiff = -0.5;
        }
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (soundProgress), 0.5 + volDiff);    
        //gtk_fixed_put(GTK_FIXED(fixed), soundProgress,  45, 521);    
    }
}

//progress timeout control
gint progress_timeout(gpointer data)
{
    gdouble new_val;
    new_val = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (songProgress)) + 0.01;
      
    if (new_val > 1.0){
	    new_val = 0.0;
    }
      /* 设置进度条的新值 */
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (songProgress), new_val);
  /* 这是一个timeout函数，返回 TRUE，这样它就能够继续被调用 */
  return TRUE;
} 
/*
puaseBtnImg = gtk_image_new();
gtk_image_set_from_stock(GTK_IMAGE(puaseBtnImg), GTK_STOCK_MEDIA_PLAY, GTK_ICON_SIZE_LARGE_TOOLBAR);
gtk_container_add(GTK_CONTAINER(puaseBtn), puaseBtnImg);

*/
int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);

    GtkWidget *preBtn, *pauseBtn, *nextBtn, *volDownBtn, *volUpBtn;
    GtkWidget *preBtnImg, *pauseBtnImg, *nextBtnImg;
    GtkWidget *window;
    GtkWidget *albumImg;
    //creat window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//main window
    gtk_window_set_title(GTK_WINDOW(window), "音乐");//title
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);//position
    gtk_widget_set_size_request(window, 330, 600);//size
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);//
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit),NULL);//close

    //fixed layout
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    //create album img
    albumImg = gtk_image_new_from_file("img/album");
    gtk_widget_set_size_request(albumImg, 276, 276);
    gtk_fixed_put(GTK_FIXED(fixed), albumImg, 25, 30);

    //song and singer
    songName = gtk_label_new("歌曲");
    gtk_widget_modify_fg(songName, GTK_STATE_NORMAL, &black);
    gtk_fixed_put(GTK_FIXED(fixed), songName,  25, 320);
    singerName = gtk_label_new("歌手");
    gtk_widget_modify_fg(singerName, GTK_STATE_NORMAL, &black);
    gtk_fixed_put(GTK_FIXED(fixed), singerName,  25, 340);

    //progresses
    songProgress = gtk_progress_bar_new();
    gtk_timeout_add(1000, progress_timeout, songProgress);//set timer
    gtk_widget_set_size_request(songProgress, 280, 10);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (songProgress), 0);
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR (songProgress), GTK_PROGRESS_LEFT_TO_RIGHT);
    gtk_fixed_put(GTK_FIXED(fixed), songProgress,  25, 380);
    soundProgress = gtk_progress_bar_new();
    gtk_widget_set_size_request(soundProgress, 240, 10);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (soundProgress), 0.5);
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR (soundProgress), GTK_PROGRESS_LEFT_TO_RIGHT);
    gtk_fixed_put(GTK_FIXED(fixed), soundProgress,  45, 521);

    //preBtn
    preBtn = gtk_button_new_with_label("<<");
    gtk_widget_set_size_request(preBtn, 89, 89);
    g_signal_connect(preBtn, "pressed", G_CALLBACK(deal_pressed), "上一曲");
    gtk_fixed_put(GTK_FIXED(fixed), preBtn, 33, 420);
    //pauseBtn
    pauseBtn = gtk_toggle_button_new_with_label("PLAY/\nPAUSE");//_with_label("暂停");
    //pauseBtnImg = gtk_image_new();
    //gtk_image_set_from_stock(GTK_IMAGE(pauseBtnImg), GTK_STOCK_MEDIA_PLAY, GTK_ICON_SIZE_LARGE_TOOLBAR);
    //gtk_container_add(GTK_CONTAINER(pauseBtn), pauseBtnImg);
    gtk_widget_set_size_request(pauseBtn, 89, 89);
    g_signal_connect(pauseBtn, "pressed", G_CALLBACK(toggle_button_callback), "暂停");
    gtk_fixed_put(GTK_FIXED(fixed), pauseBtn, 122, 420);
    //nextBtn
    nextBtn = gtk_button_new_with_label(">>");
    gtk_widget_set_size_request(nextBtn, 89, 89);
    g_signal_connect(nextBtn, "pressed", G_CALLBACK(deal_pressed), "下一曲");
    gtk_fixed_put(GTK_FIXED(fixed), nextBtn, 211, 420);
    //volDownBtn
    volDownBtn = gtk_button_new_with_label("<");
    gtk_widget_set_size_request(volDownBtn, 20, 20);
    g_signal_connect(volDownBtn, "pressed", G_CALLBACK(deal_pressed_vol), "volDown");
    gtk_fixed_put(GTK_FIXED(fixed), volDownBtn, 25, 515);
    //volUpBtn
    volUpBtn = gtk_button_new_with_label(">");
    gtk_widget_set_size_request(volUpBtn, 20, 20);
    g_signal_connect(volUpBtn, "pressed", G_CALLBACK(deal_pressed_vol), "volUp");
    gtk_fixed_put(GTK_FIXED(fixed), volUpBtn, 285, 515);


    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
//mplayer