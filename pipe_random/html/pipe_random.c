/// @file       pipe_random.c 
/// @brief      programma che permette, la somma di 10 numeri generati randomicamente con l'utilizzo di due pipe e comunicando tra proccessi
/// @date       16/12/2021
/// @author     Giuriato Simone

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
/**
* @fn           int main()
* @brief        funzione principale che crea due pipe, successivamente istanzia il processo padre che genera 10 numeri casuali e li passa al figlio utilizzando le pipe. Successivamente il processo figlio li somma e passa la somma al padre, il quale stampera' il risultato.
*/ 

int main(){
    int canale1[2], canale2[2];
    pipe(canale1);
    pipe(canale2);
    int numeri[10];
    int somma;
    int pid;
    pid=fork();
    if(pid>0)
    {
        srand(time(0));/*inizializzamo il generatore sull'ora attuale
        dell'elaboratore time(0), in questo modo si hanno 
        valori diversi*/
        for(int i=0;i<10; i++)
        {
        numeri[i]=1+rand()%100; //numeri casuali tra 1 e 100
        //printf("valore: %d\n", numeri[i]);
        }
        close(canale1[0]);  //scive solo sul canale1
        close(canale2[1]); //legge solo sul canale2
        write(canale1[1], numeri, sizeof(numeri));
        read(canale2[0], &somma, sizeof(int));
        printf("Questa è la somma fatta dal figlio: %d\n", somma);
        return 0;


    }else
    {
        
        close(canale1[1]); //legge solo sul canale1
        close(canale2[0]);  //scrive solo sul canale2
        read(canale1[0], numeri,sizeof(numeri));
        for (int i = 0; i < 10; i++)
        {
            somma=somma + numeri[i];        
        }
        write(canale2[1], &somma, sizeof(int));
        exit(1);

    }
}
