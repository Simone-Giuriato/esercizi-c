#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int pid1=0;
    int pid2=0;
    int pid3=0;
    int somma=0;
    int p1p2[2];
    int p2p3[2];
    int p3p0[2];
    char stringhe[100], risultato[1000];
     if(argc!=2){
        printf("ERRORE !!!\n");
        exit(0);
    }
    do{
        printf("\nQuale stringa vuoi cercare?");
        scanf("%s",stringhe);
        
        pipe(p1p2);
        pid1=fork();
        if(pid1==0)     //figlio 1
        {
            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);
            execlp("/bin/cat", "cat", argv[1], NULL);
            return -1;
        }
        else
        {
            pipe(p2p3);
            pid2=fork();
            if(pid2==0)     //secondo figlio
            {
                close(0);
                dup(p1p2[0]);           //leggo dalla pipe p1p2 
                close(p1p2[0]);
                close(1);
                dup(p2p3[1]);           //scrivo nella pipe p2p3
                close(p2p3[1]);
                                    //chiusura canali che rimangono aperti e che non mi servono
                close(p1p2[1]);
                close(p2p3[0]);
                execlp("/bin/grep", "grep", "-o", stringhe, NULL);          //-o conta doppioni
                return -1;

            }
            else          
            {
                pipe(p3p0);
                pid3=fork();
                if(pid3==0)
                {
                    close(0);
                    dup(p2p3[0]);
                    close(p2p3[0]);
                    close(1);
                    dup(p3p0[1]);
                    close(p3p0[1]);
                    close(p1p2[0]);
                    close(p1p2[1]);
                    close(p2p3[1]);
                    close(p3p0[0]);
                    execlp("/bin/wc", "wc", "-l",NULL);         //-l conta linee nche ha scritto la grep
                   
                }
                    ///chiudo canali che non mi servono di tutte le pipe
                                 
                    close(p2p3[1]);
                    close(p1p2[0]);
                    close(p1p2[1]);
                    close(p3p0[1]);
                    close(p2p3[0]);

                    
                    read(p3p0[0], risultato, sizeof(risultato));
                    close(p3p0[0]);
                    
                    printf("\nLa stringa %s è stata trovata %i volte\n", stringhe, atoi(risultato));
                    somma=somma+atoi(risultato);
                
            }
        }

        

    }while(strcasecmp(stringhe,"Fine")!=0);
    
    printf("Sono state trovate %i stringhe", somma);
    return 0;
}