#ifndef PAGESREPLACEMENT_TIMER_H
#define PAGESREPLACEMENT_TIMER_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include"windows.h"
#include "pagesReplacement.h"

void init_timer(int time);
void timer1(PagesHistory *pagesHistory, int time);
void timer2(PagesHistory *pagesHistory, int time);

void chooseTimer(PagesHistory *pagesHistory, int caseNum, int time);

#endif //PAGESREPLACEMENT_TIMER_H
