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

//Calcula la distancia entre dos ciudades
int DistanciaEntre(int ciudad1, int ciudad2, const vector<vector<int> > &m) {
    ciudad1--;
    ciudad2--;

    return m[ciudad1][ciudad2];
}

//Calcula la distancia de una lista de ciudades
int DistanciaTotal(const list<int> & ciudades, const vector<vector<int> > &m) {
    list<int>::const_iterator it1,it2;
    int distancia=0;
    it1=ciudades.begin();
    it2=ciudades.begin();
    it1++;

    for(it1; it1 != ciudades.end(); it1++) {
        distancia += DistanciaEntre(*it1, *it2, m);
        it2 = it1;
    }
    return distancia;
}

//Calcula el aumento de distancia a meter una nueva ciudad
pair<int,list<int>::iterator> IncrementoDeDistancia(list<int> &ciudades, const vector<vector<int> > & matriz, int ciudad) {
    list<int>::iterator it1 = ciudades.begin();
    list<int>::iterator it2 = ciudades.end();
    list<int>::iterator posicion_ciudad = ciudades.begin();
    it2--; //ultima ciudad

    int distancia;
    distancia = DistanciaEntre(*it1, ciudad, matriz) + DistanciaEntre(*it2, ciudad, matriz);
    distancia -= DistanciaEntre(*it1, *it2, matriz);

    it2 = it1; //it2 apunta a la primera ciudad
    it1++; //it apunta a la segunda ciudad

    for(it1; it1 != ciudades.end(); it1++) {
        int a = *it1;
        int b = *it2;
        int distancia2 = DistanciaEntre(a, ciudad, matriz) + DistanciaEntre(b, ciudad, matriz);
        distancia2 -= DistanciaEntre(a, b, matriz);
        if(distancia2 < distancia) {
            distancia = distancia2;
            posicion_ciudad = it1;
        }
        it2 = it1;
        it1++;
    }

    //Devueve el incremento al meter la ciudad y un iteradr a la misma
    return pair<int, list<int>::iterator>(distancia, posicion_ciudad);
}

//Inserta ciudad en una posicion dada
void InsertarCiudad(list<int> &recorrido, int ciudad, list<int>::iterator it) {
    recorrido.insert(it, ciudad);
}

//Elige la ciudad que menos incremento suponga en la lista de ciudades
pair<int,list<int>::iterator> ElegirCiudad(list<int> &ciudades, const vector<vector<int> > &matriz, list<int> &sin_visitar) {
    list<int>::iterator it, it_ciudad_seleccionada;
    pair<int,list<int>::iterator> selec;

    bool primera=false;
    int ciudad_seleccionada;
    for(it = sin_visitar.begin(); it != sin_visitar.end(); it++) {
        pair<int,list<int>::iterator> selec2;
        int nueva_ciudad = *it;
        selec2 = IncrementoDeDistancia(ciudades, matriz, nueva_ciudad);
        if(primera == false) { //if absurdo, se puede poner fuera del for y ahorrarnos "primera"
            primera = true;
            selec = selec2;
            ciudad_seleccionada = nueva_ciudad;
            it_ciudad_seleccionada = it;
        }
        else if(selec2.first < selec.first) {
            selec = selec2;
            ciudad_seleccionada = nueva_ciudad;
            it_ciudad_seleccionada = it;
        }
    }
    sin_visitar.erase(it_ciudad_seleccionada);

    return pair<int,list<int>::iterator>(ciudad_seleccionada, selec.second);
}


/*El recorrido inicial se puede construir a partir de las tres ciudades que formen un tri�ngulo
lo m�s grande posible: por ejemplo, eligiendo la ciudad que est� m�s a Este, la que est� m�s al Oeste, y la
que est� m�s al norte.
Vamos recorriendo el vector de ciudades no seleccionadas e insertando cada una de ellas en
cada posible posici�n. Utilizando el criterio de inserci�n m�s econ�mica, elegimos aquella ciudad y su
posici�n en el camino final, que provoque un menor incremente en la longitud total del circuito.*/

list<int> TSP(const vector<vector<int> > &matriz, const map<int, pair<double, double> >  &m, int &distancia_final) {
    int n=1;
    int s=1;
    int w=1;

    list<int> salida;
    map<int,pair<double,double> >::const_iterator it  = m.begin();
    list<int> ciudades_restantes;
    ciudades_restantes.push_back(1);

    //En cada par estan las coordenadas de la primera ciudad
    pair<double,double> pn=(*it).second, ps=(*it).second, pw=(*it).second;
    it++;

    //Escogemos las ciudades mas al norte, sur y oeste
    for(it; it != m.end(); it++) {
        ciudades_restantes.push_back((*it).first);
        pair<double,double> p=(*it).second;
        int ciudad_actual=(*it).first;

        //Tiene que haber elses ya que debe escoger ciudades distintas (la de mas al norte
        // y mas al oeste no pueden ser la misma)
        if(p.first<pw.first) { //Elige la de mas al oeste
            pw=p;
            w=ciudad_actual;
        }
        else if(p.second>pn.second || (n==w && n==1)) { //La de mas al norte
            pn=p;
            n=ciudad_actual;
        }
        else if(p.second<ps.second || (s==w && s==1)) { //La de mas al sur
            ps=p;
            s=ciudad_actual;
        }
    }
    //n,s,w forman el triangulo mas grande
    //suponemos que empezamos en n, una de las ciudades del triangulo

    //Mete las tres en la solucion
    salida.push_back(n);
    salida.push_back(s);
    salida.push_back(w);

    //Las elimina de las reestantes
    ciudades_restantes.remove(n);
    ciudades_restantes.remove(s);
    ciudades_restantes.remove(w);

    while(ciudades_restantes.size() > 0) {
        pair<int,list<int>::iterator> pres;
        pres = ElegirCiudad(salida, matriz, ciudades_restantes);
        InsertarCiudad(salida, pres.first, pres.second);
    }

    salida.push_back(*(salida.begin())); //volvemos a la primera ciudad
    distancia_final = DistanciaTotal(salida, matriz);

    return salida;
}



////////////////////////////////////////////////////////////////
int main(int argc, char * argv[]) {

	map<int, pair<double, double> >  M;
	vector<int> V;
	vector< vector<int> > matriz;//cremaos un matriz con la distnacia entre dos pueblos
	list<int> recorrido;
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

    matriz.resize(M.size(), vector<int>(M.size(), -1));
    Distancias(M, matriz);

    recorrido = TSP(matriz, M, distancia);

    cout << "Distancia: " << distancia << endl;

    cout << "Dimension: " << recorrido.size() << endl;

    list<int>::iterator it;
    for(it = recorrido.begin(); it != recorrido.end(); it++) {
        pair<double,double> p;
        p = (M.find(*it))->second;
        cout<< *it << " " << p.first << " " << p.second << endl;
    }

    return 0;
}
