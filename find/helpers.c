/**
 * helpers.c
 *
 * CS50 AP
 * Find
 *
 * Helper functions.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if((n < 0) || (n == 0))
    {
        return false;
    }

    int from = 0;
    int up_to = n - 1;
    //changed sign below
    for(int i = 0; i <= (n / 2); i++)
    {
        if(values[((up_to + from) / 2)] == value)
        {
            return true;
        }

        if(values[((up_to + from) / 2)] > value)
        {
            up_to = ((up_to + from) / 2) - 1;
        }

        if(values[((up_to + from) / 2)] < value)
        {
            from = ((up_to + from) / 2) + 1;
        }

        if(up_to < from)
        {
            return false;
        }
    }

    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int smallest;
    bool flag = false;
    int c;

    for(int a = 0; a < n; a++)
    {
        smallest = values[a];

        for(int b = a; b < n; b++)
        {
            if(values[b] < smallest)
            {
                smallest = values[b];
                flag = true;
                c = b;
            }
        }

        if(flag == true)
        {
            values[c] = values[a];
            values[a] = smallest;
            flag = false;
        }

        int counter = 1;

        for(int c = 0; c < n; c++)
        {
            if(values[c] < values[(c + 1)])
            {
                counter++;
            }

            else
            {
                c = n;
            }
        }

        if(counter == n)
        {
            return;
        }
    }

    return;
}
