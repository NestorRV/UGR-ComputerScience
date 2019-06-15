#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include <vector>
#include <chrono>
#include <iostream>
#include <random>
#include <algorithm>
#include "Utilidades.h"
#include "K-NN.h"

using namespace std;

// Modificar vector solucion siguiento una distribución normal
void modificarPeso(vector<float> &solucion, const int &posicion);
// Calcula el vector de pesos para el conjunto de datos train
void localSearch(const vector<vector<float> > &train, const vector<int> &clases_train, vector<float> &pesos);
// Ejecuta el algoritmo LocalSearch para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarLocalSearch(int conjunto, int bd);

#endif /* LOCALSEARCH_H */
