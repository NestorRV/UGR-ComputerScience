#ifndef PREPARACIONDATOS_H
#define PREPARACIONDATOS_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

// Para el conjunto de datos ubicado en filename determinar el número correto
// de muestras (num_muestras) y el número correcto de atributo (num_caracteristicas).
void checkSize(const char* filename, int &num_muestras, int &num_caracteristicas);
// Carga en data los datos ubicados en filename
void leerConjunto(vector<vector<float> > & data, const char* filename);

#endif /* PREPARACIONDATOS_H */
