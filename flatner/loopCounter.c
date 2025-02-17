#include "utils.h"
#include "loopCounter.h"
#include <stdlib.h>
#include <stdio.h>
#include "../data-structures/stack/stack.h"
int loopCount = 0;

STACK *loopStack;

void initializeLoopStack()
{

    loopStack = createStack();
}

char *getLoopName(int type)
{
    int c = *(int *)peekStack(loopStack);
    char *varName = malloc(getIntLength(c) + 2);
    sprintf(varName, "l%s%d", type == START ? "srt" : "stp", c);
    return varName;
}

void loopOpen()
{
    int *myint = (int *)malloc(sizeof(int));
    *myint = loopCount;
    pushStack(loopStack, myint);
    loopCount++;
}

void loopClose()
{
    popStack(loopStack);
}
