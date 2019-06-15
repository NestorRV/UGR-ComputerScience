#include "EnfriamientoSimulado.h"

default_random_engine generator3;
normal_distribution<double> distribution3(0.0, 0.09);

void mutarSolucion(vector<float> &sol, const int &indice) {
    float numero;
    sol[indice] += distribution3(generator3);
    numero = truncar(sol[indice]);
    sol[indice] = numero;
}

vector<float> EnfriamientoSimulado(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<float> solucion, sol_nueva, mejor_solucion;
    int num_caracteristicas = train[0].size(), max_vecinos = 0, max_exitos = 0, num_enfriamientos = 0, num_eval = 0, vecinos = 0, num_exitos = 1, gen = 0;
    float mejor_tasa = 0, tasa_actual = 0, tasa_nueva = 0, t_ini = 0, t_fin = 0, t_actual = 0, beta = 0, mejora = 0;
    vector<int> clasificacion;
    
    max_vecinos = 10 * num_caracteristicas;
    max_exitos = 0.1 * max_vecinos;
    num_enfriamientos = 15000 / max_vecinos;

    solucion = solInicialAleatoria(num_caracteristicas);
    KNN(train, clases_train, train, clasificacion, solucion);
    tasa_actual = tasaAgregacion(clases_train, clasificacion, solucion, 0.5);
    num_eval++;

    mejor_solucion = solucion;
    mejor_tasa = tasa_actual;
    t_ini = (0.3*(mejor_tasa/100.0))/(-log(0.3));
    t_fin = 0.001;

    while (t_fin > t_ini)
        t_fin = t_fin * 0.001;

    beta = (t_ini - t_fin) / (num_enfriamientos*t_ini*t_fin);
    t_actual = t_ini;

    while(num_exitos > 0 && num_eval < 15000 && t_actual > t_fin)	{
        num_exitos = 0;
        vecinos = 0;
        while(num_exitos < max_exitos && vecinos < max_vecinos){
            sol_nueva = solucion;
            gen = rand() % num_caracteristicas;
            mutarSolucion(sol_nueva, gen);
            num_eval++;
            vecinos++;

            KNN(train, clases_train, train, clasificacion, sol_nueva);
            tasa_nueva = tasaAgregacion(clases_train, clasificacion, sol_nueva, 0.5);
            mejora = tasa_nueva - tasa_actual;
            //Podemos aceptar porque sea mejor o por el criterio Metropolis
            if(mejora/100.0 > 0 || (static_cast<float> (rand()) / static_cast<float> (RAND_MAX)) < exp(-(mejora/100.0)/(t_actual/100))) {
                tasa_actual = tasa_nueva;
                num_exitos++;
                solucion = sol_nueva;
                if(tasa_nueva > mejor_tasa){
                    mejor_solucion = sol_nueva;
                    mejor_tasa = tasa_nueva;
                }
            }
        }
        t_actual = t_actual / (1 + beta * t_actual);
	}

    return mejor_solucion;
}

void EjecutarEnfriamientoSimulado(int conjunto, int bd, ofstream &fs, ofstream &over, ofstream &caracteristicas, vector<float> &aciertos, vector<float> &reducciones, vector<float> &finales, vector<double> &tiempos) {
    vector<vector<float> > train, test;
    vector<int> clasificacion, clases_train, clases_test;
    vector<float> pesos;
    double acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;
    std::chrono::duration<double> time;

    CargarDatos(train, test, clases_train, clases_test, conjunto, bd);

    t_inicio = std::chrono::high_resolution_clock::now();
    pesos = EnfriamientoSimulado(train, clases_train);
    t_fin = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(t_fin - t_inicio);

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
    for(int i = 0; i < pesos.size(); i++){
        if(pesos[i] < 0.1){
            caracteristicas << i << " ";
        }
    }
    caracteristicas << endl;

    aciertos.push_back(acierto);
    reducciones.push_back(reduccion);
    finales.push_back(tasa_final);
    tiempos.push_back(time.count());

    if(conjunto == 5){
        double media_acierto = 0, media_reduccion = 0, media_final = 0, media_tiempo = 0;
        for(int i = 0; i < 5; i++){
            media_acierto += aciertos[i];
            media_reduccion += reducciones[i];
            media_final += finales[i];
            media_tiempo += tiempos[i];
        }

        cout << endl << "Medias: (tasa acierto, tasa reduccion, tasa final, tiempo). " << media_acierto / 5.0 << " : " << media_reduccion / 5.0 << " : " << media_final / 5.0 << " : " << media_tiempo / 5.0 << endl;
        fs << endl << media_acierto / 5.0 << " " << media_reduccion / 5.0 << " " << media_final / 5.0 << " " << media_tiempo / 5.0 << endl;
    }
}