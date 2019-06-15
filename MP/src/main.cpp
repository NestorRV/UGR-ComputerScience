#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "conjunto.h"
#include "cdconjuntos.h"
using namespace std;

int main(int argc, char *argv[]){
  Conjunto conjunto_aux;
  ConjuntoDeConjuntos c, solucion;
  ifstream inData;
  ofstream outData;
  string cad;
  int x;
  istringstream iss;

  //Comprobar si el numero de argumentos es correcto
  if(argc!=4){
    cerr << "Error: Numero de parametros erroneo." << endl;
    cerr << "Uso de: " << argv[0]<< " k, fichero de entrada, fichero de salida." << endl;
    exit (1);
  }

  //Abro los archivos de entrada y salida
  inData.open(argv[2]);
  outData.open(argv[3]);

  //Comprobar si alguno de los ficheros ha dado error
  //al ser abierto
  if(!inData){
    cerr << "Error: no se puede abrir " << argv[2] << endl;
    exit (1);
  }
  if(!outData){
    cerr << "Error: no se puede abrir " << argv[3] << endl;
    exit (1);
  }

  //Convertir el primer argumento de la llamada al programa a entero
  char *cadena=argv[1];
  int k=atoi(cadena);

  //Leo los conjuntos del fichero de entrada
  getline(inData, cad);
  while (!inData.eof()){
    iss.str(cad);
    iss.clear();
    while(iss >> x)
      conjunto_aux.Inserta(x);
    c.Aniadir(conjunto_aux);
    conjunto_aux.Destruir();
    getline(inData, cad);
  }

  solucion=c.Solucion(k);
  outData << solucion;
  cout << "El cardinal de la interseccion de los conjuntos de la solucion es: " << (solucion.Interseccion()).Tamanio() << endl;

  //Cierro los archivos de entrada y salida
  inData.close();
  outData.close();
}
