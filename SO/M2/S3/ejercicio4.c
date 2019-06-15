#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(){
	int i, estado;
	pid_t pid[5];
	int contador=4;
	//CREAMOS HIJOS
	for(i=0; i<5; i++){
		if((pid[i] = fork())<0){
			printf("\nError %d al realizar fork",errno);
			perror("Error en fork\n");
			exit(-1);
		}
		//Hijos
		if(pid[i]==0){
			printf("Soy el hijo PID = %i\n", getpid());
			exit(0);
		}
	}

	for (int i = 0;i<5;i++) {
		if (waitpid(pid[i],0,0) > 0) {
	    	printf("Acaba de finalizar mi hijo con PID: %d\n",pid[i]);
	    	printf("Solo me quedan %d hijos vivos\n", contador);
			contador = contador - 1;
    	}
	}
/*
	//Esperamos a que se cierren primero los impares
	for (int i = 0;i<5;i = i + 2) {
		if (waitpid(pid[i],0,0) > 0) {
	    	printf("Acaba de finalizar mi hijo con PID: %d\n",pid[i]);
	    	printf("Solo me quedan %d hijos vivos\n", contador);
			contador = contador - 1;
		}
	}
	//Esperamos a que se cierren despues los pares
	for (int i = 1;i<5;i = i + 2) {
		if (waitpid(pid[i],0,0) > 0) {
	    	printf("Acaba de finalizar mi hijo con PID: %d\n",pid[i]);
	    	printf("Solo me quedan %d hijos vivos\n", contador);
			contador = contador - 1;
		}
	}
*/
	return 0;
}
