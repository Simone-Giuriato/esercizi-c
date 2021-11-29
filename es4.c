#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

typedef struct{
    char nome[10];
    char cognome[10];
}Persona_T;
Persona_T Inserisci()
{
    Persona_T persona;
    printf("Inserisci il nome della persona:");
    scanf("%s",persona.nome);
    printf("Inserisci il cognome della persona:");
    scanf("%s",persona.cognome);
    return persona;

}
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
void Maiuscolo(char stringa[100]){
    int i;
    for(i=0; i<strlen(stringa);i++)
    {
        
        stringa[i]= toupper(stringa[i]);

        
    }

}
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