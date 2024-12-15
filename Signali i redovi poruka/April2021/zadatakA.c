#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MSG_KEY 10001
#define MAX_MSG 80

struct msgbaf
{
    long type;
    char text[MAX_MSG];
};



int main(int argc, char* argv[])
{
    
    if(argc < 2)
    {
        printf("Nedovoljno argumenata!\n");
        exit(-1);
    }
    
    int pid;
    int msgqid;
    struct msgbaf bafer;

    FILE* f;
    
    char poruka[MAX_MSG];
    
    msgqid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    
    pid = fork();
    
    if(pid < 0)
    {
        printf("Doslo je do greske pri kreiranju dodatnog procesa!\n");
        exit(-1);
    }
    
    if(pid != 0)
    {
        f = fopen(argv[1], "r");
        
        int pom=0; 
        
        while(fgets(poruka, MAX_MSG , f))
        {
            strcpy(bafer.text, poruka);
            bafer.type = 1;
            
            msgsnd(msgqid, &bafer, MAX_MSG, 0);
            
            pom++;
        }
        
        strcpy(bafer.text, "END");
        msgsnd(msgqid, &bafer, MAX_MSG, 0);
        
        fclose(f);
        
        wait(NULL);
        
        for(int i=0; i<pom; i++)
        {
            msgrcv(msgqid, &bafer, MAX_MSG, 0, 0);
            
            printf("U liniji %ld, nalazi se %s velikih slova\n", bafer.type, bafer.text);
        }
        
        msgctl(msgqid, IPC_RMID, 0);
        
        return 0;
        
    }
    else if(pid == 0)
    {
        if(execl("april21a", "april21a", NULL) < 0)
        {
            printf("Greska prilikom pozivanja drugog programa!\n");
            exit(-1);
        }
    }
    
}
