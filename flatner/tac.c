#include "../data-structures/queue/queue.h"
#include "tac.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "output.h"
QUEUE *tacQueue;

char *uniqueVar;

int variableName = 1;

int isPresent(char *str, char **list, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!strcmp(str, list[i]))
        {
            return 1;
        }
    }
    return 0;
}

char *generateNext(char *s)
{
    int len = strlen(s);
    char last = s[len - 1];
    char *newStr;

    if (last == 'z')
    {
        newStr = malloc(len + 2);
        strcpy(newStr, s);
        newStr[len - 1] = '_';
        newStr[len] = 'a';
        newStr[len + 1] = '\0';
    }
    else
    {
        newStr = malloc(len + 1);
        strcpy(newStr, s);
        newStr[len - 1]++;
    }

    return newStr;
}

char *getUniqueString(char **list, int count)
{
    char *smallest = "a";

    while (isPresent(smallest, list, count))
    {
        smallest = generateNext(smallest);
    }

    return smallest;
}

void setUniqueVar(char **list, int count)
{
    uniqueVar = getUniqueString(list, count);
}

char *getTempVarName()
{
    char *varName = malloc(getIntLength(variableName) + 2);
    sprintf(varName, "%s%d", uniqueVar, variableName);
    variableName++;
    return varName;
}

void traverseGenerate(TREENODE *node, char *result)
{
    if (node == NULL)
    {
        return;
    }
    TACVAL *tacval = malloc(sizeof(TACVAL));
    tacval->tac = malloc(sizeof(TAC));

    if (node->childCount == 0)
    {
        TAC0 tac;
        tac.result = result;
        tac.identifier = node->data;

        tacval->tac->tac0 = tac;
        tacval->tacType = ZERO_OP;
    }

    if (node->childCount == 1)
    {
        char *nm = node->children[0]->data;

        if (isOperator(node->children[0]->data))
        {
            nm = getTempVarName();
            traverseGenerate(node->children[0], nm);
        }

        TAC1 tac;
        tac.result = result;
        tac.identifier = nm;
        tac.op = node->data;

        tacval->tac->tac1 = tac;
        tacval->tacType = ONE_OP;
    }

    if (node->childCount == 2)
    {

        char *nm1 = node->children[0]->data;
        char *nm2 = node->children[1]->data;

        if (isOperator(node->children[0]->data))
        {
            nm1 = getTempVarName();
            traverseGenerate(node->children[0], nm1);
        }
        if (isOperator(node->children[1]->data))
        {
            nm2 = getTempVarName();
            traverseGenerate(node->children[1], nm2);
        }

        TAC2 tac;
        tac.result = result;
        tac.firstIdentifier = nm1;
        tac.secondIdentifier = nm2;
        tac.op = node->data;

        tacval->tac->tac2 = tac;
        tacval->tacType = TWO_OP;
    }

    enqueue(tacQueue, tacval);
    tacQueue;
}

void generateTACFromTree(char *indentifier, TREENODE *node)
{
    freeQueue(tacQueue);
    tacQueue = createQueue();
    traverseGenerate(node, indentifier);
}

void displayTacQueue()
{

    while (!isEmptyQueue(tacQueue))
    {
        TACVAL *tacVal = dequeue(tacQueue);

        if (tacVal->tacType == ZERO_OP)
        {

            appendFile("%s = %s\n", tacVal->tac->tac0.result, tacVal->tac->tac0.identifier);
        }
        if (tacVal->tacType == ONE_OP)
        {

            appendFile("%s = %s%s\n", tacVal->tac->tac1.result, tacVal->tac->tac1.op, tacVal->tac->tac1.identifier);
        }
        if (tacVal->tacType == TWO_OP)
        {

            appendFile("%s = %s %s %s\n", tacVal->tac->tac2.result, tacVal->tac->tac2.firstIdentifier, tacVal->tac->tac2.op, tacVal->tac->tac2.secondIdentifier);
        }
    }
}