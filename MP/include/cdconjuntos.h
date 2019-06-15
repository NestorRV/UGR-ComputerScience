#ifndef CDCONJUNTOS
#define CDCONJUNTOS

#include <ctime>
#include <iostream>
//Para usar atoi
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;
typedef int TIPOBASE;

class ConjuntoDeConjuntos{
private:
  Conjunto *conjuntodeconjuntos;      //Puntero a objeto Conjunto
  int elementos;      //Contador para el numero de elementos
public:
  //Constructor (perteneciente a la clase ConjuntoDeConjuntos)
  ConjuntoDeConjuntos();
  //Contructor de copia (perteneciente a la clase ConjuntoDeConjuntos)
  ConjuntoDeConjuntos(const ConjuntoDeConjuntos &otro_cdc);
  //Metodo auxiliar para el destructor (perteneciente a la clase ConjuntoDeConjuntos)
  void DestruirCDC();
  //Destructor
  ~ConjuntoDeConjuntos();
  //Consultar el tamanio del conjunto (perteneciente a la clase ConjuntoDeConjuntos)
  int Tamanio() const;
  //Aniade conjunto a nuestro conjuntodeconjuntos
  //(perteneciente a la clase ConjuntoDeConjuntos)
  void Aniadir(const Conjunto &conjunto);
  //Borrar conjunto de nuestro conjuntodeconjuntos
  //(perteneciente a la clase ConjuntoDeConjuntos)
  void BorrarConjunto(int posicion);
  //Metodo para obtener un conjunto de nuestro conjuntodeconjuntos
  //(perteneciente a la clase ConjuntoDeConjuntos)
  Conjunto Get(int i) const;
  //Metodo que devuelve un conjunto formado por la interseccon de los
  //conjuntos que forman conjuntodeconjuntos
  //(perteneciente a la clase ConjuntoDeConjuntos)
  Conjunto Interseccion() const;
  //Metodo para calcular un numero aleatorio
  int Aleatorio(int i) const;
  //Metodo que devuelve el siguiente conjunto a aniadir
  int ConjuntoAniadir(ConjuntoDeConjuntos &solucion) const;
  //Metodo para editar la solucion y el conjunto original
  void Editar(ConjuntoDeConjuntos &solucion);
  //Metodo para resolver nuestro problema (perteneciente a la clase ConjuntoDeConjuntos)
  ConjuntoDeConjuntos Solucion(int k);
  //Sobrecarga del operador de asignacion (perteneciente a la clase ConjuntoDeConjuntos)
  const ConjuntoDeConjuntos& operator=(const ConjuntoDeConjuntos& otro_cdc);
  //Sobrecarga del operador << (perteneciente a la clase ConjuntoDeConjuntos)
  friend ostream& operator<<(ostream &os, const ConjuntoDeConjuntos &otro_cdc);
};

#endif
