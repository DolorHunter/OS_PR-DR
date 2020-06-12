#include "timer2.h"

void ptimer2(int *time){
    MSG msg;
    SetTimer(NULL,1,1000,NULL);  // 每秒触发一次
    while(GetMessage(&msg, NULL, 0, 0)){
        (*time)++;
        break;
    }
    KillTimer(NULL,1);
}
