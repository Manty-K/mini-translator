#include "statements.h"
#include "block_info.h"
#include "../data-structures/array/array.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

ARRAY *instructionArray;

ARRAY *declareArray;
ARRAY *initializeArray;

void initializeStatement()
{

    instructionArray = createArray(1);

    declareArray = createArray(1);

    initializeArray = createArray(1);
}

int typeStringToint(char *str)
{
    int type;
    if (!strcmp(str, "int"))
    {
        type = INT_TYPE;
    }
    else if (!strcmp(str, "float"))
    {
        type = FLOAT_TYPE;
    }
    else if (!strcmp(str, "bool"))
    {
        type = BOOL_TYPE;
    }
    else
    {
        fprintf(stderr, "Type %s not defined\n", str);
        exit(1);
    }

    return type;
}

char *typeIntToString(int type)
{
    switch (type)
    {
    case INT_TYPE:
        return "int";

    case FLOAT_TYPE:
        return "float";

    case BOOL_TYPE:
        return "bool";

    default:
        fprintf(stderr, "Type %d not defined\n", type);
        exit(1);
    }
}

void addDeclareInstruction(int type, char *identifier)
{
    DECLARE_INST declare;
    declare.identifier = identifier;
    declare.varType = type;
    declare.scope = getBlockString();

    INSTRUCTION *inst = malloc(sizeof(INSTRUCTION));
    inst->instruction_type = DECLARE;
    inst->data.declare = declare;
    appendArray(instructionArray, inst);

    // -- filling declare array separately

    INSTRUCTION *lastInst = getElementArray(instructionArray, getArraySize(instructionArray) - 1);
    appendArray(declareArray, &(lastInst->data.declare));
}

void addInitializeInstruction(char *label, TREENODE *node)
{
    INITIALIZE_INST initialize_inst;
    initialize_inst.label = label;
    initialize_inst.data = node;
    initialize_inst.scope = getBlockString();

    INSTRUCTION *inst = malloc(sizeof(INSTRUCTION));
    inst->instruction_type = INITIALIZE;
    inst->data.initialize = initialize_inst;
    appendArray(instructionArray, inst);

    // -- filling initialize array separately

    INSTRUCTION *lastInst = getElementArray(instructionArray, getArraySize(instructionArray) - 1);
    appendArray(initializeArray, &(lastInst->data.initialize));
}
void printChar(void *s)
{
    printf("%s\n", (char *)s);
}

void displayDeclateInsruction(DECLARE_INST instruction)
{
    printf("%s %s; // %s\n", typeIntToString(instruction.varType), instruction.identifier, instruction.scope);
}

void displayInitializationInsruction(INITIALIZE_INST instruction)
{

    printf("%s // %s\n", instruction.label, instruction.scope);
    displayTree(instruction.data, printChar);
}

void displayInstruction(INSTRUCTION *inst)
{
    switch (inst->instruction_type)
    {
    case DECLARE:
        displayDeclateInsruction(inst->data.declare);
        break;

    case INITIALIZE:
        displayInitializationInsruction(inst->data.initialize);
        break;

    default:
        fprintf(stderr, "Invalid Type %d\n", inst->instruction_type);
        exit(1);
        break;
    }
}

void displayInstructionArray()
{
    for (int i = 0; i < instructionArray->filled; i++)
    {
        INSTRUCTION *inst = getElementArray(instructionArray, i);
        displayInstruction(inst);
    }

    // for (int i = 0; i < initializeArray->filled; i++)
    // {
    //     INITIALIZE_INST *inst = getElementArray(initializeArray, i);
    //     displayInitializationInsruction(*inst);
    // }
}
