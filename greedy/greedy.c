#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    printf("Oh, hello! How much change is owed?\n");
    float change0 = GetFloat();
    
    if(change0 < 0)
    {
        printf("Retry: ");
        change0 = GetFloat();
    }
    
    change0 = change0 * 100;
    change0 = roundf(change0);
    int change = change0;
    int coins = 0;
  
while(true)  
    {
    
    while(change >= 25)
    {
        coins = change / 25;
        change = change % 25;
    }
    
    while(change >= 10)
    {
        coins = coins + (change / 10);
        change = change % 10;
    }
        
    while(change >= 5)
    {
        coins = coins + (change / 5);
        change = change % 5;
    }
        
    while(change >= 1)
    {
        coins = coins + (change / 1);
        change = change % 1;
    }
        
    if (change == 0)
    {
        printf("%i\n", coins);
        break;
    }
  }
}
    