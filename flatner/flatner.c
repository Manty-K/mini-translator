#include "flatner.h"

int blockNo = 0;

int blockDepth = 0;

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
