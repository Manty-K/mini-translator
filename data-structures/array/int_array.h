#ifndef ARRAY_H
typedef struct
{

    int *ptr;
    int cap;
    int filled;

} INTARRAY;

INTARRAY *createIntArray(int);

void appendIntArray(INTARRAY *, int);

int getIntElementArray(INTARRAY *, int);
void getIntArrayStatus(INTARRAY *array);

void setIntElementArray(INTARRAY *, int, int);

int popIntElementArray(INTARRAY *);

char isEmptyIntArray(INTARRAY *array);
void freeIntArray(INTARRAY *array, void (*free_func)(void *));
int getArraySize(INTARRAY *array);
#endif
