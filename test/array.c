#include <stdio.h>
#include "../data-structures/array/int_array.h"
int main()
{

    INTARRAY *array = createIntArray(1);

    int s1 = 40;
    int s2 = 50;
    int s3 = 60;
    int s4 = 70;

    appendIntArray(array, s1);
    appendIntArray(array, s2);
    getIntArrayStatus(array);
    popIntElementArray(array);
    appendIntArray(array, s3);
    getIntArrayStatus(array);

    appendIntArray(array, s1);
    appendIntArray(array, s2);
    getIntArrayStatus(array);

    // setElementArray(array, 0, s1);
    // setElementArray(array, 1, s2);
    // setElementArray(array, 2, s3);
    // setElementArray(array, 3, s1);
    // setElementArray(array, 4, s2);
    // setElementArray(array, 5, s3);
    // appendArray(array, s4);

    for (int i = 0; i < 2; i++)
    {

        printf("%d\n", getIntElementArray(array, i));
    }
}