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
   int pid;
   int msgqid;
   struct msgbafer bafer;
   int broj;
   char pom[MAX_MSG];
   
   msgqid = msgget(MSG_KEY, 0666 | IPC_CREAT);
   
   pid = fork();
   
   if(pid < 0)
   {
       printf("Greska pri kreiranju dodatnog procesa!\n");
       exit(-1);
   }
   
   if(pid == 0)
   {
       //dete
       if(execl("jun221a", "jun221a", NULL) < 0 )
       {
           printf("Greska pri pozivanju drugog programa!\n");
           exit(-1);
       }
   }
   
   for(int i=0; i<10; i++)
   {
       printf("Unesite visecifreni broj:\n");
       scanf("%d", &broj);
       
       if(broj < 10)
       {
           printf("Nevalidno! Molim vas unesite visecifreni broj!\n");
           continue;
       }
       
       sprintf(pom, "%d", broj);
       
       bafer.type = 1;
       strcpy(bafer.text, pom);
       
       msgsnd(msgqid, &bafer, MAX_MSG, 0);
   }
   
   wait(NULL);
   
   msgctl(msgqid, IPC_RMID, 0);
   
   return 0;
}
