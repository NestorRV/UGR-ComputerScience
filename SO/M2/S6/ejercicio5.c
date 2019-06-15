#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("Modo de uso: %s <origen> <destino>\n\n", argv[0]);
		exit(1);
	} else {
        struct stat sb;
		char *origen = argv[1], *destino = argv[2];
		int fd_origen, fd_destino, tama;
		char *mem_orig, *mem_dest;

		//Abrimos el fichero de origen
		fd_origen = open(origen, O_RDONLY);
		if (fd_origen == -1) {
			perror("Fallo al abrir el archivo de origen\n");
			exit(1);
		}

		//Obtenemos su stat
        if (fstat (fd_origen, &sb) == -1) {
                printf("Error al hacer stat\n");
                exit(1);
        }

        if (!S_ISREG (sb.st_mode)) {
                printf ("El fichero no es regular\n");
                exit(1);
        }

        //Guardamos el tamaño
        tama = sb.st_size;

        //Creamos el archivo de destino
        umask(0);
		fd_destino = open(destino, O_RDWR|O_CREAT|O_EXCL, S_IRWXU);
		if (fd_destino == -1) {
			perror("Fallo al crear el archivo");
			exit(1);
		}  

		//Asignamos el espacio en el destino
		ftruncate(fd_destino, tama);

		//Creamos el mapa de memoria de origen
		mem_orig = (char *) mmap(0, tama, PROT_READ, MAP_SHARED, fd_origen, 0);
		if(mem_orig == MAP_FAILED) {
			perror("Fallo en mmap (origen)");
			exit(1);
		}

		//Creamos el mapa de memoria de destino
		mem_dest = (char *) mmap(0, tama, PROT_WRITE, MAP_SHARED, fd_destino, 0);
		if(mem_dest == MAP_FAILED) {
			perror("Fallo en mmap (destino)");
			exit(1);
		}
		
		memcpy(mem_dest, mem_orig, tama);
		munmap(mem_orig, tama);
		munmap(mem_dest, tama);
		close(fd_origen);
		close(fd_destino);

		return 0;
	}
}
