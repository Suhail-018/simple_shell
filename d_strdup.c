#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include <stdio.h>
/**
 * mi_strdup - Duplicates a string.
 * @str: The string to be duplicated.
 *
 * Return: On success, a pointer to the duplicated string. On failure, NULL.
 */
char *mi_strdup(const char *str)
{
size_t len;
char *new_str;
len = my_strlen(str) + 1;
new_str = (char *)malloc(len);
if (new_str == NULL)
{
return (NULL);
}
_strncpy(new_str, str, len);
return (new_str);
}

