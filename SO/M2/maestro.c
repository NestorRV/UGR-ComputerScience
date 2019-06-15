#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int main(int argc, char *argv[]){
	int fd, fds, fdc, tmp_cli, leidos, proxypid;
	char nombrefifo[50], archSalida[50];
	int contador = 0, bloques_total = 0, bloques_hijo = 0;;
	
	umask(0);
	
	// Guardar los pids de todos los hijos lanzados
	pid_t pids[argc-1];
	
	// Comprobar uso correcto
	if(argc < 2) {
		printf("Uso: ./cliente <d1> <d2> ... <dn>");
		exit(-1);
	}
	
	// Darle nombre al fifo
	sprintf(nombrefifo,"%s", "FIFO");
	
	// Borrar el fifo por si existia
	unlink(nombrefifo);
	
	//Crear el fifo dandoles permisos
	umask(0);
	mkfifo(nombrefifo, 0666);
	
	// Abrir el fifo
	if((fd = open(nombrefifo, O_RDWR)) == -1){
		perror("Error al abrir el fifo");
		exit(1);
	}
	
	// Mientras haya directorios que procesar
	while(contador < argc - 1){
		// Creo un hijo
		pids[contador] = fork();
		
		// Soy hijo
		if(pids[contador] == 0){
			
			// Redirigir salida a fifo
			dup2(fd, STDIN_FILENO); 
			
			// Obtener pid del nuevo proceso
			proxypid = getpid();
			
			// Nombre del archivo de salida
			sprintf(archSalida, "archSalida.%d", proxypid);
			
			// Ejecutar ./cliente con el directorio correspondiente
			execlp("./contar", "contar", argv[contador + 1], archSalida, NULL);
			
			int leidos = 0;
			if((leidos = read(fd, &bloques_hijo, sizeof(int))) < 0){
				perror("Error al leer el numero de bloques_hijo");
				exit(1);
			}
			
			bloques_total += bloques_hijo;
		}
		contador += 1;
	}
	
	unlink(nombrefifo);
	
	printf("La suma de los bloques de todos los archivos regulares de todos los directorio dados como argumentos es %d. \n", bloques_total);
	
	return(0);
}