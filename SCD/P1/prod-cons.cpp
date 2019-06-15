#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>

using namespace std ;

// ---------------------------------------------------------------------
// constantes
const unsigned
  num_items  = 35 ,
  tam_vector = 5 ;

int vector[tam_vector];
int primera_libre=0;
int primera_ocupada=0;

sem_t
   puede_escribir, // inicializado a tam_vector
   puede_leer,     // inicializado a 0
   mutex ;         // inicializado a 1

// ---------------------------------------------------------------------

unsigned producir_dato()
{
  static int contador = 0 ;
  cout << "producido: " << contador << endl << flush ;
  return contador++ ;
}
// ---------------------------------------------------------------------

void consumir_dato( int dato )
{
}
// ---------------------------------------------------------------------

//LIFO

void * productor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
	int dato = producir_dato() ;
   sem_wait( &puede_escribir ) ;
	vector[primera_libre]=dato;
	primera_libre++;
   sem_post( &puede_leer ) ;
  }
  return NULL ;
}
// ---------------------------------------------------------------------

void * consumidor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
   int dato=0 ;

   sem_wait( &puede_leer ) ;
   dato = vector[primera_libre-1] ; // lee el valor generado
	primera_libre--;
   consumir_dato(dato);
	sem_wait( &mutex ) ;
   cout << "dato recibido: " << dato << endl;
   sem_post( &mutex ) ;
   sem_post( &puede_escribir ) ;
  }
  return NULL ;
}

//FIFO
/*
void * productor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
	int dato = producir_dato() ;
   sem_wait( &puede_escribir ) ;
	vector[primera_libre]=dato;
	primera_libre=(primera_libre+1)%tam_vector;
   sem_post( &puede_leer ) ;
  }
  return NULL ;
}

void * consumidor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
   int dato=0 ;

   sem_wait( &puede_leer ) ;
   dato = vector[primera_ocupada] ; // lee el valor generado
	primera_ocupada=(primera_ocupada+1)%tam_vector;
   consumir_dato(dato);
	sem_wait( &mutex ) ;
   cout << "dato recibido: " << dato << endl;
   sem_post( &mutex ) ;
   sem_post( &puede_escribir ) ;
  }
  return NULL ;
}

//----------------------------------------------------------------------
*/
int main()
{
   pthread_t hebra_escritora, hebra_lectora ;

   sem_init( &mutex,          0, 1 ); // semaforo para EM: inicializado a 1
   sem_init( &puede_escribir, 0, tam_vector ); // inicialmente se puede escribir
   sem_init( &puede_leer,     0, 0 ); // inicialmente no se puede leer

   pthread_create( &hebra_escritora, NULL, productor, NULL );
   pthread_create( &hebra_lectora,   NULL, consumidor, NULL );

   pthread_join( hebra_escritora, NULL ) ;
   pthread_join( hebra_lectora,   NULL ) ;

   sem_destroy( &puede_escribir );
   sem_destroy( &puede_leer );
   sem_destroy( &mutex );

   cout << endl << "fin" << endl;

   return 0 ;
}
