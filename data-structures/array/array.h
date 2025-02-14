
typedef struct
{

    void **ptr;
    int cap;
    int filled;

} ARRAY;

ARRAY *createArray(int);

void appendArray(ARRAY *, void *);

void *getElementArray(ARRAY *, int);

void setElementArray(ARRAY *, int, void *);

void *popElementArray(ARRAY *);

char isEmptyArray(ARRAY *array);
void freeArray(ARRAY *);
