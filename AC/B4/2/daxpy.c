#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc,char **argv) {
   unsigned int N,i,j,k, l;
   k=999;

   struct timespec cgt1,cgt2;
   double ncgt; //para tiempo de ejecución
   //Leer argumento de entrada (no de componentes de la matriz)
   if (argc<2) {
      printf("Faltan no componentes del vector\n");
      exit(-1);
   }
   N=atoi(argv[1]);
   int *A,*B,*C;

   A=(int *) malloc(N*sizeof(int));
   B=(int *) malloc(N*sizeof(int));
   C=(int *) malloc(N*sizeof(int));
   //reservamos memoria dinamica.

   for(i=0; i<N; i++) {
      B[i]=20;
      C[i]=30;
   }
   //inicializamosla matriz y el vector

   clock_gettime(CLOCK_REALTIME,&cgt1);
   for (l=0; l<N; l++)
      A[l]= k*B[l] + C[l];
   clock_gettime(CLOCK_REALTIME,&cgt2);
   ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
   (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

   //Imprimir resultado de la suma y el tiempo de ejecución
   printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",ncgt,N);
   printf("A[0] = %d // A[N-1] = %d.\n",A[0],A[N-1]);

   free(B);
   free(C);
   free(A);
   //eliminamos la memoria dinamica.
}
