#include <cs50.h>
#include <string.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./calc <number> <operator> <number>\n");
        return 1;
    }
    
    string operators_input = argv[2];
    string m = "x";
    string d = "/";
    string p = "+";
    string s = "-";
    string r = "%";
    
    if (strcmp(operators_input, m) != 0 && strcmp(operators_input, d) != 0 && strcmp(operators_input, p) != 0 && strcmp(operators_input, s) != 0 && strcmp(operators_input, r) != 0)
    {
        printf("Please use the appropriate signs for your operation! (Multiplication is inputted as an x) Calc 1.0 only handles multiplication, subtraction, division, addition, and modulus.\n");
        return 1;
    }
    
    float value_1 = atof(argv[1]);
    float value_2 = atof(argv[3]);

    if (strcmp(operators_input, m) == 0)
    {
       printf("%f\n", value_1 * value_2); 
    }
    
    if (strcmp(operators_input, d) == 0)
    {
        printf("%f\n", value_1 / value_2);   
    }
    
    if(strcmp(operators_input, p) == 0)
    {
        printf("%f\n", value_1 + value_2);
    }
    
    if(strcmp(operators_input, s) == 0)
    {
        printf("%f\n", value_1 - value_2);
    }
    
    if(strcmp(operators_input, r) == 0)
    {
        int q = (int) (value_1 / value_2);
        float mod = value_1 - (value_2 * q);
        printf("%f\n", mod);
    }

}