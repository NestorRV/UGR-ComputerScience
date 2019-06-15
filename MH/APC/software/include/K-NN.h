#ifndef K_NN_H
#define K_NN_H

#include <vector>
#include <chrono>
#include <iostream>
#include "Utilidades.h"

using namespace std;

// Calcula el mejor vecino para actual del conjunto datos teniendo en cuenta los pesos y lo almacena en elegido teniendo en cuenta
// que los conjuntos train y test son distintos
int vecinoMasCercano_distintos(const vector<vector<float> > &datos, const vector<float> &actual, const vector<float> &pesos);
// Calcula el mejor vecino para actual del conjunto datos teniendo en cuenta los pesos y lo almacena en elegido
int vecinoMasCercano(const vector<vector<float> > &datos, const vector<float> &actual, const int &posicion, const vector<float> &pesos);
// Los conjuntos train y test son distintos.
void KNN_distintos(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &test, vector<int> &clasificacion, const vector<float> &pesos);
// Clasificador 1-NN
void KNN(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &test, vector<int> &clasificacion, const vector<float> &pesos);
// Ejecuta el algoritmo K-NN para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarKNN(int conjunto, int bd);

#endif /* K_NN_H */
