#include "queries.h"
#define STR_BLOCK 5

String copyStr(const String from)
{
    #ifdef DEBUG
        assert(from != NULL);
    #endif
    String dest = NULL;
    int i;
    for (i = 0; from[i] != '\0'; i += 1)
    {
        if (i % STR_BLOCK == 0)
        {
            errno = 0;
            dest = realloc(dest, (i + STR_BLOCK) * sizeof(char));
            if (errno == ENOMEM)
            {
                free(dest);
                return NULL;
            }
        }
        dest[i] = from[i];
    }
    errno = 0;
    dest = realloc(dest, (i + 1) * sizeof(char));
    if (errno == ENOMEM)
    {
        free(dest);
        return NULL;
    }
    dest[i] = '\0';
    return dest;
}