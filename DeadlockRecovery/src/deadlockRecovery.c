#include "deadlockRecovery.h"

void initRelProcess(ResourceAllocation *rA){
    for (int i=0; i<MAX_PROCESS; ++i){
        (*rA).relProcess[i] = '\0';
    }
    (*rA).relProPos = 0;
    for (int j=0; j<MAX_RESOURCE; ++j){
        (*rA).relResource[j] = '\0';
    }
}

void genRelProcess(ResourceAllocation *rA){
    initRelProcess(rA);
    int resApply = 0;
    for (int j=0; j<MAX_RESOURCE; ++j){
        for (int i=0; i<MAX_PROCESS; ++i){
            if ((*rA).resApply[i][j] != '\0'){
                resApply += (*rA).resApply[i][j];
            }
        }
        if ((*rA).resource[j] >= resApply){
            (*rA).relResource[j] = 1;
        }
        resApply = 0;
    }
    int count = 0;
    for (int i=0; i<MAX_PROCESS; ++i){
        for (int j=0; j<MAX_RESOURCE; j++){
            if ((*rA).resApply[i][j] == '\0'){
                count++;
            }
            else{
                if ((*rA).relResource[j] == 1){
                    count++;
                }
            }
        }
        if ((*rA).process[i] == 1 && count == MAX_RESOURCE){
            int pos = (*rA).relProPos;
            (*rA).relProcess[pos] = i;
            (*rA).relProPos++;
        }
        count = 0;
    }
}

int isReleasable(ResourceAllocation *rA, int pro){
    for (int i=0; i<MAX_PROCESS; ++i){
        if ((*rA).relProcess[i] == pro){
            return 1;
        }
    }
    return 0;
}

int bestRes2Release(ResourceAllocation *rA){
    int bestProcess = 0;
    int applyRes = 0, minApplyRes = INF;
    int relRes = 0, maxRelRes = 0;
    for (int i=0; i<MAX_PROCESS; ++i){
        if ((*rA).process[i] != '\0' && isReleasable(rA, i)){
            for (int j=0; j<MAX_RESOURCE; ++j){
                if ((*rA).resApply[i][j] != '\0'){
                    applyRes += (*rA).resApply[i][j];
                }
                if ((*rA).resAllocate[i][j] != '\0'){
                    relRes += (*rA).resAllocate[i][j];
                }
            }
            if (applyRes < minApplyRes){
                minApplyRes = applyRes;
                bestProcess = i;
            }
            else if (applyRes == minApplyRes){
                if (relRes > maxRelRes){
                    maxRelRes = relRes;
                    bestProcess = i;
                }
            }
            applyRes = 0;
            relRes = 0;
        }
    }
    printf("%d", bestProcess);
    return bestProcess;
}

void addResProcess(ResourceAllocation *rA, int pro){
    int resProPos = (*rA).proNum - (*rA).leftProNum - 1;
    (*rA).resProcess[resProPos] = pro;
}

void relProcess(ResourceAllocation *rA, int pro){
    (*rA).leftProNum--;
    (*rA).process[pro] = 0;
    for (int j=0; j<MAX_RESOURCE; ++j){
            (*rA).resource[j] += (*rA).resAllocate[pro][j];
            (*rA).resAllocate[pro][j] = 0;
        if ((*rA).resApply[pro][j] != '\0'){
            (*rA).resApply[pro][j] = 0;
        }
    }
    addResProcess(rA, pro);
}

void deadlockRecovery(ResourceAllocation *rA){
    (*rA).leftProNum = (*rA).proNum;
    int deadlock = 0;
    int processMark = (*rA).leftProNum;
    while (!deadlock && (*rA).leftProNum > 0){
        genRelProcess(rA);
        relProcess(rA, bestRes2Release(rA));
        if (processMark == (*rA).leftProNum){
            deadlock = 1;
            printf("[WARNING] Deadlock!!");
            break;
        }
        processMark = (*rA).leftProNum;
    }
}


int main(){
    ResourceAllocation rA = {4,
                             {1,1,1,1},
                             {2,2, 3},
                             {{1,0,0},{0,1,0},{0,0,0},{0,0,1}},
                             {{0,1,1},{1,0,0},{1,0,1},{0,1,0}}};
    deadlockRecovery(&rA);
}
