#include "p3160069-p3160131-auebsh.h"

int main()
{
    char prompt[11] = "auebsh5> ";
    char* input;
    char** commands;
    char*** arguments;
    char* inFile;
    char* outFile;
    
    int din = dup(0);
    int dout = dup(1);
    int i, j, k;
    int status;
    
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
            int pipefd[2*(i-1)];
            for(j = 0; j < i; j++)
            {
                pipe(pipefd+j*2);
            }
            for(j = 0; j < i; j++)
            {
                pid_t x = fork();
                if(x < 0)
                {
                    perror("Error");
                    exit(1);
                }
                if(x == 0)  //Child
                {
                    inFile = getFilenames(arguments[j], '<');
                    outFile = getFilenames(arguments[j], '>');

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

                    if(j != 0)
                    {
                        dup2(pipefd[(j-1)*2], 0);
                    }
                    if(j != i-1)
                    {
                        dup2(pipefd[j*2+1], 1);
                    }
                    for(k = 0; k < i*2; k++)
                    {
                        close(pipefd[k]);
                    }
                    execvp(arguments[j][0], arguments[j]);
                    perror("Error");
                    exit(1);
                }
            }
            for(k = 0; k < i*2; k ++)
            {
                close(pipefd[k]);
            }
            for(j = 0; j < i; j++)
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
