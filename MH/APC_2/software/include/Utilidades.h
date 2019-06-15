#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <vector>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "PreparacionDatos.h"

using namespace std;

// Devuelve la distancia Euclidea entre v1 y v2
float distanciaEuclidea(const vector<float> &v1, const vector<float> &v2);
// Devuelve la distancia Euclidea entre v1 y v2 teniendo en cuenta el peso de cada caracteristca (vector pesos)
float distanciaEuclidea(const vector<float> &v1, const vector<float> &v2, const vector<float> &pesos);
// Calcula la tasa de acierto suponinendo que calculadas son las clases obtenida
// por nuestro algoritmo y que correctas son las originales
float tasaAcierto(const vector<int> &correctas, const vector<int> &calculadas);
// Calcula la tasa de reduccion, es decir, el porcentaje de valores menores que
//0.1 en el vector de pesos
float tasaReduccion(const vector<float> &pesos);
// Calcula la tasa final en función de la tasa de acierto y la tasa de reduccion
float tasaAgregacion(const vector<int> &correctas, const vector<int> &etiquetas, const vector<float> &pesos, const double &alpha);
// Carga un conjunto de la base de datos bd en trian y test y guarda las clases en clases_train y clases_test
void CargarDatos(vector<vector<float> > &train, vector<vector<float> > &test, vector<int> &clases_train, vector<int> &clases_test, const int & conjunto, const int & bd);
// Genera una primera solucion de tamaño size
vector<float> solInicialAleatoria(const int &size);
// Trunca un número a 0 si es negativo o a 1 si es mayor que uno
float truncar(const float &numero);

#endif /* UTILIDADES_H */
