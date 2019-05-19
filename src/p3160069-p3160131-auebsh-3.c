#include "p3160069-p3160131-auebsh.h"

int main()
{
    char prompt[11] = "auebsh3> ";
    char* input;
    char** arguments;
    char* inFile;
    char* outFile;
    
    int din = dup(0);
    int dout = dup(1);
    
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
        
        arguments = split_args(input);
        
        inFile = getFilenames(arguments, '<');
        outFile = getFilenames(arguments, '>');
        
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
 
        exe(arguments);
    }
    return 0;
}
