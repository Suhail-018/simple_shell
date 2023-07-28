#include <unistd.h>
#include "main.h"
#include <string.h>
void print_environment(char **env) 
{
    while (*env != NULL) 
    {
       write(STDOUT_FILENO, *env, strlen(*env));
        write(STDOUT_FILENO, "\n", 1);
        env++;
    }
}

