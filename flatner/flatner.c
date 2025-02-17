#include "flatner.h"
// #include "../data-structures/array/array.h"
#include "block_info.h"
#include <stdlib.h>
#include "output.h"
#include "instructions_processing.h"
#include "exporter.h"

typedef struct
{
    int no;
    int depth;
} BLOCK;

BLOCK block;
void initializeExtraVariableQueue();

void programStart()
{
    openOutfile();
    initializeBlockInfo();
    initializeStatement();
    initializeLoopStack();
    initializeExtraVariableQueue();
}

void bodyStart()
{

    blockOpen();
}

void bodyEnd()
{
    blockClosed();
}

void programEnd()
{
    // displayInstructionArray();
    processInstructions();

    exportFile();

    closeOutfile();
}
