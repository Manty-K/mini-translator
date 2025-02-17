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
	int b1;
	b1 = 3;
lsrt2:
	int c3;
	c3 = b1 > 0;
	if (!c3)
		goto lstp2;
	printf("j: ");
	printf("%d", b1);
	printf("\n");
	b1 = b1 - 1;
	goto lsrt2;
lstp2:
	goto lsrt1;
lstp1:
	int boom;
	int c4;
	c4 = 6 * 4;
	boom = 5 + c4;
	printf("a: ");
	printf("%d", a);
	printf("\n");
	printf("b: ");
	printf("%d", b);
	printf("\n");
	return 0;
}