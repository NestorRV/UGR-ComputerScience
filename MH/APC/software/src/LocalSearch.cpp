#include "LocalSearch.h"

default_random_engine generator;
normal_distribution<double> distribution(0.0, 0.09);

void modificarPeso(vector<float> &solucion, const int &posicion) {
    float numero;
    solucion[posicion] += distribution(generator);
    numero = truncar(solucion[posicion]);
    solucion[posicion] = numero;
}

void localSearch(const vector<vector<float> > &train, const vector<int> &clases_train, vector<float> &pesos) {
    pesos.resize(0);
    int num_eval = 0, num_vecinos = 0, num_caracteristicas = train[0].size();
    float porcentaje_ant, porcentaje_nuevo = 0;
    bool mejora = true;
    vector<float> sol_nueva;
    vector<int> clasificacion, indices(num_caracteristicas);
    int posicion_auxiliar = 0, elegido = 0, i_auxiliar = 0;

    for (int i = 0; i < num_caracteristicas; i++) {
        indices[i] = i;
    }

    pesos = solInicialAleatoria(num_caracteristicas);
    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje_ant = tasaAcierto(clases_train, clasificacion);

    while (num_eval < 15000 && num_vecinos < 20 * num_caracteristicas) {
        mejora = false;
        for (int i = 0; i < num_caracteristicas && !mejora; i++) {
            sol_nueva = pesos;
            elegido = rand() % (indices.size() - i_auxiliar) + i_auxiliar;
            posicion_auxiliar = indices[i_auxiliar];
            indices[i_auxiliar] = indices[elegido];
            indices[elegido] = posicion_auxiliar;
            modificarPeso(sol_nueva, indices[i_auxiliar]);
            num_vecinos++;
            i_auxiliar++;
            if(i_auxiliar == num_caracteristicas)
                i_auxiliar = 0;

            KNN(train, clases_train, train, clasificacion, sol_nueva);
            porcentaje_nuevo = tasaAcierto(clases_train, clasificacion);
            num_eval++;

            if (porcentaje_nuevo > porcentaje_ant) {
                pesos = sol_nueva;
                porcentaje_ant = porcentaje_nuevo;
                mejora = true;
                num_vecinos = 0;
            }
        }
    }
    cout << "Evaluaciones y numero de vecinos generados sin mejorar: " << num_eval << " : " << num_vecinos << endl;
}

void EjecutarLocalSearch(int conjunto, int bd) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    double porcentaje = 0;
    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    for (int i = 0; i < train[0].size(); i++) {
        pesos.push_back(0);
    }
    t_inicio = std::chrono::high_resolution_clock::now();
    localSearch(train, clases_train, pesos);
    t_fin = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(t_fin - t_inicio);
    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". train-train (porcentaje): " << porcentaje << endl;
    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". train-test (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;

    for (int i = 0; i < train[0].size(); i++) {
        pesos.push_back(0);
    }
    t_inicio = std::chrono::high_resolution_clock::now();
    localSearch(test, clases_test, pesos);
    t_fin = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(t_fin - t_inicio);
    KNN(test, clases_test, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". test-test (porcentaje): " << porcentaje << endl;
    KNN_distintos(test, clases_test, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". test-train (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;
}
