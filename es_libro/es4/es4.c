
/// @file       es4.c
/// @brief      file dell'esercizio 4 del libro pdf
/// @date       26/11/2021
/// @author     Giuriato Simone

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

/**
* @brief    struct Persona_T: struct formata da un nome e un cognome
* @param    char nome[10]: nome della persona
* @param    char cognome[10]: cognome della persona
*/
typedef struct{
    char nome[10];
    char cognome[10];
}Persona_T;
/**
* @fn       Persona_T Inserisci()
* @brief    funzione che permette l'inserimento delle credenziali della persona dall'utente
*/
Persona_T Inserisci()
{
    Persona_T persona;
    printf("Inserisci il nome della persona:");
    scanf("%s",persona.nome);
    printf("Inserisci il cognome della persona:");
    scanf("%s",persona.cognome);
    return persona;

}
/**
* @fn       void Trasformazione(char stringa[100])
* @brief    funzione che permette di trasformare la prima lettara in maiuscolo e tutte le altre in minuscolo
* @param    char stringa[100]: stringa da convertire
*/
void Trasformazione(char stringa[100])
{
    int i;
    for(i=0; i<strlen(stringa);i++)
    {
        if(i==0){
            stringa[i]= toupper(stringa[i]);

        }else
        {
            stringa[i]= tolower(stringa[i]);

        }
    }
}
/**
* @fn       void Maiuscolo(char stringa[100])
* @brief    funzione che permette di convertite tutta la stringa in maiuscolo
* @param    char stringa[100]: stringa da convertire
*/
void Maiuscolo(char stringa[100]){
    int i;
    for(i=0; i<strlen(stringa);i++)
    {
        
        stringa[i]= toupper(stringa[i]);

        
    }

}
/**
* @fn       int main()
* @brief    funzione principale, istanzia un processo figlio e il padre permette di leggere un nome ed un cognome, che verranno poi convertiti con la funzione Trasformazione e scritti in un file. Il file verra' poi eliminato (con remove()). Il figlio contemporaneamente legge quello che c'e' dentro il file e lo stampa a schermo, solo dopo aver convertito il nome e il cognome usando la funzione Maiuscolo    
*/
int main()
{
    Persona_T persona;
    int pid,status;
    FILE*file;
    file=fopen("prova.txt","w+");

    pid=fork();
    if(pid==0)
    {
        sleep(7);
        rewind(file);
        fscanf(file,"%s %s", persona.nome, persona.cognome);
        Maiuscolo(persona.nome);
        Maiuscolo(persona.cognome);
        printf("%s %s\n", persona.nome, persona.cognome);

        exit(1);
    }else{
        persona=Inserisci();
        
        Trasformazione(persona.nome);
        Trasformazione(persona.cognome);
        fprintf(file,"%s %s", persona.nome, persona.cognome);
        fclose(file);
        remove("prova.txt");
        wait(&pid);

        return 0;
       


    }
}
