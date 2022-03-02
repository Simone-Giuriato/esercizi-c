
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("ERRORE!!!");
        exit(0);
    }
    char  codice[5];
    char stringa[100];
    int p1p0[2];
    int pid1=0;
    int tot=0;
    
    do{
        printf("Inserisci codice da verificare:");
        scanf("%s",codice);
        if(strcasecmp(codice,"esci")!=0)
        {
            pipe(p1p0);
            pid1=fork();
            if(pid1==0)
            {
                close(p1p0[0]);
                close(1);
                dup(p1p0[1]);
                close(p1p0[1]);
                
                execlp("/bin/grep", "grep", "-c",strcat(codice, " insoluto"), argv[1], NULL);
            }
            read(p1p0[0],stringa, sizeof(stringa));
            close(p1p0[1]);
            close(p1p0[0]);
            printf("Sono stati trovati %d insoluti\n", atoi(stringa));
            tot = tot + atoi(stringa);


        }

    }while(strcasecmp(codice,"esci")!=0);
    return 0;
}