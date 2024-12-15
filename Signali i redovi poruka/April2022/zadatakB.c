#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 10001
#define MAX_MSG 20

struct msgbaf
{
   long type;
   char text[MAX_MSG];
};

int main()
{
    int msgqid;
    struct msgbaf bafer;
    int parni = 0, neparni = 0;
    int broj;
    
    msgqid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    
    do
    {
       if( msgrcv(msgqid, &bafer, MAX_MSG, 0, 0) < -1)
       {
           printf("Doslo je do greske prilikom prijema poruke!\n");
           exit(-1);
       }
        
        broj = atoi(bafer.text);
        
        if(strcmp(bafer.text, "-1") == 0)
        {
            printf("Prosledjeno je %d parnih i %d neparnih brojeva\n", parni, neparni);
            break;
        }
        
        if(broj % 2 == 0)
        {
            parni++;
        }
        else
        {
            neparni++;
        }
        
        printf("%d\n", broj);
        
    }
    while(strcmp(bafer.text, "-1") != 0);

    msgctl(msgqid, IPC_RMID, 0);
    
    return 0;
}
