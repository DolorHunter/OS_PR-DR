#ifndef DEADLOCKRECOVERY_DEADLOCKRECOVERY_H
#define DEADLOCKRECOVERY_DEADLOCKRECOVERY_H

#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 8
#define MAX_RESOURCE 8
#define INF 65535

typedef struct ResourceAllocation{
    int proNum;                                  // 初始进程数
    int process[MAX_PROCESS];                    // 进程表
    int resource[MAX_RESOURCE];                  // 资源表
    int resApply[MAX_PROCESS][MAX_RESOURCE];     // 资源申请表
    int resAllocate[MAX_PROCESS][MAX_RESOURCE];  // 资源分配表
    int relResource[MAX_RESOURCE];                // 可释放资源表
    int relProcess[MAX_PROCESS];                 // 可释放进程表
    int relProPos;                               // 可释放资源表位置
    int leftProNum;                              // 剩余进程数
    int resProcess[MAX_PROCESS];                 // 释放进程表
}ResourceAllocation;

int bestRes2Release(ResourceAllocation *rA);
void addResProcess(ResourceAllocation *rA, int pro);
void relProcess(ResourceAllocation *rA, int pro);
void deadlockRecovery(ResourceAllocation *rA);

#endif //DEADLOCKRECOVERY_DEADLOCKRECOVERY_H
