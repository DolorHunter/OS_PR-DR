/** ENCODE: WINDOWS-936 **/
#include"file.h"

void init_info(Info *info){
    (*info).pageSize = 0;
    for (int i=0; i<MAX_LENGTH; ++i){
        (*info).pageInfo[i] = '\0';
    }
}

void chooseFile(char *fileName){
    int fileNum;
    printf("******选择一批页的置换情况******\n");
    printf("(1) FILE_1\n");
    printf("(2) FILE_2\n");
    printf("(3) FILE_3\n");
    printf("请输入页面置换情况:");
    scanf("%d", &fileNum);
    switch (fileNum){
    case 1:
        strcpy(fileName, "..\\data\\FILE_1");
        break;
    case 2:
        strcpy(fileName, "..\\data\\FILE_2");
        break;
    case 3:
        strcpy(fileName, "..\\data\\FILE_3");
        break;

    default:
        break;
    }
}

void readFile(Info *info, char *fileName){
    FILE *fp;
    char ch;
    chooseFile(fileName);
    fp = fopen(fileName, "r");
    if (fp == NULL){
        printf("打开文件失败!!");
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

void saveFile(Pages *pages, PagesHistory *pagesHistory, char *fileName){
    FILE *fp;
    int num;
    char ch,snum[10];
    fileName = strcat(fileName, "_REPLY");
    fp = fopen(fileName, "w");
    if (fp == NULL){
        printf("打开文件失败!!");
        exit(-1);
    }
    for (int i=0;i<(*pagesHistory).loc;++i){
        ch = (*pagesHistory).history[i];
        fputc(ch, fp);
    }
    fputc('\n', fp);
    num = (*pagesHistory).capacity;
    itoa(num, snum, 10);
    fputs(snum,fp);
    fputc('\n', fp);
    num = (*pagesHistory).loc;
    itoa(num, snum, 10);
    fputs(snum,fp);
    fputc('\n', fp);
    num = (*pagesHistory).missTime;
    itoa(num, snum, 10);
    fputs(snum,fp);
    fclose(fp);
}


void chooseReplyFile(char *fileName){
    int fileNum;
    printf("******选择一批页的置换情况重放******\n");
    printf("(1) FILE_1_REPLY\n");
    printf("(2) FILE_2_REPLY\n");
    printf("(3) FILE_3_REPLY\n");
    printf("请输入页面置换情况:");
    scanf("%d", &fileNum);
    switch (fileNum){
    case 1:
        strcpy(fileName, "..\\data\\FILE1_REPLY");
        break;
    case 2:
        strcpy(fileName, "..\\data\\FILE2_REPLY");
        break;
    case 3:
        strcpy(fileName, "..\\data\\FILE3_REPLY");
        break;

    default:
        break;
    }
}


void readReplyFile(PagesHistory *pagesHistory, char *fileName){
    FILE *fp;
    char str[MAX_CAPACITY*MAX_LENGTH];
    chooseReplyFile(fileName);
    fp = fopen(fileName, "r");
    if (fp == NULL){
        printf("打开文件失败!!");
        exit(-1);
    }

    int n=0;
    if(fgets(str, MAX_CAPACITY*MAX_LENGTH, fp) != NULL){
        ///error here
        char *token = strtok(str, '\n');
        printf("%s",token);
        while (token != NULL){
            switch(n){
            case 0:
                for (int i=0;token[i]!='\0';++i){
                    (*pagesHistory).history[i] = token[i];
                }
                break;
            case 1:
                (*pagesHistory).capacity = atoi(token);
                break;
            case 2:
                (*pagesHistory).loc = atoi(token);
                break;
            case 3:
                (*pagesHistory).missTime = atoi(token);
                break;

            default:
                break;
            }
            strtok(NULL, '\n');
            ++n;
        }
    }
    fclose(fp);
}

/// test

int main(){
    Info info;
    Pages pages;
    PagesHistory pagesHistory;// = {3,60,12,"700700701012012123230304024423230230230103210210210721072701"};
    //init_info(&info);
    char fileName[MAX_FILENAME];// = "..\\data\\FILE_1_REPLY";//"..\\data\\FILE1";
    //readFile(&info, fileName);
    //printf("%d\t%s",info.pageSize,info.pageInfo);
    //saveFile(&pages, &pagesHistory, fileName);
    readReplyFile(&pagesHistory, fileName);
    return 0;
}

