#ifndef MEMETICOS_H
#define MEMETICOS_H

using namespace std;

#include <vector>
#include <chrono>
#include <iostream>
#include <random>
#include <algorithm>
#include <utility>
#include "Utilidades.h"
#include "K-NN.h"
#include "LocalSearch.h"
#include "Geneticos.h"

// Genera una primera población de 10 individuos, cada uno de ellos de tamaño num_caracteristicas
vector<vector<float> > poblacionInicialMemeticos(const int &num_caracteristicas);
// Escocge dos elementos aleatorios de la poblacion y devuelve del mejor en función de su porcentaje de acierto
int torneoBinarioMemetico(const vector<float> &pcts_poblacion);
// Calcula el vector de pesos para el conjunto de datos train
void localSearchMemeticos(const vector<vector<float> > &train, const vector<int> &clases_train, vector<float> &pesos, int &num_eval);
// Cada 10 generaciones, aplicar la BL sobre todos los cromosomas de la población
vector<float> MemeticoGeneracionalBLX_10_1(const vector<vector<float> > &train, const vector<int> &clases_train);
// Cada 10 generaciones, aplicar la BL sobre un subconjunto de cromosomas de la población seleccionado aleatoriamente con probabilidad p_LS igual a 0.1 para cada cromosoma
vector<float> MemeticoGeneracionalBLX_10_0_1(const vector<vector<float> > &train, const vector<int> &clases_train);
// Cada 10 generaciones, aplicar la BL sobre los 0.1·N mejores cromosomas de la población actual(N es el tamaño de ésta)
vector<float> MemeticoGeneracionalBLX_10_0_1_mej(const vector<vector<float> > &train, const vector<int> &clases_train);
// Ejecuta el algoritmo MemeticoGeneracionalBLX_10_1 para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarMemeticoGeneracionalBLX_10_1(int conjunto, int bd);
// Ejecuta el algoritmo MemeticoGeneracionalBLX_10_0_1 para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarMemeticoGeneracionalBLX_10_0_1(int conjunto, int bd);
// Ejecuta el algoritmo MemeticoGeneracionalBLX_10_0_1_mej para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarMemeticoGeneracionalBLX_10_0_1_mej(int conjunto, int bd);

#endif /* MEMETICOS_H */

