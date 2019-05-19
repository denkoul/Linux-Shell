#include "p3160069-p3160131-auebsh.h"

int main()
{
    char prompt[11] = "auebsh1> ";
    char* input;
    char* arguments[2];
    
    while(1)
    {
        input = readInput(prompt);
        if (feof(stdin))
        {
            printf("\n");
            break;
        }
	
        
        //arguments = split_args(input);
        
        arguments[0] = strtok(input, " \n\t\r\a");
        if(strtok(NULL, "\n\t\r\a") != NULL)
        {
            perror("You gave more than one arguments. Ignoring them...\n");
        }
        arguments[1] = NULL;
        
        exe(arguments);
    }
    return 0;
}
