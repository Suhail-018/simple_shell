#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

/**
 * execmd - Execute a command with given arguments.
 * @argv: Array of strings containing the command and its arguments.
 * @env: Array of strings containing the environment variables.
 *
 * Description: This function executes a command specified by argv 
 * Return: None.
 */

void execmd(char **argv, char **env)
{
char *command = NULL, *actual_command = NULL;
struct stat buffer;
if (argv) 
{
command = argv[0];
if (stat(command, &buffer) == 0)
{
if (execve(command, argv, env) == -1) 
{
errno = ENOENT;
perror(argv[0]);
exit(EXIT_FAILURE);
}
}
else
{
actual_command = get_location(command);
if (actual_command != NULL) {
if (execve(actual_command, argv, env) == -1)
{
errno = ENOENT;
perror(argv[0]);
exit(EXIT_FAILURE);
}
}
else 
{
errno = ENOENT;
perror(argv[0]);
exit(EXIT_FAILURE);
}
}
free(actual_command);
}
}
