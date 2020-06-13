#include "file.h"

void init_info(Info *info){
    (*info).pageSize = 0;
    for (int i=0; i<MAX_LENGTH; ++i){
        (*info).pageInfo[i] = '\0';
    }
}

void chooseFile(char *fileName){
    int fileNum;
    printf("******Pick a PagesReplacement Case to Play******\n");
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

void readFile(Info *info, char *fileName){
    FILE *fp;
    char ch;
    fp = fopen(fileName, "r");
    if (fp == NULL){
        printf("[ERROR] FILE OPEN FAILED!!");
        exit(-1);
    }

    int i = 0;
    while((ch = fgetc(fp)) != EOF){
        if (ch != '\n'){
            if (i == 0){
                (*info).pageSize = (int) ch - '0';
            }
            else{
                (*info).pageInfo[i-1] = ch;
            }
            i++;
        }
    }
    fclose(fp);
}

void saveFile(PagesHistory *pagesHistory, char *fileName){
    FILE *fp;
    int num;
    char ch, sNum[10];
    fileName = strcat(fileName, "_REPLAY");
    fp = fopen(fileName, "w");
    if (fp == NULL){
        printf("[ERROR] FILE OPEN FAILED!!");
        exit(-1);
    }
    for (int i=0;i<(*pagesHistory).loc;++i){
        ch = (*pagesHistory).history[i];
        if (isdigit(ch) || isalpha(ch))
            fputc(ch, fp);
        else
            fputc('0', fp);
    }
    fputc('\n', fp);
    num = (*pagesHistory).capacity;
    itoa(num, sNum, 10);
    fputs(sNum,fp);
    fputc('\n', fp);
    num = (*pagesHistory).loc;
    itoa(num, sNum, 10);
    fputs(sNum,fp);
    fputc('\n', fp);
    num = (*pagesHistory).missTime;
    itoa(num, sNum, 10);
    fputs(sNum,fp);
    fclose(fp);
}

void chooseReplayFile(char *fileName){
    int fileNum;
    printf("******Pick a PagesReplacement Case to Replay******\n");
    printf("(1) FILE_1_REPLAY\n");
    printf("(2) FILE_2_REPLAY\n");
    printf("(3) FILE_3_REPLAY\n");
    printf("Input FileNum:");
    scanf("%d", &fileNum);
    if (fileNum < 1 || fileNum > 3){
        printf("FileNum (%d) Error!! Plz choose again!!\n",fileNum);
        chooseReplayFile(fileName);
    }
    switch (fileNum){
        case 1:
            strcpy(fileName, "..\\data\\FILE1_REPLAY");
            break;
        case 2:
            strcpy(fileName, "..\\data\\FILE2_REPLAY");
            break;
        case 3:
            strcpy(fileName, "..\\data\\FILE3_REPLAY");
            break;

        default:
            break;
    }
}

void readReplayFile(PagesHistory *pagesHistory, char *fileName){
    FILE *fp;
    char str[MAX_CAPACITY*MAX_LENGTH];
    fp = fopen(fileName, "r");
    if (fp == NULL){
        printf("[ERROR] FILE OPEN FAILED!!");
        exit(-1);
    }

    if(fgets(str, MAX_CAPACITY*MAX_LENGTH, fp) != NULL){
        for (int i=0;str[i]!='\0';++i){
            (*pagesHistory).history[i] = str[i];
        }
    }
    if(fgets(str, MAX_CAPACITY*MAX_LENGTH, fp) != NULL){
        (*pagesHistory).capacity = atoi(str);
    }
    if(fgets(str, MAX_CAPACITY*MAX_LENGTH, fp) != NULL){
        (*pagesHistory).loc = atoi(str);
    }
    if(fgets(str, MAX_CAPACITY*MAX_LENGTH, fp) != NULL){
        (*pagesHistory).missTime = atoi(str);
    }
    fclose(fp);
}
