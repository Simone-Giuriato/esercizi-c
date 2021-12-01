
/// @file       es1.c
/// @brief      file dell'esercizio 1 del libro pdf
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
* @brief        funzione principale, creazione di un processo figlio, e stampa a schermo i pid del figlio e del padre con getpid().   
*/
int main(){
    int pid;
    int status;
    int pidFiglio;
    int padre;
    padre = getpid();
    pid = fork();
    if (pid == 0){
        pidFiglio = getpid();
        printf("Il mio pid e': %d", pidFiglio);
        exit(0);
    }
    else{
        pid = wait(&status);
        printf("\n Il pid del padre e': %d", padre);
        return 0;
    }
}
