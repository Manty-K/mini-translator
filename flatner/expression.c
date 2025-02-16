
#include "../data-structures/stack/stack.h"
// #include "../data-structures/tree/tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "expression.h"
#include "statements.h"

STACK *expstack;
TREENODE *currentTree;

char *identifier;

void setIndentifier(char *str)
{

    identifier = str;
}

unsigned int _getChildCountFromData(char *data)
{
    if (isalnum(data[0]))
    {
        return 0;
    }

    if (!strcmp(data, "~"))
    {
        return 1;
    }

    if (!strcmp(data, "=") || !strcmp(data, "+") || !strcmp(data, "-") || !strcmp(data, "*") || !strcmp(data, "/") || !strcmp(data, "<") || !strcmp(data, ">") || !strcmp(data, "<=") || !strcmp(data, ">=") || !strcmp(data, "==") || !strcmp(data, "&&") || !strcmp(data, "||"))
    {
        return 2;
    }

    fprintf(stderr, "Count for symbol %s not defined\n", data);
    return 0;
}

void expressionStart()
{
    expstack = createStack();
}

void pushExpTree(char *data)
{
    unsigned int childCount = _getChildCountFromData(data);
    currentTree = createTreeNode(strdup(data), childCount);
    for (int i = 0; i < childCount; i++)
    {
        currentTree->children[childCount - i - 1] = (TREENODE *)popStack(expstack);
    }
    pushStack(expstack, currentTree);
}

void expressionEnd(int type)
{

    switch (type)
    {
    case INITIALIZE:
        addInitializeInstruction(identifier, currentTree);
        break;
    case LOOP_BLOCK_START:
        addLoopStartInstruction(currentTree);
        break;

    default:
        break;
    }

    freeStack(expstack);
}
