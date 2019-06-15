#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>      // incluye "time(....)"
#include <unistd.h>    // incluye "usleep(...)"
#include <stdlib.h>    // incluye "rand(...)" y "srand"

using namespace std;

// ----------------------------------------------------------------------------
// función que simula la acción de fumar  como un retardo aleatorio de la hebra

const int NUMERO=3;

sem_t puede_fumar[NUMERO];
sem_t puede_producir;

void * fumador(void * s)
{
   while(true){
	  cout << "Fumador " << (long int) s << " esperando." << endl; 
      sem_wait(&puede_fumar[(unsigned int) s]);
      //  inicializa la semilla aleatoria  (solo la primera vez)
      static bool primera_vez = true ;
      if ( primera_vez )
      {
		primera_vez = false ;
        srand( time(NULL) );
      }

      // calcular un numero aleatorio de milisegundos (entre 1/10 y 2 segundos)
      const unsigned miliseg = 100U + (rand() % 1900U) ;

      sem_post(&puede_producir);
      // retraso bloqueado durante 'miliseg' milisegundos
      usleep( 1000U*miliseg );
      cout << "Fumador " << (long int) s << " fumando." << endl; 
   }
}

void * estanquero(void *){
   while(true){
      cout << "El estanquero esta esperando." << endl;
      sem_wait(&puede_producir);
      int aleatorio=rand()%NUMERO;
      cout << "Produzco: " << aleatorio << endl;
      sem_post(&puede_fumar[aleatorio]);
   }
}

int main()
{
   pthread_t hebra_estanquero;
	pthread_t hebra_fumador[NUMERO];

   sem_init( &puede_fumar[NUMERO], 0, 0 );
   /*for(int i=0; i<NUMERO; i++)
	   sem_init( &puede_fumar[i], 0, 0 );*/
   sem_init( &puede_producir, 0, 1 );

   pthread_create(&hebra_estanquero, NULL, estanquero, NULL);

	for(unsigned long i=0; i<NUMERO; i++){
		void * arg_ptr=(void *) i;
		pthread_create(&hebra_fumador[i], NULL, fumador, arg_ptr);
   }

   for(unsigned i=0; i<NUMERO; i++){
      pthread_join (hebra_fumador[i], NULL);
   }

   pthread_join(hebra_estanquero, NULL);

   sem_destroy( &puede_fumar[NUMERO] );
   sem_destroy( &puede_producir );

   return 0 ;
}
