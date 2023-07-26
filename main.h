#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

void execmd(char **argv, char **env);
char *get_location(char *command);
void print_environment(char **env);
char *mi_strdup(const char *str);
size_t my_strlen(const char *str);
char *my_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *str);
char *myn_getenv(const char *name);
char *my_strtok_dyn(char *str, const char *delim);
char *my_strchr(const char *str, int character);
int _strcmp(const char *str, const char *str1);
char *_strncpy(char *destn, const char *src, size_t n);
int my_atoi(const char *str);

#endif

