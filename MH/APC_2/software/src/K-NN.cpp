#include "K-NN.h"

int vecinoMasCercano(const vector<vector<float> > &datos, const vector<float> &actual, const int &posicion, const vector<float> &pesos) {
    int num_muestras, num_caracteristicas, vecino_mas_cercano = -1;
    float distancia_actual, mejor_distancia = 9999;

    num_muestras = datos.size();
    num_caracteristicas = datos[0].size();

    for (int i = 0; i < num_muestras; i++) {
        if (posicion != i) {
            distancia_actual = distanciaEuclidea(datos[i], actual, pesos);
            if (distancia_actual < mejor_distancia) {
                mejor_distancia = distancia_actual;
                vecino_mas_cercano = i;
            }
        }
    }

    return vecino_mas_cercano;
}

int vecinoMasCercano_distintos(const vector<vector<float> > &datos, const vector<float> &actual, const vector<float> &pesos) {
    int num_muestras, num_caracteristicas, vecino_mas_cercano = -1;
    float distancia_actual, mejor_distancia = 9999;

    num_muestras = datos.size();
    num_caracteristicas = datos[0].size();

    for (int i = 0; i < num_muestras; i++) {
        distancia_actual = distanciaEuclidea(datos[i], actual, pesos);
        if (distancia_actual < mejor_distancia) {
            mejor_distancia = distancia_actual;
            vecino_mas_cercano = i;
        }
    }

    return vecino_mas_cercano;
}

void KNN_distintos(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &test, vector<int> &clasificacion, const vector<float> &pesos) {
    clasificacion.resize(0);
    int vecino_mas_cercano = 0;
    vector<float> elegido;
    int num_muestras, num_caracteristicas;
    num_muestras = test.size();
    num_caracteristicas = test[0].size();

    for (int i = 0; i < num_muestras; i++) {
        vecino_mas_cercano = vecinoMasCercano_distintos(train, test[i], pesos);
        clasificacion.push_back(clases_train[vecino_mas_cercano]);
    }
}

void KNN(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &test, vector<int> &clasificacion, const vector<float> &pesos) {
    clasificacion.resize(0);
    int vecino_mas_cercano = 0;
    vector<float> elegido;
    int num_muestras, num_caracteristicas;
    num_muestras = test.size();
    num_caracteristicas = test[0].size();

    for (int i = 0; i < num_muestras; i++) {
        vecino_mas_cercano = vecinoMasCercano(train, test[i], i, pesos);
        clasificacion.push_back(clases_train[vecino_mas_cercano]);
    }
}

void EjecutarKNN(int conjunto, int bd, ofstream &fs, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos_1;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    for (int i = 0; i < train[0].size(); i++) {
        pesos_1.push_back(1);
    }

    start = std::chrono::high_resolution_clock::now();
    KNN_distintos(train, clases_train, test, clasificacion, pesos_1);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    acierto = tasaAcierto(clases_test, clasificacion);
    reduccion = tasaReduccion(pesos_1);
    tasa_final = tasaAgregacion(clases_test, clasificacion, pesos_1, 0.5);
    cout << "Set " << conjunto << ". train-test (tasa acierto, tasa reduccion, tasa final, tiempo): " << acierto << " : " << reduccion << " : " << tasa_final << " : " << time.count() << endl;
    fs << acierto << " " << reduccion << " " << tasa_final << " " << time.count() << endl;

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