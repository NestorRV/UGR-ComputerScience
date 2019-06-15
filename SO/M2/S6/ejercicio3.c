#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	struct flock cerrojo;
	int fd, i;

	if(argc != 2) {
		printf("Modo de uso: %s <archivo>\n", argv[0]);
		exit(1);
	} else {
		//Nombre del archivo
		char *archivo = argv[1];

		//Abrimos el archivo
		if ((fd=open(archivo, O_RDWR)) == -1 ){
			perror("Fallo al abrir el archivo");
			return 0;
		}

		cerrojo.l_type=F_WRLCK;
		cerrojo.l_whence=SEEK_SET;
		cerrojo.l_start=0;
		//Bloquear archivo entero
		cerrojo.l_len=0;
		
		//Intentamos un bloqueo de escritura del archivo
		printf ("Intentando bloquear %s\n", archivo);
		if (fcntl (fd, F_SETLKW, &cerrojo) == EDEADLK) {
			//Si el cerrojo falla, pintamos un mensaje
			printf ("El cerrojo ha fallado");
		}

		//El bloqueo tiene exito -> procesar el archivo
		printf ("Procesando el archivo %s\n", archivo);

		//sleep para lanzar otra vez el programa
		for (i = 0; i < 10; i++) {
			sleep(1);
		}
		
		//Desbloqueamos el archivo
		cerrojo.l_type=F_UNLCK;
		cerrojo.l_whence=SEEK_SET;
		cerrojo.l_start=0;
		cerrojo.l_len=0;
		if (fcntl (fd, F_SETLKW, &cerrojo) == -1) {
			perror ("Error al desbloquear");
		}
		
		return 0;
	}
}