#include "p3160069-p3160131-auebsh.h"

int main()
{
    char prompt[11] = "auebsh4> ";
    char* input;
    char** commands;
    char*** arguments;
    char* inFile;
    char* outFile;
    
    int din = dup(0);
    int dout = dup(1);
    int i;
    int status;
    int pipefd[2];
    
    int in, out;
    
    while(1)
    {
        dup2(din, 0);
        dup2(dout, 1);
        
        input = readInput(prompt);
        if (feof(stdin))
        {
            printf("\n");
            break;
        }
        
        commands = SplitPipes(input);
        for(i = 0; commands[i] != NULL; i ++)
        {
            arguments[i] = split_args(commands[i]);
        }
        
        if(i > 1)
        {
            pipe(pipefd);
            for(i = 0; i < 2; i++)
            {
                pid_t x = fork();
                if(x < 0)
                {
                    perror("Error");
                    exit(1);
                }
                if(x == 0)  //Child
                {
                    inFile = getFilenames(arguments[i], '<');
                    outFile = getFilenames(arguments[i], '>');

                    if (inFile != NULL) 
                    {
                        freopen(inFile, "r", stdin);
                    }

                    if (outFile != NULL) 
                    {
                        out = open(outFile, O_CREAT | O_WRONLY);
                        dup2(out, 1);
                        close(out);
                    }

                    if(i == 0)
                    {
                        dup2(pipefd[1], 1);
                        close(pipefd[0]);
                        close(pipefd[1]);
                    }
                    else
                    {
                        dup2(pipefd[0], 0);
                        close(pipefd[0]);
                        close(pipefd[1]);
                    }
                    execvp(arguments[i][0], arguments[i]);
                    perror("Error");
                    exit(1);
                }
            }
            close(pipefd[0]);
            close(pipefd[1]);
            for(i = 0; i < 2; i++)
            {
                wait(&status);
            }
        }
        else
        {
            inFile = getFilenames(arguments[0], '<');
            outFile = getFilenames(arguments[0], '>');

            if (inFile != NULL) 
            {
                freopen(inFile, "r", stdin);
            }

            if (outFile != NULL) 
            {
                out = open(outFile, O_CREAT | O_WRONLY);
                dup2(out, 1);
                close(out);
            }

            exe(arguments[0]);
        }
    }
    return 0;
}
