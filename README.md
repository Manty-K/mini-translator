# Simple Language Translator

This program translate *C like code* to **C code** without loops.

## Input
```
int N;
int k;
int fact;
int factNum;

N = 10;
factNum = 1;

while (factNum <= N) {
    fact = 1;
    k = 1;

    while (k <= factNum) {
        fact = fact * k;
        k = k + 1;
    }

    print("Factorial of ", factNum, " is: ", fact, "\n");
    factNum = factNum + 1;
}
```

## Output
```c
#include <stdio.h>
int main()
{
	int N;
	int k;
	int fact;
	int factNum;
	N = 10;
	factNum = 1;
lsrt0:
	int a1;
	a1 = factNum <= N;
	if (!a1)
		goto lstp0;
	fact = 1;
	k = 1;
lsrt1:
	int a2;
	a2 = k <= factNum;
	if (!a2)
		goto lstp1;
	fact = fact * k;
	k = k + 1;
	goto lsrt1;
lstp1:
	printf("Factorial of ");
	printf("%d", factNum);
	printf(" is: ");
	printf("%d", fact);
	printf("\n");
	factNum = factNum + 1;
	goto lsrt0;
lstp0:
	return 0;
}
```