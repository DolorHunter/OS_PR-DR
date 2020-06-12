#include "timer2.h"

void _init_timer(int time){
    time = 0;
}

void _timer1(int *time){
    char input;
    scanf("%c",&input);
    if (input == '\n'){
        (*time)++;
    }
}

void _timer2(int *time){
    MSG msg;
    SetTimer(NULL,1,1000,NULL);  // 每秒触发一次
    while(GetMessage(&msg, NULL, 0, 0)){
        (*time)++;
        break;
    }
    KillTimer(NULL,1);
}
