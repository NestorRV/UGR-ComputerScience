#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
//Usar variables bool
#include <stdbool.h>

bool par(int numero) {
	return numero % 2 == 0;
}

bool divisible(int numero) {
    return numero % 4 == 0;
}

int main(int argc, char *argv[]) {
    int numero;
    pid_t pid;

    if(argc!=2) {
        printf("Modo de uso: %s <entero>\n\n", argv[0]);
        exit(1);
    }

    numero=atoi(argv[1]);

    if((pid=fork())<0){
        printf("\nError %d al realizar fork",errno);
        perror("\nError en el fork");
        exit(EXIT_FAILURE);
    }
    //Hijo
    else if(pid==0){
        if (par(numero))
            printf("El numero %d es par\n",numero);
        else
            printf("El numero %d no es par\n",numero);
    }
    //Padre
    else {
        if (divisible(numero))
            printf("El numero %d es divisible por 4\n",numero);
        else
            printf("El numero %d no es divisible por 4\n",numero);
    }
    return EXIT_SUCCESS;
}
