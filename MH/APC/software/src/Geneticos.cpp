#include "Geneticos.h"

default_random_engine generator2;
normal_distribution<double> distribution2(0.0, 0.09);
mt19937 seed(75573052);

vector<vector<float> > poblacionInicial(const int &num_caracteristicas) {
    vector<vector<float> > poblacion_inicial(30);
    for (int i = 0; i < 30; i++) {
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
            pcts_poblacion[i] = tasaAcierto(clases_train, clasificacion);
            flag_eval[i] = true;
        }
    }
}

void evalPoblacionEstacionario(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &poblacion, vector<float> &pcts_poblacion, int &num_eval) {
    vector<int> clasificacion;

    for (int i = 0; i < poblacion.size(); i++) {
        KNN(train, clases_train, train, clasificacion, poblacion[i]);
        num_eval++;
        pcts_poblacion[i] = tasaAcierto(clases_train, clasificacion);
    }
}

int torneoBinario(const vector<float> &pcts_poblacion) {
    int uno, dos;

    uno = rand() % 30;
    do {
        dos = rand() % 30;
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

vector<float> cruceAritmetico(const vector<float> &padre_1, const vector<float> &padre_2) {
    vector<float> hijo;
    hijo.resize(padre_1.size());
    for (int i = 0; i < padre_1.size(); i++) {
        hijo[i] = (padre_1[i] + padre_2[i]) / 2;
    }
    return hijo;
}

void mutarCromosoma(vector<float> &cromosoma, const int &gen_mutar) {
    float numero;
    cromosoma[gen_mutar] += distribution2(generator2);
    numero = truncar(cromosoma[gen_mutar]);
    cromosoma[gen_mutar] = numero;
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

    poblacion = poblacionInicial(num_caracteristicas);
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
            elegido = torneoBinario(pcts_poblacion);
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

vector<float> GeneticoGeneracionalCA(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<vector<float> > poblacion, padres(60), hijos(30);
    int num_caracteristicas = train[0].size(), num_eval = 0, elegido = 0, num_cruces = 0, cromosoma_mutar = 0, gen_mutar = 0, hijos_generados = 0, genes_generacion = 0, generacion = 0, mutar = 0;
    vector<bool> flag_eval(30, 0);
    vector<float> pcts_poblacion(30), pcts_padres(60), pcts_hijos(30), mejor;
    float pct_mejor = 0;

    vector<int> index_mejores(30), index_peores(30);
    for (int i = 0; i < 30; i++) {
        index_mejores[i] = i;
        index_peores[i] = i;
    }

    poblacion = poblacionInicial(num_caracteristicas);
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
        for (int i = 0; i < 60; i++) {
            elegido = torneoBinario(pcts_poblacion);
            padres[i] = poblacion[elegido];
            pcts_padres[i] = pcts_poblacion[elegido];
        }

        // Proceso de cruce con probabilidad 0.7 y 30 parejas
        num_cruces = 0.7 * 30;
        int auxiliar = 0;
        for (int i = 0; i < num_cruces; i++) {
            hijos[i] = cruceAritmetico(padres[auxiliar], padres[auxiliar + 1]);
            hijos_generados++;
            flag_eval[i] = false;
            pcts_hijos[i] = 0;
            auxiliar += 2;
        }

        for (int i = hijos_generados; i < 30; i++) {
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

vector<float> GeneticoEstacionarioBLX(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<vector<float> > poblacion, hijos(2);
    vector<float> padre_1, padre_2, pcts_poblacion(30), pcts_hijos(2);
    vector<int> index_peores(30);
    pair<vector<float>, vector<float>> hijosBLX;
    float mejor = 0, peor = 0;
    int num_caracteristicas = train[0].size(), num_eval = 0, elegido = 0, cromosoma_mutar = 0, gen_mutar = 0, i_mejor = 0, i_peor = 0, genes_generacion = 0, generacion = 0, mutar = 0;
    for (int i = 0; i < 30; i++) {
        index_peores[i] = i;
    }

    poblacion = poblacionInicial(num_caracteristicas);
    evalPoblacionEstacionario(train, clases_train, poblacion, pcts_poblacion, num_eval);
    genes_generacion = 2 * num_caracteristicas;
    mutar = 1000.0 / genes_generacion;
    if (mutar == 0) {
        mutar = 1;
    }

    sort(index_peores.begin(), index_peores.end(), [&](int i1, int i2) {
        return pcts_poblacion[i1] < pcts_poblacion[i2]; });

    while (num_eval < 15000) {
        elegido = torneoBinario(pcts_poblacion);
        padre_1 = poblacion[elegido];

        elegido = torneoBinario(pcts_poblacion);
        padre_2 = poblacion[elegido];

        hijosBLX = cruceBLX(padre_1, padre_2);
        hijos[0] = hijosBLX.first;
        hijos[1] = hijosBLX.second;

        // Proceso de mutacion con probabilidad 0.001 (se muta 1 gen de cada 1000)
        if (generacion % mutar == 0) {
            cromosoma_mutar = rand() % 2;
            gen_mutar = rand() % num_caracteristicas;
            mutarCromosoma(hijos[cromosoma_mutar], gen_mutar);
        }

        // Evaluamos la nueva poblacion (la de hijos)
        evalPoblacionEstacionario(train, clases_train, hijos, pcts_hijos, num_eval);

        // Realizamos el reemplazo, si fuese necesario
        // Vemos que hijo es mejor para probar primero con el
        if (pcts_hijos[0] >= pcts_hijos[1]) {
            mejor = pcts_hijos[0];
            i_mejor = 0;
            peor = pcts_hijos[1];
            i_peor = 1;
        } else {
            mejor = pcts_hijos[1];
            i_mejor = 1;
            peor = pcts_hijos[0];
            i_peor = 0;
        }

        // Probamos contra el penultimo peor
        if (mejor > pcts_poblacion[index_peores[1]]) {
            // Si es mejor, lo actualizamos y probamos el segundo hijo contra el peor
            poblacion[index_peores[1]] = hijos[i_mejor];
            pcts_poblacion[index_peores[1]] = mejor;
            if (peor > pcts_poblacion[index_peores[0]]) {
                poblacion[index_peores[0]] = hijos[i_peor];
                pcts_poblacion[index_peores[0]] = peor;
            }
        } else if (mejor > index_peores[0]) {
            // Si es mejor, lo actualizamos y no probamos con el segundo hijo
            poblacion[index_peores[0]] = hijos[i_mejor];
            pcts_poblacion[index_peores[0]] = mejor;
        }


        sort(index_peores.begin(), index_peores.end(), [&](int i1, int i2) {
            return pcts_poblacion[i1] < pcts_poblacion[i2]; });

        generacion++;
    }
    return poblacion[index_peores[index_peores.size() - 1]];
}

vector<float> GeneticoEstacionarioCA(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<vector<float> > poblacion, hijos(2);
    vector<float> padre_1, padre_2, pcts_poblacion(30), pcts_hijos(2);
    vector<int> index_peores(30);
    float mejor = 0, peor = 0;
    int num_caracteristicas = train[0].size(), num_eval = 0, elegido = 0, cromosoma_mutar = 0, gen_mutar = 0, i_mejor = 0, i_peor = 0, genes_generacion = 0, generacion = 0, mutar = 0;
    for (int i = 0; i < 30; i++) {
        index_peores[i] = i;
    }

    poblacion = poblacionInicial(num_caracteristicas);
    evalPoblacionEstacionario(train, clases_train, poblacion, pcts_poblacion, num_eval);
    genes_generacion = 2 * num_caracteristicas;
    mutar = 1000.0 / genes_generacion;
    if (mutar == 0) {
        mutar = 1;
    }

    sort(index_peores.begin(), index_peores.end(), [&](int i1, int i2) {
        return pcts_poblacion[i1] < pcts_poblacion[i2]; });

    while (num_eval < 15000) {
        elegido = torneoBinario(pcts_poblacion);
        padre_1 = poblacion[elegido];
        elegido = torneoBinario(pcts_poblacion);
        padre_2 = poblacion[elegido];
        hijos[0] = cruceAritmetico(padre_1, padre_2);

        elegido = torneoBinario(pcts_poblacion);
        padre_1 = poblacion[elegido];
        elegido = torneoBinario(pcts_poblacion);
        padre_2 = poblacion[elegido];
        hijos[1] = cruceAritmetico(padre_1, padre_2);

        // Proceso de mutacion con probabilidad 0.001 (se muta 1 gen de cada 1000)
        if (generacion % mutar == 0) {
            cromosoma_mutar = rand() % 2;
            gen_mutar = rand() % num_caracteristicas;
            mutarCromosoma(hijos[cromosoma_mutar], gen_mutar);
        }

        // Evaluamos la nueva poblacion (la de hijos)
        evalPoblacionEstacionario(train, clases_train, hijos, pcts_hijos, num_eval);

        // Realizamos el reemplazo, si fuese necesario
        // Vemos que hijo es mejor para probar primero con el
        if (pcts_hijos[0] >= pcts_hijos[1]) {
            mejor = pcts_hijos[0];
            i_mejor = 0;
            peor = pcts_hijos[1];
            i_peor = 1;
        } else {
            mejor = pcts_hijos[1];
            i_mejor = 1;
            peor = pcts_hijos[0];
            i_peor = 0;
        }

        // Probamos contra el penultimo peor
        if (mejor > pcts_poblacion[index_peores[1]]) {
            // Si es mejor, lo actualizamos y probamos el segundo hijo contra el peor
            poblacion[index_peores[1]] = hijos[i_mejor];
            pcts_poblacion[index_peores[1]] = mejor;
            if (peor > pcts_poblacion[index_peores[0]]) {
                poblacion[index_peores[0]] = hijos[i_peor];
                pcts_poblacion[index_peores[0]] = peor;
            }
        } else if (mejor > index_peores[0]) {
            // Si es mejor, lo actualizamos y no probamos con el segundo hijo
            poblacion[index_peores[0]] = hijos[i_mejor];
            pcts_poblacion[index_peores[0]] = mejor;
        }


        sort(index_peores.begin(), index_peores.end(), [&](int i1, int i2) {
            return pcts_poblacion[i1] < pcts_poblacion[i2]; });

        generacion++;
    }
    return poblacion[index_peores[index_peores.size() - 1]];
}

void EjecutarGeneticoGeneracionalBLX(int conjunto, int bd) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    double porcentaje = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    start = std::chrono::high_resolution_clock::now();
    pesos = GeneticoGeneracionalBLX(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". train-train (porcentaje): " << porcentaje << endl;
    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". train-test (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;

    start = std::chrono::high_resolution_clock::now();
    pesos = GeneticoGeneracionalBLX(test, clases_test);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(test, clases_test, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". test-test (porcentaje): " << porcentaje << endl;
    KNN_distintos(test, clases_test, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". test-train (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;
}

void EjecutarGeneticoGeneracionalCA(int conjunto, int bd) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    double porcentaje = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    start = std::chrono::high_resolution_clock::now();
    pesos = GeneticoGeneracionalCA(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". train-train (porcentaje): " << porcentaje << endl;
    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". train-test (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;

    start = std::chrono::high_resolution_clock::now();
    pesos = GeneticoGeneracionalCA(test, clases_test);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(test, clases_test, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". test-test (porcentaje): " << porcentaje << endl;
    KNN_distintos(test, clases_test, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". test-train (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;
}

void EjecutarGeneticoEstacionarioBLX(int conjunto, int bd) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    double porcentaje = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    start = std::chrono::high_resolution_clock::now();
    pesos = GeneticoEstacionarioBLX(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". train-train (porcentaje): " << porcentaje << endl;
    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". train-test (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;

    start = std::chrono::high_resolution_clock::now();
    pesos = GeneticoEstacionarioBLX(test, clases_test);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(test, clases_test, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". test-test (porcentaje): " << porcentaje << endl;
    KNN_distintos(test, clases_test, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". test-train (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;
}

void EjecutarGeneticoEstacionarioCA(int conjunto, int bd) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    double porcentaje = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    start = std::chrono::high_resolution_clock::now();
    pesos = GeneticoEstacionarioCA(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". train-train (porcentaje): " << porcentaje << endl;
    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". train-test (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;

    start = std::chrono::high_resolution_clock::now();
    pesos = GeneticoEstacionarioCA(test, clases_test);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN(test, clases_test, test, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_test, clasificacion);
    cout << "Set " << conjunto << ". test-test (porcentaje): " << porcentaje << endl;
    KNN_distintos(test, clases_test, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". test-train (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;
}
