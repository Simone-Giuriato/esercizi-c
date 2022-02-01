#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main(){
    int piped[2];
    int pid1;
    int pid2;
    pipe(piped);
    pid1 = fork();
    if (pid1 == 0){
        close(1);
        dup(piped[1]);
        close(piped[1]);
        close(piped[0]);
        execlp("cat", "cat", "File.txt", NULL);
    }else{
        pid2 = fork();
        if (pid2 == 0){
            close(0);
            dup(piped[0]);
            close(piped[0]);
            close(piped[1]);
            execlp("wc", "wc", NULL);
        }
        else{
            close(piped[1]);
            close(piped[0]);
            return 0;
        }
    }
}