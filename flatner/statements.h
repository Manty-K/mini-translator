
#include "../data-structures/tree/tree.h"
#ifndef STATEMENTS_H
enum varType
{
    INT_TYPE,
    FLOAT_TYPE,
    BOOL_TYPE,
};
// Declare
typedef struct declareInst
{
    int varType; // enum varType
    char *identifier;
    char *scope;

} DECLARE_INST;

// Initialize
typedef struct initializeInst
{
    char *label;
    TREENODE *data;
    char *scope;
} INITIALIZE_INST;

// LOOP
typedef struct loopBlockStartInst
{
    char *blockName;
    TREENODE *condition;
    char *conditioVar;
} LOOP_BLOCK_START_INST;

typedef struct loopBlockEnd
{
    char *blockName;
} LOOP_BLOCK_END_INST;

// Condition
typedef struct conditionBlockStartInst
{
    TREENODE *condition;
    char *conditioVar;
} CONDITION_BLOCK_START_INST;

typedef struct conditionBlockEndInst
{

} CONDITION_BLOCK_END_INST;

// Print
typedef struct printInst
{

    char *data;
} PRINT_INST;

// Merging all
typedef union instructionData
{
    DECLARE_INST declare;
    INITIALIZE_INST initialize;
    LOOP_BLOCK_START_INST loopStart;
    LOOP_BLOCK_END_INST loopEnd;
    CONDITION_BLOCK_START_INST conditionStart;
    CONDITION_BLOCK_END_INST conditionBlockEnd;
    PRINT_INST print;

} INSTRUCTION_DATA;

enum instructionType
{
    DECLARE,
    INITIALIZE,
    LOOP_BLOCK_START,
    LOOP_BLOCK_END,
    CONDITION_BLOCK_START,
    CONDITION_BLOCK_END,
    PRINTS,

};

typedef struct instruction
{
    int instruction_type;
    INSTRUCTION_DATA data;
} INSTRUCTION;
void initializeStatement();
void addDeclareInstruction(int type, char *identifier);
int typeStringToint(char *str);
void displayInstructionArray();
void addInitializeInstruction(char *label, TREENODE *node);
void addLoopStartInstruction(TREENODE *node);
void addLoopEndInstruction();
void addConditionStartInstruction(TREENODE *node);
void addConditionEndInstruction();
void addPrintInstruction(char *data);

#endif
