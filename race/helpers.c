/**
 * helpers.c
 *
 * CS50 AP
 * Problem 3-4
 * 
 * Name: ___________________________
 *
 * Helper functions for the sort race
 */

#include <cs50.h>
#include <string.h>
#include "helpers.h"
#include <stdio.h>

/**
 * Returns true if str is a valid flag (-a, -b, -r, or -s), false otherwise
 */
bool check_flag(char* flag)
{
    //almost sorted arrays: already sorted except for two elements which have been randomly switched
    string flag_a = "-a";
    //backwards arrays
    string flag_b = "-b";
    //random arrays
    string flag_r = "-r";
    //sorted arrays
    string flag_s = "-s";
    
    if((strcmp(flag, flag_a) == 0) || (strcmp(flag, flag_b) == 0) || (strcmp(flag, flag_r) == 0) || (strcmp(flag, flag_s) == 0))
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

/**
 * Sorts array of n values using bubble sort.
 */
void bubble(int values[], int n)
{
    int swaps = 0;
    
    for(int a = 0; a < n; a++)
    {
        for(int b = 0; b < n; b++)
        {
            if(values[b] > values[(b + 1)])
            {
                int hold = values[b];
                values[b] = values[(b + 1)];
                values[(b + 1)] = hold;
                swaps++;
            }
        }
        
        if(swaps == 0)
        {
            return;
        }
        
        swaps = 0;
    }
}

/**
 * Sorts array of n values using selection sort.
 */
void selection(int values[], int n)
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
    }
    return;
}

/**
 * Sorts array of n values using insertion sort.
 */
void insertion(int values[], int n)
{
    int insert_spot;
    int insertx;
    
    for(int a = 1; a < n; a++)
    {
        insertx = values[a];
        
        for(int b = 0; b < a; b++)
        {
            if(values[b] > insertx)
            {
                insert_spot = b;
                
                for(int c = a; c > insert_spot; c--)
                {
                    values[c] = values[c - 1];
                }
                
                values[insert_spot] = insertx;
                b = a; 
                //force quit the loop that does the shifting to the right
                //if larger value than the one to be inserted in sorted portion was found
            }
        }
    }
    
    return;
}