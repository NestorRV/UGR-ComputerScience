#ifndef EVOLUTIVOS_H
#define EVOLUTIVOS_H

#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <stdlib.h> 
#include <random>
#include <utility>
#include "Utilidades.h"
#include "K-NN.h"

using namespace std;

// Genera una primera población de 30 individuos, cada uno de ellos de tamaño num_caracteristicas
vector<vector<float> > poblacionInicial(const int &num_caracteristicas, const int &size);
// Evalua como de buena es una poblacion, gaurdando el porcentaje de acierto de cada solucion en el vector pcts_poblacion
void evalPoblacion(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &poblacion, vector<float> &pcts_poblacion, vector<bool> &flag_eval, int &num_eval);
// Evalua como de buena es una poblacion, gaurdando el porcentaje de acierto de cada solucion en el vector pcts_poblacion
void evalPoblacion(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &poblacion, vector<float> &pcts_poblacion, int &num_eval);
// Escocge dos elementos aleatorios de la poblacion y devuelve del mejor en función de su porcentaje de acierto
int torneoBinario(const vector<float> &pcts_poblacion, const int &random);
// Cruce BLX-alpha con alpha = 0.3.
pair<vector<float>, vector<float>> cruceBLX(const vector<float> &padre_1, const vector<float> &padre_2);
// Mura el gen gen_mutar dentro del cromosoma cromosoma
void mutarCromosoma(vector<float> &cromosoma, const int &gen_mutar);

// Calcula el vector de pesos para el conjunto de datos train
void localSearchMemeticos(const vector<vector<float> > &train, const vector<int> &clases_train, vector<float> &pesos, int &num_eval);
// Algoritmo Genetico Generacional con cruce BLX. Devuelve el vector de pesos solución
vector<float> GeneticoGeneracionalBLX(const vector<vector<float> > &train, const vector<int> &clases_train);
// Cada 10 generaciones, aplicar la BL sobre los 0.1·N mejores cromosomas de la población actual(N es el tamaño de ésta)
vector<float> MemeticoGeneracionalBLX_10_0_1_mej(const vector<vector<float> > &train, const vector<int> &clases_train);

// Evolución diferencial Rand/1
vector<float> EvolucionDiferencialRand(const vector<vector<float> > &train, const vector<int> &clases_train);
// Evolución diferencial CurrentToBest/1
vector<float> EvolucionDiferencialBest(const vector<vector<float> > &train, const vector<int> &clases_train);

// Ejecuta el algoritmo GeneticoGeneracionalBLX para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarGeneticoGeneracionalBLX(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos);
// Ejecuta el algoritmo MemeticoGeneracionalBLX_10_0_1_mej para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarMemeticoGeneracionalBLX_10_0_1_mej(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos);
// Ejecuta el algoritmo EvolucionDiferencialRand para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarEvolucionDiferencialRand(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos);
// Ejecuta el algoritmo EvolucionDiferencialBest para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarEvolucionDiferencialBest(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos);

#endif /* EVOLUTIVOS_H */