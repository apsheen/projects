/**
 * fifteen.c:
 * implements Game of Fifteen (generalized to d x d).
 * 
 * Usage: fifteen d
 * whereby the board's dimensions are to be d x d, where d must be in [DIM_MIN,DIM_MAX].
 *
 * Note that usleep is obsolete, but offers more granularity than sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DIM_MIN 3
#define DIM_MAX 9

//board
int board[DIM_MAX][DIM_MAX];

//dimensions
int d;
int row_blank;
int col_blank;

//functions
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    
    if (file == NULL)
    {
        return 3;
    }
    
    // greet user with instructions
    greet();

    // initialize the board
    init();
    
    row_blank = d - 1;
    col_blank = d - 1;

    // accept moves until game is won
    while(true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if(won())
        {
            printf("You have won!!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);
        

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }
        
        //move function?

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes game's board w/ tiles numbered 1 through d*d - 1 by filling 2D array w/ values
 */
void init(void)
{
    int count = d * d - 1;
    
    if((d % 2) == 0)
    {
        for(int i = 0; i < d;  i++)
        {
            for(int j = 0; j < d; j++)
            {
                board[i][j] = count;
                count--;
            }
        }
        board[d - 1][d - 2] = 2;
        board[d - 1][d - 3] = 1;
    }
    
    else
    {
        for(int i = 0; i < d;  i++)
        {
            for(int j = 0; j < d; j++)
            {
                    board[i][j] = count;
                    count--;
            }
        }
    }
}

/**
 * Prints board in current state
 */
void draw(void)
{
    for(int i = 0; i < d;  i++)
    {
        for(int j = 0; j < d; j++)
        {
            if((board[i][j] <= 9) && (board[i][j] > 0))
            {
                printf(" ");
            }
            
            if(board[i][j] == 0)
            {
                printf("  _");
            }
            
            else
            {
                printf(" %d", board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else returns false. 
 */
bool move(int tile)
{
    int tile_row;
    int tile_col;
    
    for(int i = 0; i < d;  i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] == tile)
            {
                tile_row = i;
                tile_col = j;
                break;
            }
        }
    }
    
    //right : ((row_blank == tile_row) && (col_blank == tile_col - 1))
    //left : ((row_blank == tile_row)&& (col_blank == tile_col + 1))
    //up : ((row_blank == tile_row + 1) && (col_blank == tile_col))
    //down : ((row_blank == tile_row - 1) && (col_blank == tile_col))
    
    if(((row_blank == tile_row) && (col_blank == tile_col + 1)) || ((row_blank == tile_row) && (col_blank == tile_col - 1)) || ((row_blank == tile_row + 1) && (col_blank == tile_col)) || ((row_blank == tile_row - 1) && (col_blank == tile_col)))
    {
        board[row_blank][col_blank] = tile;
        board[tile_row][tile_col] = 0;
        row_blank = tile_row;
        col_blank = tile_col;
        return true;
    }
    
    else
    {
        return false;
    }
    
    return 0;
}

/**
 * Returns true if game is won (board in winning configuration), else false.
 */
bool won(void)
{
    int counter = 1;
    
    for(int i = 0; i < d;  i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] != (counter % (d * d)))
            {
                return false;
            }
            
            counter++;
        }
    }
    
    if((counter - 1) == (d * d))
    {
        return true;
    }
    
    return 0;
}