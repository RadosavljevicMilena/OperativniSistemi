#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_MSG 80
#define MSG_KEY 10001

struct msgbaffer
{
    long type;
    char text[MAX_MSG];
};

int main()
{
    int pid1, pid2;
    int msgqid;
    struct msgbaffer bafer;
    FILE* f;
    char procitano[80];
    int linija = 1;
    
    msgqid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    
    pid1 = fork();
    
    if(pid1 < 0)
    {
        printf("Doslo je do greske prilikom kreiranja procesa deteta!\n");
        exit(-1);
        
    }
    if(pid1 == 0) //dete
    {
        if(execl("prvisept23a","prvisept23a", NULL) < 0)
        {
            printf("Problem pri pokretanju drugog programa!\n");
            exit(-1);
        }
    }
    
    pid2 = fork();
    
    if(pid2 < 0)
    {
        printf("Doslo je do greske prilikom kreiranja procesa deteta!\n");
        exit(-1);
        
    }
    if(pid2 == 0) //dete
    {
        if(execl("prvisept23a","prvisept23a", NULL) < 0)
        {
            printf("Problem pri pokretanju drugog programa!\n");
            exit(-1);
        }
    }
    
    
    f=fopen("poruka.txt", "r");
    
    while(fgets(procitano, MAX_MSG, f) != NULL)
    {
        strcpy(bafer.text, procitano);
        
        if(linija %2 != 0)
        {
            bafer.type = 1;
        }
        if(linija %2 == 0)
        {
            bafer.type = 2;
        }
        
        msgsnd(msgqid, &bafer, MAX_MSG, 0);
        
        linija++;
    }
    strcpy(bafer.text, "KRAJ");
    bafer.type = 1;
    msgsnd(msgqid, &bafer, MAX_MSG, 0);
    bafer.type = 2;
    msgsnd(msgqid, &bafer, MAX_MSG, 0);
    
    
    fclose(f);
    
    wait(NULL);
    wait(NULL);
    
    msgctl(msgqid, IPC_RMID, 0);
    
    return 0;
    
}
