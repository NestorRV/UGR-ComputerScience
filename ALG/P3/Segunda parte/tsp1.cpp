#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

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
void leer_puntos(string & nombre, map<int, pair<double, double> > & M){
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
void leer_orden(string & nombre, vector<int> & V){
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

//NUESTRAS FUNCIONES

int Euclides (double x1,double y1,double x2,double y2) {
    double aux1, aux2;
    int salida;
    aux1 = (x2-x1)*(x2-x1);
    aux2 = (y2-y1)*(y2-y1);
    aux2 += aux1;
    salida = sqrt(aux2);
    return salida;
}

void Distancias(map<int, pair<double, double> > m, vector<vector<int> > & matriz) {
    for(int i = 0; i < matriz.size(); i++)
        for(int j = 0; j < matriz[i].size(); j++)
            if(i != j)
                matriz[i][j] = Euclides(m[i+1].first, m[i+1].second, m[j+1].first, m[j+1].second);
}

void InvalidarColumna(vector< vector<int> > & m, int c) {
    for(int i = 0; i < m.size(); i++)
        for(int j = 0; j < m[i].size(); j++)
            if(c == j)
                m[i][j] = -1;
}

/*Comenzamos seleccionando la ciudad inicial como la 1. Recorremos la fila 1 y seleccionamos la ciudad a
menor distancia (columnas). Cuando hacemos esto saltamos a la fila de la ciudad seleccionada y volvemos a
realizar este procedimiento. Tenemos en cuenta que no podemos introducir ciudades repetidas.
Cuando haya introducido de la lista todas las ciudades sin repeticiones, aniadimos a la distancia final el
camino entre la ultima ciudad y la primera, e insertamos de nuevo la ciudad 1 (unica que se repite).*/

vector<int> TSP(vector< vector<int> > matriz, int & distancia) {
   vector<int> recorrido;
   int ciudad, min, pos, j;
   ciudad = 0;
   min = 0;
   pos = 0;
   j = 0;

   recorrido.push_back(1);
   for(int i = 1; i < matriz.size(); i++) {
      j = 1;
      while(matriz[ciudad][j] == -1)
         j++;

      min = matriz[ciudad][j];
      pos = j;
      for(j; j < matriz[ciudad].size(); j++)
         if(matriz[ciudad][j] != -1 && min > matriz[ciudad][j]) {
            min = matriz[ciudad][j];
            pos = j;
         }

      ciudad = pos;
      recorrido.push_back(ciudad+1);
      InvalidarColumna(matriz,ciudad);
      distancia += min;
   }

   distancia += matriz[ciudad][0];
   recorrido.push_back(1);
   return recorrido;
}

int main(int argc, char * argv[])
{

   map<int, pair<double, double> > M;
   vector<vector<int> > matriz;
   vector<int> V;
   int distancia = 0;
   string fp,fok;
   if (argc == 1) {
      cout << "Error Formato:  tsp puntos orden_correcto" << endl;
      exit(1);
   }

   CLParser cmd_line(argc,argv,false);

   fp = cmd_line.get_arg(1);
   leer_puntos(fp,M);

   fok = cmd_line.get_arg(2);
   leer_orden(fok,V);

   matriz.resize(M.size(), vector<int>(M.size(),-1));
   Distancias(M, matriz);
   V = TSP(matriz, distancia);

   cout << "Distancia: " << distancia << endl;

   cout << "Dimension: " << V.size() << endl;
   for (int i=0;i<V.size(); i++)
      cout << V[i] << " " << M[V[i]].first << " " << M[V[i]].second << endl;

    return 0;
}
