#include <vector>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "K-NN.h"
#include "Relief.h"
#include "LocalSearch.h"
#include "Geneticos.h"
#include "Memeticos.h"

using namespace std;

int main(int argc, char** argv) {
    srand(75573052);
    bool all = true;

    if (all) {
        std::chrono::high_resolution_clock::time_point start, end;
        std::chrono::duration<double> time;
        cout << "******************************************************************************************" << endl;
        cout << "********** Ejecución de todos los algoritmos para todos los conjuntos de datos. **********" << endl;
        cout << "******************************************************************************************" << endl;
        start = std::chrono::high_resolution_clock::now();
        for (int j = 1; j < 4; j++) {
            if (j == 1) {
                cout << endl;
                cout << "============================" << endl;
                cout << "========= sonar ============" << endl;
                cout << "============================" << endl;
            } else if (j == 2) {
                cout << endl;
                cout << "============================" << endl;
                cout << "========= spambase =========" << endl;
                cout << "============================" << endl;
            } else if (j == 3) {
                cout << endl;
                cout << "============================" << endl;
                cout << "========= wdbc =============" << endl;
                cout << "============================" << endl;
            }

            cout << endl << "*************** K-NN (K=1) // pesos[i]=1. *************************" << endl;
            for (int i = 1; i < 6; i++)
                EjecutarKNN(i, j);

            cout << endl << "*************** Algoritmo Relief. *********************************" << endl;
            for (int i = 1; i < 6; i++)
                EjecutarRelief(i, j);

            cout << endl << "*************** Algoritmo LocalSearch. ****************************" << endl;
            for (int i = 1; i < 6; i++)
                EjecutarLocalSearch(i, j);

            cout << endl << "*************** Algoritmo GeneticoGeneracionalBLX. ****************" << endl;
            for (int i = 1; i < 6; i++)
                EjecutarGeneticoGeneracionalBLX(i, j);

            cout << endl << "*************** Algoritmo GeneticoGeneracionalCA. *****************" << endl;
            for (int i = 1; i < 6; i++)
                EjecutarGeneticoGeneracionalCA(i, j);

            cout << endl << "*************** Algoritmo GeneticoEstacionarioBLX. ****************" << endl;
            for (int i = 1; i < 6; i++)
                EjecutarGeneticoEstacionarioBLX(i, j);

            cout << endl << "*************** Algoritmo GeneticoEstacionarioCA. *****************" << endl;
            for (int i = 1; i < 6; i++)
                EjecutarGeneticoEstacionarioCA(i, j);

            cout << endl << "*************** Algoritmo MemeticoGeneracionalBLX_10_1. ***********" << endl;
            for (int i = 1; i < 6; i++)
                EjecutarMemeticoGeneracionalBLX_10_1(i, j);

            cout << endl << "*************** Algoritmo MemeticoGeneracionalBLX_10_0_1. *********" << endl;
            for (int i = 1; i < 6; i++)
                EjecutarMemeticoGeneracionalBLX_10_0_1(i, j);

            cout << endl << "*************** Algoritmo MemeticoGeneracionalBLX_10_0_1_mej. *****" << endl;
            for (int i = 1; i < 6; i++)
                EjecutarMemeticoGeneracionalBLX_10_0_1_mej(i, j);
        }

        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        cout << "******************************************************************************************" << endl;
        cout << "Tiempo total empleado: " << time.count() << " segundos." << endl;
        cout << "******************************************************************************************" << endl;
    } else {
        int bd = 1;
        cout << "Pulse 1 para usar sonar, 2 para spambase y 3 para wdbc: ";
        cin >> bd;
        
        cout << endl << "*************** K-NN (K=1) // pesos[i]=1. *************************" << endl;
        for (int i = 1; i < 6; i++)
            EjecutarKNN(i, bd);

        cout << endl << "*************** Algoritmo Relief. *********************************" << endl;
        for (int i = 1; i < 6; i++)
            EjecutarRelief(i, bd);

        cout << endl << "*************** Algoritmo LocalSearch. ****************************" << endl;
        for (int i = 1; i < 6; i++)
            EjecutarLocalSearch(i, bd);

        cout << endl << "*************** Algoritmo GeneticoGeneracionalBLX. ****************" << endl;
        for (int i = 1; i < 6; i++)
            EjecutarGeneticoGeneracionalBLX(i, bd);
        
        cout << endl << "*************** Algoritmo GeneticoGeneracionalCA. *****************" << endl;
        for (int i = 1; i < 6; i++)
            EjecutarGeneticoGeneracionalCA(i, bd);

        cout << endl << "*************** Algoritmo GeneticoEstacionarioBLX. ****************" << endl;
        for (int i = 1; i < 6; i++)
            EjecutarGeneticoEstacionarioBLX(i, bd);

        cout << endl << "*************** Algoritmo GeneticoEstacionarioCA. *****************" << endl;
        for (int i = 1; i < 6; i++)
            EjecutarGeneticoEstacionarioCA(i, bd);

        cout << endl << "*************** Algoritmo MemeticoGeneracionalBLX_10_1. ***********" << endl;
        for (int i = 1; i < 6; i++)
            EjecutarMemeticoGeneracionalBLX_10_1(i, bd);

        cout << endl << "*************** Algoritmo MemeticoGeneracionalBLX_10_0_1. *********" << endl;
        for (int i = 1; i < 6; i++)
            EjecutarMemeticoGeneracionalBLX_10_0_1(i, bd);

        cout << endl << "*************** Algoritmo MemeticoGeneracionalBLX_10_0_1_mej. *****" << endl;
        for (int i = 1; i < 6; i++)
            EjecutarMemeticoGeneracionalBLX_10_0_1_mej(i, bd);
    }
}
