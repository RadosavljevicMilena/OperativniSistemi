#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define message_key 10001
#define max_message 80

struct msgbuff

{

    long type;

    char text[max_message];

};

int main()
{
    int msgqid;

    struct msgbuff bafer;

    char poruka[max_message];

    msgqid=msgget(message_key, 0666 | IPC_CREAT);

    int broj;

    int linija=1;
    
    do
    {
        broj = 0;
        
        msgrcv(msgqid, &bafer, max_message, 0, 0);
        
        strcpy(poruka, bafer.text);
    
        if(strcmp(poruka, "END") == 0)
            break;
        
        for(int i=0; i<strlen(poruka)+1; i++)
        {
            if(poruka[i] >= 'A' && poruka[i] <= 'Z')
            {
                broj++;
            }
        }
        
        
        char brojLinija[10];
        sprintf(brojLinija, "%d", broj);
                
        bafer.type = linija;
        strcpy(bafer.text, brojLinija);
        
        msgsnd(msgqid, &bafer, max_message, 0);
        
        linija++;
        
    }
    while(strcmp(poruka, "END") != 0);
    
    return 0;
}
