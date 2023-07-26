#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

/**
 * main - Entry point of the shell program.
 *
 * @argc: The number of arguments passed to the program.
 * @argv: An array of strings containing the command-line arguments.
 * @env: An array of strings containing the environment variables.
 *
 * Return: Always 0.
 */
int main(int argc, char **argv, char **env) {
char *prompt = " $"; 
char *lineptr = NULL;
size_t n = 0;
ssize_t in_read;
int length = strlen(prompt);
char *lineptr_copy = NULL;
const char *delim = " \n";
pid_t pid; 
int num_tokens = 0;
int i;
char *token;
bool fpipe = false;
while (1 && !fpipe) {
if(isatty(STDIN_FILENO) == 0)
fpipe = true;
write(STDOUT_FILENO, prompt, length);
in_read = getline(&lineptr, &n, stdin); 
if (in_read == -1) 
{
return (-1);
}
if (lineptr[in_read - 1]== '\n')
{
lineptr[in_read -1]='\0';
}
write(STDOUT_FILENO, lineptr, n);
lineptr_copy = malloc(sizeof(char) * n);
if (lineptr_copy == NULL)
{
perror("tsh: memory allocation error");
return (-1);
}
_strcpy(lineptr_copy, lineptr);
token = my_strtok_dyn(lineptr, delim);
while (token != NULL) 
{
num_tokens++;
token = my_strtok_dyn(NULL, delim);
}
argc = num_tokens; 
argv = malloc(sizeof(char *) * (num_tokens + 1)); 
if (argv == NULL)
{
perror("tsh: memory allocation error");
return (-1);
}
token = my_strtok_dyn(lineptr_copy, delim);
for (i = 0; token != NULL; i++) {
argv[i] = malloc(sizeof(char) * (my_strlen(token) + 1)); 
_strcpy(argv[i], token);
token = my_strtok_dyn(NULL, delim);
}
argv[i] = NULL;
if(_strcmp(argv[0], "exit") == 0) 
{
for (i = 0; i < argc; i++)
{  
free(argv[i]);
}
free(argv);
free(lineptr);
free(lineptr_copy);
break;     
}
else  if (_strcmp(argv[0], "env") == 0) 
{
if (argv[1] != NULL) {
execmd(&argv[1], env);
}
else 
{
print_environment(env);
}
continue;
}
pid = fork(); 
if (pid == -1) 
{
perror("tsh: fork error"); 
}
else if (pid == 0) 
{
execmd(argv, env);
exit(EXIT_FAILURE);
}
else
{
wait(NULL); 
}
}
return (0);
}

