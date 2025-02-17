#include "statements.h"
#include "block_info.h"
#include "../data-structures/array/array.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "loopCounter.h"

ARRAY *instructionArray;

ARRAY *declareArray;
ARRAY *initializeArray;
ARRAY *loopArray;
ARRAY *conditionArray;

ARRAY *printArray;

unsigned int lineNo = 0;

void initializeStatement()
{
    instructionArray = createArray(1);
    declareArray = createArray(1);
    initializeArray = createArray(1);
    loopArray = createArray(1);
    conditionArray = createArray(1);
    printArray = createArray(1);
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

    INSTRUCTION *inst = malloc(sizeof(INSTRUCTION));
    inst->instruction_type = DECLARE;
    inst->data.declare = declare;
    inst->scope = getBlockString();
    inst->lineNo = lineNo;
    lineNo++;
    appendArray(instructionArray, inst);

    // -- filling declare array separately

    INSTRUCTION *lastInst = getElementArray(instructionArray, getArraySize(instructionArray) - 1);
    appendArray(declareArray, lastInst);
}

void addInitializeInstruction(char *label, TREENODE *node)
{
    INITIALIZE_INST initialize_inst;
    initialize_inst.label = label;
    initialize_inst.data = node;

    INSTRUCTION *inst = malloc(sizeof(INSTRUCTION));
    inst->instruction_type = INITIALIZE;
    inst->data.initialize = initialize_inst;
    inst->scope = getBlockString();
    inst->lineNo = lineNo;
    lineNo++;
    appendArray(instructionArray, inst);

    // -- filling initialize array separately

    INSTRUCTION *lastInst = getElementArray(instructionArray, getArraySize(instructionArray) - 1);
    appendArray(initializeArray, lastInst);
}

void addLoopStartInstruction(TREENODE *node)
{
    incrementLoopCount();

    LOOP_BLOCK_START_INST loopBlockStartInst;
    loopBlockStartInst.blockStart = getLoopName(START);
    loopBlockStartInst.blockEnd = getLoopName(END);
    loopBlockStartInst.condition = node;

    INSTRUCTION *inst = malloc(sizeof(INSTRUCTION));
    inst->instruction_type = LOOP_BLOCK_START;
    inst->data.loopStart = loopBlockStartInst;
    inst->scope = getBlockString();
    inst->lineNo = lineNo;
    lineNo++;
    appendArray(instructionArray, inst);

    // -- filling loop array separately

    INSTRUCTION *lastInst = getElementArray(instructionArray, getArraySize(instructionArray) - 1);
    appendArray(loopArray, lastInst);
}

void addLoopEndInstruction()
{
    LOOP_BLOCK_END_INST loopBlockEnd;
    loopBlockEnd.blockStart = getLoopName(START);
    loopBlockEnd.blockEnd = getLoopName(END);

    INSTRUCTION *inst = malloc(sizeof(INSTRUCTION));
    inst->instruction_type = LOOP_BLOCK_END;
    inst->data.loopEnd = loopBlockEnd;
    inst->scope = getBlockString();
    inst->lineNo = lineNo;
    lineNo++;
    appendArray(instructionArray, inst);
    decrementLoopCount();
}

void addConditionStartInstruction(TREENODE *node)
{

    CONDITION_BLOCK_START_INST conditionBlockStartInst;
    conditionBlockStartInst.condition = node;

    INSTRUCTION *inst = malloc(sizeof(INSTRUCTION));
    inst->instruction_type = CONDITION_BLOCK_START;
    inst->data.conditionStart = conditionBlockStartInst;
    inst->scope = getBlockString();
    inst->lineNo = lineNo;
    lineNo++;
    appendArray(instructionArray, inst);

    // -- filling condition array separately

    INSTRUCTION *lastInst = getElementArray(instructionArray, getArraySize(instructionArray) - 1);
    appendArray(conditionArray, lastInst);
}

void addPrintInstruction(char *data)
{

    PRINT_INST printInst;
    printInst.data = data;

    INSTRUCTION *inst = malloc(sizeof(INSTRUCTION));
    inst->instruction_type = PRINT_LABEL;
    inst->data.print = printInst;
    inst->scope = getBlockString();
    inst->lineNo = lineNo;
    lineNo++;
    appendArray(instructionArray, inst);

    // -- filling loop array separately
    INSTRUCTION *lastInst = getElementArray(instructionArray, getArraySize(instructionArray) - 1);
    appendArray(printArray, lastInst);
}

void addPrintSInstruction(char *data)
{
    PRINTS_INST printInst;
    printInst.data = data;

    INSTRUCTION *inst = malloc(sizeof(INSTRUCTION));
    inst->instruction_type = PRINT_STR;
    inst->data.printS = printInst;
    inst->scope = getBlockString();
    inst->lineNo = lineNo;
    lineNo++;
    appendArray(instructionArray, inst);
}

void addConditionEndInstruction()
{
    CONDITION_BLOCK_END_INST conditionBlockEnd;

    INSTRUCTION *inst = malloc(sizeof(INSTRUCTION));
    inst->instruction_type = CONDITION_BLOCK_END;
    inst->data.conditionBlockEnd = conditionBlockEnd;
    inst->scope = getBlockString();
    inst->lineNo = lineNo;
    lineNo++;
    appendArray(instructionArray, inst);
}

void printChar(void *s)
{
    printf("%s\n", (char *)s);
}

void displayDeclareInsruction(DECLARE_INST instruction)
{
    printf("%s %s; \n", typeIntToString(instruction.varType), instruction.identifier);
}

void displayInitializationInsruction(INITIALIZE_INST instruction)
{

    printf("%s\n", instruction.label);
    displayTree(instruction.data, printChar);
}
void displayLoopStartInsruction(LOOP_BLOCK_START_INST instruction)
{

    printf("%s \n", instruction.blockStart);
    displayTree(instruction.condition, printChar);
}

void displayLoopEndInsruction(LOOP_BLOCK_END_INST instruction)
{
    printf("%s \n", instruction.blockStart);
}

void displayConditionStartInsruction(CONDITION_BLOCK_START_INST instruction)
{
    printf("if\n");
    displayTree(instruction.condition, printChar);
}

void displayConditionEndInsruction(CONDITION_BLOCK_END_INST instruction)
{
    printf("end if\n");
}

void displayPrintInsruction(PRINT_INST instruction)
{
    printf("print %s\n", instruction.data);
}

void displayInstruction(INSTRUCTION *inst)
{

    printf("Line : %u - SCOPE :%s\n", inst->lineNo, inst->scope);
    switch (inst->instruction_type)
    {
    case DECLARE:
        displayDeclareInsruction(inst->data.declare);
        break;

    case INITIALIZE:
        displayInitializationInsruction(inst->data.initialize);
        break;
    case LOOP_BLOCK_START:
        displayLoopStartInsruction(inst->data.loopStart);
        break;
    case LOOP_BLOCK_END:
        displayLoopEndInsruction(inst->data.loopEnd);
        break;
    case CONDITION_BLOCK_START:
        displayConditionStartInsruction(inst->data.conditionStart);
        break;
    case CONDITION_BLOCK_END:
        displayConditionEndInsruction(inst->data.conditionBlockEnd);
        break;
    case PRINT_LABEL:
        displayPrintInsruction(inst->data.print);
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
