/*
打字游戏：

	1.打印游戏规则                            printf
		按下任意键开始游戏
		当你按下首字母开始计时
		正确原样输出，错误输出_


	2.按下任意键（无回显的按下）				mygetch
		先生成随机字符并组成随机字符串         for循环生成  srand(time(NULL));//设置随机数种子
												再利用rand()就可以生成随机时间 20191231112028
												rand()%26+'a';
		打印生成好的随机字符串
	3.按下键盘进行比较   if
		如果是第一次按下就记录一下时间
		判断按下的键和随机字符串中的字符进行比较
			如果正确就原样输出，并且记录一下正确个数
			如果错误就打印_
	4.打完了之后进行记录时间
	5.输出用时、正确率 



友情提供：(#^.^#)
获得键盘输入的函数
*/

#include<termios.h>   //tcgetattr函数所需头文件
#include<unistd.h>
#include"mygetch.h"
char mygetch()
{
	struct termios oldt,newt;
	char ch;
	tcgetattr(STDIN_FILENO,&oldt);
	newt=oldt;
	newt.c_lflag &=~( ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW ,&newt );
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW ,&oldt );
	return ch;
}




