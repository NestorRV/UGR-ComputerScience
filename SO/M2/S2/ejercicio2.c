#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[]){
   DIR *directorio;
   int permisos;
   struct stat atributos;
   struct dirent *ed;
   char aux[100];
   umask(0);
   if (argc!=3){
      printf("Introduzca: pathname - permisos (numero en octal)\n");
      exit(-1);
   }
   else{
      directorio=opendir(argv[1]);
      permisos=strtol(argv[2],NULL,8);
   }
   //Leo
   ed=readdir(directorio);
   //Mientras no he terminado de leer
   while(ed!=NULL){
      //Guardo en aux el directorio donde tengo que trabajar
      sprintf(aux,"%s/%s",argv[1],ed->d_name);
      if(stat(aux,&atributos) < 0){
         printf("\nError %d al acceder a los atributos",errno);
		 perror("\nError en lstat");
		 printf("\n");
		 exit(EXIT_FAILURE);
      }
      //Cambio los permisos permisos solo si es un archivo regular
      //para no cambiar los permisos a . y ..
      if(S_ISREG(atributos.st_mode)){
         printf("%s%s%o",ed->d_name," Antiguos: ",atributos.st_mode);
         chmod(aux,permisos);
         if(chmod(aux,permisos) != 0) {
            printf("\nError %d",errno);
            printf("\n");
         }
         else{
            stat(aux,&atributos);
            printf(" Nuevos: %o \n",atributos.st_mode);
         }
      }
      ed=readdir(directorio);
   }
   closedir(directorio);
   return EXIT_SUCCESS;
}
