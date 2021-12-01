/// @file       es3.c
/// @brief      file dell'esercizio 3 del libro pdf
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
* @brief        funzione principale che crea tre processi figli, i quali stamperanno "Ciao, io sono Qui", "Ciao, io sono Quo", "Ciao, io sono Qua"
*/
int main(){
    int pid;
    int pid1;
    int pid2;
    int status;
    pid=fork();
    if(pid==0){
        printf("Ciao, io sono Qui \n");
        exit(1);
    }
    else{
        pid1=fork();
        if(pid1==0){
            printf("Ciao, io sono Quo \n");
            sleep(1);
            exit(2);

        }
         else{
        pid2=fork();
        if(pid2==0){
            printf("Ciao, io sono Qua \n");
            sleep(1);
            exit(3);

        }
        else{
            waitpid(pid2, &status, 0);
            return 0;
        }

    }
	}
   

}
