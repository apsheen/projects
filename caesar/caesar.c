#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./caeser <key for encryption>\n");
        return 1;
    }
    
    int key = atoi(argv[1]);
    
    if(!(key > 0))
    {
        printf("Usage: key for encryption must be nonegative!\n");
        return 1;
    }
    
    string message = GetString();
    int letter;
    int message1[strlen(message)];
    
    for(int i = 0; i < strlen(message); i++)
    {
        if(isalpha(message[i]))
        {
            if(isupper(message[i]))
            {
                letter = (int)message[i] - 65;
                message1[i] = ((letter + key) % 26) + 65 ;
            }
            
            if(islower(message[i]))
            {
                letter = (int)message[i] - 97;
                message1[i] = ((letter + key) % 26) + 97 ;
            }
        }
        
        else
        {
            message1[i] = (int)message[i];
        }
    }
    
    for(int n = 0; n < strlen(message); n++)
       {
           printf("%c", message1[n]);
       }
       
    printf("\n");
}