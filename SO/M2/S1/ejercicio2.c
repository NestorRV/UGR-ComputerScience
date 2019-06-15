#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

char aux[80];
char bloque[80];
char total[80];
int contador=0;
char pantalla[5];

int main(int argc, char *argv[]){
	int entrada, salida;
	ssize_t r, w;

	if(argc == 1){
		scanf("%s", pantalla);
	}

	if(argc == 2){
		if( (entrada=open(argv[1],O_RDONLY,S_IRUSR|S_IWUSR))<0) {
			printf("\nError %d en open entrada",errno);
			perror("\nError en open entrada");
			printf("\n");
			exit(EXIT_FAILURE);
		}
	}

	if( (salida=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
		printf("\nError %d en open salida",errno);
		perror("\nError en open salida");
		printf("\n");
		exit(EXIT_FAILURE);
	}

	if(lseek(salida,100,SEEK_SET) < 0) {
			perror("\nError en lseek");
			exit(EXIT_FAILURE);
	}

	if(argc == 2){
		r=read(entrada,aux,80);
		while(r!=0){
			contador=contador+1;
			sprintf(bloque, "Bloque %d", contador);
			write(salida, "\n", 1);
			write(salida,bloque, 80);
			write(salida,"\n", 1);
			w=write(salida,aux,(unsigned int) r);
			if(w!=(unsigned int) r) {
				perror("Error en write. \n");
				exit(EXIT_FAILURE);
			}
			r=read(entrada,aux,80);
		}

		if(lseek(salida,0,SEEK_SET) < 0) {
			perror("\nError en lseek");
			exit(EXIT_FAILURE);
		}
		write(salida,"Numero de bloques ", 18);
		sprintf(total, "%d", contador);
		write(salida,total,80);
		write(salida,"\n",1);
	}

	if(argc==1){
		r=read(0,aux,80);
		while(r!=0){
			contador=contador+1;
			sprintf(bloque, "Bloque %d", contador);
			write(salida, "\n", 1);
			write(salida,bloque, 80);
			write(salida,"\n", 1);
			w=write(salida,aux,(unsigned int) r);
			if(w!=(unsigned int) r) {
				perror("Error en write. \n");
				exit(EXIT_FAILURE);
			}
			r=read(0,aux,80);
		}

		if(lseek(salida,0,SEEK_SET) < 0) {
			perror("\nError en lseek");
			exit(EXIT_FAILURE);
		}
		write(salida,"Numero de bloques ", 18);
		sprintf(total, "%d", contador);
		write(salida,total,80);
		write(salida,"\n",1);
	}

	close(entrada);
	close(salida);
	return EXIT_SUCCESS;
}
