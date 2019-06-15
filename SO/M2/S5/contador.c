#include <stdio.h>
#include <signal.h>
static int j;
static int contadores[31];

static void handler (int i){
	if (i >= 1 && i <= 31) {
 		contadores[i]++;
 		printf("La señal %d se ha recibido %d veces\n", i, contadores[i]);
 	} else {
 		printf("No puedo manejar la señal %d\n", i);
	}
}

int main(){
	struct sigaction sa;
	sa.sa_handler = handler; // ignora la señal
	sigemptyset(&sa.sa_mask);

	//Reiniciar las funciones
	sa.sa_flags = SA_RESTART;

	for ( j = 1 ; j<=31 ; j++)
		contadores[j] = 0;
	int i;
	for ( i = 1 ; i<=60 ; i++){
		if (sigaction(i, &sa, NULL) == -1){
			printf("Error al intentar establecer el manejador de señal.\n");
		}
	}
	while(1);
}
