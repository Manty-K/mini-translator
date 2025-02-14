#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    void **ptr;
    int cap;
    int filled;
} ARRAY;

ARRAY *createArray(int capacity)
{
    ARRAY *arr = malloc(sizeof(ARRAY));
    if (arr == NULL)
    {
        perror("malloc failed");
        return NULL;
    }
    arr->cap = capacity;
    arr->filled = 0;
    arr->ptr = malloc(sizeof(void *) * arr->cap);
    if (arr->ptr == NULL)
    {
        perror("malloc failed");
        free(arr);
        return NULL;
    }
    return arr;
}
char isEmptyArray(ARRAY *array)
{
    return array == NULL || array->filled == 0;
}

void *getNewArrayPtr(size_t newSize)
{
    void *newPtr = malloc(sizeof(void *) * newSize);
    if (newPtr == NULL)
    {
        perror("malloc failed");
        return NULL;
    }
    return newPtr;
}

void appendArray(ARRAY *array, void *data)
{
    if (array == NULL)
        return;

    if (array->filled == array->cap)
    {
        void *newPtr = realloc(array->ptr, sizeof(void *) * array->cap * 2);
        if (newPtr == NULL)
        {
            fprintf(stderr, "realloc failed!\n");
            return;
            array->ptr = newPtr;
            array->cap *= 2;
        }
        array->ptr[array->filled++] = data;
    }
}

void *getElementArray(ARRAY *array, int index)
{
    if (array == NULL || index >= array->filled)
    {
        fprintf(stderr, "Invalid array or index out of bounds.\n");
        return NULL;
    }
    return array->ptr[index];
}

void setElementArray(ARRAY *array, int index, void *data)
{
    if (array == NULL || index >= array->cap)
    {
        fprintf(stderr, "Cannot set out of capacity\n");
        return;
    }

    array->ptr[index] = data;
}

void *popElementArray(ARRAY *array)
{
    if (array == NULL || isEmptyArray(array))
    {
        fprintf(stderr, "Array empty cannot pop.\n");
        return NULL;
    }
    return array->ptr[--array->filled];
}

void freeArray(ARRAY *array, void (*free_func)(void *))
{
    if (array == NULL)
        return;
    if (free_func != NULL)
    {
        for (int i = 0; i < array->filled; i++)
        {
            free_func(array->ptr[i]);
        }
    }
    free(array->ptr);
    free(array);
}

// void free_int(void *data)
// {
//     free(data);
// }
