#ifndef DEADLOCKRECOVERY_FILE_H
#define DEADLOCKRECOVERY_FILE_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deadlockRecovery.h"

void chooseFile(char *fileName);
void readFile(ResourceAllocation *rA, char *fileName);

#endif //DEADLOCKRECOVERY_FILE_H
