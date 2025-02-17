/*Program Start*/

#include <stdio.h>

int main(int argc, char const *argv[])
{
	/*Program Start*/
	int i;
	i = 10;
lsrt0:
	int a1;
	a1 = i > 0;
	if (!a1)
		goto lstp0;
	printf("%d", i);
	i = i - 1;
	goto lsrt0;
lstp0:
	/*Program End*/

	return 0;
}
