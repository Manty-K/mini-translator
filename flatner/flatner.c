#include "flatner.h"
// #include "../data-structures/array/array.h"
#include "block_info.h"
#include <stdlib.h>
#include "output.h"

typedef struct
{
    int no;
    int depth;
} BLOCK;

BLOCK block;

void programStart()
{
    openOutfile();
    appendFile("/*Program Start*/\n");
    initializeBlockInfo();
}

void bodyStart()
{

    appendFile("/*Body Start*/\n");

    blockOpen();
}

void bodyEnd()
{
    blockClosed();

    appendFile("/*Body End*/\n");
}

void programEnd()
{
    appendFile("/*Program End*/\n");
    closeOutfile();
}
