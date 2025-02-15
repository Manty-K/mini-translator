#include "../data-structures/array/int_array.h"

#include "block_info.h"

INTARRAY *indentArray;
int indentDept = 0;

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
    getBlockStatus();
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

char *getBlockString()
{
}
