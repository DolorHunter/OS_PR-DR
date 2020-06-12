#ifndef PAGESREPLACEMENT_PAGESREPLACEMENT_H
#define PAGESREPLACEMENT_PAGESREPLACEMENT_H

#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 256
#define MAX_CAPACITY 8

typedef struct Pages{
    int capacity;                    // capacity
    int load;                        // load
    char page[MAX_CAPACITY];         // curPage
    int pagePointer;                 // pointer(CLOCK)
    int pageTime[MAX_CAPACITY];      // exist time(FIFO/LRU)
    int postPageTime[MAX_CAPACITY];  // next time to use(OPT)
}Pages;

typedef struct PagesHistory{
    int capacity;                           // capacity
    int loc;                                // pointer(capacity*pageNum)
    int missTime;                           // missTime
    char history[MAX_CAPACITY*MAX_LENGTH];  // history
}PagesHistory;

typedef struct Info{
    int pageSize;
    char pageInfo[MAX_LENGTH];
}Info;

void init_pages(Pages *pages, Info *info, PagesHistory *pagesHistory);
int inPageLoc(Pages *pages, char elem);
void allPagesTimePlus(Pages *pages);
int maxTimeLoc(Pages *pages);
void allPostTime(Pages *pages, Info *info, int loc);
int maxPostTimeLoc(Pages *pages);
void savePagesHistory(Pages *pages, PagesHistory *pagesHistory);
void prtCurPage(PagesHistory *pagesHistory, int time);
void prtPagesHistory(PagesHistory *pagesHistory);

void fifo(Pages *pages, Info *Info, PagesHistory *pagesHistory);
void lru(Pages *pages, Info *info, PagesHistory *pagesHistory);
void opt(Pages *pages, Info *info, PagesHistory *pagesHistory);
void clock(Pages *pages, Info *info, PagesHistory *pagesHistory);
void chooseReplacement(int caseNum, Pages *pages, Info *info, PagesHistory *pagesHistory);

#endif //PAGESREPLACEMENT_PAGESREPLACEMENT_H
