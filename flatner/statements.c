#include "statements.h"
#include "block_info.h"
#include "../data-structures/array/array.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

ARRAY *instructionArray;

ARRAY *declareArray;

void initializeStatement()
{

    instructionArray = createArray(1);

    declareArray = createArray(1);
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

void displayDeclateInsruction(DECLARE_INST instruction)
{

    printf("%s %s; // %s\n", typeIntToString(instruction.varType), instruction.identifier, instruction.scope);
}

void displayInstruction(INSTRUCTION *inst)
{
    switch (inst->instruction_type)
    {
    case DECLARE:
        displayDeclateInsruction(inst->data.declare);
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
}
