#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_KEY 10001
#define MAX_MSG 20

struct msgbafer
{
    long type;
    char text[MAX_MSG];
};

int main()
{
   int msgqid;
   struct msgbafer bafer;
   int broj;
   int sum;
   int cifra;
   int pom;
   
   msgqid = msgget(MSG_KEY, 0666 | IPC_CREAT);
   
   for(int i=0; i<10; i++)
   {
       msgrcv(msgqid, &bafer, MAX_MSG, 0, 0);
       
       sum = 0;
       broj = atoi(bafer.text);
       pom = broj;
       
       while(broj > 0)
       {
           cifra = broj % 10;
           sum += cifra;
           
           broj/=10;
       }
       
       printf("Suma cifara broja %d je %d\n", pom, sum);
   }
   
   msgctl(msgqid, IPC_RMID, 0);
   
   return 0;
}
