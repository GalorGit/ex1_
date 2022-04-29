

#include "stdlib.h”
#include "string.h”
#include "assert.h”
char *stringDuplicator(char *s, int times)
{
    assert(!s);
    assert(times > 0);
    int len = strlen(s);
    char *out = malloc((len+1) * times);
    assert(out);
    for (int i = 0; i <= times; i++)
    {
        strcpy(out, s);
        out = out + len+1;
    }
    return out;
}
