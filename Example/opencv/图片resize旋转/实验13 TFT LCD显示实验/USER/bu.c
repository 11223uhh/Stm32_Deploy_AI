#include "bu.h"
#include "malloc.h"

char *strdup(const char *s)
{
        char *t = "";
        if (s && (t = (char*)malloc(strlen(s) + 1)))
        strcpy(t, s);
        return t;
}  