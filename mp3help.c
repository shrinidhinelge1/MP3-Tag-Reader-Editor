#include<stdio.h>
void mp3help(char *filename)
{
    printf("USE : \n");
    printf("View : ./a.out -v sample.mp3\n");
    printf("Edit : ./a.out -e -t/-a/-A/-y/-T/-c new_name sample.mp3\n");
    printf("-v  ->    Prints MP3 file details\n");
    printf("-e  ->    Allows to edit a tag\n");
    printf("-t  ->    Allows to edit a title tag\n");
    printf("-a  ->    Allows to edit a artist tag\n");
    printf("-A  ->    Allows to edit a album tag\n");
    printf("-y  ->    Allows to edit a year tag\n");
    printf("-T  ->    Allows to edit a music tag\n");
    printf("-c  ->    Allows to edit a comment tag\n");
    
}