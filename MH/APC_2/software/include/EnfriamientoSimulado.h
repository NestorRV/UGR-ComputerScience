#ifndef ENFRIAMIENTOSIMULADO_H
#define ENFRIAMIENTOSIMULADO_H

#include <vector>
#include <chrono>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "Utilidades.h"
#include "K-NN.h"

using namespace std;

//Muta la componente indice del vector solucion siguiendo una distribucion normal
void mutarSolucion(vector<float> &sol, const int &gen);
// Algoritmos d eenfriamiento simulado
vector<float> EnfriamientoSimulado(const vector<vector<float> > &train, const vector<int> &clases_train);
// Ejecuta el algoritmos Enfriamiento Simulado
void EjecutarEnfriamientoSimulado(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos);

#endif /* ENFRIAMIENTOSIMULADO_H */
