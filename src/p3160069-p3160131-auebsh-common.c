#include "p3160069-p3160131-auebsh.h"


char* readInput(char* prompt)
{
    char * input = NULL;
    printf("%s", prompt);
    ssize_t siz = 0;
    getline(&input, &siz, stdin);
    return input;
}

char ** split_args(char* input) 
{
    int bufsize = 64;
    char **ret = malloc(bufsize * sizeof(char*));
    char *token;
    int i = 0;
    
    token = strtok(input, " \t\n\r\a");
    while (!(token == NULL)) 
    {
        ret[i] = token;
        i++;
        if (i >= bufsize) 
        {
            bufsize += 64;
            ret = realloc (ret, bufsize * sizeof(char*));
        }
        token = strtok(NULL, " \t\n\r\a");
    }
    ret[i] = NULL;
    return ret;   
}

char * getFilenames (char** args, char s) 
{
    int i, j;
    int size = sizeof(args);
    char* ret;
    for (i=0; args[i] != NULL; i++)
    {
        if (args[i][0] == s)
        {
            args[i] = NULL;
            ret = args[i+1];
            for(j = i; args[j-1] != NULL; j++)
            {
                args[j] = args[j+2];
            }
            return ret;
        }
    }
    return NULL;
}

int exe(char** args)
{
    pid_t x = fork();
    
    if(x < 0)
    {
        perror("Error");
        exit(1);
    }
    if(x == 0)
    {
        printf("%s", args[0]);
        execvp(args[0], args);
        perror("Error");
        exit(1);
    }
    if (x > 0)
    {
        wait(NULL);
    }  
}

char ** SplitPipes(char* input) 
{
    int bufsize = 64;
    char **ret = malloc(bufsize * sizeof(char*));
    char *token;
    int i = 0;
    
    token = strtok(input, "|");
    while (!(token == NULL)) 
    {
        ret[i] = token;
        i++;
        if (i >= bufsize) 
        {
            bufsize += 64;
            ret = realloc (ret, bufsize * sizeof(char*));
        }
        token = strtok(NULL, "|");
    }
    return ret;
}