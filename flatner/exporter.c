
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

void exportLoopStartInsruction(INSTRUCTION *instruction)
{

    instruction->data.loopStart.conditioVar = getTempVarName();
    generateTACFromTree(instruction->data.loopStart.conditioVar, instruction->data.loopStart.condition);
    appendFile("%s:\n", instruction->data.loopStart.blockStart);
    displayTacQueue();
    appendFile("if(!%s)\n", instruction->data.loopStart.conditioVar);
    appendFile("\tgoto %s;\n", instruction->data.loopStart.blockEnd);
}

void exportLoopEndInsruction(INSTRUCTION *instruction)
{
    // printf("%s \n", instruction.blockName);
    appendFile("goto %s;\n", instruction->data.loopEnd.blockStart);
    appendFile("%s:\n", instruction->data.loopEnd.blockEnd);
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
void exportPrintSInsruction(PRINTS_INST instruction)
{
    appendFile("printf(\"%s\");\n", instruction.data);
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
        exportLoopStartInsruction(inst);
        break;
    case LOOP_BLOCK_END:
        exportLoopEndInsruction(inst);
        break;
    case CONDITION_BLOCK_START:
        exportConditionStartInsruction(inst);
        break;
    case CONDITION_BLOCK_END:
        exportConditionEndInsruction(inst);
        break;
    case PRINT_LABEL:
        exportPrintInsruction(inst->data.print);
        break;
    case PRINT_STR:
        exportPrintSInsruction(inst->data.printS);
        break;
    default:
        fprintf(stderr, "Invalid Type %d\n", inst->instruction_type);
        exit(1);
        break;
    }
}

void exportStartContent()
{

    appendFile("#include<stdio.h>\n int main(){\n");
}

void exportEndContent()
{

    appendFile("return 0;\n }");
}

void exportFile()
{
    // exportStartContent();
    for (int i = 0; i < instructionArray->filled; i++)
    {
        INSTRUCTION *inst = getElementArray(instructionArray, i);
        exportInstruction(inst);
    }
    // exportEndContent();
}
