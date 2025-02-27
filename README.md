# Simple Language Translator

This program translate *C like code* to **C code** without loops.

## Input
```
int a;
int b;
int fibCount;
int temp;
int N;
N = 20;

a = 0;
b = 1;
fibCount = 1;

print("Fibonacci sequence up to ", N, " terms: ");
    
while (fibCount <= N) {
    print(a, " ");
    temp = a + b;
    a = b;
    b = temp;
    fibCount = fibCount + 1;
}

print("\n");
```

## Ouptput
```c
#include <stdio.h>
int main()
{
	int a;
	int b;
	int fibCount;
	int temp;
	int N;
	N = 20;
	a = 0;
	b = 1;
	fibCount = 1;
	printf("Fibonacci sequence up to ");
	printf("%d", N);
	printf(" terms: ");
lsrt0:
	int a1;
	a1 = fibCount <= N;
	if (!a1)
		goto lstp0;
	printf("%d", a);
	printf(" ");
	temp = a + b;
	a = b;
	b = temp;
	fibCount = fibCount + 1;
	goto lsrt0;
lstp0:
	printf("\n");
	return 0;
}

```