#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

void f_recursiva(DIR *direct, char pathname[], int *reg, int *tamanio){
    struct stat atributos;
    struct dirent *ed;
    DIR *actual;
    char cadena[500];
    ed=readdir(direct);
    while(ed != NULL){
        // Ignorar el . y ..
        if (strcmp(ed->d_name, ".") != 0 && strcmp(ed->d_name, "..") != 0){
            sprintf(cadena,"%s/%s",pathname,ed->d_name);
            if(stat(cadena,&atributos) < 0) {
                printf("\nError al acceder a los atributos");
                perror("\nError en lstat");
                exit(EXIT_FAILURE);
            }
            if ((((atributos.st_mode) & ~S_IFMT) & 011) == 011){
                if ((actual = opendir(cadena)) == NULL)
                    printf("\nError al abrir el directorio %s \n",cadena);
                else
                    f_recursiva(actual, cadena, reg, tamanio);
            }
            else{
                printf("%s %ld \n", cadena, atributos.st_ino);
                if (S_ISREG(atributos.st_mode)){
                    if ((((atributos.st_mode) & ~S_IFMT) & 011) == 011){
                        (*reg)++;
                        (*tamanio) += (int) atributos.st_size;
                    }
                }
            }
        }
        ed=readdir(direct);
    }
    closedir(direct);
}

int main(int argc, char *argv[]){
    DIR *direct;
    char pathname[500];
    int reg=0,tamanio=0;
    if (argc==2){
        strcpy(pathname,argv[1]);
    }
    else{
        strcpy(pathname,".");
    }
    if((direct=opendir(pathname)) == NULL){
        printf("\nError al abrir directorio\n");
        exit(EXIT_FAILURE);
    }
    printf("i-nodos: \n");
    f_recursiva(direct,pathname,&reg,&tamanio);
    printf("Hay %d archivos regulares.\n",reg);
    printf("El tamaño ocupado por los archivos es %d B.\n",tamanio);
    return EXIT_SUCCESS;
}
