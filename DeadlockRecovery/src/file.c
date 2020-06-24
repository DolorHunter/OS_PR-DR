#include "file.h"

void chooseFile(char *fileName){
    int fileNum;
    printf("******Pick a DeadlockRecovery Case to Play******\n");
    printf("(1) FILE1\n");
    printf("(2) FILE2\n");
    printf("(3) FILE3\n");
    printf("Input FileNum:");
    scanf("%d", &fileNum);
    if (fileNum < 1 || fileNum > 3){
        printf("FileNum (%d) Error!! Plz choose again!!\n",fileNum);
        chooseFile(fileName);
    }
    switch (fileNum){
        case 1:
            strcpy(fileName, "..\\data\\FILE1");
            break;
        case 2:
            strcpy(fileName, "..\\data\\FILE2");
            break;
        case 3:
            strcpy(fileName, "..\\data\\FILE3");
            break;

        default:
            break;
    }
}

void readFile(ResourceAllocation *rA, char *fileName){
    FILE *fp;
    char str[INF];
    fp = fopen(fileName, "r");
    if (fp == NULL){
        printf("[ERROR] FILE OPEN FAILED!!");
        exit(-1);
    }

    if (fgets(str, INF, fp) != NULL){
        (*rA).proNum = atoi(str);
    }
    if (fgets(str, INF, fp) != NULL){
        for (int i=0; str[i]!='\0'; ++i){
            if (str[i] == '\n')
                break;
            (*rA).process[i] = (int)str[i] - '0';
        }
    }
    if (fgets(str, INF, fp) != NULL){
        int pos = 0;
        for (int i=0; str[i]!='\0'; ++i){
            if (str[i] == '\n')
                break;
            if (str[i] != ','){
                (*rA).resource[pos] = (int)str[i] - '0';
            }
            else{
                pos++;
            }
        }
    }
    if (fgets(str, INF, fp) != NULL){
        int row = 0, col = 0;
        for (int i=0; str[i]!='\0'; ++i){
            if (str[i] == '\n')
                break;
            if (str[i] != ','){
                (*rA).resApply[row][col] = (int)str[i] - '0';
                col++;
            }
            else{
                row++;
                col = 0;
            }
        }
    }
    if (fgets(str, INF, fp) != NULL){
        int row = 0, col = 0;
        for (int i=0; str[i]!='\0'; ++i){
            if (str[i] == '\n')
                break;
            if (str[i] != ','){
                (*rA).resAllocate[row][col] = (int)str[i] - '0';
                col++;
            }
            else{
                row++;
                col = 0;
            }
        }
    }
}

/*
int main(){
    ResourceAllocation  rA;
    char fileName[30];
    readFile(&rA, "..\\data\\FILE1");
    prtResourceAllocation(&rA);
}
*/