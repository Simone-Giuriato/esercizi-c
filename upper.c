#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include<sys/wait.h>

void Maiuscolo(char stringa[]){
    int i;
    for(i=0;i<strlen(stringa);i++){
        stringa[i]=toupper(stringa[i]);
    }

}

int main(int argc, char *argv[])
{
        char stringa[strlen(argv[1])];
    int pid = fork();
    if(pid==0)
    {
        strcpy(stringa,argv[1]);
        Maiuscolo(stringa);
        printf("la stringa in maiuscolo è: %s\n\n", stringa);
        exit(1);
    }else
    {
        wait(&pid);

    }
    return 0;
}
