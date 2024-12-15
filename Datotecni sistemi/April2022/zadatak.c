#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void rekurzija(char* putanja1, char* putanja2)
{
    DIR* dp1;
    DIR* dp2;
    struct dirent* dir1;
    struct dirent* dir2;
    struct stat statbuf1;
    struct stat statbuf2;
    
    char path1[80];
    char path2[80];
    
    if((dp1 = opendir(putanja1)) == NULL)
    {
        printf("Greska pri otvaranju direktorijuma!\n");
    }
    
    if((dp2 = opendir(putanja2)) == NULL)
    {
        printf("Greska pri otvaranju direktorijuma!\n");
    }
    
    while((dir1 = readdir(dp1)) != NULL)
    {
        if(strcmp(dir1->d_name, ".") == 0 || strcmp(dir1->d_name, "..") == 0)
            continue;
        
        strcpy(path1, putanja1);
        strcat(path1, "/");
        strcat(path1, dir1->d_name);
        
        stat(path1, &statbuf1);
        
        while((dir2 = readdir(dp2)) != NULL)
        {
            if(strcmp(dir2->d_name, ".") == 0 || strcmp(dir2->d_name, "..") == 0)
                continue;
            
            strcpy(path2, putanja2);
            strcat(path2, "/");
            strcat(path2, dir2->d_name);
            
            stat(path2, &statbuf2);
            
            if(S_ISREG(statbuf2.st_mode) && statbuf1.st_size == statbuf2.st_size && strcmp(dir1->d_name, dir2->d_name) == 0)
            {
                printf("Datoteka %s / %s postoji u oba direktorijuma\n", path1, path2);
            }
            
            if(S_ISDIR(statbuf2.st_mode))
            {
                rekurzija(putanja1, path2);
            }

        }
        
        //Vraca pokazivac na pocetak datoteke
        rewinddir(dp2);
    }
    
    closedir(dp1);
    closedir(dp2);
}

int main(int argc, char* argv[])
{
    
    if(argc < 3)
    {
        printf("Nedovoljan broj argumenata!\n");
    }
    
    rekurzija(argv[1], argv[2]);
}
