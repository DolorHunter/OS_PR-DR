#include "main.h"

int pickPlay(int casePlay){
    printf("******Play or Replay******\n");
    printf("(1) Play\n");
    printf("(2) Replay\n");
    printf("Input PlayNum:");
    scanf("%d",&casePlay);
    if (casePlay < 1 || casePlay > 2){
        printf("[WARNING] PlayCase Overflow!! Plz try again!!");
        pickPlay(casePlay);
    }
    return casePlay;
}

int pickReplacement(int caseReplacement){
    printf("******PagesReplacement Algo******\n");
    printf("(1) FIFO\n");
    printf("(2) LRU\n");
    printf("(3) OPT\n");
    printf("(4) CLOCK\n");
    printf("Input AlgoNum:");
    scanf("%d",&caseReplacement);
    if (caseReplacement < 1 || caseReplacement > 4){
        printf("[WARNING] CaseReplacement Overflow!! Plz try again!!");
        pickReplacement(caseReplacement);
    }
    return caseReplacement;
}

int pickTimer(int caseTimer){
    printf("******Timer Algo******\n");
    printf("(1) TYPING ENTER\n");
    printf("(2) WM_WAVER\n");
    printf("Input TimerNum:");
    scanf("%d",&caseTimer);
    if (caseTimer < 1 || caseTimer > 2){
        printf("[WARNING] CaseTimer Overflow!! Plz try again!!");
        pickTimer(caseTimer);
    }
    return caseTimer;
}

int main(){
    int casePlay,caseReplacement,caseTimer;
    int time;
    char fileName[MAX_FILENAME];
    Info info;
    Pages pages;
    PagesHistory pagesHistory;

    init_info(&info);
    init_timer(time);
    casePlay = pickPlay(casePlay);
    if (casePlay == 1){  // Play
        caseReplacement = pickReplacement(caseReplacement);
        caseTimer = pickTimer(caseTimer);
        chooseFile(fileName);
        readFile(&info, fileName);
        init_pages(&pages, &info, &pagesHistory);
        chooseReplacement(caseReplacement, &pages, &info, &pagesHistory);
        chooseTimer(&pagesHistory, caseTimer, time);
        saveFile(&pagesHistory, fileName);
    }
    else if (casePlay == 2){  // Replay
        caseTimer = pickTimer(caseTimer);
        chooseReplayFile(fileName);
        readReplayFile(&pagesHistory, fileName);
        chooseTimer(&pagesHistory, caseTimer, time);
    }
    else{
        printf("CasePlay (%d) Overflow!!", casePlay);
    }
    return 0;
}

