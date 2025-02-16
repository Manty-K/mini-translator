#include "../data-structures/array/array.h"
#include <stdio.h>
#include <stdlib.h>
#include "statements.h"
#include "instructions_processing.h"
#include "unique_generator.h"
#include "utils.h"
#include <string.h>
extern ARRAY *instructionArray;

extern ARRAY *declareArray;
extern ARRAY *initializeArray;
extern ARRAY *loopArray;
extern ARRAY *conditionArray;
extern ARRAY *printArray;

char *uniqueLabel;

int variableNum = 0;

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
        INSTRUCTION *inst = getElementArray(declareArray, i);

        DECLARE_INST decl = inst->data.declare;
        labelsArray[i] = decl.identifier;
    }
}
int getIndexOfPrevDeclaration(int target)
{

    int left = 0;
    int right = getArraySize(declareArray) - 1;

    int result;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        INSTRUCTION *inst = getElementArray(declareArray, mid);

        if (inst->lineNo < target)
        {
            result = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return result;
}

char is_child(const char *parent, const char *child)
{
    int parent_len = strlen(parent);
    int child_len = strlen(child);

    if (parent_len == 0)
    {
        return 1;
    }

    if (strncmp(parent, child, parent_len) == 0)
    {
        if (child_len >= parent_len)
        {
            return 1;
        }
    }

    return 0;
}

void processPrint()
{
    int printCount = getArraySize(printArray);

    for (int i = 0; i < printCount; i++)
    {
        int found = 0;
        INSTRUCTION *pinst = getElementArray(printArray, i);

        PRINT_INST printInst = pinst->data.print;

        int preindex = getIndexOfPrevDeclaration(pinst->lineNo);

        for (int j = preindex; j >= 0; j--)
        {
            INSTRUCTION *inst = ((INSTRUCTION *)getElementArray(declareArray, j));

            if (!strcmp(inst->data.declare.identifier, printInst.data))
            {

                if (is_child(inst->scope, pinst->scope))
                {
                    printf("%s at line %d can be taken\n", inst->data.declare.identifier, inst->lineNo);
                    found = 1;
                    break;
                }
            }
        }
        if (!found)
        {
            fprintf(stderr, "'%s' not declared (Instruction no: %d).\n", printInst.data, pinst->lineNo);
            exit(1);
        }
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

    processPrint();
    // generateUnique();

    // printf("Uniqie = %s\n", uniqueLabel);
}
