#include <iostream>
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"
#include <mpi.h>

#define CAMARERO 10

using namespace std;

void Filosofo( int id, int nprocesos);
void Tenedor ( int id, int nprocesos);
void Camarero ();

int sentarse = 111;
int levantarse = 222;

// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int rank, size;
   
   srand(time(0));
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   
   if( size!=11)
   {
      if( rank == 0) 
         cout<<"El numero de procesos debe ser 11" << endl << flush ;
      MPI_Finalize( ); 
      return 0; 
   }

	if (rank == 10)
        Camarero(); // El proceso 10 es el camarero
    else if (rank%2 == 0)
        Filosofo(rank,size); // Los pares son Filosofos
    else
        Tenedor(rank,size); // Los impares son Tenedor
   
   MPI_Finalize( );
   return 0;
}  
// ---------------------------------------------------------------------

void Camarero(){  
  int filosofo, contador=0;
    MPI_Status status;
    while (true){
        // El maximo de filosofos comiendo es 4
        if (contador < 4)
			      // Puede sentarse o levantarse
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status); 
        else
			      // Solo puede levantarse
            MPI_Probe(MPI_ANY_SOURCE, levantarse, MPI_COMM_WORLD, &status);

        if (status.MPI_TAG == sentarse){
			      // Sentarse
            filosofo=status.MPI_SOURCE;
            MPI_Recv(NULL, 0, MPI_INT, filosofo, sentarse, MPI_COMM_WORLD, &status);
            contador++;
            MPI_Send(NULL, 0, MPI_INT, filosofo, sentarse, MPI_COMM_WORLD);
        }

        if (status.MPI_TAG == levantarse){
			      // Levantarse
            filosofo=status.MPI_SOURCE;
            MPI_Recv( NULL, 0, MPI_INT, filosofo, levantarse, MPI_COMM_WORLD, &status);
            contador--;
        }
    }
}

void Filosofo( int id, int nprocesos )
{
   // Ahora hay un proceso mas
   int izq = (id+1) % (nprocesos-1);
   int der = (id+nprocesos-2) % (nprocesos-1);
   MPI_Status status;   
   
   while(1)
   {
      // Piensa (espera bloqueada aleatorio del proceso)
      cout << "Filosofo " << id << " PENSANDO" << endl << flush;
      
      // espera bloqueado durante un intervalo de tiempo aleatorio 
      // (entre una décima de segundo y un segundo)
      usleep( 1000U * (100U+(rand()%900U)) );
      
      // El filosofo pide sentarse
      cout << "Filosofo " << id << " solicita sentarse " << endl << flush;
      MPI_Send(NULL, 0, MPI_INT, CAMARERO, sentarse, MPI_COMM_WORLD);

      // El filosofo espera a que le digan que puede sentarse
      MPI_Recv(NULL, 0, MPI_INT, CAMARERO, sentarse, MPI_COMM_WORLD, &status);
      cout << "Filosofo " << id << " se sienta " << endl << flush;
      // El filosofo se sienta      
      
      // Solicita tenedor izquierdo
      MPI_Ssend(&izq, 1, MPI_INT, izq, izq, MPI_COMM_WORLD);
      cout << "Filosofo "<< id << " adquiere tenedor izq " << izq << endl << flush;

      // Solicita tenedor derecho
      MPI_Ssend(&der, 1, MPI_INT, der, der, MPI_COMM_WORLD);
      cout << "Filosofo "<< id << " adquiere tenedor der " << der << endl << flush;
  
      cout<<"Filosofo "<< id << " COMIENDO"<<endl<<flush;
      sleep((rand() % 3)+1);  //comiendo
      
      // Suelta el tenedor izquierdo
      MPI_Ssend(&izq, 1, MPI_INT, izq, izq, MPI_COMM_WORLD);
      cout <<"Filosofo "<< id << " ha soltado tenedor izq " << izq << endl << flush;      
      
      // Suelta el tenedor derecho
      MPI_Ssend(&der, 1, MPI_INT, der, der, MPI_COMM_WORLD);
      cout <<"Filosofo "<< id << " ha soltado tenedor der " << der << endl << flush;
      
      // El filosofo se levanta
      cout << "Filosofo " << id << " se levanta " << endl << flush;
      MPI_Ssend(NULL, 0, MPI_INT, CAMARERO, levantarse, MPI_COMM_WORLD);
      
 }
}
// ---------------------------------------------------------------------

void Tenedor(int id, int nprocesos)
{
  int buf; 
  MPI_Status status; 
  int Filo;
  
  while( true ){
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
