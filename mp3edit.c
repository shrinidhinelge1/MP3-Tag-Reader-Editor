#include<stdio.h>
#include<string.h>
void mp3edit(char *option, char *new_name, char *filename)
{
    FILE *fp;
    fp=fopen(filename,"rb");
    if(fp==NULL)
    {
        printf("File unable to open\n");
        return;
    }
    char header[100];
    if(fread(header,1,10,fp)!=10)
    {
        printf("Enable to read header\n");
        fclose(fp);
        return;
    }

    if(header[0]!='I'||header[1]!='D'||header[2]!='3')
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
    
    char target[5]="";
    if(strcmp(option,"-t")==0)
      strcpy(target,"TIT2");
    else if(strcmp(option,"-a")==0)
      strcpy(target,"TPE1");
    else if(strcmp(option,"-A")==0)
      strcpy(target,"TALB");
    else if(strcmp(option,"-y")==0)
      strcpy(target,"TYER");
    else if(strcmp(option,"-T")==0)
      strcpy(target,"TCON");
    else if(strcmp(option,"-c")==0)
      strcpy(target,"COMM");
    else{
        printf("Error: Invalid option\n");
        fclose(fp);
        return;
    }

    FILE *temp=fopen("temp.mp3","wb");
    if(temp==NULL)
    {
        printf("File unable to open\n");
        fclose(fp);
        return;
    }
    fwrite(header,1,10,temp);
    int found=0;

    for(int i=0;i<6;i++)
    {
        char tag[5];
        if(fread(tag,1,4,fp)!=4)
          break;
        tag[4]='\0';

        int size;
        char size_bytes[4];
        if(fread(size_bytes,1,4,fp)!=4)
          break;

        size=(size_bytes[0]<<24)|(size_bytes[1]<<16)|(size_bytes[2]<<8)|size_bytes[3];

        
        char flag[2];
        if(fread(flag,1,2,fp)!=2)
          break;

        char data[100];
        if(size<0 || size>=100)
        {
            break;
        }
        if(fread(data,1,size,fp)!=size)
            break;

        if(strcmp(tag,target)==0)
        {
            found=1;

            size=strlen(new_name)+1;
            if(size>=100)
            {
                break;
            }
            
            data[0]=0;
            strcpy(data+1,new_name);

            size_bytes[0]=(size>>24);
            size_bytes[1]=(size>>16);
            size_bytes[2]=(size>>8);
            size_bytes[3]=size;
        }

        fwrite(tag,1,4,temp);
        fwrite(size_bytes,1,4,temp);
        fwrite(flag,1,2,temp);
        fwrite(data,1,size,temp);
    }
    if(found==0)
    {
        printf("Entered option not found\n");
        fclose(fp);
        fclose(temp);
        return;
    }

    int ch;
    while((ch=fgetc(fp))!=EOF)
      fputc(ch,temp);

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.mp3",filename);

    printf("Tag edited successfully\n");
}
