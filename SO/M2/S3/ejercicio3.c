#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(){
    pid_t pid_hijo;
    if(setvbuf(stdout, NULL, _IONBF,0)){
        perror("Error en setvbuf. \n");
    }
    /*
    // Jerarquía de procesos tipo 1
    for (int i=1; i < 20; i++) {
        if ((pid_hijo= fork()) == -1) {
            printf("\nError %d al realizar fork",errno);
            exit(-1);
        }
        if (pid_hijo)
            break;
        printf("PID = %d.\t PID del padre = %d\n", getpid(), getppid());
    }
    */
    // Jerarquía de procesos tipo 2
    for (int i=1; i < 20; i++) {
        if ((pid_hijo= fork()) == -1) {
            printf("\nError %d al realizar fork",errno);
            exit(-1);
        }
        printf("PID = %d.\t PID del padre = %d\n", getpid(), getppid());
        if (!pid_hijo)
            break;
    }

    return 0;
}
