/* 10-SumaVectoresSections.c
Suma de dos vectores: v3 = v1 + v2
Para compilar usar (-lrt: real time library):
gcc -O2 10-SumaVectoresSections.c -o 10-SumaVectoresSections -lrt
gcc -O2 –S 10-SumaVectoresSections.c –lrt   //para generar el código ensamblador
Para ejecutar use: 10-SumaVectoresSections longitud
*/
#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h>  // biblioteca donde se encuentra la función printf()
#include <time.h>   // biblioteca donde se encuentra la función clock_gettime()
#include <omp.h>

#define PRINTF_ALL // comentar para quitar el printf que imprime todos los componentes

//Sólo puede estar definida una de las tres constantes VECTOR_ (sólo uno de los ...
//tres defines siguientes puede estar descomentado):

//#define VECTOR_LOCAL // descomentar para que los vectores sean variables ...
                       // locales (si se supera el tamaño de la pila se ...
                       // generará el error "Violación de Segmento")

//#define VECTOR_GLOBAL // descomentar para que los vectores sean variables ...
                        // globales (su longitud no estará limitada por el ...
                        // tamaño de la pila del programa)

#define VECTOR_DYNAMIC // descomentar para que los vectores sean variables ...
                       // dinámicas (memoria reutilizable durante la ejecución)

#ifdef VECTOR_GLOBAL
#define MAX 33554432 //=2^25
double v1[MAX], v2[MAX], v3[MAX];
#endif

int main(int argc, char** argv){
  //Indices para cada hebra
  int i, j, k, l;
  double inicio, fin, tiempo;
  //Leer argumento de entrada (nº de componentes del vector)
  if (argc<2){
    printf("Faltan nº componentes del vector\n");
    exit(-1);
  }

  unsigned int N = atoi(argv[1]); // Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)
  #ifdef VECTOR_LOCAL
  // Tamaño variable local en tiempo de ejecución disponible en C a partir de actualización C99
  double v1[N], v2[N], v3[N];
  #endif

  #ifdef VECTOR_GLOBAL
  if (N>MAX) N=MAX;
  #endif

  #ifdef VECTOR_DYNAMIC
  double *v1, *v2, *v3;
  v1 = (double*) malloc(N*sizeof(double));// malloc necesita el tamaño en bytes
  v2 = (double*) malloc(N*sizeof(double)); //si no hay espacio suficiente malloc devuelve NULL
  v3 = (double*) malloc(N*sizeof(double));

  if ( (v1==NULL) || (v2==NULL) || (v3==NULL) ){
     printf("Error en la reserva de espacio para los vectores\n");
     exit(-2);
  }
  #endif

  //Inicializacion dividida en cuatro partes para aprovechar las 4 hebras.

  #pragma omp parallel sections
  {
	  #pragma omp section
	  {
		  for(i=0; i<N/2; i++){
			 v1[i] = N*0.1+i*0.1;
		  }
	  }
	  #pragma omp section
	  {
		  for(j=0; j<N/2; j++){
			 v2[j] = N*0.1-j*0.1;
		  }
	  }
	  #pragma omp section
	  {
		  for(k=N/2; k<N; k++){
			 v1[k] = N*0.1+k*0.1;
		  }
	  }
	  #pragma omp section
	  {
		  for(l=N/2; l<N; l++){
			 v2[l] = N*0.1-l*0.1;
		  }
	  }
  }

  inicio = omp_get_wtime();
  //Calcular suma de vectores aprovechando tambien las 4 hebras

  #pragma omp parallel sections
  {
	  #pragma omp section
	  {
		  for(i=0; i<N/4; i++){
			 v3[i] = v1[i] + v2[i];
		  }
	  }
	  #pragma omp section
	  {
		  for(j=N/4; j<N/2; j++){
			 v3[j] = v1[j] + v2[j];
		  }
	  }
	  #pragma omp section
	  {
		  for(k=N/2; k<3*N/4; k++){
			 v3[k] = v1[k] + v2[k];
		  }
	  }
	  #pragma omp section
	  {
		  for(l=3*N/4; l<N; l++){
			 v3[l] = v1[l] + v2[l];
		  }
	  }
  }

 fin = omp_get_wtime();
 tiempo = fin - inicio;


 //Imprimir resultado de la suma y el tiempo de ejecución
 #ifdef PRINTF_ALL
 printf("%f\t%f\t%f\t\n",tiempo, v3[0], v3[N-1]);
 #else
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",tiempo,N,v1[0],v2[0],v3[0],N-1,N-1,N-1,v1[N-1],v2[N-1],v3[N-1]);
 #endif

 if (N < 100)
    for(i=0; i<N; i++)
      printf("%f + %f = %f\n",v1[i], v2[i], v3[i]);

 #ifdef VECTOR_DYNAMIC
 free(v1); // libera el espacio reservado para v1
 free(v2); // libera el espacio reservado para v2
 free(v3); // libera el espacio reservado para v3
 #endif
 return 0;
}
