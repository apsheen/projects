#include<cs50.h>
#include<math.h>
#include<stdio.h>

int main(void)
{   
    printf("Enter an ISBN-10 to see if it is legit: \n");
    long long ISBN = GetLongLong();
    long long legit = 0;
    int a = 0;
    long long c = 0;
    
    for(int b = 10; b >= 1; b--)
    {
        c = pow(10, a);
        legit = legit + (b * ((ISBN / c) % 10));
        a++;
    }

    legit = legit % 11;
    
    if(legit == 0)
    {
        printf("YES\n");
    }
    
    else
    {
        printf("NO\n");
    }
}