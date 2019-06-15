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

void EjecutarKNN(int conjunto, int bd) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos_1;
    double porcentaje = 0;
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
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". train-test (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;

    start = std::chrono::high_resolution_clock::now();
    KNN_distintos(test, clases_test, train, clasificacion, pesos_1);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". test-train (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;
}
