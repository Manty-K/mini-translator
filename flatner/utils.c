#include "utils.h"
int getIntLength(int num)
{
    if (num == 0)
        return 1;

    int length = 0;
    while (num)
    {
        num /= 10;
        length++;
    }
    return length;
}