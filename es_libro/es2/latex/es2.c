/// @file       es2.c
/// @brief      file dell'esercizio 2 del libro pdf
/// @date       26/11/2021
/// @author     Giuriato Simone

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

/**
* @fn           int main()
* @brief        funzione principale che chiede in input un numero e poi crea un processo figlio, successivamente il processo padre somma 10 al numero e il processo figlio somma 15. Fatte le operazioni vengono stampate le due somme
*/
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
