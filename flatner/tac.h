#ifndef TAC_H
#include "../data-structures/tree/tree.h"

typedef struct tac0
{
    char *result;
    char *identifier;

} TAC0;
typedef struct tac1
{
    char *result;
    char *identifier;
    char *op;

} TAC1;
typedef struct tac2
{
    char *result;
    char *firstIdentifier;
    char *secondIdentifier;
    char *op;

} TAC2;

typedef union tac
{
    TAC0 tac0;
    TAC1 tac1;
    TAC2 tac2;
} TAC;

enum tackType
{
    ZERO_OP,
    ONE_OP,
    TWO_OP,
};

typedef struct tacval
{
    int tacType;
    TAC *tac;
} TACVAL;

void setUniqueVar(char **list, int count);
void generateTACFromTree(char *indentifier, TREENODE *node);
void displayTacQueue();

#endif