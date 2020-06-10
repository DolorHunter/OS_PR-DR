/** ENCODE: WINDOWS-936 **/
#ifndef FILE_H
#define FILE_H

#pragma once

#include<stdio.h>
#include<stdlib.h>
#include"pagesReplacement.h"

#define MAX_FILENAME 64

void init_info(Info *info);
void chooseFile(char *fileName);
void readFile(Info *info, char *fileName);
void saveFile(Pages *pages, PagesHistory *pagesHistory, char *fileName);
void chooseReplyFile(char *fileName);
void readReplyFile(PagesHistory *pagesHistory, char *fileName);

#endif // FILE_H
