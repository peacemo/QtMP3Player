#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#define FIFO "tmp/myfifo"
 
int main()
{
	char * path = "music/demo.mp3";
	if(mkfifo("tmp/myfifo",0777))
		printf("fifo create error\n");
 
	if(!fork())
	{
		system("mplayer -idle -slave -quiet music/demo.mp3");
		exit(0);
	}
	else
	{
		sleep(10);
		int fd = open(FIFO, O_WRONLY);
		write(fd, "pause\n",strlen("pause\n"));
		close(fd);
	}
 
	printf("end!\n");
	
	return 0;
}