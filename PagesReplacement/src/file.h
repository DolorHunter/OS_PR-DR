#ifndef PAGESREPLACEMENT_FILE_H
#define PAGESREPLACEMENT_FILE_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pagesReplacement.h"

#define MAX_FILENAME 64

void init_info(Info *info);
void chooseFile(char *fileName);
void readFile(Info *info, char *fileName);
void saveFile(PagesHistory *pagesHistory, char *fileName);
void chooseReplayFile(char *fileName);
void readReplayFile(PagesHistory *pagesHistory, char *fileName);

#endif //PAGESREPLACEMENT_FILE_H
