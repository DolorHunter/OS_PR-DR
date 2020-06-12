#include "timer.h"

void init_timer(int time){
    time = 0;
}

void timer1(PagesHistory *pagesHistory, int time){
    char input;
    int pageNum = (*pagesHistory).loc / (*pagesHistory).capacity;
    while (time <= pageNum){
        scanf("%c",&input);
        if (input == '\n'){
            prtCurPage(pagesHistory, time);
            time++;
        }
    }
}

void timer2(PagesHistory *pagesHistory, int time){
    MSG msg;
    int pageNum = (*pagesHistory).loc / (*pagesHistory).capacity;
    SetTimer(NULL,1,1000,NULL);  // 每秒触发一次
    while(GetMessage(&msg, NULL, 0, 0)){
        prtCurPage(pagesHistory, time);
        time++;
        if(time >= pageNum)
            break;
    }
    KillTimer(NULL,1);
}

void chooseTimer(PagesHistory *pagesHistory, int caseNum, int time){
    if (caseNum < 1 || caseNum > 2){
        printf("Timer Case (%d) Error!! Plz choose again!!\n",caseNum);
        scanf("%d",&caseNum);
        chooseTimer(pagesHistory, caseNum, time);
    }
    else{
        switch (caseNum){
            case 1:
                printf("Timer Case: TYPING ENTER\n");
                timer1(pagesHistory, time);
                break;
            case 2:
                printf("Timer Case: WM_TIMER\n");
                timer2(pagesHistory, time);
                break;

            default:
                break;
        }
        int missTime = (*pagesHistory).missTime;
        int pagesNum = (*pagesHistory).loc / (*pagesHistory).capacity;
        float missRate = (float)missTime / (float)pagesNum;
        printf("missTime:%d\tpagesNum%d\tmissRate%f",missTime,pagesNum, missRate);
    }
}
