#include "../data-structures/array/array.h"
#include <stdio.h>
#include <stdlib.h>
#include "statements.h"
#include "instructions_processing.h"
#include "unique_generator.h"
// #include "tac.h"
#include "utils.h"
#include <string.h>
extern ARRAY *instructionArray;

extern ARRAY *declareArray;
extern ARRAY *initializeArray;
extern ARRAY *loopArray;
extern ARRAY *conditionArray;
extern ARRAY *printArray;

char **labelsArray;
void setUniqueVar(char **list, int count);

void fillLabelsArray()
{

    for (int i = 0; i < getArraySize(declareArray); i++)
    {
        INSTRUCTION *inst = getElementArray(declareArray, i);

        DECLARE_INST decl = inst->data.declare;
        labelsArray[i] = strdup(decl.identifier);
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

char *appendStrings(const char *str1, const char *str2)
{
    if (!str1)
        str1 = "";
    if (!str2)
        str2 = "";

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    char *result = (char *)malloc(len1 + len2 + 1);
    if (!result)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    strcpy(result, str1);
    strcat(result, str2);

    return result;
}

void traverseChangeScope(TREENODE *tree, char *currentScope, unsigned int lineNo)
{

    if (isLabel((char *)tree->data))
    {
        int found = 0;
        int preindex = getIndexOfPrevDeclaration(lineNo);

        for (int j = preindex; j >= 0; j--)
        {
            INSTRUCTION *inst = ((INSTRUCTION *)getElementArray(declareArray, j));

            if (!strcmp(inst->data.declare.identifier, tree->data))
            {

                if (is_child(inst->scope, currentScope))
                {
                    tree->data = appendStrings(tree->data, inst->scope);
                    found = 1;
                    break;
                }
            }
        }
        if (!found)
        {
            fprintf(stderr, "'%s' not declared (Instruction no: %d).\n", (char *)tree->data, lineNo);
            exit(1);
        }
    }

    for (int i = 0; i < tree->childCount; i++)
    {

        traverseChangeScope(tree->children[i], currentScope, lineNo);
    }
}

void processInitialize()
{

    int initializeInstrictionCount = getArraySize(initializeArray);

    for (int i = 0; i < initializeInstrictionCount; i++)
    {
        int found = 0;
        INSTRUCTION *inst = getElementArray(initializeArray, i);

        INITIALIZE_INST initInst = inst->data.initialize;

        traverseChangeScope(initInst.data, inst->scope, inst->lineNo);

        int preindex = getIndexOfPrevDeclaration(inst->lineNo);

        for (int j = preindex; j >= 0; j--)
        {
            INSTRUCTION *dinst = ((INSTRUCTION *)getElementArray(declareArray, j));

            if (!strcmp(dinst->data.declare.identifier, initInst.label))
            {

                if (is_child(dinst->scope, inst->scope))
                {
                    inst->data.initialize.label = appendStrings(initInst.label, dinst->scope);

                    found = 1;
                    break;
                }
            }
        }
        if (!found)
        {
            fprintf(stderr, "'%s' not declared (Instruction no: %d).\n", initInst.label, inst->lineNo);
            exit(1);
        }
    }
}

void processConditions()
{

    int conditionInstrictionCount = getArraySize(conditionArray);

    for (int i = 0; i < conditionInstrictionCount; i++)
    {
        INSTRUCTION *condInst = getElementArray(conditionArray, i);

        traverseChangeScope(condInst->data.conditionStart.condition, condInst->scope, condInst->lineNo);
    }
}

void processLoops()
{

    int loopInstructionCount = getArraySize(loopArray);

    for (int i = 0; i < loopInstructionCount; i++)
    {
        INSTRUCTION *loopInst = getElementArray(loopArray, i);

        traverseChangeScope(loopInst->data.loopStart.condition, loopInst->scope, loopInst->lineNo);
    }
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
                    pinst->data.print.postfix = inst->scope;
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
    setUniqueVar(labelsArray, getArraySize(declareArray));
    // uniqueLabel = getUniqueString(labelsArray, getArraySize(declareArray));
    //   free(labelsArray);
}

void processInstructions()
{
    generateUnique();

    processPrint();
    processInitialize();
    processConditions();
    processLoops();
    // generateUnique();

    // printf("Uniqie = %s\n", uniqueLabel);
}
