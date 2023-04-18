#include "utils.h"

#include <string.h>
#include <stdlib.h>

char *concatenar_strings(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char *result = (char *)malloc(len1 + len2 + 1); // add 1 for the null terminator
    if (result == NULL)
    {
        return NULL;
    }
    strcpy(result, str1);
    strcpy(result + len1, str2);
    return result;
}
