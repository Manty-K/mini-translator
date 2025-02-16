#include <stdio.h>

int main()
{
    int a;

    int b;

    a = 0;

    int c1;

    c1 = 4 * 2;

    b = 2 + c1;

lsrt1:
    int c2;
    c2 = a < 2;
    if (!c2)
        goto lstp1;

    a = a + 1;

    int b_1;

    b_1 = 3;

lsrt2:
    int c4;
    c4 = b_1 > 0;
    if (!c4)
        goto lstp2;
    printf("j: %d\n", b_1);
    b_1--;
    goto lsrt2;
lstp2:

    goto lsrt1;

lstp1:
    int boom;
    int c3;
    c3 = 6 * 4;

    boom = 5 + c3;

    printf("a:%d\n", a);
    printf("b:%d\n", b);
}
