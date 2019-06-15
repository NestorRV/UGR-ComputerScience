#include <iostream>
#include <cmath>
#include "mpi.h"

using namespace std;

#define Productor 1
#define Consumidor 2
#define Buffer 5
#define ITERS 20
#define TAM 5

void productor(int rank){
    for(unsigned int i = 0; i < 4; i++)    {
        cout << "Productor " << rank << ", valor: " << i << endl;
        MPI_Ssend(&i, 1, MPI_INT, Buffer, Productor, MPI_COMM_WORLD); // La etiqueta del productor es 1
    }
}

void consumidor(int rank){
    int value, peticion=1;
    float raiz;
    MPI_Status status;
    
    for(unsigned int i = 0; i < 5; i++){

        // De entrada el consumidor envia peticion para recibir datos
        MPI_Ssend(&peticion, 1, MPI_INT, Buffer, Consumidor, MPI_COMM_WORLD); // La etiqueta de envio a consumidor es 2

        // Una vez aceptada la petición por el buffer le pedimos al mismo que nos mande un valor producido
        MPI_Recv (&value, 1, MPI_INT, Buffer, 0, MPI_COMM_WORLD, &status);  // La etiquete de envio de buffer a consumidor es 0
        cout << "Consumidor " << rank << " valor: " << value << " de Buffer." << endl;
        raiz = sqrt(value);
        cout << raiz << endl;
    }
}

void buffer(){
    int value[TAM], peticion, pos=0, rama;
    MPI_Status status;

    for(unsigned int i = 0; i < 40; i++){
        if (pos==0)         // el consumidor no puede consumir, se debe producir
            rama=0;
        else if (pos==TAM)  // el productor no puede producir, se debe consumir
            rama=1;
        else{        
            // ...se puede consumir o producir
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            
            if (status.MPI_TAG == Productor) //segun la etiqeta que tenga sera un rama o otra.
                rama = 0;
            else
                rama = 1;
        }
        
        // Recibe del productor
        if(rama == 0){
            // Recibe de cualquiera de los productores (etiqueta 1)
            MPI_Recv(&value[pos], 1, MPI_INT, MPI_ANY_SOURCE, Productor, MPI_COMM_WORLD, &status);
            cout << "Buffer recibe " << value[pos] << " de Prod. " << status.MPI_SOURCE << endl;
            pos++;
            break;
        }
        // Envia al consumidor
        else{
            // Recibe de cualquiera de los consumidores (etiqueta 2)
            MPI_Recv(&peticion, 1, MPI_INT, MPI_ANY_SOURCE, Consumidor, MPI_COMM_WORLD, &status);

            // Devuelve al consumidor que le envió la peticion con etiquete 0
            MPI_Ssend(&value[pos-1], 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
            cout << "Buffer envia " << value[pos-1] << " a Cons. " << status.MPI_SOURCE << endl;
            pos--;
            break;
        }
    }
}

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(size!=10){
        if (rank == 0)
            cout << "Uso: mpirun -np 10 " << argv[0] << endl;
    }
    else{
        if (rank < Buffer)
            productor(rank);
        else if (rank == Buffer)
            buffer();
        else
            consumidor(rank);
    }
    
    MPI_Finalize();
    return 0;

}