/** ENCODE: WINDOWS-936 **/
#include"timer.h"

// (1) �����̣�ÿ��һ�ο���Ϊ��һ��ʱ�䵥λ
void timer1(int time, int pageNum){
    char input;
    while (time <= pageNum){
        scanf("%c",&input);
        if (input == '\n'){
            time += 1;
        }
    }
}

// (2) ��Ӧ WM_TIMER
void timer2(int time, int pageNum){
    MSG msg;
	SetTimer(NULL,1,1000,NULL);  // ÿ��һ���Ӵ���һ��
    while(GetMessage(&msg, NULL, 0, 0)){
        time++;
        if(time >= pageNum)
            break;
        }
	KillTimer(NULL,1);   //���ٶ�ʱ��
}

void caseTimer(int caseNum, int time, int pageNum){
    if (caseNum < 1 || caseNum > 2){
        printf("ʱ������ѡ�����!!����������!!\n");
        scanf("%d",&caseNum);
        caseTimer(caseNum, time, pageNum);
    }
    else{
        switch (caseNum){
        case 1:
            printf("ʱ�����ŷ�ʽ: ���س���ÿ��һ�ο���Ϊ��һ��ʱ�䵥λ\n");
            timer1(time, pageNum);
            break;
        case 2:
            printf("ʱ�����ŷ�ʽ: ��Ӧ WM_TIMER\n");
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
