#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>


    int main()
    {
        int pid1, pid2, pid3, p1p2[2], p2p3[2], p3p0[2];
        double totale=0;
        char buffer[1], *ptr, strimporto[100];

        pipe(p1p2);
        pid1=fork();
        if(pid1==0)     //figlio 1
        {
            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);
            execlp("/bin/cat", "cat", "traceroute.txt", NULL);
            return -1;
        } else
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
                execlp("/usr/bin/awk", "awk", "{print $4}", NULL);          
                return -1;
            }else          
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
                    execlp("/bin/tail", "tail", "-n","+2",NULL);
                    return -1;                   
                }
                  ///chiudo canali che non mi servono di tutte le pipe  (Padre)
                                 
                    close(p2p3[1]);
                    close(p2p3[0]);
                    close(p1p2[0]);
                    close(p1p2[1]);
                    close(p3p0[1]);

                    //while(read(p2p0[0], buffer, 1) > 0){

                    //}
            }
        }

        
        return 0;
}