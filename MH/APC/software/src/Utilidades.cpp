#include "Utilidades.h"

float distanciaEuclidea(const vector<float> &v1, const vector<float> &v2) {
    float distancia = 0, diferencia = 0;
    int num_caracteristicas = v1.size();

    for (int i = 0; i < num_caracteristicas; i++) {
        diferencia = v1[i] - v2[i];
        distancia += diferencia * diferencia;
    }
    return sqrt(distancia);
}

float distanciaEuclidea(const vector<float> &v1, const vector<float> &v2, const vector<float> &pesos) {
    int num_caracteristicas = v1.size();
    float distancia = 0, diferencia = 0;

    for (int i = 0; i < num_caracteristicas; i++) {
        diferencia = pesos[i] * (v1[i] - v2[i]);
        distancia += diferencia * diferencia;
    }
    return sqrt(distancia);
}

double tasaAcierto(const vector<int> &correctas, const vector<int> &calculadas) {
    int num_caracteristicas, correctos = 0;
    double porcentaje = -1;
    num_caracteristicas = correctas.size();

    for (int i = 0; i < num_caracteristicas; i++) {
        if (correctas[i] == calculadas[i]) {
            correctos++;
        }
    }
    porcentaje = (correctos * 1.0 / num_caracteristicas)*100.0;
    return porcentaje;
}

void CargarDatos(vector<vector<float> > &train, vector<vector<float> > &test, vector<int> &clases_train, vector<int> &clases_test, const int &conjunto, const int & bd) {
    switch (bd) {
        case 1:
            switch (conjunto) {
                case 1:
                    leerConjunto(train, "./Data/csv/sonar_train_1.csv");
                    leerConjunto(test, "./Data/csv/sonar_test_1.csv");
                    break;
                case 2:
                    leerConjunto(train, "./Data/csv/sonar_train_2.csv");
                    leerConjunto(test, "./Data/csv/sonar_test_2.csv");
                    break;
                case 3:
                    leerConjunto(train, "./Data/csv/sonar_train_3.csv");
                    leerConjunto(test, "./Data/csv/sonar_test_3.csv");
                    break;
                case 4:
                    leerConjunto(train, "./Data/csv/sonar_train_4.csv");
                    leerConjunto(test, "./Data/csv/sonar_test_4.csv");
                    break;
                case 5:
                    leerConjunto(train, "./Data/csv/sonar_train_5.csv");
                    leerConjunto(test, "./Data/csv/sonar_test_5.csv");
                    break;
            }
            break;
        case 2:
            switch (conjunto) {
                case 1:
                    leerConjunto(train, "./Data/csv/spambase_train_1.csv");
                    leerConjunto(test, "./Data/csv/spambase_test_1.csv");
                    break;
                case 2:
                    leerConjunto(train, "./Data/csv/spambase_train_2.csv");
                    leerConjunto(test, "./Data/csv/spambase_test_2.csv");
                    break;
                case 3:
                    leerConjunto(train, "./Data/csv/spambase_train_3.csv");
                    leerConjunto(test, "./Data/csv/spambase_test_3.csv");
                    break;
                case 4:
                    leerConjunto(train, "./Data/csv/spambase_train_4.csv");
                    leerConjunto(test, "./Data/csv/spambase_test_4.csv");
                    break;
                case 5:
                    leerConjunto(train, "./Data/csv/spambase_train_5.csv");
                    leerConjunto(test, "./Data/csv/spambase_test_5.csv");
                    break;
            }
            break;
        case 3:
            switch (conjunto) {
                case 1:
                    leerConjunto(train, "./Data/csv/wdbc_train_1.csv");
                    leerConjunto(test, "./Data/csv/wdbc_test_1.csv");
                    break;
                case 2:
                    leerConjunto(train, "./Data/csv/wdbc_train_2.csv");
                    leerConjunto(test, "./Data/csv/wdbc_test_2.csv");
                    break;
                case 3:
                    leerConjunto(train, "./Data/csv/wdbc_train_3.csv");
                    leerConjunto(test, "./Data/csv/wdbc_test_3.csv");
                    break;
                case 4:
                    leerConjunto(train, "./Data/csv/wdbc_train_4.csv");
                    leerConjunto(test, "./Data/csv/wdbc_test_4.csv");
                    break;
                case 5:
                    leerConjunto(train, "./Data/csv/wdbc_train_5.csv");
                    leerConjunto(test, "./Data/csv/wdbc_test_5.csv");
                    break;
            }
            break;
    }

    for (int i = 0; i < train.size(); i++) {
        clases_train.push_back(train[i][train[i].size() - 1]);
        train[i].pop_back();
    }

    for (int i = 0; i < test.size(); i++) {
        clases_test.push_back(test[i][test[i].size() - 1]);
        test[i].pop_back();
    }
}

vector<float> solInicialAleatoria(const int &size) {
    vector<float> solucion_inicial(size);
    for (int i = 0; i < size; i++) {
        solucion_inicial[i] = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
    }
    return solucion_inicial;
}

float truncar(const float &numero) {
    float salida = numero;
    if (numero < 0) {
        salida = 0;
    } else if (numero > 1) {
        salida = 1;
    }
    return salida;
}
