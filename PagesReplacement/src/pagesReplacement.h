/** ENCODE: WINDOWS-936 **/
#ifndef PAGESREPLACEMENT_H
#define PAGESREPLACEMENT_H

#pragma once

#include"file.h"

#define MAX_LENGTH 256
#define MAX_CAPACITY 8

typedef struct Pages{
    int capacity;                    // ҳ������
    int load;                        // ҳ�浱ǰ����
    char page[MAX_CAPACITY];         // ҳ��
    int pagePointer;                 // ҳ��ָ��(CLOCK)
    int pageTime[MAX_CAPACITY];      // ҳ�����ʱ��(FIFO/LRU)
    int postPageTime[MAX_CAPACITY];  // ҳ���´�ʹ��ʱ��(OPT)
}Pages;

typedef struct PagesHistory{
    int capacity;                           // ҳ������
    int loc;                                // ָ��λ��(ҳ��*����)
    int missTime;                           // ȱҳ����
    char history[MAX_CAPACITY*MAX_LENGTH];  // ��ʷ��¼
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
