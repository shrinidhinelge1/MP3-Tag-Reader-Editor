#include <stdio.h>
#include <string.h>

// Function to read and display MP3 tag details
void mp3view(char *filename)
{
    FILE *fp=fopen(filename,"rb");
    if(fp==NULL)
    {
        printf("File unable to open\n");
        return;
    }

    char header[10];
    if (fread(header, 1, 10, fp) != 10)
    {
        printf("Unable to read header\n");
        fclose(fp);
        return;
    }
    if(header[0]!='I' || header[1]!='D' || header[2]!='3')
    {
        printf("ID3 is not present in your mp3 file\n");
        fclose(fp);
        return;
    }
    if(header[3]!=3 || header[4]!=0)
    {
        printf("ID3 vession is not supported\n");
        fclose(fp);
        return;
    }

    char title[100]="";
    char artist[100]="";
    char album[100]="";
    char year[100]="";
    char music[100]="";
    char comment[100]="";

    char tag[5];
    for(int i=0;i<6;i++)
    {
        if(fread(tag,1,4,fp)!=4)
        {
            break;
        }

        tag[4]='\0';

        int size;
        char size_bytes[4];
        fread(size_bytes,1,4,fp);
        size=(size_bytes[0]<<24)|(size_bytes[1]<<16)|(size_bytes[2]<<8)|size_bytes[3];

        char flags[2];
        fread(flags,1,2,fp);

        char data[100];
        if(size>0 && size<100)
        {
            if(fread(data,1,size,fp)!=size)
            {
              break;
            }
        }
        data[size]='\0';

        if(strcmp(tag,"TIT2")==0)
          strcpy(title, data+1);
        else if(strcmp(tag,"TPE1")==0)
          strcpy(artist, data+1);
        else if(strcmp(tag,"TALB")==0)
          strcpy(album, data+1);
        else if(strcmp(tag,"TYER")==0)
          strcpy(year, data+1);
        else if(strcmp(tag,"TCON")==0)
          strcpy(music, data+1);
        else if(strcmp(tag,"COMM")==0)
          strcpy(comment, data+1);
    }
    printf("Title : %s\n",title);
    printf("Artist : %s\n",artist);
    printf("Album : %s\n",album);
    printf("Year : %s\n",year);
    printf("Music : %s\n",music);
    printf("Comment : %s\n",comment);

    fclose(fp);
}