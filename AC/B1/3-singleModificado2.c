#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char ** argv){
   int n = 9, i, a, b[n];
   for (i=0; i<n; i++)
      b[i] = -1;
   #pragma omp parallel
   {
      #pragma omp single
      {
         printf("Introduce valor de inicialización a: ");
         scanf("%d", &a );
         printf("Single ejecutada por el thread %d\n", omp_get_thread_num());
      }
      #pragma omp for
         for (i=0; i<n; i++)
            b[i] = a;
      #pragma omp master
      {
         printf("Dentro de la región parallel:\n");
         for (i=0; i<n; i++)
            printf("b[%d] = %d\t",i,b[i]);
         printf("\n");
         printf("Single ejecutada por el thread %d. \n", omp_get_thread_num());
      }
   }
   return 0;
}
