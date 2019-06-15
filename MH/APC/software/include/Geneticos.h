#ifndef GENETICOS_H
#define GENETICOS_H

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
vector<vector<float> > poblacionInicial(const int &num_caracteristicas);
// Evalua como de buena es una poblacion, gaurdando el porcentaje de acierto de cada solucion en el vector pcts_poblacion
void evalPoblacion(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &poblacion, vector<float> &pcts_poblacion, vector<bool> &flag_eval, int &num_eval);
// Evalua como de buena es una poblacion, gaurdando el porcentaje de acierto de cada solucion en el vector pcts_poblacion (version para AGEstacionarios)
void evalPoblacionEstacionarios(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &poblacion, vector<float> &pcts_poblacion, int &num_eval);
// Escocge dos elementos aleatorios de la poblacion y devuelve del mejor en función de su porcentaje de acierto
int torneoBinario(const vector<float> &pcts_poblacion);
// Cruce BLX-alpha con alpha = 0.3.
pair<vector<float>, vector<float>> cruceBLX(const vector<float> &padre_1, const vector<float> &padre_2);
// Mura el gen gen_mutar dentro del cromosoma cromosoma
void mutarCromosoma(vector<float> &cromosoma, const int &gen_mutar);
// Algoritmo Genetico Generacional con cruce BLX. Devuelve el vector de pesos solución
vector<float> GeneticoGeneracionalBLX(const vector<vector<float> > &train, const vector<int> &clases_train);
// Algoritmo Genetico Generacional con cruce aritmetico. Devuelve el vector de pesos solución
vector<float> GeneticoGeneracionalCA(const vector<vector<float> > &train, const vector<int> &clases_train);
// Algoritmo Genetico Estacionario con cruce BLX. Devuelve el vector de pesos solución
vector<float> GeneticoEstacionarioBLX(const vector<vector<float> > &train, const vector<int> &clases_train);
// Algoritmo Genetico Estacionario con cruce aritmetico. Devuelve el vector de pesos solución
vector<float> GeneticoEstacionarioCA(const vector<vector<float> > &train, const vector<int> &clases_train);


// Ejecuta el algoritmo GeneticoGeneracionalBLX para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarGeneticoGeneracionalBLX(int conjunto, int bd);
// Ejecuta el algoritmo GeneticoGeneracionalBLX para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarGeneticoGeneracionalCA(int conjunto, int bd);
// Ejecuta el algoritmo GeneticoEstacionarioBLX para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarGeneticoEstacionarioBLX(int conjunto, int bd);
// Ejecuta el algoritmo GeneticoEstacionarioCA para el conjunto de datos indicado por conjunto sobre la base de datos bd
void EjecutarGeneticoEstacionarioCA(int conjunto, int bd);

#endif /* GENETICOS_H */
