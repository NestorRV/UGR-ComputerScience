#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
   #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv) {
   int i, n=200,chunk,a[n],suma=0;
   int *chunk_size;
   omp_sched_t *kind;
   if(argc < 3) {
      fprintf(stderr,"\nFalta iteraciones o chunk \n");
      exit(-1);
   }
   n = atoi(argv[1]); if (n>200) n=200; chunk = atoi(argv[2]);
   for (i=0; i<n; i++) a[i] = i;

   #pragma omp parallel
	{
		#pragma omp single
        {
			printf("dyn-var: %d \n",omp_get_dynamic());
			printf("nthreads-var: %d \n",omp_get_max_threads());
			printf("thread-limit-var: %d \n",omp_get_thread_limit());
         //https://gcc.gnu.org/onlinedocs/libgomp/omp_005fget_005fschedule.html
			omp_get_schedule(&kind,&chunk_size);
			printf("run-sched-var: (Kind: %d, Modifier: %d) \n",kind,chunk_size);
		}

   	#pragma omp for firstprivate(suma) \
            lastprivate(suma) schedule(dynamic,chunk)
      for (i=0; i<n; i++)
      {
         suma = suma + a[i];
         printf(" thread %d suma a[%d]=%d suma=%d \n",
         omp_get_thread_num(),i,a[i],suma);
      }
   }

   printf("Fuera de 'parallel for' suma=%d\n",suma);
   printf("dyn-var FUERA de 'parallel for': %d \n",omp_get_dynamic());
   printf("nthreads-var FUERA de 'parallel for': %d \n",omp_get_max_threads());
   printf("thread-limit-var FUERA de 'parallel for': %d \n",omp_get_thread_limit());
   omp_get_schedule(&kind,&chunk_size);
   printf("run-sched-var dentro de 'parallel for'. (Kind: %d. Modifier: %d) \n",kind,chunk_size);

   printf("Fuera de 'parallel for' suma=%d\n",suma);
}
