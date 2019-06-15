#include "Evolutivos.h"

default_random_engine generator2;
normal_distribution<double> distribution2(0.0, 0.09);
mt19937 seed(75573052);

vector<vector<float> > poblacionInicial(const int &num_caracteristicas, const int &size) {
    vector<vector<float> > poblacion_inicial(size);
    for (int i = 0; i < size; i++) {
        poblacion_inicial[i] = solInicialAleatoria(num_caracteristicas);
    }
    return poblacion_inicial;
}

void evalPoblacion(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &poblacion, vector<float> &pcts_poblacion, vector<bool> &flag_eval, int &num_eval) {
    vector<int> clasificacion;

    for (int i = 0; i < poblacion.size(); i++) {
        if (!flag_eval[i]) {
            KNN(train, clases_train, train, clasificacion, poblacion[i]);
            num_eval++;
            pcts_poblacion[i] = tasaAgregacion(clases_train, clasificacion, poblacion[i], 0.5);
            flag_eval[i] = true;
        }
    }
}

void evalPoblacion(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &poblacion, vector<float> &pcts_poblacion, int &num_eval) {
    vector<int> clasificacion;

    for (int i = 0; i < poblacion.size(); i++) {
        KNN(train, clases_train, train, clasificacion, poblacion[i]);
        num_eval++;
        pcts_poblacion[i] = tasaAgregacion(clases_train, clasificacion, poblacion[i], 0.5);
    }
}

int torneoBinario(const vector<float> &pcts_poblacion, const int &random) {
    int uno, dos;

    uno = rand() % random;
    do {
        dos = rand() % random;
    } while (uno == dos);

    if (pcts_poblacion[uno] > pcts_poblacion[dos]) {
        dos = uno;
    }
    return dos;
}

pair<vector<float>, vector<float>> cruceBLX(const vector<float> &padre_1, const vector<float> &padre_2) {
    pair<vector<float>, vector<float>> hijos;
    hijos.first.resize(padre_1.size());
    hijos.second.resize(padre_1.size());
    float minimo, maximo, intervalo, aleatorio;
    for (int i = 0; i < padre_1.size(); i++) {
        maximo = max(padre_1[i], padre_2[i]);
        minimo = min(padre_1[i], padre_2[i]);

        intervalo = maximo - minimo;
        uniform_real_distribution<> distr(minimo - intervalo * 0.3, maximo + intervalo * 0.3);
        aleatorio = distr(seed);
        aleatorio = truncar(aleatorio);
        hijos.first[i] = aleatorio;
        aleatorio = distr(seed);
        aleatorio = truncar(aleatorio);
        hijos.second[i] = aleatorio;
    }
    return hijos;
}

void mutarCromosoma(vector<float> &cromosoma, const int &gen_mutar) {
    float numero;
    cromosoma[gen_mutar] += distribution2(generator2);
    numero = truncar(cromosoma[gen_mutar]);
    cromosoma[gen_mutar] = numero;
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
    porcentaje_ant = tasaAgregacion(clases_train, clasificacion, pesos, 0.5);

    while (num_vecinos < 2 * num_caracteristicas) {
        mejora = false;
        for (int i = 0; i < num_caracteristicas && !mejora; i++) {
            sol_nueva = pesos;
            elegido = rand() % (indices.size() - i_auxiliar) + i_auxiliar;
            posicion_auxiliar = indices[i_auxiliar];
            indices[i_auxiliar] = indices[elegido];
            indices[elegido] = posicion_auxiliar;
            mutarCromosoma(sol_nueva, indices[i_auxiliar]);
            num_vecinos++;
            i_auxiliar++;
            if (i_auxiliar == num_caracteristicas)
                i_auxiliar = 0;

            KNN(train, clases_train, train, clasificacion, sol_nueva);
            porcentaje_nuevo = tasaAgregacion(clases_train, clasificacion, sol_nueva, 0.5);
            num_eval++;

            if (porcentaje_nuevo > porcentaje_ant) {
                pesos = sol_nueva;
                porcentaje_ant = porcentaje_nuevo;
                mejora = true;
            }
        }
    }
}

vector<float> GeneticoGeneracionalBLX(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<vector<float> > poblacion, padres(30), hijos(30);
    int num_caracteristicas = train[0].size(), num_eval = 0, elegido = 0, num_cruces = 0, cromosoma_mutar = 0, gen_mutar = 0, genes_generacion = 0, generacion = 0, mutar = 0;
    vector<bool> flag_eval(30, 0);
    vector<float> pcts_poblacion(30), pcts_padres(30), pcts_hijos(30), mejor;
    float pct_mejor = 0;
    pair<vector<float>, vector<float>> hijosBLX;

    vector<int> index_mejores(30), index_peores(30);
    for (int i = 0; i < 30; i++) {
        index_mejores[i] = i;
        index_peores[i] = i;
    }

    poblacion = poblacionInicial(num_caracteristicas, 30);
    evalPoblacion(train, clases_train, poblacion, pcts_poblacion, flag_eval, num_eval);
    genes_generacion = 30 * num_caracteristicas;
    mutar = 1000.0 / genes_generacion;
    if (mutar == 0) {
        mutar = 1;
    }

    sort(index_mejores.begin(), index_mejores.end(), [&](int i1, int i2) {
        return pcts_poblacion[i1] > pcts_poblacion[i2]; });

    while (num_eval < 15000) {
        // Las parejas se cruzan la i con la i+1 (primera con segunda, tercera con cuarta...)
        for (int i = 0; i < 30; i++) {
            elegido = torneoBinario(pcts_poblacion, 30);
            padres[i] = poblacion[elegido];
            pcts_padres[i] = pcts_poblacion[elegido];
        }

        // Proceso de cruce con probabilidad 0.7 y 15 parejas
        num_cruces = 0.7 * 30;
        for (int i = 0; i < num_cruces; i += 2) {
            hijosBLX = cruceBLX(padres[i], padres[i + 1]);
            hijos[i] = hijosBLX.first;
            hijos[i + 1] = hijosBLX.second;
            flag_eval[i] = false;
            flag_eval[i + 1] = false;
            pcts_hijos[i] = 0;
            pcts_hijos[i + 1] = 0;
        }

        for (int i = num_cruces; i < 30; i++) {
            hijos[i] = padres[i];
            pcts_hijos[i] = pcts_padres[i];
        }

        // Proceso de mutacion con probabilidad 0.001 (se muta 1 gen de cada 1000)
        if (generacion % mutar == 0) {
            cromosoma_mutar = rand() % 30;
            gen_mutar = rand() % num_caracteristicas;
            mutarCromosoma(hijos[cromosoma_mutar], gen_mutar);
            flag_eval[cromosoma_mutar] = false;
        }

        // Evaluamos la nueva poblacion (la de hijos)
        evalPoblacion(train, clases_train, hijos, pcts_hijos, flag_eval, num_eval);
        // Obtenemos cual es el peor hijo ordenando un indice en función de los porcentajes
        sort(index_peores.begin(), index_peores.end(), [&](int i1, int i2) {
            return pcts_hijos[i1] < pcts_hijos[i2]; });

        // Guardamos el mejor de la población anterior y su porcenaje
        mejor = poblacion[index_mejores[0]];
        pct_mejor = pcts_poblacion[index_mejores[0]];

        poblacion = hijos;
        pcts_poblacion = pcts_hijos;

        // Elitismo
        if (pct_mejor > pcts_poblacion[index_peores[index_peores.size() - 1]]) {
            poblacion[index_peores[0]] = mejor;
            pcts_poblacion[index_peores[0]] = pct_mejor;
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

    poblacion = poblacionInicial(num_caracteristicas, 10);
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
            elegido = torneoBinario(pcts_poblacion, 10);
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
        if (generacion % 10 == 0) {
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

vector<float> EvolucionDiferencialRand(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<vector<float> > poblacion(50), hijos(50);
    int num_caracteristicas = train[0].size(), num_eval = 0, elegido = 0, posicion_auxiliar = 0, gen_elegido = 0, i_aux = 0, indices_generados = 0, pos_max = 0;
    vector<int> indices(50);
    vector<float> pcts_poblacion(50), pcts_hijos(50), padre1(num_caracteristicas), padre2(num_caracteristicas), padre3(num_caracteristicas), hijo(num_caracteristicas);
    float random = 0, crossover = 0.5, numero = 0, max = 0;

    for (int i = 0; i < indices.size(); i++)
        indices[i] = i;

    poblacion = poblacionInicial(num_caracteristicas, 50);
    evalPoblacion(train, clases_train, poblacion, pcts_poblacion, num_eval);

    while (num_eval < 15000) {
        for (int i = 0; i < poblacion.size(); i++) {
            indices_generados = 0;
            i_aux = 0;
            while (indices_generados < 4) {
                elegido = rand() % (indices.size() - i_aux) + i_aux;
                posicion_auxiliar = indices[i_aux];
                indices[i_aux] = indices[elegido];
                indices[elegido] = posicion_auxiliar;
                if (indices[i_aux] != i) {
                    indices_generados++;
                    i_aux++;
                }
            }
            padre1 = poblacion[indices[0]];
            padre2 = poblacion[indices[1]];
            padre3 = poblacion[indices[2]];

            gen_elegido = rand() % num_caracteristicas;
            for (int j = 0; j < num_caracteristicas; j++) {
                random = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
                if (random < crossover || gen_elegido == j) {
                    numero = padre1[j] + 0.5 * (padre2[j] - padre3[j]);
                    numero = truncar(numero);
                    hijo[j] = numero;
                } else {
                    hijo[j] = poblacion[i][j];
                }
            }
            hijos[i] = hijo;
        }

        evalPoblacion(train, clases_train, hijos, pcts_hijos, num_eval);

        for (int i = 0; i < poblacion.size(); i++) {
            if (pcts_poblacion[i] < pcts_hijos[i]) {
                poblacion[i] = hijos[i];
                pcts_poblacion[i] = pcts_hijos[i];
            }
        }
    }

    for (int i = 0; i < pcts_poblacion.size(); i++) {
        if (pcts_poblacion[i] > max) {
            pos_max = i;
            max = pcts_poblacion[i];
        }
    }
    
    return poblacion[pos_max];
}

vector<float> EvolucionDiferencialBest(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<vector<float> > poblacion(50), hijos(50);
    int num_caracteristicas = train[0].size(), num_eval = 0, elegido = 0, posicion_auxiliar = 0, gen_elegido = 0, i_aux = 0, indices_generados = 0, pos_max = 0;
    vector<int> indices(50), index_mejores(50);
    vector<float> pcts_poblacion(50), pcts_hijos(50), padre1(num_caracteristicas), padre2(num_caracteristicas), best_padre(num_caracteristicas), hijo(num_caracteristicas);
    float random = 0, crossover = 0.5, numero = 0, max = 0;

    for (int i = 0; i < indices.size(); i++){
        indices[i] = i;
        index_mejores[i] = i;
    }

    poblacion = poblacionInicial(num_caracteristicas, 50);
    evalPoblacion(train, clases_train, poblacion, pcts_poblacion, num_eval);

    sort(index_mejores.begin(), index_mejores.end(), [&](int i1, int i2) {
        return pcts_poblacion[i1] > pcts_poblacion[i2]; });

    best_padre = poblacion[index_mejores[0]];

    while (num_eval < 15000) {
        for (int i = 0; i < poblacion.size(); i++) {
            indices_generados = 0;
            i_aux = 0;
            while (indices_generados < 3) {
                elegido = rand() % (indices.size() - i_aux) + i_aux;
                posicion_auxiliar = indices[i_aux];
                indices[i_aux] = indices[elegido];
                indices[elegido] = posicion_auxiliar;
                if (indices[i_aux] != i) {
                    indices_generados++;
                    i_aux++;
                }
            }
            padre1 = poblacion[indices[0]];
            padre2 = poblacion[indices[1]];

            gen_elegido = rand() % num_caracteristicas;
            for (int j = 0; j < num_caracteristicas; j++) {
                random = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
                if (random < crossover || gen_elegido == j) {
                    numero = poblacion[i][j] + 0.5 * (best_padre[j] - poblacion[i][j]) + 0.5 * (padre1[j] - padre2[j]);
                    numero = truncar(numero);
                    hijo[j] = numero;
                } else {
                    hijo[j] = poblacion[i][j];
                }
            }
            hijos[i] = hijo;
        }

        evalPoblacion(train, clases_train, hijos, pcts_hijos, num_eval);

        for (int i = 0; i < poblacion.size(); i++) {
            if (pcts_poblacion[i] < pcts_hijos[i]) {
                poblacion[i] = hijos[i];
                pcts_poblacion[i] = pcts_hijos[i];
            }
        }

        sort(index_mejores.begin(), index_mejores.end(), [&](int i1, int i2) {
            return pcts_poblacion[i1] > pcts_poblacion[i2]; });

        best_padre = poblacion[index_mejores[0]];
    }
    
    return poblacion[index_mejores[0]];
}

void EjecutarGeneticoGeneracionalBLX(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    start = std::chrono::high_resolution_clock::now();
    pesos = GeneticoGeneracionalBLX(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    KNN(train, clases_train, train, clasificacion, pesos);
    acierto = tasaAcierto(clases_train, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_train, clasificacion, pesos, 0.5);
    cout << "Set " << conjunto << ". train-train (tasa acierto, tasa reduccion, tasa final): " << acierto << " : " << reduccion << " : " << tasa_final << endl;
    over << acierto << " " << reduccion << " " << tasa_final << endl;

    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    acierto = tasaAcierto(clases_test, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_test, clasificacion, pesos, 0.5);
    cout << "Set " << conjunto << ". train-test (tasa acierto, tasa reduccion, tasa final, tiempo): " << acierto << " : " << reduccion << " : " << tasa_final << " : " << time.count() << endl;
    fs << acierto << " " << reduccion << " " << tasa_final << " " << time.count() << endl;
    over << acierto << " " << reduccion << " " << tasa_final << endl;
    for (int i = 0; i < pesos.size(); i++) {
        if (pesos[i] < 0.1) {
            caracteristicas << i << " ";
        }
    }
    caracteristicas << endl;

    aciertos.push_back(acierto);
    reducciones.push_back(reduccion);
    finales.push_back(tasa_final);
    tiempos.push_back(time.count());

    if (conjunto == 5) {
        float media_acierto = 0, media_reduccion = 0, media_final = 0, media_tiempo = 0;
        for (int i = 0; i < 5; i++) {
            media_acierto += aciertos[i];
            media_reduccion += reducciones[i];
            media_final += finales[i];
            media_tiempo += tiempos[i];
        }

        cout << endl << "Medias: (tasa acierto, tasa reduccion, tasa final, tiempo). " << media_acierto / 5.0 << " : " << media_reduccion / 5.0 << " : " << media_final / 5.0 << " : " << media_tiempo / 5.0 << endl;
        fs << endl << media_acierto / 5.0 << " " << media_reduccion / 5.0 << " " << media_final / 5.0 << " " << media_tiempo / 5.0 << endl;
    }
}

void EjecutarMemeticoGeneracionalBLX_10_0_1_mej(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    start = std::chrono::high_resolution_clock::now();
    pesos = MemeticoGeneracionalBLX_10_0_1_mej(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    KNN(train, clases_train, train, clasificacion, pesos);
    acierto = tasaAcierto(clases_train, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_train, clasificacion, pesos, 0.5);
    cout << "Set " << conjunto << ". train-train (tasa acierto, tasa reduccion, tasa final): " << acierto << " : " << reduccion << " : " << tasa_final << endl;
    over << acierto << " " << reduccion << " " << tasa_final << endl;

    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    acierto = tasaAcierto(clases_test, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_test, clasificacion, pesos, 0.5);
    cout << "Set " << conjunto << ". train-test (tasa acierto, tasa reduccion, tasa final, tiempo): " << acierto << " : " << reduccion << " : " << tasa_final << " : " << time.count() << endl;
    fs << acierto << " " << reduccion << " " << tasa_final << " " << time.count() << endl;
    over << acierto << " " << reduccion << " " << tasa_final << endl;
    for (int i = 0; i < pesos.size(); i++) {
        if (pesos[i] < 0.1) {
            caracteristicas << i << " ";
        }
    }
    caracteristicas << endl;

    aciertos.push_back(acierto);
    reducciones.push_back(reduccion);
    finales.push_back(tasa_final);
    tiempos.push_back(time.count());

    if (conjunto == 5) {
        float media_acierto = 0, media_reduccion = 0, media_final = 0, media_tiempo = 0;
        for (int i = 0; i < 5; i++) {
            media_acierto += aciertos[i];
            media_reduccion += reducciones[i];
            media_final += finales[i];
            media_tiempo += tiempos[i];
        }

        cout << endl << "Medias: (tasa acierto, tasa reduccion, tasa final, tiempo). " << media_acierto / 5.0 << " : " << media_reduccion / 5.0 << " : " << media_final / 5.0 << " : " << media_tiempo / 5.0 << endl;
        fs << endl << media_acierto / 5.0 << " " << media_reduccion / 5.0 << " " << media_final / 5.0 << " " << media_tiempo / 5.0 << endl;
    }
}

void EjecutarEvolucionDiferencialRand(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    start = std::chrono::high_resolution_clock::now();
    pesos = EvolucionDiferencialRand(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    KNN(train, clases_train, train, clasificacion, pesos);
    acierto = tasaAcierto(clases_train, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_train, clasificacion, pesos, 0.5);
    cout << "Set " << conjunto << ". train-train (tasa acierto, tasa reduccion, tasa final): " << acierto << " : " << reduccion << " : " << tasa_final << endl;
    over << acierto << " " << reduccion << " " << tasa_final << endl;

    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    acierto = tasaAcierto(clases_test, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_test, clasificacion, pesos, 0.5);
    cout << "Set " << conjunto << ". train-test (tasa acierto, tasa reduccion, tasa final, tiempo): " << acierto << " : " << reduccion << " : " << tasa_final << " : " << time.count() << endl;
    fs << acierto << " " << reduccion << " " << tasa_final << " " << time.count() << endl;
    over << acierto << " " << reduccion << " " << tasa_final << endl;
    for (int i = 0; i < pesos.size(); i++) {
        if (pesos[i] < 0.1) {
            caracteristicas << i << " ";
        }
    }
    caracteristicas << endl;

    aciertos.push_back(acierto);
    reducciones.push_back(reduccion);
    finales.push_back(tasa_final);
    tiempos.push_back(time.count());

    if (conjunto == 5) {
        float media_acierto = 0, media_reduccion = 0, media_final = 0, media_tiempo = 0;
        for (int i = 0; i < 5; i++) {
            media_acierto += aciertos[i];
            media_reduccion += reducciones[i];
            media_final += finales[i];
            media_tiempo += tiempos[i];
        }

        cout << endl << "Medias: (tasa acierto, tasa reduccion, tasa final, tiempo). " << media_acierto / 5.0 << " : " << media_reduccion / 5.0 << " : " << media_final / 5.0 << " : " << media_tiempo / 5.0 << endl;
        fs << endl << media_acierto / 5.0 << " " << media_reduccion / 5.0 << " " << media_final / 5.0 << " " << media_tiempo / 5.0 << endl;
    }
}

void EjecutarEvolucionDiferencialBest(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    start = std::chrono::high_resolution_clock::now();
    pesos = EvolucionDiferencialBest(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    KNN(train, clases_train, train, clasificacion, pesos);
    acierto = tasaAcierto(clases_train, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_train, clasificacion, pesos, 0.5);
    cout << "Set " << conjunto << ". train-train (tasa acierto, tasa reduccion, tasa final): " << acierto << " : " << reduccion << " : " << tasa_final << endl;
    over << acierto << " " << reduccion << " " << tasa_final << endl;

    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    acierto = tasaAcierto(clases_test, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_test, clasificacion, pesos, 0.5);
    cout << "Set " << conjunto << ". train-test (tasa acierto, tasa reduccion, tasa final, tiempo): " << acierto << " : " << reduccion << " : " << tasa_final << " : " << time.count() << endl;
    fs << acierto << " " << reduccion << " " << tasa_final << " " << time.count() << endl;
    over << acierto << " " << reduccion << " " << tasa_final << endl;
    for (int i = 0; i < pesos.size(); i++) {
        if (pesos[i] < 0.1) {
            caracteristicas << i << " ";
        }
    }
    caracteristicas << endl;

    aciertos.push_back(acierto);
    reducciones.push_back(reduccion);
    finales.push_back(tasa_final);
    tiempos.push_back(time.count());

    if (conjunto == 5) {
        float media_acierto = 0, media_reduccion = 0, media_final = 0, media_tiempo = 0;
        for (int i = 0; i < 5; i++) {
            media_acierto += aciertos[i];
            media_reduccion += reducciones[i];
            media_final += finales[i];
            media_tiempo += tiempos[i];
        }

        cout << endl << "Medias: (tasa acierto, tasa reduccion, tasa final, tiempo). " << media_acierto / 5.0 << " : " << media_reduccion / 5.0 << " : " << media_final / 5.0 << " : " << media_tiempo / 5.0 << endl;
        fs << endl << media_acierto / 5.0 << " " << media_reduccion / 5.0 << " " << media_final / 5.0 << " " << media_tiempo / 5.0 << endl;
    }
}