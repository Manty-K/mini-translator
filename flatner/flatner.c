#include "flatner.h"
// #include "../data-structures/array/array.h"
#include "../data-structures/array/int_array.h"
#include <stdlib.h>

typedef struct
{
    int no;
    int depth;
} BLOCK;

BLOCK block;

char *outputFileName = NULL;
FILE *fp;

INTARRAY *indentArray;
int indentDept = 0;

void openOutfile()
{
    fp = fopen(outputFileName, "w");

    if (fp == NULL)
    {
        fprintf(stderr, "File Open Error");
    }
}

void programStart()
{
    openOutfile();
    fprintf(fp, "Program Start\n");

    indentArray = createIntArray(1);

    puts("Started");
}

void getBlockStatus()
{
    for (int i = 0; i < getArraySize(indentArray); i++)
    {

        fprintf(fp, "%d ", getIntElementArray(indentArray, i));
    }

    fprintf(fp, "\n");
}

void printStatement()
{
    // temporary
    // getBlockStatus();
}

void bodyStart()
{

    fprintf(fp, "Body Start\n");

    if (getArraySize(indentArray) <= indentDept)
    {
        appendIntArray(indentArray, 1);
    }

    indentDept++;
    getBlockStatus();
}

void bodyEnd()
{

    fprintf(fp, "Body End\n");
    indentDept--;

    setIntElementArray(indentArray, indentDept, getIntElementArray(indentArray, indentDept) + 1);

    while (getArraySize(indentArray) > indentDept + 1)
    {
        popIntElementArray(indentArray);
    }
}

void closeOutfile()
{
    fclose(fp);
}

void programEnd()
{
    fprintf(fp, "Program End\n");
    closeOutfile();
}
