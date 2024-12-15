#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <string.h>

#define MSG_KEY 10001
#define MAX_MSG 20

struct msgbuff
{
    long type;
    char text[MAX_MSG];
};

int main()
{
    int pid;
    int msgqid;
    struct msgbuff bafer;
    int broj;
    char pom[MAX_MSG];
    char prekid[MAX_MSG] = "";
    
    msgqid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    
    pid = fork();
    
    if(pid == 0)
    {
       if(execl("kol23a", "kol23a", NULL) < 0)
       {
           printf("Greska pri pozivanju drugog programa!\n");
           exit(-1);
       }
    }
    
    do
    {
        broj = rand() % 1000;
        sprintf(pom, "%d", broj);
        strcpy(bafer.text, pom);
        
        if(broj <10)
            bafer.type = 1;
        else if(broj < 100)
            bafer.type = 2;
        else if(broj < 1000)
            bafer.type = 3;
        
        msgsnd(msgqid, &bafer, MAX_MSG, 0);
        
        if(msgrcv(msgqid, &bafer, MAX_MSG, 5, 0) > 0)
        {
            strcpy(prekid, bafer.text);
        }
        else
            continue;
    }
    while(strcmp(prekid, "KRAJ") != 0);
    
    wait(NULL);
    
    msgctl(msgqid, IPC_RMID, 0);
    
    return 0;
}
