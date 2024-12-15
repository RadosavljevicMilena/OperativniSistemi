#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

void rekurzija(char* path, int level)
{
    DIR* dp;
    struct dirent* dirp;
    struct stat statbuf;
    char putanja[30];
    int pid;
    
    if((dp = opendir(path)) == NULL)
    {
        printf("Greska pri otvaranju direktorijuma!\n");
        exit(-1);
    }
    
    while((dirp = readdir(dp)) != NULL)
    {
        if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            continue;
        
        strcpy(putanja, path);
        strcat(putanja, "/");
        strcat(putanja, dirp->d_name);
        
        stat(putanja, &statbuf);
        
        if(S_ISREG(statbuf.st_mode) && strstr(putanja, "log") != 0 && statbuf.st_size > 15*1024)
        {
            if(pid = fork() == 0)
            {
                execlp("rm", "rm", putanja, NULL);
            }
        }
        
        wait(NULL);
        
        if(S_ISDIR(statbuf.st_mode) && level < 2)
        {
            rekurzija(putanja, level+1);
        }
    }
    
    closedir(dp);
    
}

int main(int argc, char* argv[])
{
    rekurzija(argv[1], 0);
    
     return 0;
}
