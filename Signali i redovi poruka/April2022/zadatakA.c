#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MSG_KEY 10001
#define MAX_MSG 20

struct msgbaf
{
   long type;
   char text[MAX_MSG];
};

int main()
{
    int pid;
    int msgqid;
    struct msgbaf bafer;
    int N;
    int randBr;
    
    pid = fork();
    
    if(pid < 0)
    {
        printf("Doslo je do greske prilikom kreiranja dodatnog procesa!\n");
        exit(-1);
    }
    
    if(pid == 0)
    {
        if(execl("april22a", "april22a", NULL) < 0)
        {
            printf("Doslo je do greske prilikom pozivanja drugog programa!\n");
            exit(-1);
        }
    }
    
    msgqid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    
    N = rand() % 20;
    bafer.type = 1;
    
    for(int i = 0; i < N; i++)
    {
        randBr = rand() % 100;
        sprintf(bafer.text, "%d", randBr);
        
        if(msgsnd(msgqid, &bafer, MAX_MSG, 0) < -1)
        {
            printf("Doslo je do greske prilikom slanja poruke!\n");
            exit(-1);
        }
    }
    
    sprintf(bafer.text, "%d", -1);
    
    if(msgsnd(msgqid, &bafer, MAX_MSG, 0) < -1)
    {
        printf("Doslo je do greske prilikom slanja poruke!\n");
        exit(-1);
    }
    
    wait(NULL);
    
    msgctl(msgqid, IPC_RMID, 0);
    
    return 0;
}
