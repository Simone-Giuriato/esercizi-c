#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]){
    int piped[2];
    int pid1, pid2;
    pipe(piped);
    pid1=fork();
    if(pid1==0){        //figlio
    close(1);
    dup(piped[1]);
    close(piped[1]);
    close(piped[0]);
     execlp("/bin/cat", "cat", "file.txt", NULL); // exec per chiamare il comando cat per file.txt

    }else{
        pid2=fork();
        if(pid2==0){        //secondo figlio
        close(0);
         dup(piped[0]);
        close(piped[0]);
        close(piped[1]);
        execlp("/bin/wc", "wc", "file.txt", NULL);  // exec per chiamare il comando wc (conta righe, parole e caratteri) sul file.txt


        }
        else if(pid2>0){  
            close(piped[1]);
            close(piped[0]);
            return 0;      //padre

        }
    }

}