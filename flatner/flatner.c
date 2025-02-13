#include "flatner.h"
#include <stdio.h>

FILE *fp; // Output File

int blockNo = 0;

int blockDepth = 0;

void openOutfile(char *filename)
{

    fp = fopen(filename, "w");
}

void programStart()
{
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

void programEnd()
{
    fprintf(fp, "Program End\n");
}

void closeOutfile()
{

    fclose(fp);
}
