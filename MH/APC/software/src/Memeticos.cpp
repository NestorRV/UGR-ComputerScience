#include "Memeticos.h"

vector<vector<float> > poblacionInicialMemeticos(const int &num_caracteristicas) {
    vector<vector<float> > poblacion_inicial(10);
    for (int i = 0; i < 10; i++) {
        poblacion_inicial[i] = solInicialAleatoria(num_caracteristicas);
    }
    return poblacion_inicial;
}

int torneoBinarioMemetico(const vector<float> &pcts_poblacion) {
    int uno, dos;

    uno = rand() % 10;
    do{
        dos = rand() % 10;
    } while(uno == dos);

    if (pcts_poblacion[uno] > pcts_poblacion[dos]) {
        dos = uno;
    }
    return dos;
}

void localSearchMemeticos(const vector<vector<float> > &train, const vector<int> &clases_train, vector<float> &pesos, int &num_eval) {
    int num_vecinos = 0, num_caracteristicas = train[0].size();
    float porcentaje_ant, porcentaje_nuevo = 0;
    bool mejora = true;
    vector<float> sol_nueva;
    vector<int> clasificacion, indices(num_caracteristicas);
    int posicion_auxiliar = 0, elegido = 0, i_auxiliar = 0;

    for (int i = 0; i < num_caracteristicas; i++) {
        indices[i] = i;
    }

    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje_ant = tasaAcierto(clases_train, clasificacion);

    while (num_vecinos < 2 * num_caracteristicas) {
        mejora = false;
        for (int i = 0; i < num_caracteristicas && !mejora; i++) {
            sol_nueva = pesos;
            elegido = rand() % (indices.size() - i_auxiliar) + i_auxiliar;
            posicion_auxiliar = indices[i_auxiliar];
            indices[i_auxiliar] = indices[elegido];
            indices[elegido] = posicion_auxiliar;
            modificarPeso(sol_nueva, indices[i_auxiliar]);
            num_vecinos++;
            i_auxiliar++;
            if (i_auxiliar == num_caracteristicas)
                i_auxiliar = 0;

            KNN(train, clases_train, train, clasificacion, sol_nueva);
            porcentaje_nuevo = tasaAcierto(clases_train, clasificacion);
            num_eval++;

            if (porcentaje_nuevo > porcentaje_ant) {
                pesos = sol_nueva;
                porcentaje_ant = porcentaje_nuevo;
                mejora = true;
            }
        }
    }
}

vector<float> MemeticoGeneracionalBLX_10_1(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<vector<float> > poblacion, padres(10), hijos(10);
    int num_caracteristicas = train[0].size(), num_eval = 0, elegido = 0, num_cruces = 0, cromosoma_mutar = 0, gen_mutar = 0, genes_generacion = 0, generacion = 0, mutar = 0;
    vector<bool> flag_eval(10, 0);
    vector<float> pcts_poblacion(10), pcts_padres(10), pcts_hijos(10), mejor;
    float porcentaje_mejor = 0;
    pair<vector<float>, vector<float> > hijosBLX;

    vector<int> index_mejores(10), index_peores(10);
    for (int i = 0; i < 10; i++) {
        index_mejores[i] = i;
        index_peores[i] = i;
    }

    poblacion = poblacionInicialMemeticos(num_caracteristicas);
    evalPoblacion(train, clases_train, poblacion, pcts_poblacion, flag_eval, num_eval);
    genes_generacion = 10 * num_caracteristicas;
    mutar = 1000.0 / genes_generacion;
    if (mutar == 0) {
        mutar = 1;
    }

    sort(index_mejores.begin(), index_mejores.end(), [&](int i1, int i2) {
        return pcts_poblacion[i1] > pcts_poblacion[i2]; });

    while (num_eval < 15000) {
        // Las parejas se cruzan la i con la i+1 (primera con segunda, tercera con cuarta...)
        for (int i = 0; i < 10; i++) {
            elegido = torneoBinarioMemetico(pcts_poblacion);
            padres[i] = poblacion[elegido];
            pcts_padres[i] = pcts_poblacion[elegido];
        }

        // Proceso de cruce con probabilidad 0.7 y 10 parejas
        num_cruces = 0.7 * 10;
        for (int i = 0; i < num_cruces; i += 2) {
            hijosBLX = cruceBLX(padres[i], padres[i + 1]);
            hijos[i] = hijosBLX.first;
            hijos[i + 1] = hijosBLX.second;
            flag_eval[i] = false;
            flag_eval[i + 1] = false;
            pcts_hijos[i] = 0;
            pcts_hijos[i + 1] = 0;
        }

        for (int i = num_cruces; i < 10; i++) {
            hijos[i] = padres[i];
            pcts_hijos[i] = pcts_padres[i];
        }

        // Proceso de mutacion con probabilidad 0.001 (se muta 1 gen de cada 1000)
        if (generacion % mutar == 0) {
            cromosoma_mutar = rand() % 10;
            gen_mutar = rand() % num_caracteristicas;
            mutarCromosoma(hijos[cromosoma_mutar], gen_mutar);
            flag_eval[cromosoma_mutar] = false;
        }

        // Aplicamos la busqueda local a toda la poblacion
        if(generacion % 10 == 0){
            for (int i = 0; i < hijos.size(); i++) {
                localSearchMemeticos(train, clases_train, hijos[i], num_eval);
                flag_eval[i] = false;
            }
        }

        // Evaluamos la nueva poblacion (la de hijos)
        evalPoblacion(train, clases_train, hijos, pcts_hijos, flag_eval, num_eval);
        // Obtenemos cual es el peor hijo ordenando un indice en función de los porcentajes
        sort(index_peores.begin(), index_peores.end(), [&](int i1, int i2) {
            return pcts_hijos[i1] < pcts_hijos[i2]; });

        // Guardamos el mejor de la población anterior y su porcenaje
        mejor = poblacion[index_mejores[0]];
        porcentaje_mejor = pcts_poblacion[index_mejores[0]];

        poblacion = hijos;
        pcts_poblacion = pcts_hijos;

        // Elitismo
        if (porcentaje_mejor > pcts_poblacion[index_peores[index_peores.size() - 1]]) {
            poblacion[index_peores[0]] = mejor;
            pcts_poblacion[index_peores[0]] = porcentaje_mejor;
        }

        sort(index_mejores.begin(), index_mejores.end(), [&](int i1, int i2) {
            return pcts_poblacion[i1] > pcts_poblacion[i2]; });

        generacion++;
    }
    return poblacion[index_mejores[0]];
}

vector<float> MemeticoGeneracionalBLX_10_0_1(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<vector<float> > poblacion, padres(10), hijos(10);
    int num_caracteristicas = train[0].size(), num_eval = 0, elegido = 0, num_cruces = 0, cromosoma_mutar = 0, gen_mutar = 0, genes_generacion = 0, generacion = 0, mutar = 0;
    int elegidoLS = 0;
    vector<bool> flag_eval(10, 0);
    vector<float> pcts_poblacion(10), pcts_padres(10), pcts_hijos(10), mejor;
    float porcentaje_mejor = 0;
    pair<vector<float>, vector<float> > hijosBLX;

    vector<int> index_mejores(10), index_peores(10);
    for (int i = 0; i < 10; i++) {
        index_mejores[i] = i;
        index_peores[i] = i;
    }

    poblacion = poblacionInicialMemeticos(num_caracteristicas);
    evalPoblacion(train, clases_train, poblacion, pcts_poblacion, flag_eval, num_eval);
    genes_generacion = 10 * num_caracteristicas;
    mutar = 1000.0 / genes_generacion;
    if (mutar == 0) {
        mutar = 1;
    }

    sort(index_mejores.begin(), index_mejores.end(), [&](int i1, int i2) {
        return pcts_poblacion[i1] > pcts_poblacion[i2]; });

    while (num_eval < 15000) {
        // Las parejas se cruzan la i con la i+1 (primera con segunda, tercera con cuarta...)
        for (int i = 0; i < 10; i++) {
            elegido = torneoBinarioMemetico(pcts_poblacion);
            padres[i] = poblacion[elegido];
            pcts_padres[i] = pcts_poblacion[elegido];
        }

        // Proceso de cruce con probabilidad 0.7 y 10 parejas
        num_cruces = 0.7 * 10;
        for (int i = 0; i < num_cruces; i += 2) {
            hijosBLX = cruceBLX(padres[i], padres[i + 1]);
            hijos[i] = hijosBLX.first;
            hijos[i + 1] = hijosBLX.second;
            flag_eval[i] = false;
            flag_eval[i + 1] = false;
            pcts_hijos[i] = 0;
            pcts_hijos[i + 1] = 0;
        }

        for (int i = num_cruces; i < 10; i++) {
            hijos[i] = padres[i];
            pcts_hijos[i] = pcts_padres[i];
        }

        // Proceso de mutacion con probabilidad 0.001 (se muta 1 gen de cada 1000)
        if (generacion % mutar == 0) {
            cromosoma_mutar = rand() % 10;
            gen_mutar = rand() % num_caracteristicas;
            mutarCromosoma(hijos[cromosoma_mutar], gen_mutar);
            flag_eval[cromosoma_mutar] = false;
        }

        // Aplicamos la busqueda local a un cromosoma aleatorio de la poblacion
        if(generacion % 10 == 0){
            elegidoLS = rand() % 10;
            localSearchMemeticos(train, clases_train, hijos[elegidoLS], num_eval);
            flag_eval[elegidoLS] = false;
        }

        // Evaluamos la nueva poblacion (la de hijos)
        evalPoblacion(train, clases_train, hijos, pcts_hijos, flag_eval, num_eval);
        // Obtenemos cual es el peor hijo ordenando un indice en función de los porcentajes
        sort(index_peores.begin(), index_peores.end(), [&](int i1, int i2) {
            return pcts_hijos[i1] < pcts_hijos[i2]; });

        // Guardamos el mejor de la población anterior y su porcenaje
        mejor = poblacion[index_mejores[0]];
        porcentaje_mejor = pcts_poblacion[index_mejores[0]];

        poblacion = hijos;
        pcts_poblacion = pcts_hijos;

        // Elitismo
        if (porcentaje_mejor > pcts_poblacion[index_peores[index_peores.size() - 1]]) {
            poblacion[index_peores[0]] = mejor;
            pcts_poblacion[index_peores[0]] = porcentaje_mejor;
        }

        sort(index_mejores.begin(), index_mejores.end(), [&](int i1, int i2) {
            return pcts_poblacion[i1] > pcts_poblacion[i2]; });

        generacion++;
    }
    return poblacion[index_mejores[0]];
}

vector<float> MemeticoGeneracionalBLX_10_0_1_mej(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<vector<float> > poblacion, padres(10), hijos(10);
    int num_caracteristicas = train[0].size(), num_eval = 0, elegido = 0, num_cruces = 0, cromosoma_mutar = 0, gen_mutar = 0, genes_generacion = 0, generacion = 0, mutar = 0;
    vector<bool> flag_eval(10, 0);
    vector<float> pcts_poblacion(10), pcts_padres(10), pcts_hijos(10), mejor;
    float porcentaje_mejor = 0;
    pair<vector<float>, vector<float> > hijosBLX;

    vector<int> index_mejores(10), index_peores(10);
    for (int i = 0; i < 10; i++) {
        index_mejores[i] = i;
        index_peores[i] = i;
    }

    poblacion = poblacionInicialMemeticos(num_caracteristicas);
    evalPoblacion(train, clases_train, poblacion, pcts_poblacion, flag_eval, num_eval);
    genes_generacion = 10 * num_caracteristicas;
    mutar = 1000.0 / genes_generacion;
    if (mutar == 0) {
        mutar = 1;
    }

    sort(index_mejores.begin(), index_mejores.end(), [&](int i1, int i2) {
        return pcts_poblacion[i1] > pcts_poblacion[i2]; });

    while (num_eval < 15000) {
        // Las parejas se cruzan la i con la i+1 (primera con segunda, tercera con cuarta...)
        for (int i = 0; i < 10; i++) {
            elegido = torneoBinarioMemetico(pcts_poblacion);
            padres[i] = poblacion[elegido];
            pcts_padres[i] = pcts_poblacion[elegido];
        }

        // Proceso de cruce con probabilidad 0.7 y 10 parejas
        num_cruces = 0.7 * 10;
        for (int i = 0; i < num_cruces; i += 2) {
            hijosBLX = cruceBLX(padres[i], padres[i + 1]);
            hijos[i] = hijosBLX.first;
            hijos[i + 1] = hijosBLX.second;
            flag_eval[i] = false;
            flag_eval[i + 1] = false;
            pcts_hijos[i] = 0;
            pcts_hijos[i + 1] = 0;
        }

        for (int i = num_cruces; i < 10; i++) {
            hijos[i] = padres[i];
            pcts_hijos[i] = pcts_padres[i];
        }

        // Proceso de mutacion con probabilidad 0.001 (se muta 1 gen de cada 1000)
        if (generacion % mutar == 0) {
            cromosoma_mutar = rand() % 10;
            gen_mutar = rand() % num_caracteristicas;
            mutarCromosoma(hijos[cromosoma_mutar], gen_mutar);
            flag_eval[cromosoma_mutar] = false;
        }

        // Evaluamos la nueva poblacion (la de hijos)
        evalPoblacion(train, clases_train, hijos, pcts_hijos, flag_eval, num_eval);
        // Obtenemos cual es el peor hijo ordenando un indice en función de los porcentajes
        sort(index_peores.begin(), index_peores.end(), [&](int i1, int i2) {
            return pcts_hijos[i1] < pcts_hijos[i2]; });

        // Aplicamos la busqueda local al mejor cromosoma de la poblacion
        if(generacion % 10 == 0){
            localSearchMemeticos(train, clases_train, hijos[index_peores[index_peores.size() - 1]], num_eval);
            flag_eval[index_peores[index_peores.size() - 1]] = false;
        }

        // Evaluamos la nueva poblacion con el mejor hijo mejorado
        evalPoblacion(train, clases_train, hijos, pcts_hijos, flag_eval, num_eval);
        // Obtenemos cual es el peor hijo ordenando un indice en función de los porcentajes
        sort(index_peores.begin(), index_peores.end(), [&](int i1, int i2) {
            return pcts_hijos[i1] < pcts_hijos[i2]; });

        // Guardamos el mejor de la población anterior y su porcenaje
        mejor = poblacion[index_mejores[0]];
        porcentaje_mejor = pcts_poblacion[index_mejores[0]];

        poblacion = hijos;
        pcts_poblacion = pcts_hijos;

        // Elitismo
        if (porcentaje_mejor > pcts_poblacion[index_peores[index_peores.size() - 1]]) {
            poblacion[index_peores[0]] = mejor;
            pcts_poblacion[index_peores[0]] = porcentaje_mejor;
        }

        sort(index_mejores.begin(), index_mejores.end(), [&](int i1, int i2) {
            return pcts_poblacion[i1] > pcts_poblacion[i2]; });

        generacion++;
    }
    return poblacion[index_mejores[0]];
}

void EjecutarMemeticoGeneracionalBLX_10_1(int conjunto, int bd) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    double porcentaje = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    start = std::chrono::high_resolution_clock::now();
    pesos = MemeticoGeneracionalBLX_10_1(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". train-train (porcentaje): " << porcentaje << endl;
    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". train-test (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;

    start = std::chrono::high_resolution_clock::now();
    pesos = MemeticoGeneracionalBLX_10_1(test, clases_test);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(test, clases_test, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". test-test (porcentaje): " << porcentaje << endl;
    KNN_distintos(test, clases_test, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". test-train (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;
}

void EjecutarMemeticoGeneracionalBLX_10_0_1(int conjunto, int bd) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    double porcentaje = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    start = std::chrono::high_resolution_clock::now();
    pesos = MemeticoGeneracionalBLX_10_0_1(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". train-train (porcentaje): " << porcentaje << endl;
    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". train-test (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;

    start = std::chrono::high_resolution_clock::now();
    pesos = MemeticoGeneracionalBLX_10_0_1(test, clases_test);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(test, clases_test, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". test-test (porcentaje): " << porcentaje << endl;
    KNN_distintos(test, clases_test, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". test-train (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;
}

void EjecutarMemeticoGeneracionalBLX_10_0_1_mej(int conjunto, int bd) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    double porcentaje = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    start = std::chrono::high_resolution_clock::now();
    pesos = MemeticoGeneracionalBLX_10_0_1_mej(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". train-train (porcentaje): " << porcentaje << endl;
    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". train-test (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;

    start = std::chrono::high_resolution_clock::now();
    pesos = MemeticoGeneracionalBLX_10_0_1_mej(test, clases_test);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(test, clases_test, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". test-test (porcentaje): " << porcentaje << endl;
    KNN_distintos(test, clases_test, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". test-train (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;
}
