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
    porcentaje_ant = tasaAgregacion(clases_train, clasificacion, pesos, 0.5);

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
            porcentaje_nuevo = tasaAgregacion(clases_train, clasificacion, pesos, 0.5);
            num_eval++;

            if (porcentaje_nuevo > porcentaje_ant) {
                pesos = sol_nueva;
                porcentaje_ant = porcentaje_nuevo;
                mejora = true;
                num_vecinos = 0;
            }
        }
    }
}

void EjecutarLocalSearch(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    double acierto = 0, reduccion = 0, tasa_final = 0;
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
    acierto = tasaAcierto(clases_train, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_train, clasificacion, pesos, 0.5);
    cout << "Set " << conjunto << ". train-train (tasa acierto, tasa reduccion, tasa final): " << acierto << " : " << reduccion << " : " << tasa_final << endl;
    over << acierto << " " << reduccion << " " << tasa_final << endl;

    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    acierto = tasaAcierto(clases_test, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_test, clasificacion, pesos, 0.5);
    cout << "Set " << conjunto << ". train-test (tasa acierto, tasa reduccion, tasa final, tiempo): " << acierto << " : " << reduccion << " : " << tasa_final << " : " << time.count() << endl;
    fs << acierto << " " << reduccion << " " << tasa_final << " " << time.count() << endl;
    over << acierto << " " << reduccion << " " << tasa_final << endl;
    for(int i = 0; i < pesos.size(); i++){
        if(pesos[i] < 0.1){
            caracteristicas << i << " ";
        }
    }
    caracteristicas << endl;

    aciertos.push_back(acierto);
    reducciones.push_back(reduccion);
    finales.push_back(tasa_final);
    tiempos.push_back(time.count());

    if(conjunto == 5){
        double media_acierto = 0, media_reduccion = 0, media_final = 0, media_tiempo = 0;
        for(int i = 0; i < 5; i++){
            media_acierto += aciertos[i];
            media_reduccion += reducciones[i];
            media_final += finales[i];
            media_tiempo += tiempos[i];
        }

        cout << endl << "Medias: (tasa acierto, tasa reduccion, tasa final, tiempo). " << media_acierto / 5.0 << " : " << media_reduccion / 5.0 << " : " << media_final / 5.0 << " : " << media_tiempo / 5.0 << endl;
        fs << endl << media_acierto / 5.0 << " " << media_reduccion / 5.0 << " " << media_final / 5.0 << " " << media_tiempo / 5.0 << endl;
    }
}
