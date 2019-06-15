#include "Relief.h"

void amigo_enemigoCercano(const vector<vector<float> > & train, const vector<int> &clases, const vector<float> &actual, const int &posicion, vector<float> &amigo, vector<float> &enemigo) {
    float distancia_actual, mejor_distancia_amigo = 9999, mejor_distancia_enemigo = 9999;
    int mejor_amigo, mejor_enemigo;
    for (int i = 0; i < train.size(); i++) {
        distancia_actual = distanciaEuclidea(actual, train[i]);
        if (clases[i] == clases[posicion]) {
            if (posicion != i && distancia_actual < mejor_distancia_amigo) {
                mejor_distancia_amigo = distancia_actual;
                mejor_amigo = i;
            }
        } else {
            if (posicion != i && distancia_actual < mejor_distancia_enemigo) {
                mejor_distancia_enemigo = distancia_actual;
                mejor_enemigo = i;
            }
        }
    }
    amigo = train[mejor_amigo];
    enemigo = train[mejor_enemigo];
}

void actualizarPesos(vector<float> &pesos, const vector<float> & amigo, const vector<float> & enemigo, const vector<float> & actual) {
    for (int i = 0; i < pesos.size(); i++) {
        pesos[i] = pesos[i] + fabs(actual[i] - enemigo[i]) - fabs(actual[i] - amigo[i]);
    }
}

void Relief(const vector<vector<float> > &train, const vector<int> &clases, vector<float> &pesos) {
    vector<float> amigo, enemigo;
    pesos.resize(train[0].size());
    for (int i = 0; i < pesos.size(); i++)
        pesos[i] = 0;

    for (int i = 0; i < train.size(); i++) {
        amigo_enemigoCercano(train, clases, train[i], i, amigo, enemigo);
        actualizarPesos(pesos, amigo, enemigo, train[i]);
    }

    float max_peso = *max_element(pesos.begin(), pesos.end());

    for (int i = 0; i < pesos.size(); i++) {
        if (pesos[i] < 0)
            pesos[i] = 0;
        else
            pesos[i] /= max_peso;
    }
}

void EjecutarRelief(int conjunto, int bd, ofstream &fs, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    for (int i = 0; i < train[0].size(); i++) {
        pesos.push_back(0);
    }
    start = std::chrono::high_resolution_clock::now();
    Relief(train, clases_train, pesos);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    acierto = tasaAcierto(clases_test, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_test, clasificacion, pesos, 0.5);
    cout << "Set " << conjunto << ". train-test (tasa acierto, tasa reduccion, tasa final, tiempo): " << acierto << " : " << reduccion << " : " << tasa_final << " : " << time.count() << endl;
    fs << acierto << " " << reduccion << " " << tasa_final << " " << time.count() << endl;
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
        float media_acierto = 0, media_reduccion = 0, media_final = 0, media_tiempo = 0;
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