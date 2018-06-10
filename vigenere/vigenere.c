#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./vigenere <key for encryption>\n");
        return 1;
    }
    
    string keyword = argv[1];

    for(int i = 0; i < strlen(keyword); i++)
    {
        if(isalpha(keyword[i]) == false)
        {
            printf("Usage: key for encryption must be all alphabetical characters!\n");
            return 1;
        }
    }
    
    string message = GetString();
    int letter = 0;
    int key_letter = 0;
    int message1[strlen(message)];
    int pos_keywd = 0;
    int key_counter = 0;
    
   for(int i = 0; i < strlen(message); i++)
    {
        if(isalpha(message[i]))
        {
            if(islower(message[i]))
            {
                letter = (int)message[i] - 97;
                pos_keywd = key_counter % strlen(keyword);
                 
                if(islower(keyword[pos_keywd]))
                {
                    key_letter = ((int)keyword[pos_keywd]) - 97;
                }
                
                if(isupper(keyword[pos_keywd]))
                {
                    key_letter = ((int)keyword[pos_keywd]) - 65;
                }
                
                message1[i] = ((letter + key_letter) % 26) + 97 ;
                key_counter++;
            }
            
            if(isupper(message[i]))
            {
                letter = (int)message[i] - 65;
                pos_keywd = key_counter % strlen(keyword);
                 
                if(islower(keyword[pos_keywd]))
                {
                    key_letter = ((int)keyword[pos_keywd]) - 97;
                }
                
                if(isupper(keyword[pos_keywd]))
                {
                    key_letter = ((int)keyword[pos_keywd]) - 65;
                }
                
                message1[i] = ((letter + key_letter) % 26) + 65 ;
                key_counter++;
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