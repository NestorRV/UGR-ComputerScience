// Compilar con -O2 y -fopenmp
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc,char **argv) {
   int h, i, j, k;
   double t1, t2, total;
   int suma = 0; int suma2 = 0;

   //Leer argumento de entrada (no de componentes del vector)
   if (argc<2){
      printf("Falta tamaño de matriz\n");
      exit(-1);
   }

   unsigned int N = atoi(argv[1]); // Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)

   double **M1, **M2, **M3;
   //M1 = M2 * M3;
	M1 = (double**) malloc(N*sizeof(double *));
   M2 = (double**) malloc(N*sizeof(double *));
   M3 = (double**) malloc(N*sizeof(double *));

	if ( (M1==NULL) || (M2==NULL) || (M3==NULL) ){
		printf("Error en la reserva de espacio para las matrices\n");
		exit(-2);
	}

	for (i=0; i<N; i++){
		M1[i] = (double*) malloc(N*sizeof(double));
      M2[i] = (double*) malloc(N*sizeof(double));
      M3[i] = (double*) malloc(N*sizeof(double));
		if ( M1[i]==NULL || M2[i]==NULL || M3[i]==NULL ){
			printf("Error en la reserva de espacio para los matrices\n");
			exit(-2);
		}
	}

	//A partir de aqui se pueden acceder las componentes de la matriz como M[i][j]

	//Inicializar matriz y vectores

   //Cambiamos el acceso a las matrices
   for (i=0; i<N; i++){
		for (j=0; j<N; j++){
         M1[j][i] = 0;
			M2[j][i] = 2;
			M3[j][i] = 2;
		}
	}

   //Medida de tiempo
   t1 = omp_get_wtime();

   //Calcular producto de matriz por matriz M1 = M2 * M3

   int bucle_interno = N/8;
   for (i=0; i<N; i++){
		for(j=0; j<N; j++){
			suma = 0; suma2 = 0;
			for (h=0, k=0; h < bucle_interno; ++h, k+=8){
				suma += (M2[i][k]*M3[k][j]);
				suma += (M2[i][k+1]*M3[k+1][j]);
				suma += (M2[i][k+2]*M3[k+2][j]);
				suma += (M2[i][k+3]*M3[k+3][j]);
				suma2 += (M2[i][k+4]*M3[k+4][j]);
				suma2 += (M2[i][k+5]*M3[k+5][j]);
				suma2 += (M2[i][k+6]*M3[k+6][j]);
				suma2 += (M2[i][k+7]*M3[k+7][j]);
			}
			M1[i][j] = suma + suma2;
			for(k=bucle_interno*8; k<N; ++k){
				suma += (M2[i][k]*M3[k][j]);
			}
			M1[i][j] = suma + suma2;
		}
	}

   //Medida de tiempo
	t2 = omp_get_wtime();
	total = t2 - t1;

   //Imprimir el resultado y el tiempo de ejecución
   printf("Tiempo(seg.): %11.9f\t / Tamaño:%u\t/ M1[0][0]=%8.6f M1[%d][%d]=%8.6f\n", total,N,M1[0][0],N-1,N-1,M1[N-1][N-1]);

	for (i=0; i<N; i++){
		free(M1[i]); free(M2[i]); free(M3[i]);
   }

	free(M1); free(M2); free(M3);

   return 0;
}
