#ifndef _auebsh
#define _auebsh
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

int exe(char** args);

int exePipes(char*** args);

char* readInput(char* prompt);

char ** split_args(char* input);

char * getFilenames (char** args, char s);

char ** SplitPipes(char* input);

#endif
