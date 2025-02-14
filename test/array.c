#include <stdio.h>
#include "../data-structures/array/array.h"
int main()
{

    ARRAY *array = createArray(1);

    char *s1 = " Hello";

    char *s2 = " Worht";
    char *s3 = " manthan";
    char *s4 = "appended";

    appendArray(array, s1);
    appendArray(array, s2);
    popElementArray(array);
    appendArray(array, s3);

    // setElementArray(array, 0, s1);
    // setElementArray(array, 1, s2);
    // setElementArray(array, 2, s3);
    // setElementArray(array, 3, s1);
    // setElementArray(array, 4, s2);
    // setElementArray(array, 5, s3);
    // appendArray(array, s4);

    for (int i = 0; i < 2; i++)
    {

        printf("%s\n", (char *)getElementArray(array, i));
    }
}