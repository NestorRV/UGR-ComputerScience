#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	if(argc != 4) {
		printf("Modo de uso: %s <programa> <simbolo> <archivo>\n\n", argv[0]);
		exit(1);
	} else {
		char *comando, *archivo;
		int fd;

		comando = argv[1];
		archivo = argv[3];

		if (strcmp(argv[2], "<") == 0) {
			//entrada
			fd = open (archivo, O_RDONLY);
			close(STDIN_FILENO);
			if (fcntl(fd, F_DUPFD, STDIN_FILENO) == -1)
				perror ("Error en fcntl");
		} else if (strcmp(argv[2], ">") == 0) {
			//salida
			fd = open (archivo, O_CREAT|O_WRONLY);
			close (STDOUT_FILENO);
			if (fcntl(fd, F_DUPFD, STDOUT_FILENO) == -1) 
				perror ("Error en fcntl");
		} else {
			printf("Debe pasarse \"<\" o \">\" con las comillas %s\n\n", argv[2]);
			exit(1);
		}

	    if((execlp(comando, comando, NULL) < 0)) {
			perror("Error en el execlp\n");
			exit(-1);
		}

		close(fd);
	}
}
