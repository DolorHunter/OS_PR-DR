#include "deadlockRecovery.h"

int bestRes2Release(ResourceAllocation *rA){
    int bestProcess = 0;
    int releaseRes = 0, maxReleaseRes = 0;
    for (int i=0; i<MAX_PROCESS; ++i){
        for (int j=0; j<MAX_RESOURCE; ++j){
            if ((*rA).resAllocate[i][j] != '\0'){
                releaseRes += (*rA).resAllocate[i][j];
            }
        }
        if (releaseRes > maxReleaseRes){
            maxReleaseRes = releaseRes;
            bestProcess = i;
        }
        releaseRes = 0;
    }
    return bestProcess;
}

void addResProcess(ResourceAllocation *rA, int pro){
    int resProPos = (*rA).proNum - (*rA).leftProNum - 1;
    (*rA).resProcess[resProPos] = pro;
    //printf("%d\t",pro);  // test
}

void relProcess(ResourceAllocation *rA, int pro){
    (*rA).leftProNum--;
    (*rA).process[pro] = 0;
    for (int j=0; j<MAX_RESOURCE; ++j){
        if ((*rA).resAllocate[pro][j] != '\0'){
            (*rA).resource[j] += (*rA).resAllocate[pro][j];
            (*rA).resAllocate[pro][j] = 0;
        }
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
        relProcess(rA, bestRes2Release(rA));
        printf("%d\t",bestRes2Release(rA));  // test
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
