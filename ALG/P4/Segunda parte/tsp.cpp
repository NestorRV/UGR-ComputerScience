#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <queue>
#include <chrono>

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#define DATOS

//Lee el fichero de coordenadas de un fichero de TSP y el recorrido �ptimo (en ese orden) y da como salida el fichero de coordenadas pero reordenado seg�n el orden �ptimo, para poder dibujarlo con gnuplot

class CLParser
{
public:

    CLParser(int argc_, char * argv_[],bool switches_on_=false);
    ~CLParser(){}

    string get_arg(int i);
    string get_arg(string s);

private:

    int argc;
    vector<string> argv;

    bool switches_on;
    map<string,string> switch_map;
};

CLParser::CLParser(int argc_, char * argv_[],bool switches_on_)
{
    argc=argc_;
    argv.resize(argc);
    copy(argv_,argv_+argc,argv.begin());
    switches_on=switches_on_;

    //map the switches to the actual
    //arguments if necessary
    if (switches_on)
    {
        vector<string>::iterator it1,it2;
        it1=argv.begin();
        it2=it1+1;

        while (true)
        {
            if (it1==argv.end()) break;
            if (it2==argv.end()) break;

            if ((*it1)[0]=='-')
                switch_map[*it1]=*(it2);

            it1++;
            it2++;
        }
    }
}

string CLParser::get_arg(int i)
{
    if (i>=0&&i<argc)
        return argv[i];

    return "";
}

string CLParser::get_arg(string s)
{
    if (!switches_on) return "";

    if (switch_map.find(s)!=switch_map.end())
        return switch_map[s];

    return "";
}



/*
*/
void leer_puntos(string & nombre, map<double, pair<double, double> > & M){
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;


    datos.open(nombre.c_str());
    if (datos.is_open()) {
    datos >> s; // Leo "dimension:"
    datos >> n;
    int i=0;
    while (i<n) {
        datos >> act >> p.first >> p.second;
	M[act] = p;
	i++;
      }

    datos.close();
    }
   else {
      cout << "Error de Lectura en " << nombre << endl;
    }
 }



/*
*/
void leer_orden(string & nombre, vector<double> & V){
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;

    datos.open(nombre.c_str());
    if (datos.is_open()) {
    datos >> s; // Leo "dimension:"
    datos >> n;
    V.reserve(n);
    int i=0;
    while (i<n) {
        datos >> act;
	V.push_back(act);
	i++;
      }

    datos.close();
    }
   else {
      cout << "Error de Lectura en " << nombre << endl;
    }
 }
//////////////////////////////////////////////////////////////

typedef struct {
    vector<double> ruta;
    int indice;
    float mejores_aristas;
    float coste;
} Nodo;

typedef struct {
    float numNodos = 0;
    float tamanioCola = 0;
    float numPodas = 0;
    double tiempo = 0;
} Complejidad;

Complejidad complejidad;

double Euclides (double x1,double y1,double x2,double y2) {
    double aux1, aux2;
    double salida;
    aux1 = (x2-x1)*(x2-x1);
    aux2 = (y2-y1)*(y2-y1);
    aux2 += aux1;
    salida = sqrt(aux2);
    return salida;
}

void Distancias(map<double, pair<double, double> > m, vector<vector<double> > & matriz) {
    for(int i = 0; i < matriz.size(); i++)
        for(int j = 0; j < matriz[i].size(); j++)
            if(i != j)
                matriz[i][j] = Euclides(m[i+1].first, m[i+1].second, m[j+1].first, m[j+1].second);
}

bool Cruce(int u, int v, int w, int z, const vector<vector<double> > & matriz) {
    // Calcula si se produce un cruce
    return matriz[u][v] + matriz[w][z] > matriz[u][w] + matriz[v][z];
}

class FunctorPQ{
    public:
        bool operator()(Nodo& n1, Nodo& n2) {
            return n1.coste + n1.mejores_aristas < n2.coste + n2.mejores_aristas;
        }
};

vector<double> MinimosNodos(vector<vector<double> > & matriz) {
    vector<double> min;
    for (unsigned i = 0; i < matriz.size(); ++i) {
        float minimo = 999999999.0;

        for (unsigned j = 0; j < matriz[i].size(); ++j) {
            float posible = matriz[i][j];

            if (posible < minimo && posible > 0)
                minimo = posible;
        }
        min.push_back(minimo);
    }

    return min;
}

void aniadirPrimera(Nodo & n, vector<vector<double> > & matriz){
    n.ruta.resize(matriz.size());
    n.indice = 1;
    n.mejores_aristas = 0;
    n.coste = 0;
}

Nodo TSP(vector<vector<double> > & matriz) {
    priority_queue<Nodo, vector<Nodo>, FunctorPQ> nodosVivos;
    double dim = matriz.size();

    Nodo mejor;
    aniadirPrimera(mejor, matriz);
    for(int i = 0; i < mejor.ruta.size(); i++)
        mejor.ruta[i] = i;

    vector<double> min_distancias = MinimosNodos(matriz);
    mejor.mejores_aristas = 0;
    for(int i = 0; i < mejor.ruta.size(); i++)
        mejor.mejores_aristas += min_distancias[i];

    nodosVivos.push(mejor);
    int maximo = 1, contador = 1;
    mejor.coste = 999999999.0;

    while (!nodosVivos.empty()) {
        Nodo actual = nodosVivos.top();
        nodosVivos.pop();
        complejidad.numNodos++;
        contador--;

        // Caso de la ruta finalizada
        // Comprueba si se mejora el óptimo
        if (actual.indice == dim) {
            float total = actual.coste + matriz[actual.ruta[dim-1]][actual.ruta[0]];

            if (total < mejor.coste) {
                mejor.ruta = actual.ruta;
                mejor.coste = total;
            }
        }
        else if (actual.coste + actual.mejores_aristas < mejor.coste) {
            for (unsigned i = actual.indice; i < dim; ++i) {
                bool cruce = false;
                // Si se introduce un cruce de caminos:
                for (unsigned j = 1; j < actual.indice && !cruce; j++)
                    cruce = Cruce(actual.ruta[i], actual.ruta[actual.indice-1], actual.ruta[j], actual.ruta[j-1], matriz);

                if (!cruce) {
                    Nodo hijo(actual);
                    swap(hijo.ruta[i], hijo.ruta[hijo.indice]);

                    hijo.coste += matriz[hijo.ruta[hijo.indice - 1]][hijo.ruta[hijo.indice]];
                    hijo.mejores_aristas -= min_distancias[hijo.indice - 1];
                    hijo.indice++;

                    nodosVivos.push(hijo);
                    contador++;
                    if(contador > maximo)
                        maximo = contador;
                }
            }
        }
        else {
            // Poda
            complejidad.numPodas++;
        }

    }

    complejidad.tamanioCola = maximo;

    return mejor;
}

int main(int argc, char * argv[]){
    map<double, pair<double, double> > M;
    vector<vector<double> > matriz;
    vector<double> V;
    Nodo N;
    chrono::high_resolution_clock::time_point tantes, tdespues;
    chrono::duration<double> transcurrido;

    string fp,fok;
    if (argc == 1) {
        cout << "Error Formato: tsp puntos orden_correcto" << endl;
        exit(1);
    }

    CLParser cmd_line(argc,argv,false);

    fp = cmd_line.get_arg(1);
    leer_puntos(fp,M);

    fok = cmd_line.get_arg(2);
    leer_orden(fok,V);

    matriz.resize(M.size(), vector<double>(M.size(),-1));
    Distancias(M, matriz);

    tantes = chrono::high_resolution_clock::now();
    N = TSP(matriz);
    tdespues = chrono::high_resolution_clock::now();
    transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);

    complejidad.tiempo = transcurrido.count();

    cout << "Dimension: " << N.ruta.size() << endl;
    for(int i = 0; i < N.ruta.size(); i++)
        cout << N.ruta[i] << " " << M[N.ruta[i]+1].first << " " << M[N.ruta[i]+1].second << endl;

    #ifdef DATOS
        cout << endl << endl << endl << endl;
        cout << "Mejor coste obtenido: " << N.coste << endl;
        cout << "Numero de nodos expandidos: " << complejidad.numNodos << endl;
        cout << "Tamaño maximo de la cola: " << complejidad.tamanioCola << endl;
        cout << "Numero de podas: " << complejidad.numPodas << endl;
        cout << "Tiempo: " << complejidad.tiempo << endl;
    #endif

    return 0;
}
