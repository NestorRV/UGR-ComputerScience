#include <iostream>
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"
#include <mpi.h>

using namespace std;

void Filosofo( int id, int nprocesos);
void Tenedor ( int id, int nprocesos);

// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int rank, size;
   
   srand(time(0));
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   
   if( size!=10)
   {
      if( rank == 0) 
         cout<<"El numero de procesos debe ser 10" << endl << flush ;
      MPI_Finalize( ); 
      return 0; 
   }
   
   if ((rank%2) == 0)  
      Filosofo(rank,size); // Los pares son Filosofos 
   else 
      Tenedor(rank,size);  // Los impares son Tenedores 
   
   MPI_Finalize( );
   return 0;
}  
// ---------------------------------------------------------------------

void Filosofo( int id, int nprocesos )
{
   int izq = (id+1) % nprocesos;
   int der = ((id+nprocesos)-1) % nprocesos;   
   
   while(1)
   {
      // Piensa (espera bloqueada aleatorio del proceso)
      cout << "Filosofo " << id << " PENSANDO" << endl << flush;
      
      // espera bloqueado durante un intervalo de tiempo aleatorio 
      // (entre una décima de segundo y un segundo)
      usleep( 1000U * (100U+(rand()%900U)) );
      
      if(id == 0){
        // Solicita tenedor derecho
        MPI_Ssend(&der, 1, MPI_INT, der, der, MPI_COMM_WORLD);
        cout << "Filosofo "<<id<< " adquiere tenedor der " << der << endl << flush;
        
        // Solicita tenedor izquierdo
        MPI_Ssend(&izq, 1, MPI_INT, izq, izq, MPI_COMM_WORLD);
        cout << "Filosofo "<<id<< " adquiere tenedor izq " << izq << endl << flush;
      }
      else{
        // Solicita tenedor izquierdo
        MPI_Ssend(&izq, 1, MPI_INT, izq, izq, MPI_COMM_WORLD);
        cout << "Filosofo "<<id<< " adquiere tenedor izq " << izq << endl << flush;
  
        // Solicita tenedor derecho
        MPI_Ssend(&der, 1, MPI_INT, der, der, MPI_COMM_WORLD);
        cout << "Filosofo "<<id<< " adquiere tenedor der " << der << endl << flush;
      }
  
      cout<<"Filosofo "<<id<< " COMIENDO"<<endl<<flush;
      sleep((rand() % 3)+1);  //comiendo
      
      // Suelta el tenedor izquierdo
      MPI_Ssend(&izq, 1, MPI_INT, izq, izq, MPI_COMM_WORLD);
      cout <<"Filosofo "<<id<< " ha soltado tenedor izq " << izq << endl << flush;      
      
      // Suelta el tenedor derecho
      MPI_Ssend(&der, 1, MPI_INT, der, der, MPI_COMM_WORLD);
      cout <<"Filosofo "<<id<< " ha soltado tenedor der " << der << endl << flush; 
 }
}
// ---------------------------------------------------------------------

void Tenedor(int id, int nprocesos)
{
  int buf; 
  MPI_Status status; 
  int Filo;
  
  while( true )
  {
    // Espera un peticion desde cualquier filosofo vecino ...
    MPI_Probe(MPI_ANY_SOURCE, id, MPI_COMM_WORLD, &status);
    
    // Recibe la peticion del filosofo ...
    MPI_Recv(&buf, 1, MPI_INT, MPI_ANY_SOURCE, id, MPI_COMM_WORLD, &status);
    
    Filo = status.MPI_SOURCE;
    
    cout << "Ten. " << id << " recibe petic. de " << Filo << endl << flush;
    
	// Espera un peticion desde cualquier filosofo vecino ...
    MPI_Probe(MPI_ANY_SOURCE, id, MPI_COMM_WORLD, &status);
    // Espera a que el filosofo suelte el tenedor...
    MPI_Recv(&buf, 1, MPI_INT, Filo, id, MPI_COMM_WORLD, &status);
    cout << "Ten. " << id << " recibe liberac. de " << Filo << endl << flush; 
  }
}
// ---------------------------------------------------------------------
