
#ifndef STATEMENTS_H
#include "../data-structures/tree/tree.h"

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

} DECLARE_INST;

// Initialize
typedef struct initializeInst
{
    char *label;
    TREENODE *data;
} INITIALIZE_INST;

// LOOP
typedef struct loopBlockStartInst
{
    char *blockStart;
    char *blockEnd;
    TREENODE *condition;
    char *conditioVar;
} LOOP_BLOCK_START_INST;

typedef struct loopBlockEnd
{
    char *blockStart;
    char *blockEnd;
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

// Print Label
typedef struct printInst
{
    char *data;
    char *postfix;
} PRINT_INST;

// Print String
typedef struct printSInst
{
    char *data;
} PRINTS_INST;

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
    PRINTS_INST printS;

} INSTRUCTION_DATA;

enum instructionType
{
    DECLARE,
    INITIALIZE,
    LOOP_BLOCK_START,
    LOOP_BLOCK_END,
    CONDITION_BLOCK_START,
    CONDITION_BLOCK_END,
    PRINT_LABEL,
    PRINT_STR,

};

typedef struct instruction
{

    int instruction_type;
    INSTRUCTION_DATA data;
    char *scope;
    unsigned int lineNo;

} INSTRUCTION;
void initializeStatement();
void addDeclareInstruction(int type, char *identifier);
int typeStringToint(char *str);
char *typeIntToString(int type);
void displayInstructionArray();
void addInitializeInstruction(char *label, TREENODE *node);
void addLoopStartInstruction(TREENODE *node);
void addLoopEndInstruction();
void addConditionStartInstruction(TREENODE *node);
void addConditionEndInstruction();
void addPrintInstruction(char *data);
void addPrintSInstruction(char *data);

#endif
