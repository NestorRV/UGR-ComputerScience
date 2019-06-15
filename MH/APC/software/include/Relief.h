#ifndef RELIEF_H
#define RELIEF_H

#include <vector>
#include <algorithm>
#include <chrono>
#include <math.h>
#include <iostream>
#include "K-NN.h"
#include "Utilidades.h"

using namespace std;

// Guarda en amigo y enemigo el amigo y el enemigo, respectivamente, más cercanos a actual del conjunto train
void amigo_enemigoCercano(const vector<vector<float> > & train, const vector<vector<float> > &clases, const vector<float> &actual, const int &posicion, vector<float> &amigo, vector<float> &enemigo);
// Actualizar el vector de pesos en función del amigo y el enemigo más cercano y el propio elemento actual)
void actualizarPesos(vector<float> &pesos, const vector<float> & amigo, const vector<float> & enemigo, const vector<float> & actual);
// Calcula el vector de pesos para el conjunto train y lo almacena en pesos
void Relief(const vector<vector<float> > &train, const vector<int> &clases, vector<float> &pesos);
// Ejecuta el algoritmo Relief para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarRelief(int conjunto, int bd);

#endif /* RELIEF_H */
