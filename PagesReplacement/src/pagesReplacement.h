#ifndef PAGESREPLACEMENT_H
#define PAGESREPLACEMENT_H

#include"file.h"

#define MAX_CAPACITY 16

typedef struct Pages{
    int capacity;                    // ҳ������
    int load;                        // ҳ�浱ǰ����
    int missTime;                    // ȱҳ����
    char page[MAX_CAPACITY];         // ҳ��
    int pagePointer;                 // ҳ��ָ��(CLOCK)
    int pageTime[MAX_CAPACITY];      // ҳ�����ʱ��(FIFO/LRU)
    int postPageTime[MAX_CAPACITY];  // ҳ���´�ʹ��ʱ��(OPT)
}Pages;

typedef struct PagesHistory{
    int loc;                                // ָ��λ��
    char history[MAX_CAPACITY*MAX_LENGTH];  // ��ʷ��¼
}PagesHistory;

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
