#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <ctype.h>

#define MAX_MSG 80
#define MSG_KEY 10001

struct msgbaffer
{
    long type;
    char text[MAX_MSG];
};

int main()
{
    int msgqid;
    struct msgbaffer bafer;
    FILE* f;
    char procitano[MAX_MSG];
    char konvertovana[MAX_MSG];
    
    msgqid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    
    f=fopen("sredjeno.txt", "w");
    
    do
    {
        msgrcv(msgqid, &bafer, MAX_MSG, 0, 0);
        strcpy(procitano, bafer.text);
        
        if(bafer.type == 1)
        {
            for(int i = 0; i<strlen(procitano); i++)
            {
                konvertovana[i] = toupper(procitano[i]);
            }
        }
        else if(bafer.type == 2)
        {
            for(int i = 0; i<strlen(procitano); i++)
            {
                konvertovana[i] = tolower(procitano[i]);
            }
        }
        fputs(konvertovana, f);
    }
    while(strcmp(procitano, "KRAJ") != 0);
    
    fclose(f);
    
    msgctl(msgqid, IPC_RMID, 0);
    
    return 0;
}
