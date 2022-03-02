#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char*argv[]){
    int pid1, pid2;
    int fd;
    int p1p2[2]; 
    int p2p0[2];
    pipe(p1p2);
    pid1=fork();
    if(pid1==0){            //figlio 1
        close(1);
        dup(p1p2[1]);
        close(p1p2[1]);
        close(p1p2[0]);
        execlp("/bin/cat","cat","file.txt", NULL);
    }else{
    pipe(p2p0);
    pid2=fork();        //figlio 2
    if(pid2==0){
        close(0);
        
        dup(p1p2[0]);
        close(p1p2[0]);
        close(p1p2[1]);
        close(1);
        dup(p2p0[1]);
        close(p2p0[0]);
        close(p2p0[1]);
        execlp("/bin/wc","wc",NULL);

    }else{
        close(0);
        dup(p2p0[0]);
        close(p2p0[0]);
        close(p2p0[1]);
        close(p1p2[1]);
        close(p1p2[0]);
       
        fd=open("wc.txt", O_RDWR | O_CREAT, 0777);      //open con flag e permessi(0777)
        close(1);
        dup(fd);

        close(fd);
        
        execlp("/bin/tee", "tee", NULL);            //comando tee legge e scrive 
        return 0;
           

    }

    }

}