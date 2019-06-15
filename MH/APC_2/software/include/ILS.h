#ifndef ILS_H
#define ILS_H

#include <vector>
#include <chrono>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "Utilidades.h"
#include "K-NN.h"
#include "LocalSearch.h"

using namespace std;

void mutarPosicion(vector<float> &solucion, const int &posicion);
void localSearchILS(const vector<vector<float> > &train, const vector<int> &clases_train, vector<float> &pesos);
vector<float> ILS(const vector<vector<float> > &train, const vector<int> &clases_train);
void EjecutarILS(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos);

#endif /* ILS_H */