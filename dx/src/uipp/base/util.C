#include <string.h>

#include <dxconfig.h>


int
STRLEN(char *a)
{
    if (!a) return 0;
    else return strlen(a);
}

int
STRCMP(char *a, char *b)
{
    if (!a || !b) 
        if (!a) return strcmp("", b);
	else return strcmp(a, "");
    else return strcmp(a, b);
}

int
STRCMP(char *a, char *b, int n)
{
    if (!a || !b) 
        if (!a) return strncmp("", b, n);
	else return strncmp(a, "", n);
    else return strncmp(a, b, n);
}
