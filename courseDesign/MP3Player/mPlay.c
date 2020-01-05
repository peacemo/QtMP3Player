#include "mPlay.h"
#define FIFO "tmp/mPlayFifo"

void playNPause(char cmd[]){
    static int flag = 0;
    int fd = 0;
    char *path = "music/demo.mp3";
    if (flag == 0){
        system("mplayer -idle -slave -quiet music/demo.mp3");
        flag = 1;
    }
    if (flag == 1){
        write(fd,cmd,strlen(cmd));
        flag = 1;
    }
}
void volumeControl(char cmd[]);
void progressControl(char cmd[]);