#include<stdio.h>
#include<string.h>
#include "mp3help.h"
#include "mp3view.h"
#include "mp3edit.h"
int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Invalid arguments\n");
        printf("Use :\n");
        printf("Help : ./a.out --h sample.mp3\n");
        printf("View : ./a.out -v sample.mp3\n");
        printf("Edit : ./a.out -e -t new_title sample.mp3\n");
        return 1;      //stop program 1 error found
    }
    
    if(strcmp(argv[1], "--h")==0)
    {
        if(argc!=3)
        {
            printf("Error : Invalid arguments\n");
            return 1;
        }
        printf("SELECTED HELP DETAILS\n\n");
        mp3help(argv[2]);
    }
    else if(strcmp(argv[1], "-v") == 0)
    {
        if(argc!=3)
        {
            printf("Error : Invalid arguments\n");
            return 1;
        }
        printf("SELECTED VIEW DETAILS\n\n");
        mp3view(argv[2]);
    }

    else if(strcmp(argv[1], "-e")==0)
    {
        if(argc!=5)
        {
            printf("Error : Invalid arguments\n");
            return 1;
        }
        printf("SELECTED EDIT DETAILS\n\n");
        mp3edit(argv[2],argv[3],argv[4]);
    }

    else{
        printf("Error : Invalid option\n");
        return 1;
    }
}
