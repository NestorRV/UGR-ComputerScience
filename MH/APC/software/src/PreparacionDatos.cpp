#include "PreparacionDatos.h"

void checkSize(const char* filename, int &num_muestras, int &num_caracteristicas) {
    if (strcmp(filename, "./Data/csv/sonar_test_1.csv") == 0) {
        num_muestras = 104;
        num_caracteristicas = 61;
    } else if (strcmp(filename, "./Data/csv/sonar_test_2.csv") == 0) {
        num_muestras = 104;
        num_caracteristicas = 61;
    } else if (strcmp(filename, "./Data/csv/sonar_test_3.csv") == 0) {
        num_muestras = 104;
        num_caracteristicas = 61;
    } else if (strcmp(filename, "./Data/csv/sonar_test_4.csv") == 0) {
        num_muestras = 104;
        num_caracteristicas = 61;
    } else if (strcmp(filename, "./Data/csv/sonar_test_5.csv") == 0) {
        num_muestras = 104;
        num_caracteristicas = 61;
    } else if (strcmp(filename, "./Data/csv/sonar_train_1.csv") == 0) {
        num_muestras = 104;
        num_caracteristicas = 61;
    } else if (strcmp(filename, "./Data/csv/sonar_train_2.csv") == 0) {
        num_muestras = 104;
        num_caracteristicas = 61;
    } else if (strcmp(filename, "./Data/csv/sonar_train_3.csv") == 0) {
        num_muestras = 104;
        num_caracteristicas = 61;
    } else if (strcmp(filename, "./Data/csv/sonar_train_4.csv") == 0) {
        num_muestras = 104;
        num_caracteristicas = 61;
    } else if (strcmp(filename, "./Data/csv/sonar_train_5.csv") == 0) {
        num_muestras = 104;
        num_caracteristicas = 61;
    } else if (strcmp(filename, "./Data/csv/spambase_test_1.csv") == 0) {
        num_muestras = 230;
        num_caracteristicas = 58;
    } else if (strcmp(filename, "./Data/csv/spambase_test_2.csv") == 0) {
        num_muestras = 230;
        num_caracteristicas = 58;
    } else if (strcmp(filename, "./Data/csv/spambase_test_3.csv") == 0) {
        num_muestras = 230;
        num_caracteristicas = 58;
    } else if (strcmp(filename, "./Data/csv/spambase_test_4.csv") == 0) {
        num_muestras = 230;
        num_caracteristicas = 58;
    } else if (strcmp(filename, "./Data/csv/spambase_test_5.csv") == 0) {
        num_muestras = 230;
        num_caracteristicas = 58;
    } else if (strcmp(filename, "./Data/csv/spambase_train_1.csv") == 0) {
        num_muestras = 230;
        num_caracteristicas = 58;
    } else if (strcmp(filename, "./Data/csv/spambase_train_2.csv") == 0) {
        num_muestras = 230;
        num_caracteristicas = 58;
    } else if (strcmp(filename, "./Data/csv/spambase_train_3.csv") == 0) {
        num_muestras = 230;
        num_caracteristicas = 58;
    } else if (strcmp(filename, "./Data/csv/spambase_train_4.csv") == 0) {
        num_muestras = 230;
        num_caracteristicas = 58;
    } else if (strcmp(filename, "./Data/csv/spambase_train_5.csv") == 0) {
        num_muestras = 230;
        num_caracteristicas = 58;
    } else if (strcmp(filename, "./Data/csv/wdbc_test_1.csv") == 0) {
        num_muestras = 285;
        num_caracteristicas = 31;
    } else if (strcmp(filename, "./Data/csv/wdbc_test_2.csv") == 0) {
        num_muestras = 285;
        num_caracteristicas = 31;
    } else if (strcmp(filename, "./Data/csv/wdbc_test_3.csv") == 0) {
        num_muestras = 285;
        num_caracteristicas = 31;
    } else if (strcmp(filename, "./Data/csv/wdbc_test_4.csv") == 0) {
        num_muestras = 285;
        num_caracteristicas = 31;
    } else if (strcmp(filename, "./Data/csv/wdbc_test_5.csv") == 0) {
        num_muestras = 285;
        num_caracteristicas = 31;
    } else if (strcmp(filename, "./Data/csv/wdbc_train_1.csv") == 0) {
        num_muestras = 284;
        num_caracteristicas = 31;
    } else if (strcmp(filename, "./Data/csv/wdbc_train_2.csv") == 0) {
        num_muestras = 284;
        num_caracteristicas = 31;
    } else if (strcmp(filename, "./Data/csv/wdbc_train_3.csv") == 0) {
        num_muestras = 284;
        num_caracteristicas = 31;
    } else if (strcmp(filename, "./Data/csv/wdbc_train_4.csv") == 0) {
        num_muestras = 284;
        num_caracteristicas = 31;
    } else if (strcmp(filename, "./Data/csv/wdbc_train_5.csv") == 0) {
        num_muestras = 284;
        num_caracteristicas = 31;
    }
}

void leerConjunto(vector<vector<float> > & data, const char* filename) {
    int num_muestras = 0, num_caracteristicas = 0;
    data.resize(0);
    checkSize(filename, num_muestras, num_caracteristicas);
    data.resize(num_muestras);
    for (int i = 0; i < num_muestras; i++)
        data[i].resize(num_caracteristicas);
    ifstream file(filename);

    std::string line;
    std::getline(file, line);
    for (int row = 0; row < num_muestras; row++) {
        //Leo de nuevo para empezar a coger datos y no coger la cabecera
        std::getline(file, line);
        stringstream iss(line);

        for (int col = 0; col <= num_caracteristicas; ++col) {
            std::string val;
            std::getline(iss, val, ',');
            stringstream convertor(val);
            convertor >> data[row][col];
        }
    }
}
