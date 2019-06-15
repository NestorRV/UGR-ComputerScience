#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//Lee el fichero de coordenadas de un fichero de TSP y el recorrido �ptimo (en ese orden) y da como salida el fichero de coordenadas pero reordenado seg�n el orden �ptimo, para poder dibujarlo con gnuplot
//Este algoritmo est� implementado por nosotros, en el cu�l creamos un
//map ( map<int , pair<int, int> > aristas) formado por la distancia entre dos ciudades cada entrada.
//Vamos seleccionando las distancias menores entre dos ciudades y a�adiendo estas al conjunto de
//seleccionados. Para poder insertar una nueva ciudad, esta no puede tener m�s de 2 aristas ni
//crear un ciclo. C�mo el camino resultante de este algoritmo no es cerrado, tenemos que
//recorrer el camino y a�adir la distancia entre las 2 ciudades que �nicamente tienen una arista.

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

//Distancia de ciudad A a B, y el par de las ciudades A y B
multimap<int , pair<int,int> > ObtenerAristas(const vector< vector<int> > & m) {

    multimap<int , pair<int,int> > salida;
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++) {
            /*Como la matriz m es simetrica con diagonal 0
            (vease calcular matriz, la distancia de la ciudad i a la j es la misma que
            de la j a la i) solo metemos la parte superior de la matriz para evitar tener
            repetidos*/
            if(j>i) {
                salida.insert(pair<int, pair<int,int> >(m[i][j],pair<int,int>(i+1,j+1)));
            }
        }
    }
    return salida;
}

//Comprueba si es factible a�adir un nodo (tiene mas de dos aristas)
bool CiudadFactible( list<pair<int,int> > & aux, const pair<int,int> & s) {
    int CiudadA = s.first;
    int CiudadB = s.second;
    int contadorA = 0;
    int contadorB = 0;
    /*
    A:una ciudad
    B:otra ciudad
    contA: Numero de aristas de A
    contB: Numero de aristas de B
    */
    list<pair<int, int> >::iterator it = aux.begin();
    for(it; it != aux.end(); it++) {
        if(CiudadA == (*it).first || CiudadA == (*it).second)
            contadorA++;
        if(CiudadB == (*it).first || CiudadB == (*it).second)
            contadorB++;
    }
    return !(contadorA>1 or contadorB>1);
}

//Busca la primera ocurrencia de la ciudad "ciudad", cambia el valor de ciudad
//A la ciudad a la que aparezca conectada y devuelve un iterador a dicha ciudad
list<pair<int,int> >::iterator BuscarCiudadConectada(list<pair<int,int> >& aux, int & ciudad) {
    list<pair<int,int> >::iterator it;
    for(it=aux.begin(); it!=aux.end(); it++) {
        if((*it).first==ciudad) {
            ciudad=(*it).second;

            return it;
        }
        else if((*it).second==ciudad) {
            ciudad=(*it).first;

            return it;
        }
    }
}

//Busca la ciudad "ciudad" y devuelve un iterador sobre la lista que apunta a
//dicha ciudad
list<pair<int,int> >::iterator BuscarCiudad(list<pair<int,int> >& aux,int  ciudad) {
    list<pair<int,int> >::iterator it;
    for(it=aux.begin(); it!=aux.end(); it++) {
        if((*it).first==ciudad) {
            return it;
        }
        else if((*it).second==ciudad) {
            return it;
        }
    }
    return aux.end();
}

//Si al a�adirle el nodo, todas las ciudades tienen dos aristas, se crea un ciclo
bool ExistenCiclos(list<pair<int,int> > aristas, const pair<int,int> & nodo) {
    int pos,res;
    list<pair<int,int> >::iterator it;
    res = nodo.second;
    pos = nodo.first;
    it = BuscarCiudad(aristas, pos);

    /*
    Busca en aux (conjuntos de grupos de dos ciudades, lo que vienen a ser aristas)
    una de las dos ciudades de la arista (pos) y se guarda la otra (res).
    Elimina la arista por la que acaba de pasar (por eso no se pasa por referencia) y vuelve
    a buscar la ciudad pos, entonces mueve pos a la ciudad a la que esta conectada, vuelve a
    eliminar la arista y vuelve a buscar otra arista que conecte a pos. Si al final pos vuelve
    a res (donde el principio) es porque hay un ciclo
    */
    while(it != aristas.end()) {
        if(pos == (*it).first)
            pos = (*it).second;
        else
            pos = (*it).first;

        aristas.erase(it);
        it = BuscarCiudad(aristas,pos);
    }
    return pos == res;
}

//Transforma la lista de aristas en un unico camino de ciudades
vector <int> TransformaACamino(list<pair<int,int> > ciudades) {
    vector<int> salida;
    list <pair<int,int> >::iterator it = ciudades.begin();
    salida.push_back((*it).first);
    int obj = (*it).second;
    ciudades.erase(it);

    while(!ciudades.empty()) {
        salida.push_back(obj);
        it = BuscarCiudadConectada(ciudades, obj);
        ciudades.erase(it);
    }
    salida.push_back(salida.front());

    return salida;
}

//Cuando ya solo falta un nodo, lo introducimos en el camino y cerramos el ciclo.
void CerrarCiclo(list <pair<int,int> > & aux, multimap<int, pair<int,int> > & m, int & distancia) {
    int ciudad1=0,ciudad2=0,conexiones1=0,conexiones2=0;
    list<pair<int,int> >::iterator it1,it2;

    for(it1=aux.begin(); it1!=aux.end(); it1++) {
        for(it2=aux.begin(); it2!=aux.end(); it2++) {
            //Cuenta que cada ciudad aparezca 2 veces, es decir, al final de una arista y al
            //principio de otra, indicando asi que est� conectada y despu�s se sale
            if((*it1).first==(*it2).first or (*it1).first==(*it2).second)
                conexiones1++;
            if((*it1).second==(*it2).first or (*it1).second==(*it2).second)
                conexiones2++;
            if(conexiones1==2 and conexiones2==2)
                break;
        }

        //Almacena aquellas ciudades que no tengan conexion en ciudad1 y ciudad2
        if(conexiones1<2 and ciudad1==0)
            ciudad1=(*it1).first;
        else if(conexiones1<2 and ciudad2==0)
            ciudad2=(*it1).first;

        if(conexiones2<2 and ciudad1==0)
            ciudad1=(*it1).second;
        else if(conexiones2<2 and ciudad2==0)
            ciudad2=(*it1).second;

        conexiones1=conexiones2=0;
    }
    //Introduce la nueva conexion que faltaba entre la ciudad ciudad1 y ciudad2, y a�ade
    //la distancia
    multimap<int , pair<int,int> >::iterator it;
    for(it=m.begin(); it!=m.end(); it++) {
        if((((*it).second).first==ciudad1 and ((*it).second).second==ciudad2)or  (((*it).second).first==ciudad2 and ((*it).second).second==ciudad1)) {
            aux.push_back((*it).second);
            distancia+=(*it).first;
        }
    }
}

vector<int> TSP(multimap<int, pair<int,int> > & aristas_par_ciudades, int & distancia) {
    vector<int> salida;
    list<pair<int,int> > aux;
    multimap<int , pair<int,int> >::iterator it = aristas_par_ciudades.begin();

    //Mete la primera arista
    aux.push_back((*it).second);
    //a�ade su distancia
    distancia+=(*it).first;
    it++;
    while(it != aristas_par_ciudades.end()) {
        //Si no hay ciclos y la nueva arista no provoca que un vertice tenga mas de dos aristas
        //se mete en la lista
        if(CiudadFactible(aux, (*it).second) && !ExistenCiclos(aux, (*it).second)) {
            aux.push_back((*it).second);
            distancia += (*it).first;
        }
        it++;
    }
    //Se cierra el ciclo (conectar ultimo con el primero)
    CerrarCiclo(aux, aristas_par_ciudades, distancia);
    //Se obtiene el camino creado
    salida = TransformaACamino(aux);

    return salida;
}

//////////////////////////////////////////////////////////////

int main(int argc, char * argv[]) {

  map<int, pair<double, double> >  M;
  vector< vector<int> > matriz;
  multimap<int , pair<int,int> > aristas;
  vector<int> V;
  int distancia;
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

    matriz.resize(M.size(), vector<int>(M.size(), -1));
    Distancias(M, matriz);

    //aristas -> multimap: calcula la distancia entre A y B, par de A,B
    aristas = ObtenerAristas(matriz);

    //devuelve un vector, le pasas las aristas y la distancia por referencia para almacenarla ahi
    V = TSP(aristas, distancia);

    cout << "Distancia: " << distancia << endl;

    cout << "Dimension: " << V.size() << endl;
    for (int i=0;i<V.size(); i++){
      cout << V[i] << " " << M[V[i]].first << " " << M[V[i]].second << endl;

    }

    return 0;
}
