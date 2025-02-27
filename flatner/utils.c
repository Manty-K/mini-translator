#include "utils.h"
#include <ctype.h>
#include <string.h>
int getIntLength(unsigned int val)
{
    if (val == 0)
        return 1;

    int length = 0;
    int v = val;

    while (v > 0)
    {
        v /= 10;
        length++;
    }
    return length;
}

char isOperator(char *data)
{
    char *operators[] = {"+", "-", "*", "/", "<", ">", "<=", ">=", "==", "!=", "&&", "||", "~"};
    int operatorsLength = sizeof(operators) / sizeof(operators[0]);

    for (int i = 0; i < operatorsLength; i++)
    {
        if (!strcmp(data, operators[i]))
        {
            return 1;
        }
    }
    return 0;
}

char isLabel(char *data)
{

    return isalpha(data[0]) ? 1 : 0;
}