#include "main.h"

int main(){
    ResourceAllocation  rA;
    char fileName[30];
    initDeadlockRecovery(&rA);
    chooseFile(fileName);
    readFile(&rA, fileName);
    printf("ANS = ");
    deadlockRecovery(&rA);
    printf("\nANS1: 2013 / 2031\n");
    printf("ANS2: 41203 / 41230\n");
    printf("ANS3: 0365142 / 3065142\n");
    printf("Deadlock Recovery Process\n");
    for (int i=0; i<INF; ++i){
        if (rA.searchProcess[i][0] || rA.searchProcess[i][1] || rA.searchProcess[i][2] || rA.searchProcess[i][3])
            printf("%d\t%d\t%d\t%d\n", rA.searchProcess[i][0],rA.searchProcess[i][1],rA.searchProcess[i][2],rA.searchProcess[i][3]);
    }
    return 0;
}
