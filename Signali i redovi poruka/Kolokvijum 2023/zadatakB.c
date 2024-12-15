/*1. Korišćenjem programskog jezika C napisati Linux program koji kreira dodatni proces dete. Roditelj generiše slučajne brojeve u opsegu od 0 do 999 i korišćenjem reda poruka šalje procesu detetu.  Brojevi se šalju sa pridruženim prioritetom pri čemu jednocifreni brojevi imaju prioritet 1, dvocifreni  prioritet 2, a trocifreni prioritet 3. Proces dete sumira primljene brojeve u tri različite sume (za svaki  prioritet zasebna suma) tako što sumiranje imaju brojevi prioriteta 1, zatim brojevi prioriteta 2 a tek  na kraju brojevi prioriteta 3. Proces dete sumiranje prekida kada zbir sve tri sume pređe vrednost  50000. O prekidu sumiranja proces dete korišćenjem istog reda poruka obaveštava proces roditelj  kako bi prekinuo generisanje brojeva. (25 poena) */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
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
    int msgqid;
    struct msgbuff bafer;
    int broj;
    int suma1 = 0;
    int suma2 = 0;
    int suma3 = 0;
    int total_sum = 0;
    
    msgqid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    
    do
    {
        msgrcv(msgqid, &bafer, MAX_MSG, 0, 0);
        
        broj = atoi(bafer.text);
        
        printf("Primljen broj %d sa prioritetom: %ld\n", broj, bafer.type);
        
        if(bafer.type == 1)
            suma1 += broj;
        else if(bafer.type == 2)
            suma2 += broj;
        else if(bafer.type == 3)
            suma3 += broj;
        
        total_sum += broj;
        
        printf("Suma: %d\n", total_sum);
        
        if(total_sum >= 50000)
        {
            strcpy(bafer.text, "KRAJ");
            bafer.type = 5;
            msgsnd(msgqid, &bafer, MAX_MSG, 0);
            break;
        }
        else
        {
            strcpy(bafer.text, "Nastavi");
            bafer.type = 5;
            msgsnd(msgqid, &bafer, MAX_MSG, 0);
        }
    }
    while(total_sum <= 50000);
    
    msgctl(msgqid, IPC_RMID, 0);
    
    return 0;
}
