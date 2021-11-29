#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int pid;
    int status;
    int numero;
    int somma;
    
    printf("Inserisci un numero\n");
    scanf("%d",&numero);

    pid=fork();
    if(pid==0)
    {
        somma=numero+15;
        printf("\n Ciao sono il figlio e la somma è: %d", somma);
        exit(1);
    }else{
        pid= wait(&status);
        somma=numero+10;
        printf("\n Sono il padre e la somma è: %d\n", somma);
        return 0;



    }
}