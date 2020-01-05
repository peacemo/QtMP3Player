#include "loadGUI.h"
#include "mPlay.h"

//callBack funcs
void deal_pressed(GtkButton *button, gpointer user_data);
void toggle_button_callback (GtkWidget *widget, gpointer data);
void deal_pressed_vol(GtkButton *button, gpointer user_data);
gint progress_timeout(gpointer data);


//globle variases
GtkWidget *songName, *singerName;
GtkWidget *songProgress, *soundProgress;
GtkWidget *fixed;
GtkWidget *preBtn, *pauseBtn, *nextBtn, *volDownBtn, *volUpBtn;
GtkWidget *preBtnImg, *pauseBtnImg, *nextBtnImg;
GtkWidget *window;
GtkWidget *albumImg, *startBtnImg, *pauseBtnImg, *preBtnImg, *nextBtnImg;
static GdkColor black = {0, 0, 0, 0};


//loadGUI
void loadGUI(){
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

    //create Btn images
    startBtnImg = gtk_image_new_from_file("img/startBtn.png");
    pauseBtnImg = gtk_image_new_from_file("img/pauseBtn.png");
    preBtnImg = gtk_image_new_from_file("img/preBtn.png");
    nextBtnImg = gtk_image_new_from_file("img/nextBtn.png");

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
    preBtn = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(preBtn), preBtnImg);
    gtk_widget_set_size_request(preBtn, 89, 89);
    g_signal_connect(preBtn, "pressed", G_CALLBACK(deal_pressed), "上一曲");
    gtk_fixed_put(GTK_FIXED(fixed), preBtn, 33, 420);
    //pauseBtn
    pauseBtn = gtk_toggle_button_new();//_with_label("暂停");
    gtk_button_set_image(GTK_BUTTON(pauseBtn), startBtnImg);
    gtk_widget_set_size_request(pauseBtn, 89, 89);
    g_signal_connect(pauseBtn, "pressed", G_CALLBACK(toggle_button_callback), "暂停");
    gtk_fixed_put(GTK_FIXED(fixed), pauseBtn, 122, 420);
    //nextBtn
    nextBtn = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(nextBtn), nextBtnImg);
    gtk_widget_set_size_request(nextBtn, 89, 89);
    g_signal_connect(nextBtn, "pressed", G_CALLBACK(deal_pressed), "下一曲");
    gtk_fixed_put(GTK_FIXED(fixed), nextBtn, 211, 420);
    //volDownBtn
    volDownBtn = gtk_button_new_with_label("<");
    gtk_widget_set_size_request(volDownBtn, 20, 20);
    g_signal_connect(volDownBtn, "pressed", G_CALLBACK(deal_pressed_vol), "volDown");
    gtk_fixed_put(GTK_FIXED(fixed), volDownBtn, 25, 516);
    //volUpBtn
    volUpBtn = gtk_button_new_with_label(">");
    gtk_widget_set_size_request(volUpBtn, 20, 20);
    g_signal_connect(volUpBtn, "pressed", G_CALLBACK(deal_pressed_vol), "volUp");
    gtk_fixed_put(GTK_FIXED(fixed), volUpBtn, 285, 516);
    gtk_widget_show_all(window);
}


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
        //gtk_button_set_image(GTK_BUTTON(pauseBtn), startBtnImg);
        playNPause("pause");
        printf("ON\n");
    } else {
        /* 如果运行到这里，开关按钮是弹起的 */
        //gtk_button_set_image(GTK_BUTTON(pauseBtn), pauseBtnImg);
        playNPause("pause");
        printf("OFF\n");
    }
}


//volume control call back
void deal_pressed_vol(GtkButton *button, gpointer user_data)
{
	// 获得按钮的文本信息
    static double volDiff = 0;
	const char *text = gtk_button_get_label( button );
    g_print("button_text = %s; user_data = %s\n", text, (gchar *)user_data);
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
// void load_image(GtkWidget *tmp, const gchar *file_name, gint w, gint h)
// {
// 	//清空原有图片既清空控件内容
// 	gtk_image_clear(GTK_IMAGE(tmp));

// 	//创建一个图片资源控件
// 	GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(file_name,NULL);

// 	//修改图片大小
// 	GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf,w,h,GDK_INTERP_BILINEAR);
// 	//将图片资源设置到图片控件中
// 	gtk_image_set_from_pixbuf(GTK_IMAGE(tmp),dst_pixbuf);

// 	//释放图片资源
// 	g_object_unref(src_pixbuf);
// 	g_object_unref(dst_pixbuf);

// 	return;
// }