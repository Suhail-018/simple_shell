#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

void execmd(char **argv, char **env) {
    char *command = NULL, *actual_command = NULL;
    struct stat buffer;

    if (argv) {
        /* Get the command */
        command = argv[0];

        // Check if the command is an absolute or relative path
        if (stat(command, &buffer) == 0) {
            // If the command is a valid path, execute it directly
            if (execve(command, argv, env) == -1) {
		    errno = ENOENT;
                perror(argv[0]);
                // Add an exit call here to terminate the child process if exec fails.
                exit(EXIT_FAILURE);
            }
        } else {
            // The command is not a valid path, try to find its location in the PATH environment variable
            actual_command = get_location(command);

            if (actual_command != NULL) {
                // If the actual command is found in the PATH, execute it
                if (execve(actual_command, argv, env) == -1) {
			errno = ENOENT;
                    perror(argv[0]);
                    // Add an exit call here to terminate the child process if exec fails.
                    exit(EXIT_FAILURE);
                }
            } else {
                // If the actual command is not found, print an error message and exit the child process
              errno = ENOENT;
    		    perror(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    // Free allocated memory for 'actual_command'.
    free(actual_command);
}
}
