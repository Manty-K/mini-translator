#include <stdio.h>
#include <stdarg.h>
#include "output.h"

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

int appendFile(const char *format, ...)
{

    if (fp == NULL)
    {
        fprintf(stderr, "File not initialized!\n");
        return -1;
    }

    va_list args;
    va_start(args, format);
    int result = vfprintf(fp, format, args); // Use vfprintf instead of fprintf
    va_end(args);

    return result;
}

void closeOutfile()
{
    fclose(fp);
}