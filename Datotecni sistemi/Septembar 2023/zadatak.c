#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int m,n;
    DIR* dp;
    FILE* f;
    struct stat statbuf;
    struct dirent* dirp;
    char path[50];
    int brojac=0;
    char linija[100];
    
    if(argc < 4)
    {
        printf("Nedovoljno argumenata!\n");
        exit(-1);
    }
    
    if((dp = opendir(argv[1])) < 0)
    {
        printf("Greska prilikom otvaranja direktorijuma!\n");
        exit(-1);
    }
    
    m = atoi(argv[2]);
    n = atoi(argv[3]);
    
    while((dirp = readdir(dp)) != 0)
    {
        strcpy(path, argv[1]);
        strcat(path, "/");
        strcat(path, dirp->d_name);
        
        stat(path, &statbuf);
        
        
        if(S_ISREG(statbuf.st_mode) && brojac < n)
        {
            int brLinije = 1;
            f=fopen(path, "r");
            for(int i=0; i<m; i++)
            {
                fgets(linija, 100, f);
                printf("Text sa linije %d: %s\n", brLinije, linija);
                    
                brLinije++;
            }
                
            brojac++;
            fclose(f);
        }
            
        if(brojac == n)
            break;
    }
    
    closedir(dp);
    return 0;
}
