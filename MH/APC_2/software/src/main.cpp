#include <vector>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "K-NN.h"
#include "Relief.h"
#include "LocalSearch.h"
#include "Evolutivos.h"
#include "EnfriamientoSimulado.h"
#include "ILS.h"

using namespace std;

int main(int argc, char** argv) {
    srand(75573052);

    ofstream ejecucionCompleta("./Resultados/EjecucionCompleta");
    ofstream sobreaprendizaje("./Resultados/SobreAprendizaje");
    ofstream caracteristicas("./Resultados/Caracteristicas");
    vector<float> aciertos, reducciones, finales;
    vector<double> tiempos;

    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;
    start = std::chrono::high_resolution_clock::now();
    for (int j = 1; j < 4; j++) {
        if (j == 1) {
            cout << endl;
            cout << "============================" << endl;
            cout << "========= sonar ============" << endl;
            cout << "============================" << endl;
            ejecucionCompleta << endl;
            ejecucionCompleta << "============================" << endl;
            ejecucionCompleta << "========= sonar ============" << endl;
            ejecucionCompleta << "============================" << endl;
            sobreaprendizaje << endl;
            sobreaprendizaje << "============================" << endl;
            sobreaprendizaje << "========= sonar ============" << endl;
            sobreaprendizaje << "============================" << endl;
        } else if (j == 2) {
            cout << endl;
            cout << "============================" << endl;
            cout << "========= wdbc =============" << endl;
            cout << "============================" << endl;
            ejecucionCompleta << endl;
            ejecucionCompleta << "============================" << endl;
            ejecucionCompleta << "========= wdbc =============" << endl;
            ejecucionCompleta << "============================" << endl;
            sobreaprendizaje << endl;
            sobreaprendizaje << "============================" << endl;
            sobreaprendizaje << "========= wdbc =============" << endl;
            sobreaprendizaje << "============================" << endl;
        } else if (j == 3) {
            cout << endl;
            cout << "============================" << endl;
            cout << "========= spambase =========" << endl;
            cout << "============================" << endl;
            ejecucionCompleta << endl;
            ejecucionCompleta << "============================" << endl;
            ejecucionCompleta << "========= spambase =========" << endl;
            ejecucionCompleta << "============================" << endl;
            sobreaprendizaje << endl;
            sobreaprendizaje << "============================" << endl;
            sobreaprendizaje << "========= spambase =========" << endl;
            sobreaprendizaje << "============================" << endl;
        }

        cout << endl << "*************** K-NN. *******************" << endl;
        ejecucionCompleta << endl << "*************** K-NN. *******************" << endl;
        aciertos.resize(0); reducciones.resize(0); finales.resize(0), tiempos.resize(0);
        for (int i = 1; i < 6; i++)
            EjecutarKNN(i, j, ejecucionCompleta, aciertos, reducciones, finales, tiempos);

        cout << endl << "*************** Relief. *****************" << endl;
        ejecucionCompleta << endl << "*************** Relief. *****************" << endl;
        caracteristicas << endl << "*************** Relief. *****************" << endl;
        aciertos.resize(0); reducciones.resize(0); finales.resize(0), tiempos.resize(0);
        for (int i = 1; i < 6; i++)
            EjecutarRelief(i, j, ejecucionCompleta, caracteristicas, aciertos, reducciones, finales, tiempos);

        cout << endl << "*************** ES. *********************" << endl;
        ejecucionCompleta << endl << "*************** ES. *********************" << endl;
        sobreaprendizaje << endl << "*************** ES. *********************" << endl;
        caracteristicas << endl << "*************** ES. *********************" << endl;
        aciertos.resize(0); reducciones.resize(0); finales.resize(0), tiempos.resize(0);
        for (int i = 1; i < 6; i++)
            EjecutarEnfriamientoSimulado(i, j, ejecucionCompleta, sobreaprendizaje, caracteristicas, aciertos, reducciones, finales, tiempos);

        cout << endl << "*************** ILS. ********************" << endl;
        ejecucionCompleta << endl << "*************** ILS. ********************" << endl;
        sobreaprendizaje << endl << "*************** ILS. ********************" << endl;
        caracteristicas << endl << "*************** ILS. ********************" << endl;
        aciertos.resize(0); reducciones.resize(0); finales.resize(0), tiempos.resize(0);
        for (int i = 1; i < 6; i++)
            EjecutarILS(i, j, ejecucionCompleta, sobreaprendizaje, caracteristicas, aciertos, reducciones, finales, tiempos);

        cout << endl << "*************** DE/rand/1. **************" << endl;
        ejecucionCompleta << endl << "*************** DE/rand/1. **************" << endl;
        sobreaprendizaje << endl << "*************** DE/rand/1. **************" << endl;
        caracteristicas << endl << "*************** DE/rand/1. **************" << endl;
        aciertos.resize(0); reducciones.resize(0); finales.resize(0), tiempos.resize(0);
        for (int i = 1; i < 6; i++)
            EjecutarEvolucionDiferencialRand(i, j, ejecucionCompleta, sobreaprendizaje, caracteristicas, aciertos, reducciones, finales, tiempos);

        cout << endl << "*************** DE/current-to-best/1. ***" << endl;
        ejecucionCompleta << endl << "*************** DE/current-to-best/1. ***" << endl;
        sobreaprendizaje << endl << "*************** DE/current-to-best/1. ***" << endl;
        caracteristicas << endl << "*************** DE/current-to-best/1. ***" << endl;
        aciertos.resize(0); reducciones.resize(0); finales.resize(0), tiempos.resize(0);
        for (int i = 1; i < 6; i++)
            EjecutarEvolucionDiferencialBest(i, j, ejecucionCompleta, sobreaprendizaje, caracteristicas, aciertos, reducciones, finales, tiempos);

        cout << endl << "*************** LS. *********************" << endl;
        ejecucionCompleta << endl << "*************** LS. *********************" << endl;
        sobreaprendizaje << endl << "*************** LS. *********************" << endl;
        caracteristicas << endl << "*************** LS. *********************" << endl;
        aciertos.resize(0); reducciones.resize(0); finales.resize(0), tiempos.resize(0);
        for (int i = 1; i < 6; i++)
            EjecutarLocalSearch(i, j, ejecucionCompleta, sobreaprendizaje, caracteristicas, aciertos, reducciones, finales, tiempos);

        cout << endl << "*************** AGG-BLX. ****************" << endl;
        ejecucionCompleta << endl << "*************** AGG-BLX. ****************" << endl;
        sobreaprendizaje << endl << "*************** AGG-BLX. ****************" << endl;
        caracteristicas << endl << "*************** AGG-BLX. ****************" << endl;
        aciertos.resize(0); reducciones.resize(0); finales.resize(0), tiempos.resize(0);
        for (int i = 1; i < 6; i++)
            EjecutarGeneticoGeneracionalBLX(i, j, ejecucionCompleta, sobreaprendizaje, caracteristicas, aciertos, reducciones, finales, tiempos);

        cout << endl << "*************** AM10-0.1mej. ************" << endl;
        ejecucionCompleta << endl << "*************** AM10-0.1mej. ************" << endl;
        sobreaprendizaje << endl << "*************** AM10-0.1mej. ************" << endl;
        caracteristicas << endl << "*************** AM10-0.1mej. ************" << endl;
        aciertos.resize(0); reducciones.resize(0); finales.resize(0), tiempos.resize(0);
        for (int i = 1; i < 6; i++)
            EjecutarMemeticoGeneracionalBLX_10_0_1_mej(i, j, ejecucionCompleta, sobreaprendizaje, caracteristicas, aciertos, reducciones, finales, tiempos);
    }
    
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Tiempo total empleado: " << time.count() << " segundos." << endl;
    ejecucionCompleta << "Tiempo total empleado: " << time.count() << " segundos." << endl;
    sobreaprendizaje << "Tiempo total empleado: " << time.count() << " segundos." << endl;

    ejecucionCompleta.close();
    sobreaprendizaje.close();
    caracteristicas.close();
}
