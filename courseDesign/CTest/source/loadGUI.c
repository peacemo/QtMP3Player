#include "loadGUI.h"
#include "mPlay.h"
#define FIFO "../tmp/myfifo"
//callBack funcs
void deal_pressed(GtkButton *button, gpointer user_data);
void toggle_button_callback (GtkWidget *widget, gpointer data);
void deal_pressed_vol(GtkButton *button, gpointer user_data);
gint progress_timeout(gpointer data);
void initProgress();

//globle variases
GtkWidget *songName;
GtkWidget *songProgress, *soundProgress;
GtkWidget *fixed;
GtkWidget *preBtn, *pauseBtn, *nextBtn, *volDownBtn, *volUpBtn;
GtkWidget *foreBtn, *backBtn, *muteBtn, *unMuteBtn;
GtkWidget *preBtnImg, *pauseBtnImg, *nextBtnImg, *backBtnImg, *foreBtnImg, *muteBtnImg, *unMuteBtnImg;
GtkWidget *window;
GtkWidget *albumImg, *startBtnImg, *pauseBtnImg, *preBtnImg, *nextBtnImg;
GtkWidget *listOfSongs;
const gchar *rows[3];
static GdkColor black = {0, 0, 0, 0};
int fd = 0;


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
    albumImg = gtk_image_new_from_file("../img/album.png");
    gtk_widget_set_size_request(albumImg, 276, 276);
    gtk_fixed_put(GTK_FIXED(fixed), albumImg, 25, 30);

    //create Btn images
    startBtnImg = gtk_image_new_from_file("../img/startBtn.png");
    pauseBtnImg = gtk_image_new_from_file("../img/pauseBtn.png");
    preBtnImg = gtk_image_new_from_file("../img/preBtn.png");
    nextBtnImg = gtk_image_new_from_file("../img/nextBtn.png");
    backBtnImg = gtk_image_new_from_file("../img/backBtn.png");
    foreBtnImg = gtk_image_new_from_file("../img/foreBtn.png");
    muteBtnImg = gtk_image_new_from_file("../img/muteBtn.png");
    unMuteBtnImg = gtk_image_new_from_file("../img/unMuteBtn.png");

    //list
    listOfSongs = gtk_clist_new(1);
    rows[0] = "Hey Jude - The Beatles";
    rows[1] = "Golden Slumbers - The Beatles";
    rows[2] = "Let It Be - The Beatles";
    gtk_clist_set_column_title(GTK_CLIST(listOfSongs), 0, "songInfo");
    gtk_clist_append(GTK_CLIST(listOfSongs), (gchar**)rows);

    //song and singer
    songName = gtk_label_new(rows[0]);
    gtk_widget_modify_fg(songName, GTK_STATE_NORMAL, &black);
    gtk_fixed_put(GTK_FIXED(fixed), songName,  25, 320);

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
    gtk_fixed_put(GTK_FIXED(fixed), soundProgress,  45, 511);

    //preBtn
    preBtn = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(preBtn), preBtnImg);
    gtk_widget_set_size_request(preBtn, 89, 89);
    g_signal_connect(preBtn, "pressed", G_CALLBACK(deal_pressed), "上一曲");
    gtk_fixed_put(GTK_FIXED(fixed), preBtn, 33, 410);
    //pauseBtn
    pauseBtn = gtk_toggle_button_new();//_with_label("暂停");
    gtk_button_set_image(GTK_BUTTON(pauseBtn), startBtnImg);
    gtk_widget_set_size_request(pauseBtn, 89, 89);
    g_signal_connect(pauseBtn, "pressed", G_CALLBACK(toggle_button_callback), "暂停");
    gtk_fixed_put(GTK_FIXED(fixed), pauseBtn, 122, 410);
    //nextBtn
    nextBtn = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(nextBtn), nextBtnImg);
    gtk_widget_set_size_request(nextBtn, 89, 89);
    g_signal_connect(nextBtn, "pressed", G_CALLBACK(deal_pressed), "下一曲");
    gtk_fixed_put(GTK_FIXED(fixed), nextBtn, 211, 410);
    //volDownBtn
    volDownBtn = gtk_button_new_with_label("-");
    gtk_widget_set_size_request(volDownBtn, 20, 20);
    g_signal_connect(volDownBtn, "pressed", G_CALLBACK(deal_pressed_vol), "volDown");
    gtk_fixed_put(GTK_FIXED(fixed), volDownBtn, 25, 506);
    //volUpBtn
    volUpBtn = gtk_button_new_with_label("+");
    gtk_widget_set_size_request(volUpBtn, 20, 20);
    g_signal_connect(volUpBtn, "pressed", G_CALLBACK(deal_pressed_vol), "volUp");
    gtk_fixed_put(GTK_FIXED(fixed), volUpBtn, 285, 506);
    gtk_widget_show_all(window);
    //backBtn
    backBtn = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(backBtn), backBtnImg);
    gtk_widget_set_size_request(backBtn, 50, 50);
    g_signal_connect(backBtn, "pressed", G_CALLBACK(deal_pressed), "backward");
    gtk_fixed_put(GTK_FIXED(fixed), backBtn, 25, 533);
    //muteBtn
    muteBtn = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(muteBtn), muteBtnImg);
    gtk_widget_set_size_request(muteBtn, 50, 50);
    g_signal_connect(muteBtn, "pressed", G_CALLBACK(deal_pressed_vol), "mute");
    gtk_fixed_put(GTK_FIXED(fixed), muteBtn, 102, 533);
    //unMuteBtn
    unMuteBtn = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(unMuteBtn), unMuteBtnImg);
    gtk_widget_set_size_request(unMuteBtn, 50, 50);
    g_signal_connect(unMuteBtn, "pressed", G_CALLBACK(deal_pressed_vol), "unmute");
    gtk_fixed_put(GTK_FIXED(fixed), unMuteBtn, 179, 533);
    //foreBtn
    foreBtn = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(foreBtn), foreBtnImg);
    gtk_widget_set_size_request(foreBtn, 50, 50);
    g_signal_connect(foreBtn, "pressed", G_CALLBACK(deal_pressed), "foreward");
    gtk_fixed_put(GTK_FIXED(fixed), foreBtn, 256, 533);
    gtk_widget_show_all(window);

    //initProgress();
    
}


//the active function when press the normal btn
void deal_pressed(GtkButton *button, gpointer user_data)
{
    static int flagOfSong = 0;
	// 获得按钮的文本信息
	const char *text = gtk_button_get_label( button );
    char cmd[128] = {'\0'};
    if(text == NULL){
        text = "null";
    }
	// g_print() 相当于C语言的 printf(), gchar相当于char
    if(strcmp(user_data, "下一曲") == 0){
        flagOfSong += 1;
        if(flagOfSong > 2){
            flagOfSong = 0;
        }
        sprintf(cmd, "loadfile \"../music/%s.mp3\"\n", rows[flagOfSong]);
        write(fd, cmd, strlen(cmd));
        gtk_label_set_label(GTK_LABEL(songName), rows[flagOfSong]);
    }
    if(strcmp(user_data, "上一曲") == 0){
        flagOfSong -= 1;
        if(flagOfSong < 0){
            flagOfSong = 2;
        }
        sprintf(cmd, "loadfile \"../music/%s.mp3\"\n", rows[flagOfSong]);
        write(fd, cmd, strlen(cmd));
        gtk_label_set_label(GTK_LABEL(songName), rows[flagOfSong]);
    }
    if(strcmp(user_data, "backward") == 0){
        char cmd[] = "seek -10\n";
        write(fd, cmd, strlen(cmd));
    }
    if(strcmp(user_data, "foreward") == 0){
        char cmd[] = "seek 10\n";
        write(fd, cmd, strlen(cmd));
    }
    
	g_print("button_text = %s; user_data = %s\n", text, (gchar *)user_data);
    
}


//toggle btn call back
void toggle_button_callback (GtkWidget *widget, gpointer data)
{
    char cmd[] = "pause\n";
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget))) 
    {
        /* 如果运行到这里，开关按钮是按下的 */
        write(fd, cmd, strlen(cmd));
    } else {
        /* 如果运行到这里，开关按钮是弹起的 */
        write(fd, cmd, strlen(cmd));
    }
}



//volume control call back
void deal_pressed_vol(GtkButton *button, gpointer user_data)
{
    static int volVal = 0;
    static double volDiff = 0;
	const char *text = gtk_button_get_label( button );
    if(text == NULL){
        text = "null";
    }
    char cmd[128] = {'\0'};
    g_print("button_text = %s; user_data = %s\n", text, (gchar *)user_data);

    if(strcmp(user_data, "volUp") == 0){  
        volDiff += 0.04;
        if(volDiff > 0.5){
            volDiff = 0.5;
        }
        volVal = (int)((0.5 + volDiff)*100);
        sprintf(cmd, "volume %d 1\n", volVal);
        write(fd, cmd, strlen(cmd));
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (soundProgress), 0.5 + volDiff);       
    }

    if(strcmp(user_data, "volDown") == 0){
        char cmd[] = "volume ";
        volDiff -= 0.04;
        if(volDiff < -0.5){
            volDiff = -0.5;
        }
        volVal = (int)((0.5 + volDiff)*100);
        sprintf(cmd, "volume %d 1\n", volVal);
        write(fd, cmd, strlen(cmd));
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (soundProgress), 0.5 + volDiff);
    }

    if(strcmp(user_data, "mute") == 0){
        char cmd[] = "mute 1\n";
        write(fd, cmd, strlen(cmd));
    }

    if(strcmp(user_data, "unmute") == 0){
        char cmd[] = "mute 0\n";
        write(fd, cmd, strlen(cmd));
    }
}


//progress timeout control
gint progress_timeout(gpointer data)
{
    gdouble new_val;
    new_val = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (songProgress)) + 0.0023;

      
    if (new_val > 1.0){
	    new_val = 0.0;
    }
      /* 设置进度条的新值 */
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (songProgress), new_val);
  return TRUE;
} 

//initialize progress
//create a fifo file as a pipe 
//then create progress, 0 stands for child progress
//load GUI in the parent progress and mplayer is loaded in the child progress
void initProgress(){
    //int ret = 0;
    //ret = mkfifo(FIFO, 0666);//make a fifo file
    if ((mkfifo(FIFO, 0666) < 0) && (errno != EEXIST)){
             perror("Cannot create fifo file\n");
             exit(1);
    }
    fd = open(FIFO, O_RDWR);//get the file describtion symbol
    // loadGUI();
    int pid = 0;
    pid = fork();//create pprogress
    if (pid <0)
    {
        perror("fork");
    }
    else if (pid == 0)//child progress
    {
        execlp("mplayer","mplayer","-ac", "mad", "-slave","-quiet","-idle","-input","file=../tmp/myfifo","../music/Hey Jude - The Beatles.mp3",NULL);
    }
    else{//parent progress
        loadGUI();
        write(fd, "volume 50 1\n", strlen("volume 50 1\n"));
    }
}