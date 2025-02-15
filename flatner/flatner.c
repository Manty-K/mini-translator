#include "flatner.h"
// #include "../data-structures/array/array.h"
#include "block_info.h"
#include <stdlib.h>

typedef struct
{
    int no;
    int depth;
} BLOCK;

BLOCK block;

char *outputFileName = NULL;
FILE *fp;

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
    initializeBlockInfo();
}

void printStatement()
{
}

void bodyStart()
{

    fprintf(fp, "Body Start\n");

    blockOpen();
}

void bodyEnd()
{
    blockClosed();

    fprintf(fp, "Body End\n");
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
