/// @file   gerarchia.c
/// @date   18/11/2021
/// @brief  programma dove un padre genera due figli, i quali generano altri due figli F1--> G1+H1
/// @author: Giuriato Simone

/**
* @fn       int main()
* @brief    padre genera due figli, i quali generano altri due figli F1--> G1+H1
*/
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
int main()
{
    int pid, F1, G1, H1, F2, G2, H2;
    int status;

    F1 = fork();
    if (F1 == 0)
    {
        printf("Ciao sono: F1 con pid:%i\n",getpid());
        G1 = fork();
        if (G1 == 0)
        {
            printf("Ciao sono:G1, il primo figlio di F1 con pid: %i \n",getpid());
            sleep(1);
            exit(0);
        }
        else
        {
            H1 = fork();
            {
                if (H1 == 0)
                {
                    printf("Ciao sono:H1, il secondo figlio di F1 con pid: %i\n",getpid());
                    sleep(1);
                    exit(1);
                }
            }
        }
    }
    else
    {
        pid = waitpid(H1, &status, 0);
        sleep(4);
        printf("Sono io il Padre di F1 con pid:%i\n",getpid());
        F2 = fork();
        if (F2 == 0)
        {
            printf("Ciao sono:F2 con pid: %i\n",getpid());
            G2 = fork();
            if (G2 == 0)
            {
                printf("Ciao sono:G2, il primo figlio di F2 con pid: %i\n",getpid());
                sleep(1);
                exit(2);
            }
            else
            {
                H2 = fork();
                if (H2 == 0)
                {
                    printf("Ciao sono:H2,il secondo figlio di F2 con pid: %i\n",getpid());
                    sleep(1);
                    exit(3);
                }
            }
        }
        else
        {
            waitpid(H2, &status, 0);
            sleep(1);
            printf("Sono il padre di F2 con pid: %i \n",getpid());
            return 0;
        }
    }
}
