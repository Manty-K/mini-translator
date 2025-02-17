
enum loopType
{
    START,
    END,
};

char *getLoopName(int type);

void loopOpen();

void loopClose();

void initializeLoopStack();