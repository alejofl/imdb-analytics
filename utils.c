#include "queries.h"
#define STR_BLOCK 5

String copyStr(const String from)
{
    if (TEST)
        assert(from != NULL);
    String dest = NULL;
    int i;
    for (i = 0; from[i] != '\0'; i += 1)
    {
        if (i % STR_BLOCK == 0)
        {
            dest = realloc(dest, (i + STR_BLOCK) * sizeof(char));
            // TODO: Cambiar esto a errno
            if (dest == NULL)
            {
                return NULL;
            }
        }
        dest[i] = from[i];
    }
    dest = realloc(dest, i * sizeof(char));
    // TODO: Cambiar esto a errno
    if (dest == NULL)
    {
        return NULL;
    }
    dest[i] = '\0';
    return dest;
}