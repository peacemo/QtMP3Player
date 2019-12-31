#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include"mygetch.h"
void startGame();
//main()
int main(){
    char restartFlag[] = "y";
    printf("---游戏规则：系统给出一段字符，请按原样将其键入\n");
    printf("---当你按下首字母开始计时\n---正确则原样输出，错误输出\"*\"\n---按下任意键开始游戏...\n");
    mygetch();
    do{
        startGame();
        printf("\n*Do it again? [y/n]: ");
        while(1){//the loop to judge if you input is [y/n]
            scanf("%s", restartFlag);
            getchar();//Catch the extra "Enter"
            //if the input is [y/n], break while n' into do-while
            if(strcmp(restartFlag, "y") == 0 || strcmp(restartFlag, "n") == 0){break;}
            //if the input isn't [y/n], reinput the choise
            else{printf("[y/n] are expected, check your input: ");}
        }
    }while(strcmp(restartFlag, "y") == 0);
    return 0;
}
//startGame()
void startGame(){
    fflush(stdin);//refresh the input cache
    int rightCount = 0;
    time_t startTime, endTime;
    char ques[14] = {0};
    char ans[14] = {0};
    
    srand((unsigned)time(NULL));
    printf("--------------------\n");
    //get the random list
    for(int i = 0; i < 14; i++){
        ques[i] = rand() % 26 + 'a';
    }
    printf("%s\n", ques);
    //get input
    ans[0] = mygetch();
    time(&startTime);
    if(ans[0] == ques[0]){
            printf("%c", ans[0]);
            rightCount++;
    }
    else{
        printf("*");
    }
    for(int j = 1; j < 14; j++){
        ans[j] = mygetch();
        if(ans[j] == ques[j]){
            printf("%c", ans[j]);
            rightCount++;
        }
        else{
            printf("*");
        }
    }
    time(&endTime);
    printf("\n----\n*游戏结束\n*正确率：%.1f%%(%d/14)\n", ((rightCount * 1.0)/(14 * 1.0)) * 100.0, rightCount);
    printf("*用时：%lus\n", (endTime - startTime));
}