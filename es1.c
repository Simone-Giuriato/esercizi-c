#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

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