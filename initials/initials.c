#include<ctype.h>
#include<cs50.h>
#include<stdio.h>
#include<string.h>

int main(void)
{
    string name = GetString();
    char initials[strlen(name)];
    initials[0] = toupper(name[0]);
    int b = 1;
    
    for(int a = 1; a < strlen(name); a++)
    {
        if(isblank(name[a]) == true)
        {   
            char c = toupper(name[a + 1]);
            initials[b] = c;
            b++;
        }
    }
    
    printf("%s\n", initials);

}