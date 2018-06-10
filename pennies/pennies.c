#include <cs50.h>
#include <math.h>
#include <stdio.h>

#define MAX_DAYS 31
#define MIN_DAYS 28

int main(int argc, string argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./pennies <days in month> <pennies on first day>\n");
        return 1;
    }
    
    int days = atoi(argv[1]); //converting days in month input
    int pennies = atoi(argv[2]); //converting pennies input
    
    if (days < MIN_DAYS || days > MAX_DAYS) //days in month check
    {
        printf("A month cannot have more than 31 days or less than 28 days!\n");
        return 1;
    }
    
    if (pennies <= 0) //pennies check
    {
        printf("You cannot have negative pennies!\n");
        return 1;
    }
    
    long long total = pennies;
    
    for(int i = 1; i < days; i++)
    {
        total += pennies * pow(2,i);
    }
        
    printf("$%.2f\n", ((double) total) / 100);
}
