#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void funkcija(char* putanja)
{
    DIR* dp;
    struct dirent* dir;
    struct stat statbuf;
    FILE* f;
    int link = 0;
    int podfolder = 0;
    int prazneReg = 0;
    int neprazneReg = 0;
    
    char path[80];
    
    if((dp = opendir(putanja)) == NULL)
    {
        printf("Greska pri otvaranju direktorijuma!\n");
        exit(-1);
    }
    
    while((dir = readdir(dp)) != NULL)
    {
        if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
            continue;
        strcpy(path, putanja);
        strcat(path, "/");
        strcat(path, dir->d_name);
        
        stat(path, &statbuf);
        
        if(S_ISDIR(statbuf.st_mode))
            podfolder++;
        if(S_ISLNK(statbuf.st_mode))
            link++;
        if(S_ISREG(statbuf.st_mode) && statbuf.st_size == 0)
            prazneReg++;
        if(S_ISREG(statbuf.st_mode) && statbuf.st_size > 0)
            neprazneReg++;
    }
    
    printf("Tekuci direktorijum ima %d poddirektorijuma, %d linkova, %d praznih regularnih datoteka i %d nepraznih regularnih datoteka!\n", podfolder, link, prazneReg, neprazneReg);
    
    closedir(dp);
}

int main()
{
    funkcija(".");
}

