/**********************************
 * finder.c
 *
 * CS50 AP
 * Finder
 *
 * Searches for a target string in all files in a directory
 **********************************/

#define _BSD_SOURCE
#define _GNU_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// struct to hold the file name and type
typedef struct
{
    string name;
    string type;
}
path;

// struct to hold the directory info
typedef struct
{
    string name;
    int npaths;
    path* paths;
}
directory;

// string to hold the word to seek
string key;

// the function to search for files in a directory and populate the struct
directory populate(directory dir);

// the function to recursively iterate through directories and handle files
int seek(directory dir);

// main - sets arguments and calls the seek function
int main(int argc, char* argv[])
{
    //ensure proper number of command line arguments
    if ((argc > 3) || (argc < 2))
    {
        printf("Usage: ./finder <search string> [optional directory to search/]\n");
        return 1;
    }

    key = argv[1];

    //create initial directory
    directory dir;

    //set "dir"s name based on command line arguments entered
    if(argc == 3)
        dir.name = argv[2];

    else
        dir.name = "./";

    //call the seek function
    return seek(dir);
}

// for a given directory, searches for files and fills array in the struct
directory populate(directory dir)
{
    //initialize all pointers and values in the given struct
    dir.npaths = 0;
    dir.paths = NULL;
    DIR* dirp;
    struct dirent* entry;

    //opendir is a system call that opens a "directory stream" containing
    //information about all files in the given directory (represented here by dir.name)
    dirp = opendir(dir.name);
    if (dirp == NULL)
    {
        printf("Opening directory failed. Check your input filepath!\n");
        return dir;
    }

    //while directory stream still contains files, seek through them
    while((entry = readdir(dirp)) != NULL)
    {
        //if entry is a directory and not '.' or '..', increase file count and populate the struct
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            // allocate zeroed-out memory for the construction of the file name
            string name = calloc(1, strlen(dir.name) + strlen(entry->d_name) + 2);
            strcat(name, dir.name);
            strcat(name, entry->d_name);
            strcat(name, "/");

            // reallocate memory to expand the array
            dir.paths = realloc(dir.paths, (dir.npaths + 1) * sizeof(path));

            // add a new element to the array containing names and types
            path newPath = {.name = name, .type = "directory"};
            dir.paths[dir.npaths] = newPath;

            // increase file count for the directory
            dir.npaths++;
        }

        // else if entry is a file, increase file count and populate the struct
        else if (entry->d_type == DT_REG)
        {
            // allocate zeroed-out memory for the construction of the file name
            string name = calloc(1, strlen(dir.name) + strlen(entry->d_name) + 1);
            strcat(name, dir.name);
            strcat(name, entry->d_name);

            // reallocate memory to expand the array
            dir.paths = realloc(dir.paths, (dir.npaths + 1) * sizeof(path));

            //add a new element to the array containing names and types
            path newPath = {.name = name, .type = "file"};
            dir.paths[dir.npaths] = newPath;

            // increase file count for the directory
            dir.npaths++;
        }
    }

    // close directory stream using system call closedir and return struct
    closedir(dirp);
    return dir;

}

//recursive function to iterate through directories and search files
int seek(directory dir)
{
    directory user_dir = populate(dir);

    for(int i = 0; i < user_dir.npaths; i++)
    {
        if(strcmp(user_dir.paths[i].type, "file") == 0)
        {
            FILE* fp_looking = fopen(user_dir.paths[i].name, "r");

            if(fp_looking == NULL)
            {
                printf("File does not exist in either your specified directory or current directory.\n");
                return 1;
            }

            int already_found = 0;
            char looking[50];

            while(fgets(looking, 50, fp_looking) != NULL)
            {
                if((strstr(looking, key) != NULL) && (already_found < 1))
                {
                    FILE* fp_found = fopen("found.txt", "a");

                    if(fp_found == NULL)
                    {
                        printf("An error occured opening found.txt.\n");
                        return 1;
                    }

                    fputs(user_dir.paths[i].name, fp_found);
                    fputs("\n", fp_found);
                    fclose(fp_found);
                    already_found++;
                }
            }
            
            fclose(fp_looking);
        }

        if(strcmp(user_dir.paths[i].type, "directory") == 0)
        {
            directory next_dir;
            next_dir.name = user_dir.paths[i].name;
            seek(next_dir);
        }
    }

    return 0;
}