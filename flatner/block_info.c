#include <stdlib.h>
#include <stdio.h>

#include "../data-structures/array/int_array.h"

#include "block_info.h"

INTARRAY *indentArray;
int indentDept = 0;

int getIntLength(int num)
{
    if (num == 0)
        return 1;

    int length = 0;
    while (num)
    {
        num /= 10;
        length++;
    }
    return length;
}

void initializeBlockInfo()
{
    indentArray = createIntArray(1);
}

void getBlockStatus()
{
    for (int i = 0; i < getArraySize(indentArray); i++)
    {

        printf("%d ", getIntElementArray(indentArray, i));
    }

    printf("\n");
}

void blockOpen()
{
    if (getArraySize(indentArray) <= indentDept)
    {
        appendIntArray(indentArray, 1);
    }

    indentDept++;

    printf("%s\n", getBlockString());
}

void blockClosed()
{
    indentDept--;

    setIntElementArray(indentArray, indentDept, getIntElementArray(indentArray, indentDept) + 1);

    while (getArraySize(indentArray) > indentDept + 1)
    {
        popIntElementArray(indentArray);
    }
}

int totalLengthIndentArray()
{

    int total = 0;

    for (int i = 0; i < getArraySize(indentArray); i++)
    {
        total += getIntLength(getIntElementArray(indentArray, i));
    }

    total += getArraySize(indentArray) - 1; // for dots
    return total;
}

char *getBlockString()
{
    char *output = (char *)malloc(totalLengthIndentArray());

    int offset = 0;

    for (int i = 0; i < getArraySize(indentArray); i++)
    {
        offset += sprintf(output + offset, "%d%s", getIntElementArray(indentArray, i), (i < getArraySize(indentArray) - 1) ? "." : "");
    }

    return output;
}
int compareVersions(const char *v1, const char *v2)
{
    char *ver1 = strdup(v1);
    char *ver2 = strdup(v2);

    char *token1 = strtok(ver1, ".");
    char *token2 = strtok(ver2, ".");

    while (token1 != NULL || token2 != NULL)
    {
        int num1 = token1 ? atoi(token1) : 0;
        int num2 = token2 ? atoi(token2) : 0;

        if (num1 > num2)
        {
            free(ver1);
            free(ver2);
            return 1;
        }
        else if (num1 < num2)
        {
            free(ver1);
            free(ver2);
            return -1;
        }

        token1 = strtok(NULL, ".");
        token2 = strtok(NULL, ".");
    }

    free(ver1);
    free(ver2);
    return 0;
}