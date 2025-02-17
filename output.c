#include<stdio.h>
 int main(){
int i;
int j;
i = 3;
lsrt0:
int a1;
a1 = i > 0;
if(!a1)
	goto lstp0;
j = 2;
goto lsrt0;
lstp0:
printf("Srushti Yedi\n");
lsrt1:
int a2;
a2 = i > 0;
if(!a2)
	goto lstp1;
j = 5;
lsrt1:
int a3;
a3 = i > 0;
if(!a3)
	goto lstp1;
j = 2;
goto lsrt1;
lstp1:
j = 4;
goto lsrt2;
lstp2:
return 0;
 }