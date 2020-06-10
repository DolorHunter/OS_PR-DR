/** ENCODE: WINDOWS-936 **/
#include"timer.h"

// (1) 按键盘，每按一次可认为过一个时间单位
void timer1(int time, int pageNum){
    char input;
    while (time <= pageNum){
        scanf("%c",&input);
        if (input == '\n'){
            time += 1;
        }
    }
}

// (2) 响应 WM_TIMER
void timer2(int time, int pageNum){
    MSG msg;
	SetTimer(NULL,1,1000,NULL);  // 每隔一秒钟触发一次
    while(GetMessage(&msg, NULL, 0, 0)){
        time++;
        if(time >= pageNum)
            break;
        }
	KillTimer(NULL,1);   //销毁定时器
}

void caseTimer(int caseNum, int time, int pageNum){
    if (caseNum < 1 || caseNum > 2){
        printf("时间流逝选择错误!!请重新输入!!\n");
        scanf("%d",&caseNum);
        caseTimer(caseNum, time, pageNum);
    }
    else{
        switch (caseNum){
        case 1:
            printf("时间流逝方式: 按回车，每按一次可认为过一个时间单位\n");
            timer1(time, pageNum);
            break;
        case 2:
            printf("时间流逝方式: 响应 WM_TIMER\n");
            timer2(time, pageNum);

        default:
            break;
        }
    }
}


/// test
/*
int main(){
    caseTimer(3,0,3);
}
*/
