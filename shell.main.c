#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Add this line to include the string.h header.
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
int main(int argc, char **argv, char **env) {
    char *prompt = " $"; // Use double quotes for string literals.
    char *lineptr = NULL;
    ssize_t n = 0;
    ssize_t in_read;
    int length = strlen(prompt);
    char *lineptr_copy = NULL;
    const char *delim = " \n";
    pid_t pid; // Declare the 'pid' variable to store the process ID.
    int i;
    bool fpipe = false;

    while (1 && !fpipe) {
	    if(isatty(STDIN_FILENO) == 0)
		    fpipe = true;

        write(STDOUT_FILENO, prompt, length);
        in_read = getline(&lineptr, &n, stdin); // Use 'stdin' instead of 'STDIN'.
        if (in_read == -1) {
            return (-1);
        }
if (lineptr[in_read - 1]== '\n')
{
	lineptr[in_read -1]='\0';
}



	lineptr_copy = malloc(sizeof(char) * n); // Change 'nchars_read' to 'n'.
        if (lineptr_copy == NULL) {
            perror("tsh: memory allocation error");
            return (-1);
        }
        _strcpy(lineptr_copy, lineptr);

        int num_tokens = 0; // Add this variable to count the number of tokens.
        char *token = strtok(lineptr, delim);
        while (token != NULL) {
            num_tokens++;
            token = strtok(NULL, delim);
        }

        argc = num_tokens; // Change 'argc++' to 'argc = num_tokens'.
 
        argv = malloc(sizeof(char *) * (num_tokens + 1)); // Add +1 for the NULL terminator.
        if (argv == NULL) {
            perror("tsh: memory allocation error");
            return (-1);
        }

        token = strtok(lineptr_copy, delim);
        for (i = 0; token != NULL; i++) {
            argv[i] = malloc(sizeof(char) * (my_strlen(token) + 1)); // Add +1 for the NULL terminator.
            _strcpy(argv[i], token);
            token = strtok(NULL, delim);
        }
        argv[i] = NULL;
    if(_strcmp(argv[0], "exit") == 0) {
for (i = 0; i < argc; i++)
{  
free(argv[i]);
}
free(argv);
free(lineptr);
free(lineptr_copy);

break;      //Terminate the shell
}

 // Check if the command is "env" and handle it as a built-in command
else  if (_strcmp(argv[0], "env") == 0) {
            // If there's an argument, execute the command in a modified environment
            if (argv[1] != NULL) {
                execmd(&argv[1], env);
            } else {
                // If no argument, print the current environment
                print_environment(env);
            }

            // Free memory allocated for cmd_argv elements.

            continue; // Skip the rest of the loop and start a new iteration
        }

       


pid = fork(); // Add a semicolon at the end of this line.
        if (pid == -1) {
            perror("tsh: fork error"); // Enclose "error exiting" in double quotes.
        } else if (pid == 0) {
            execmd(argv, env);
            // Add an exit call here to terminate the child process if exec fails.
            exit(EXIT_FAILURE);
        } else {
            wait(NULL); // Use 'wait(NULL)' to wait for the child process to finish.
        }

        // Free memory allocated for argv elements.





    }

    return (0);
}

