#ifndef _MPLAY_H_
    #define _MPLAY_H
        #include <stdio.h>
        #include <stdlib.h>
        #include <unistd.h>
        #include <sys/types.h>
        #include <sys/stat.h>
        #include <string.h>
        #include <fcntl.h>
        void playNPause(char cmd[]);
        void volumeControl(char cmd[]);
        void progressControl(char cmd[]);
#endif