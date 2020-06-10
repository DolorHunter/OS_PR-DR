/** ENCODE: WINDOWS-936 **/
#ifndef PAGESREPLACEMENT_H
#define PAGESREPLACEMENT_H

#pragma once

#include"file.h"

#define MAX_LENGTH 256
#define MAX_CAPACITY 8

typedef struct Pages{
    int capacity;                    // 页面容量
    int load;                        // 页面当前负载
    char page[MAX_CAPACITY];         // 页面
    int pagePointer;                 // 页面指针(CLOCK)
    int pageTime[MAX_CAPACITY];      // 页面存在时间(FIFO/LRU)
    int postPageTime[MAX_CAPACITY];  // 页面下次使用时间(OPT)
}Pages;

typedef struct PagesHistory{
    int capacity;                           // 页面容量
    int loc;                                // 指针位置(页面*容量)
    int missTime;                           // 缺页次数
    char history[MAX_CAPACITY*MAX_LENGTH];  // 历史记录
}PagesHistory;

typedef struct Info{
    int pageSize;
    char pageInfo[MAX_LENGTH];
}Info;

void init_pages(Pages *ages, Info *info, PagesHistory *pagesHistory);
int inPageLoc(Pages *pages, char elem);
void allPagesTimePlus(Pages *pages);
int maxTimeLoc(Pages *pages);
void allPostTime(Pages *pages, Info *info, int loc);
int maxPostTimeLoc(Pages *pages);
void savePagesHistory(Pages *pages, PagesHistory *pagesHistory);
void prtPagesHistory(Pages *pages, PagesHistory *pagesHistory);

void fifo(Pages *pages, Info *Info, PagesHistory *pagesHistory);
void lru(Pages *pages, Info *info, PagesHistory *pagesHistory);
void opt(Pages *pages, Info *info, PagesHistory *pagesHistory);
void clock(Pages *pages, Info *info, PagesHistory *pagesHistory);
void casePagesPlacement(int caseNum, Pages *pages, Info *info, PagesHistory *pagesHistory);

#endif // PAGESREPLACEMENT_H
