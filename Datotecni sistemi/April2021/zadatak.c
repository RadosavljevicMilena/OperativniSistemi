#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int size[20];
char* name[20];
int i=0;

void rekurzija(char* putanja)
{
    DIR* dp;
    struct dirent* dir;
    struct stat statbuf;
    
    char path[80];
    
    
    
    if((dp = opendir(putanja)) == NULL)
    {
        printf("Greska pri otvaranju direktorijuma!\n");
        exit(-1);
    }
    
    while((dir = readdir(dp)) != NULL)
    {
        if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
        {
            continue;
        }
        
        strcpy(path, putanja);
        strcat(path, "/");
        strcat(path, dir->d_name);
        
        stat(path, &statbuf);

        if(S_ISREG(statbuf.st_mode) && statbuf.st_size > 102400)
        {
            size[i] = statbuf.st_size;
            name[i] = strdup(dir->d_name);
            i++;
        }
        
        if(S_ISDIR(statbuf.st_mode))
        {
            rekurzija(path);
        }
    }
    
    closedir(dp);
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Nedovoljan broj argumenata!\n");
        exit(-1);
    }
    
    rekurzija(argv[1]);
    
    int pom;
    char pom1[80];
    
    for(int j=0; j<i-1; j++)
    {
        for(int k=j+1; k<i; k++)
        {
            if(size[j] > size[k])
            {
                pom = size[j];
                strcpy(pom1, name[j]);
                size[j] = size[k];
                strcpy(name[j], name[k]);
                size[k] = pom;
                strcpy(name[k], pom1);
            }
        }
    }
    
    for(int j=0; j<i; j++)
    {
        printf("Datoteka %s sa velicinom %d\n", name[j], size[j]);
        free(name[j]);
    }
    
}
