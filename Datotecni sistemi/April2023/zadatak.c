#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>

int size = 0;
char name[80];

void rekurzija(char* putanja, int level)
{
    DIR* dp;
    struct dirent* dir;
    struct stat statbuf;
    char path[80];
    int lvl = level;
    
    if((dp = opendir(putanja)) == NULL)
    {
        printf("Greska pri otvaranju datoteke!\n");
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
       
       if(S_ISREG(statbuf.st_mode))
       {
           if(size < statbuf.st_size)
           {
               size = statbuf.st_size;
               strcpy(name, dir->d_name);
           }
       }
       
       if(S_ISDIR(statbuf.st_mode) && lvl <= 5)
       {
           rekurzija(path, lvl+1);
           lvl++;
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
   
   rekurzija(argv[1], 1);
   
   printf("Najveca datoteka: %s sa velicinom: %d\n", name, size);
}
