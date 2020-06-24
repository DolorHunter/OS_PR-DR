#include "main.h"

int main(){
    ResourceAllocation  rA;
    char fileName[30];
    printf("Deadlock Recovery\n");
    initDeadlockRecovery(&rA);
    chooseFile(fileName);
    readFile(&rA, fileName);
    printf("Resource Allocation Diagram File\n");
    prtResourceAllocation(&rA);
    printf("\nANS = ");
    deadlockRecovery(&rA);
    printf("\nANS1: 2013 / 2031\n");
    printf("ANS2: 41203 / 41230\n");
    printf("ANS3: 0365142 / 3065142\n");
    printf("Deadlock Recovery Process\n");
    prtSearchProcess(&rA);
    return 0;
}
