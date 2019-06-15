#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

int Primo(int n){
	int i;
	int limite = sqrt(n);
	int primo = 1;
	for (i = 2; i <= limite && primo; i++)
		if (n % i == 0)
			primo = 0;
	return primo;
};

int main(int argc, char *argv[]){
	int inicio, fin, i;
	inicio = atoi(argv[1]);
	fin = atoi(argv[2]);
	for (i = inicio; i < fin; i++)
		if (Primo(i))
			write(STDOUT_FILENO, &i, sizeof(int));
	return 0;
}
