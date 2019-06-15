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
#include <dirent.h>

//Macros para ver los permisos
#define S_IXUSR2(mode) (((mode)&S_IFMT) == S_IXUSR)
#define S_IXGRP2(mode) (((mode)&S_IFMT) == S_IXGRP)

int main(int argc, char *argv[]){
	int fd, num_bloques = 0;
	char archSalida[50];
	pid_t pid;
	DIR *directorio;
	struct stat atributos;
	struct dirent *ed;
	char aux[100];
	umask(0);
	
	// Comprobar uso correcto
	if(argc != 3) {
		printf("Uso: ./contar <directorio> <archivo_salida>. \n");
		exit(-1);
	}
	
	// Darle nombre a fichero
	sprintf(archSalida,"%s",argv[2]);
	
	// Abrir el archivo
	if((fd = open(archSalida, O_RDWR|O_CREAT, S_IRWXU)) == -1){
		perror("Error al abrir el archivo de salida");
		exit(1);
	}
	
	// Abrir el directorio
	if((directorio = opendir(argv[1])) < 0){
		perror("Error al abrir el directorio");
		exit(1);
	}
	
	// Leo
	ed=readdir(directorio);
	// Mientras no he terminado de leer
	while(ed!=NULL){
		// Guardo en aux el archivo donde tengo que trabajar
		sprintf(aux,"%s/%s",argv[1],ed->d_name);
		if(stat(aux,&atributos) < 0){
			printf("\nError %d al acceder a los atributos",errno);
			perror("\nError en lstat");
			printf("\n");
			exit(EXIT_FAILURE);
		}
		// Comprubo si es regular, si tiene permisos de ejecucion para el propietario
		// y si tiene permisos de ejecucion para el grupo
		if(S_ISREG(atributos.st_mode) && S_IXUSR2(atributos.st_mode) && S_IXGRP2(atributos.st_mode)){
			// Escribir el archivo entero en archSalida
			
			// Calcular el numero de bloques
			num_bloques += (int) atributos.st_size;
		}
		ed=readdir(directorio);
	}
	
	// Cierrro el directorio
	closedir(directorio);
	
	// Escribir el numero de bloques ocupados por todos los archivos regulares
	write(STDOUT_FILENO, &num_bloques, sizeof(int));	
	
	return(0);
}