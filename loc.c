#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
/**
 * get_location - Find the location of a command in the system's PATH.
 * @command: The command to find in the PATH.
 *
 * Return: A pointer to a string containing the absolute path of the command.
 * 
 */
char *get_location(char *command) 
{
char *path, *path_copy, *path_token, *command_path;
int command_length, token_length;
struct stat buffer;
path = getenv("PATH");
path_copy = mi_strdup(path);
command_length = my_strlen(command);
path_token = my_strtok_dyn(path_copy, ":");
while (path_token != NULL) 
{
token_length = my_strlen(path_token);
command_path = malloc(command_length + token_length + 2); 
if (command_path == NULL)
{
perror("Memory allocation error");
return (NULL);
}
_strcpy(command_path, path_token);
my_strcat(command_path, "/");
my_strcat(command_path, command);
if (stat(command_path, &buffer) == 0)
{
free(path_copy);
return (command_path);
}
else 
{
free(command_path);
path_token = my_strtok_dyn(NULL, ":");
}
}
free(path_copy);
return (NULL);
}

