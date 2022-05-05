#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char*argv[]){
    
    if(argc != 17){
        printf("Errore nei parametri (sono 16). Inserire uno spazio tra ogni numero!!!\n");
        exit(0);
    }

    int somma = 0;
    int numero = 0;
    
    
    for(int i = 1; i < 17; i++){
        numero = atoi(argv[i]);
        if(i % 2 == 0){
            somma = somma + (numero * 2);
        }
        else{
            somma = somma + numero;
        }
    }

    if(somma%10 == 0){
        printf("La somma delle cifre è: %d",somma);
        printf("\nIl Codice PAN è valido.\n");
        exit(1);
    }
    else{
        printf("La somma delle cifre è: %d",somma);
        printf("\nIl Codice Pan non è valido.\n");
    }

    return 0;
}