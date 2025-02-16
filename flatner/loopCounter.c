#include "utils.h"
#include "loopCounter.h"
#include <stdlib.h>
#include <stdio.h>
int loopCount = 0;

char *getLoopName(int type)
{
    char *varName = malloc(getIntLength(loopCount) + 2);
    sprintf(varName, "l%s%d", type == START ? "srt" : "stp", loopCount);
    return varName;
}

void incrementLoopCount()
{
    loopCount++;
}
