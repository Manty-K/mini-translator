#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *ptr;
    int cap;
    int filled;
} INTARRAY;

INTARRAY *createIntArray(int capacity)
{
    if (capacity <= 0)
    {
        fprintf(stderr, "Invalid capacity: %d\n", capacity);
        return NULL;
    }

    INTARRAY *arr = malloc(sizeof(INTARRAY));
    if (arr == NULL)
    {
        perror("malloc failed");
        return NULL;
    }

    arr->cap = capacity;
    arr->filled = 0;
    arr->ptr = malloc(sizeof(int) * arr->cap);
    if (arr->ptr == NULL)
    {
        perror("malloc failed");
        free(arr);
        return NULL;
    }

    return arr;
}

char isEmptyIntArray(INTARRAY *array)
{
    return array == NULL || array->filled == 0;
}

void getIntArrayStatus(INTARRAY *array)
{
    if (array == NULL)
    {
        fprintf(stderr, "Array is NULL\n");
        return;
    }
    printf("Filled: %d, Cap: %d\n", array->filled, array->cap);
}

void appendIntArray(INTARRAY *array, int data)
{
    if (array == NULL)
        return;

    if (array->filled == array->cap)
    {
        int newCap = array->cap * 2;
        if (newCap < array->cap) // Prevent integer overflow
        {
            fprintf(stderr, "Array capacity overflow.\n");
            return;
        }

        int *newPtr = realloc(array->ptr, sizeof(int) * newCap);
        if (newPtr == NULL)
        {
            fprintf(stderr, "realloc failed!\n");
            return;
        }

        array->ptr = newPtr;
        array->cap = newCap;
    }

    array->ptr[array->filled++] = data;
}

int getIntElementArray(INTARRAY *array, int index)
{
    if (array == NULL || index >= array->filled || index < 0)
    {
        fprintf(stderr, "Index %d out of bounds. Filled: %d, Cap: %d\n",
                index, array ? array->filled : -1, array ? array->cap : -1);
        return -1; // Return an error value
    }
    return array->ptr[index];
}

void setIntElementArray(INTARRAY *array, int index, int data)
{
    if (array == NULL || index >= array->filled) // Fix: Only allow setting within `filled` range
    {
        fprintf(stderr, "Cannot set out of filled range. Index: %d, Filled: %d\n", index, array->filled);
        return;
    }
    array->ptr[index] = data;
}

int popIntElementArray(INTARRAY *array)
{
    if (array == NULL || isEmptyIntArray(array))
    {
        fprintf(stderr, "Array empty, cannot pop.\n");
        return -1;
    }

    int poppedValue = array->ptr[array->filled - 1];
    array->ptr[array->filled - 1] = 0;
    array->filled--;

    return poppedValue;
}

void freeIntArray(INTARRAY *array)
{
    if (array == NULL)
        return;
    free(array->ptr);
    free(array);
}

int getArraySize(INTARRAY *array)
{

    return array->filled;
}
