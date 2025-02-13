#include "flatner.h"

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
    block.no = 0;
    block.depth = 0;
}

void getBlockStatus()
{

    fprintf(fp, "No: %d, Dept : %d\n", block.no, block.depth);
}

void printStatement()
{
    getBlockStatus();
}

void bodyStart()
{
    fprintf(fp, "Body Start\n");
}

void bodyEnd()
{
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
