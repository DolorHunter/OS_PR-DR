#include "pagesReplacement.h"

void init_pages(Pages *pages, Info *info, PagesHistory *pagesHistory){
    (*pages).load = 0;
    (*pages).capacity = (*info).pageSize;
    (*pages).pagePointer = 0;
    for (int i=0;i<MAX_CAPACITY;++i){
        (*pages).page[i] = '\0';
        (*pages).pageTime[i] = 0;
        (*pages).postPageTime[i] = 0;
    }
    (*pagesHistory).capacity = (*info).pageSize;
    (*pagesHistory).loc = 0;
    (*pagesHistory).missTime = 0;
    for (int i=0;i<MAX_CAPACITY*MAX_LENGTH;++i){
        (*pagesHistory).history[i] = '\0';
    }
}

int inPageLoc(Pages *pages, char elem){
    for (int i=0; i<(*pages).capacity; ++i){
        if (elem == (*pages).page[i]){
            return i;
        }
    }
    return -1;
}

void allPagesTimePlus(Pages *pages){
    for (int i=0; i<(*pages).load; ++i){
        (*pages).pageTime[i]++;
    }
}

int maxTimeLoc(Pages *pages){
    int maxTime = 0;
    int maxLoc = 0;
    for (int i=0; i<(*pages).load; ++i){
        int curTime = (*pages).pageTime[i];
        if (curTime > maxTime){
            maxTime = curTime;
            maxLoc = i;
        }
    }
    return maxLoc;
}

void allPostTime(Pages *pages, Info *info, int loc){
    int len = 0;
    char curPage = (*info).pageInfo[loc];
    for (int i=0; i<(*pages).load; ++i){
        while(curPage != (*pages).page[i] && curPage !='#'){
            len++;
            curPage = (*info).pageInfo[loc+len];
        }
        (*pages).postPageTime[i] = len;
        len = 0;
    }
}

int maxPostTimeLoc(Pages *pages){
    int maxPostTime = 0;
    int maxLoc = 0;
    for (int i=0; i<(*pages).load; ++i){
        int curPostTime = (*pages).postPageTime[i];
        if (curPostTime > maxPostTime){
            maxPostTime = curPostTime;
            maxLoc = i;
        }
    }
    return maxLoc;
}

void savePagesHistory(Pages *pages, PagesHistory *pagesHistory){
    for (int i=0;i<(*pages).capacity;++i){
        int curLoc = (*pagesHistory).loc;
        (*pagesHistory).history[curLoc+i] = (*pages).page[i];
    }
    (*pagesHistory).loc += (*pages).capacity;
}

void prtCurPage(PagesHistory *pagesHistory, int time){
    char elem;
    int capacity = (*pagesHistory).capacity;
    for (int i=0; i<capacity; ++i){
        elem = (*pagesHistory).history[capacity*time+i];
        printf("%c\t", elem);
    }
    printf("\n");
}

void prtPagesHistory(PagesHistory *pagesHistory){
    for (int i=0;i<(*pagesHistory).loc;++i){
        if (i%(*pagesHistory).capacity == 0 && i>0)
            printf("\n");
        printf("%c",(*pagesHistory).history[i]);
    }
}

void fifo(Pages *pages, Info *info, PagesHistory *pagesHistory){
    int loc=0;
    char curPage = (*info).pageInfo[loc];
    while (curPage != '#'){
        if ((*pages).capacity > (*pages).load){
            (*pages).page[(*pages).load] = curPage;
            (*pages).load++;
        }
        else if ((*pages).capacity == (*pages).load){
            int pageLoc = inPageLoc(pages, curPage);
            if (pageLoc == -1){
                int timeLoc = maxTimeLoc(pages);
                (*pages).page[timeLoc] = curPage;
                (*pages).pageTime[timeLoc] = 0;
                (*pagesHistory).missTime++;
            }
        }
        else{
            printf("[ERROR] PageSize (%d) > Capacity!!",(*info).pageSize, (*pages).capacity);
            exit(-1);
        }
        allPagesTimePlus(pages);
        loc++;
        savePagesHistory(pages, pagesHistory);
        curPage = (*info).pageInfo[loc];
    }
}

void lru(Pages *pages, Info *info, PagesHistory *pagesHistory){
    int loc=0;
    char curPage = (*info).pageInfo[loc];
    while (curPage != '#'){
        if ((*pages).capacity > (*pages).load){
            (*pages).page[(*pages).load] = curPage;
            (*pages).load++;
        }
        else if ((*pages).capacity == (*pages).load){
            int pageLoc = inPageLoc(pages, curPage);
            if (pageLoc == -1){
                int timeLoc = maxTimeLoc(pages);
                (*pages).page[timeLoc] = curPage;
                (*pages).pageTime[timeLoc] = 0;
                (*pagesHistory).missTime++;
            }
            else{
                (*pages).pageTime[pageLoc] = 0;
            }
        }
        else{
            printf("[ERROR] PageSize (%d) > Capacity!!",(*info).pageSize, (*pages).capacity);
            exit(-1);
        }
        allPagesTimePlus(pages);
        loc++;
        savePagesHistory(pages, pagesHistory);
        curPage = (*info).pageInfo[loc];
    }
}

void opt(Pages *pages, Info *info, PagesHistory *pagesHistory){
    int loc=0;
    char curPage = (*info).pageInfo[loc];
    while (curPage != '#'){
        if ((*pages).capacity > (*pages).load){
            (*pages).page[(*pages).load] = curPage;
            (*pages).load++;
        }
        else if ((*pages).capacity == (*pages).load){
            int pageLoc = inPageLoc(pages, curPage);
            if (pageLoc == -1){
                allPostTime(pages, info, loc);
                int timeLoc = maxPostTimeLoc(pages);
                (*pages).page[timeLoc] = curPage;
                (*pagesHistory).missTime++;
            }
        }
        else{
            printf("[ERROR] PageSize (%d) > Capacity!!",(*info).pageSize, (*pages).capacity);
            exit(-1);
        }
        loc++;
        savePagesHistory(pages, pagesHistory);
        curPage = (*info).pageInfo[loc];
    }
}

void clock(Pages *pages, Info *info, PagesHistory *pagesHistory){
    int loc=0;
    char curPage = (*info).pageInfo[loc];
    while (curPage != '#'){
        if ((*pages).capacity > (*pages).load){
            (*pages).page[(*pages).load] = curPage;
            (*pages).load++;
            (*pages).pagePointer++;
            (*pages).pagePointer %= (*pages).capacity;
        }
        else if ((*pages).capacity == (*pages).load){
            int pageLoc = inPageLoc(pages, curPage);
            if (pageLoc == -1){
                int pointer = (*pages).pagePointer;
                (*pages).page[pointer] = curPage;
                (*pages).pagePointer++;
                (*pages).pagePointer %= (*pages).capacity;
                (*pagesHistory).missTime++;
            }
        }
        else{
            printf("[ERROR] PageSize (%d) > Capacity!!",(*info).pageSize, (*pages).capacity);
            exit(-1);
        }
        loc++;
        savePagesHistory(pages, pagesHistory);
        curPage = (*info).pageInfo[loc];
    }
}

void chooseReplacement(int caseNum, Pages *pages, Info *info, PagesHistory *pagesHistory){
    if (caseNum < 1 || caseNum > 4){
        printf("PagesReplacement Case (%d) Error!! Plz choose again!!\n",caseNum);
        scanf("%d",&caseNum);
        chooseReplacement(caseNum, pages, info, pagesHistory);
    }
    else{
        switch (caseNum){
            case 1:
                printf("PagesReplacement Algo: FIFO\n");
                fifo(pages, info, pagesHistory);
                break;
            case 2:
                printf("PagesReplacement Algo: LRU\n");
                lru(pages, info, pagesHistory);
                break;
            case 3:
                printf("PagesReplacement Algo: OPT\n");
                opt(pages, info, pagesHistory);
                break;
            case 4:
                printf("PagesReplacement Algo: CLOCK\n");
                clock(pages, info, pagesHistory);
                break;

            default:
                break;
        }
    }
}
