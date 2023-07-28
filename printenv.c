#include <unistd.h>
#include "main.h"
#include <string.h>
// Function to print the current environment variables
void print_environment(char **env) {
    while (*env != NULL) {
        // Use the write system call to print each environment variable
        write(STDOUT_FILENO, *env, strlen(*env));
        write(STDOUT_FILENO, "\n", 1);
        env++;
    }
}

