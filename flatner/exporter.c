
#include "exporter.h"
#include "statements.h"
#include <stdio.h>
#include "../data-structures/array/array.h"
#include "output.h"
#include <stdlib.h>

void setUniqueVar(char **list, int count);
void generateTACFromTree(char *indentifier, TREENODE *node);
void displayTacQueue();
char *getTempVarName();
// #include "tac.h"
extern ARRAY *instructionArray;

void exportDeclareInsruction(INSTRUCTION *instruction)
{
    appendFile("%s %s%s;\n", typeIntToString(instruction->data.declare.varType), instruction->data.declare.identifier, instruction->scope);
}

void exportInitializationInsruction(INSTRUCTION *instruction)
{
    generateTACFromTree(instruction->data.initialize.label, instruction->data.initialize.data);
    displayTacQueue();
}

void exportLoopStartInsruction(LOOP_BLOCK_START_INST instruction)
{

    // printf("%s \n", instruction.blockName);
    // exportTree(instruction.condition, printChar);
}

void exportLoopEndInsruction(LOOP_BLOCK_END_INST instruction)
{
    // printf("%s \n", instruction.blockName);
}

void exportConditionStartInsruction(INSTRUCTION *instruction)
{
    instruction->data.conditionStart.conditioVar = getTempVarName();
    generateTACFromTree(instruction->data.conditionStart.conditioVar, instruction->data.conditionStart.condition);
    displayTacQueue();
    appendFile("if(%s){\n", instruction->data.conditionStart.conditioVar);
    // exportTree(instruction.condition, printChar);
}

void exportConditionEndInsruction(INSTRUCTION *instruction)
{
    appendFile("}\n");
}

void exportPrintInsruction(PRINT_INST instruction)
{
    appendFile("printf(\"%%d\",%s%s);\n", instruction.data, instruction.postfix);
}

void exportInstruction(INSTRUCTION *inst)
{
    switch (inst->instruction_type)
    {
    case DECLARE:
        exportDeclareInsruction(inst);
        break;
    case INITIALIZE:
        exportInitializationInsruction(inst);
        break;
    case LOOP_BLOCK_START:
        exportLoopStartInsruction(inst->data.loopStart);
        break;
    case LOOP_BLOCK_END:
        exportLoopEndInsruction(inst->data.loopEnd);
        break;
    case CONDITION_BLOCK_START:
        exportConditionStartInsruction(inst);
        break;
    case CONDITION_BLOCK_END:
        exportConditionEndInsruction(inst);
        break;
    case PRINTS:
        exportPrintInsruction(inst->data.print);
        break;
    default:
        fprintf(stderr, "Invalid Type %d\n", inst->instruction_type);
        exit(1);
        break;
    }
}

void exportFile()
{
    for (int i = 0; i < instructionArray->filled; i++)
    {
        INSTRUCTION *inst = getElementArray(instructionArray, i);
        exportInstruction(inst);
    }
}