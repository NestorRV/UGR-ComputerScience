#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void bloqueardesbloquear(int entero, int orden){
	struct flock cerrojo;
	cerrojo.l_type = orden;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;
	if(fcntl(entero, F_SETLKW, &cerrojo) == -1){
		perror("Error al bloquear en proxy.");
		exit(1);
	}
}

int main(int argc, char *argv[]){
	char buffer[1024];
	int dbloqueo, nbytes;
	FILE *tmp = tmpfile();
	char fifoproxy[256];
	
	//Leemos de STDIN_FILENO y escribimos en el temporal
	while((nbytes = read(STDIN_FILENO,buffer,1024)) > 0){
		fwrite(buffer,sizeof(char),nbytes,tmp);
	}
	
	//Ganar EM en pantalla
	if ((dbloqueo = open("bloqueo",O_RDWR)) == -1){
		perror("Error al abrir bloqueo.");
		exit(1);
	}
	
	//Bloquear pantalla
	bloqueardesbloquear(dbloqueo, F_WRLCK);
	
	//Leer de temporal y escribir en la pantalla
	while(!feof(tmp)){
		//Leemos de temporal
		fread(buffer,sizeof(char),1024,tmp);
		//Escribimos en pantalla
		write(STDOUT_FILENO,buffer,1024);		
	}
	
	//Desbloqueamos
	bloqueardesbloquear(dbloqueo, F_UNLCK);
	
	// Eliminar fifo
	sprintf(fifoproxy,"fifo.%d", getpid());
	unlink(fifoproxy);
	
	exit(0);
}