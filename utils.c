#include "queries.h"
#define STR_BLOCK 5

String copyStr(const String from)
{
    if (TEST)
        assert(from != NULL);
    String dest = NULL;
    int i;
    for (i = 0; from[i] != '\n'; i += 1)
    {
        if (i % STR_BLOCK == 0)
        {
            dest = malloc((i + STR_BLOCK) * sizeof(char));
            if (dest == NULL)
            {
                return NULL;
            }
        }
        dest[i] = from[i];
    }
    dest = realloc(dest, (i + 1) * sizeof(char));
    if (dest == NULL)
    {
        return NULL;
    }
    dest[i] = '\n';
    return dest;
}