#include "../data-structures/array/array.h"
#include <stdio.h>
#include <stdlib.h>
#include "statements.h"
#include "instructions_processing.h"
#include "utils.h"
extern ARRAY *instructionArray;

extern ARRAY *declareArray;
extern ARRAY *initializeArray;
extern ARRAY *loopArray;
extern ARRAY *conditionArray;

char *uniqueLabel;

int variableNum = 0;

char *getUniqueString(char **list, int count);

char **labelsArray;

char *getTempVarName()
{
    char *varName = malloc(getIntLength(variableNum) + 2);
    sprintf(varName, "%s%d", uniqueLabel, variableNum);
    variableNum++;
    return varName;
}

void fillLabelsArray()
{

    for (int i = 0; i < getArraySize(declareArray); i++)
    {
        INSTRUCTION *inst = getElementArray(declareArray, 0);

        DECLARE_INST decl = inst->data.declare;
        labelsArray[i] = decl.identifier;
    }
}

void generateUnique()
{
    labelsArray = malloc(getArraySize(declareArray));
    fillLabelsArray();
    uniqueLabel = getUniqueString(labelsArray, getArraySize(declareArray));
    free(labelsArray);
}

void processInstructions()
{
    generateUnique();

    printf("Uniqie = %s\n", uniqueLabel);
}
