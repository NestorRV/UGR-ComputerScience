#include <mpi.h>
#include <iostream>
#include <math.h>
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"


#define Productor  1
#define Consumidor 2
#define Buffer     5
#define ITERS      20
#define TAM        5

using namespace std;

void productor(int rank) {
    // 4 valores, por 5 productores serán 20
    for (unsigned int i = 0; i < 4; i++) {
        // Producimos un valor
        cout << "Productor " << rank << " produce valor " << i << endl << flush;
        
        // espera bloqueado durante un intervalo de tiempo aleatorio 
        // (entre una décima de segundo y un segundo)
        usleep( 1000U * (100U+(rand()%900U)) );
        
        // La etiqueta del productor es 1
        MPI_Ssend(&i, 1, MPI_INT, Buffer, Productor, MPI_COMM_WORLD);
    }
}

void consumidor(int rank) {
    int value, peticion = 1;
    float raiz;
    MPI_Status status;

    // 5 valores, por 4 consumidores serán 20
    for (unsigned int i = 0; i < 5; i++) {

        // El consumidor envia peticion para recibir
        // La etiqueta de envio a consumidor es 2
        MPI_Ssend(&peticion, 1, MPI_INT, Buffer, Consumidor, MPI_COMM_WORLD);

        // Una vez aceptada la petición le pedimos un valor a Buffer
        // La etiqueta de envio de buffer a consumidor es 0
        MPI_Recv(&value, 1, MPI_INT, Buffer, 0, MPI_COMM_WORLD, &status);
        cout << "Consumidor " << rank << " recibe valor " << value << " de Buffer " << endl << flush;
        
        // espera bloqueado durante un intervalo de tiempo aleatorio 
        // (entre una décima de segundo y un segundo)
        usleep( 1000U * (100U+(rand()%900U)) );
        raiz = sqrt(value);
    }
}

void buffer() {
    int        value[TAM] , 
              peticion , 
              pos  =  0,
              rama ;
    MPI_Status status ;

    for (unsigned int i = 0; i < 40; i++) {
        if ( pos==0 )      // el consumidor no puede consumir
         rama = 0 ;        
        else if (pos==TAM) // el productor no puede producir
         rama = 1 ;           
        else               // ambas guardas son ciertas
        {
            // leer 'status' del siguiente mensaje (esperando si no hay)
            MPI_Probe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
         
            // calcular la rama en función del origen del mensaje
            if ( status.MPI_SOURCE == Productor ) 
                rama = 0 ; 
            else 
                rama = 1 ;
        }

        switch (rama) {
            // Recibe del productor
            case 0:
            {
                // Recibe de cualquiera de los productores
                MPI_Recv(&value[pos], 1, MPI_INT, MPI_ANY_SOURCE, Productor, MPI_COMM_WORLD, &status);
                cout << "Buffer recibe " << value[pos] << " de Prod. " << status.MPI_SOURCE << endl << flush;
                pos++;
                break;
            }
            // Envia al consumidor
            case 1:
            {
                // Recibe de cualquiera de los consumidores
                MPI_Recv(&peticion, 1, MPI_INT, MPI_ANY_SOURCE, Consumidor, MPI_COMM_WORLD, &status);

                // Devuelve al consumidor que le envió la peticion con etiqueta 0
                MPI_Ssend(&value[pos - 1], 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
                cout << "Buffer envia " << value[pos - 1] << " a Cons. " << status.MPI_SOURCE << endl << flush;
                pos--;
                break;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    
    // inicializar MPI, leer identif. de proceso y número de procesos
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // inicializa la semilla aleatoria:
    srand ( time(NULL) );

    // comprobar el número de procesos con el que el programa 
    // ha sido puesto en marcha (debe ser 10)
    if (size != 10) {
        if (rank == 0){
            cout << "Uso: mpirun -np 10 " << argv[0] << endl;
            return 0;
        }
    }
    
    // Llamamos a los metodos dependiendo de cual sea su numero "rank"
    if (rank < Buffer)
        productor(rank);
    else if (rank == Buffer)
        buffer();
    else
        consumidor(rank);
    

    // al terminar el proceso, finalizar MPI
    MPI_Finalize();
    return 0;
}