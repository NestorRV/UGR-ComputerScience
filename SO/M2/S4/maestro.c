#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd1[2], fd2[2], leido, leido2, val1, val2;
    int inicio, final, inicio2, final2, inicio3, final3;
    pid_t esclavo1, esclavo2;
    char aux[10], aux2[10];

    if (argc < 3) {
        perror("Uso: ./maestro inicio fin.\n");
        exit(-1);
    }

    inicio = atoi(argv[1]);
    final = atoi(argv[2]);
    inicio2 = inicio;
    final2 = ((final + inicio) / 2) - 1;
    inicio3 = final2 + 1;
    final3 = final;

    pipe(fd1);
    pipe(fd2);
    printf("Primos entre %d y %d:\n", inicio, final);

    esclavo1 = fork();
    //Guardo en aux y en aux2 el intervalo del esclavo 1.
    sprintf(axu, "%d", inicio2);
    sprintf(aux2, "%d", final2);
    if (esclavo1 == 0) {
        close(fd1[0]);
        dup2(fd1[1], STDOUT_FILENO);
        if (execl("./esclavo", "esclavo", aux, aux2, NULL) < 0) {
            perror("\nError al ejecutar ./esclavo");
            exit(-1);
        }
    } else {
        close(fd1[1]);
        while ((leido = read(fd1[0], &val1, sizeof (int))) > 0) {
            printf("%d ", val1);
        }
        close(fd1[0]);
    }

    // Segundo esclavo
    esclavo2 = fork();
    sprintf(aux, "%d", inicio3);
    sprintf(aux2, "%d", final3);
    if (esclavo2 == 0) {
        close(fd2[0]);
        dup2(fd2[1], STDOUT_FILENO);
        if (execl("./esclavo", "esclavo", aux, aux2, NULL) < 0) {
            perror("\nError al ejecutar ./esclavo");
            exit(-1);
        }
    } else {
        close(fd2[1]);
        while ((leido2 = read(fd2[0], &val2, sizeof (int))) > 0) {
            printf("%d ", val2);
        }
        close(fd2[0]);
    }
    return 0;
}
