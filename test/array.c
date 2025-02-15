#include <stdio.h>
#include "../data-structures/array/array.h"
int main()
{

    ARRAY *array = createArray(1);

    int s1 = 40;
    int s2 = 50;
    int s3 = 60;
    int s4 = 70;

    appendArray(array, &s1);
    appendArray(array, &s2);
    // getArrayStatus(array);
    popElementArray(array);
    appendArray(array, &s3);
    // getArrayStatus(array);

    appendArray(array, &s1);
    appendArray(array, &s2);
    // getArrayStatus(array);

    // setElementArray(array, 0, s1);
    // setElementArray(array, 1, s2);
    // setElementArray(array, 2, s3);
    // setElementArray(array, 3, s1);
    // setElementArray(array, 4, s2);
    // setElementArray(array, 5, s3);
    // appendArray(array, s4);

    for (int i = 0; i < 2; i++)
    {
        printf("%d\n", *(int *)getElementArray(array, i));
    }
}