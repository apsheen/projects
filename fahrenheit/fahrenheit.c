#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./fahrenheit <degrees Celsius>\n");
        return 1;
    }
    float fahrenheit = (atof(argv[1]) * 9) / 5 + 32;
    printf("F: %.1f\n", fahrenheit);
}
