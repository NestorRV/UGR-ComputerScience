#include "ILS.h"

default_random_engine generator4;
normal_distribution<double> distribution4(0.0, 0.16);

void mutarPosicion(vector<float> &solucion, const int &posicion) {
    float numero;
    solucion[posicion] += distribution4(generator4);
    numero = truncar(solucion[posicion]);
    solucion[posicion] = numero;
}

void localSearchILS(const vector<vector<float> > &train, const vector<int> &clases_train, vector<float> &pesos) {
    int num_eval = 0, num_caracteristicas = train[0].size();
    float porcentaje_ant, porcentaje_nuevo = 0;
    bool mejora = true;
    vector<float> sol_nueva;
    vector<int> clasificacion, indices(num_caracteristicas);
    int posicion_auxiliar = 0, elegido = 0, i_auxiliar = 0;

    for (int i = 0; i < num_caracteristicas; i++) {
        indices[i] = i;
    }

    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje_ant = tasaAgregacion(clases_train, clasificacion, pesos, 0.5);

    while (num_eval < 1000) {
        mejora = false;
        for (int i = 0; i < num_caracteristicas && !mejora; i++) {
            sol_nueva = pesos;
            elegido = rand() % (indices.size() - i_auxiliar) + i_auxiliar;
            posicion_auxiliar = indices[i_auxiliar];
            indices[i_auxiliar] = indices[elegido];
            indices[elegido] = posicion_auxiliar;
            modificarPeso(sol_nueva, indices[i_auxiliar]);
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
            }
        }
    }
}

vector<float> ILS(const vector<vector<float> > &train, const vector<int> &clases_train) {
    int num_caracteristicas = train[0].size(), num_mutaciones = 0, indice = 0, elegido = 0, posicion_auxiliar = 0;
    vector <float> solucion, mejor_solucion, sol_aux;
    float tasa_actual = 0, tasa_mejor = 0;
    vector<int> clasificacion, indices(num_caracteristicas);

    for (int i = 0; i < num_caracteristicas; i++) {
        indices[i] = i;
    }

    solucion = solInicialAleatoria(num_caracteristicas);
    KNN(train, clases_train, train, clasificacion, solucion);
    tasa_actual = tasaAgregacion(clases_train, clasificacion, solucion, 0.5);
    mejor_solucion = solucion;
    tasa_mejor = tasa_actual;
    
    num_mutaciones = 0.1 * num_caracteristicas;

    localSearchILS(train, clases_train, solucion);
    
    for(int i = 0; i < 14; i++){
        for(int j = 0; j < num_mutaciones; j++) {
            elegido = rand() % (indices.size() - j) + j;
            posicion_auxiliar = indices[j];
            indices[j] = indices[elegido];
            indices[elegido] = posicion_auxiliar;
        }

        for(int i = 0; i < num_mutaciones; i++){
            mutarPosicion(solucion, indices[i]);
        }

        localSearchILS(train, clases_train, solucion);
        
        KNN(train, clases_train, train, clasificacion, solucion);
        tasa_actual = tasaAgregacion(clases_train, clasificacion, solucion, 0.5);

        if(tasa_actual > tasa_mejor) {
            mejor_solucion = solucion;
            tasa_mejor = tasa_actual;
        }

        solucion = mejor_solucion;
    }

    return mejor_solucion;
}

void EjecutarILS(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    double acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    t_inicio = std::chrono::high_resolution_clock::now();
    pesos = ILS(train, clases_train);
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