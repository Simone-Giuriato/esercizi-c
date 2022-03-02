#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char*argv[])
{
    
    int pid1=0, somma=0;
    char stringhe[100], risultato[100];
    int piped[2];
    pipe(piped);
    if(argc!=2){
        printf("ERRORE !!!\n");
        exit(0);
    }
    do{
        printf("scrivi quale stringa hai il piacere di cercare: ");
        scanf("%s", stringhe);
        pid1=fork();
        if(pid1==0)
        {
            close(0);
            dup(piped[0]);
            close(piped[0]);
            
            close(1);
            dup(piped[1]);
            close(piped[1]);
            execl("/bin/grep", "grep", "-c", stringhe, argv[1], NULL);
            
        }
        read(piped[0],risultato, sizeof(risultato));
        printf("La stringa %s è stata trovata %i volte\n\n",stringhe, atoi(risultato));
        somma= somma+atoi(risultato);


    }while(strcasecmp(stringhe,"Fine")!=0);
    close(piped[1]);
    close(piped[0]);
    printf("Sono state trovate %i stringhe",somma);
    return 0;

}