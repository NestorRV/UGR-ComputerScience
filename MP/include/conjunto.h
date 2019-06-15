#ifndef CONJUNTO
#define CONJUNTO

#include <ctime>
#include <iostream>
//Para usar atoi
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;
typedef int TIPOBASE;

struct Celda{
  TIPOBASE info;
  Celda *sig;
};

class Conjunto{
private:
  Celda *l;     //Puntero a la primera celda
  Celda *ultimo;      //Puntero a la ultima celda
  int elementos;      //Contador para el numero de elementos
public:
  //Constructor (perteneciente a la clase Conjunto)
  Conjunto();
  //Crea un conjunto con un unico elemento, valor (perteneciente a la clase Conjunto)
  Conjunto(TIPOBASE valor);
  //Constructor de copia (perteneciente a la clase Conjunto)
  Conjunto(const Conjunto& otroconjunto);
  //Destructor (perteneciente a la clase Conjunto)
  ~Conjunto();
  //Ver si el conjunto esta vacio (perteneciente a la clase Conjunto)
  bool Vacio() const;
  //Consultar el tamanio del conjunto (perteneciente a la clase Conjunto)
  int Tamanio() const;
  //Metodo auxiliar para el destructor (perteneciente a la clase Conjunto)
  void Destruir();
  //Metodo auxiliar para la asignacion y el constructor de copia
  //(perteneciente a la clase Conjunto)
  void CopiarConjunto(const Conjunto& otroconjunto);
  //Buscar un elemento en el conjunto (perteneciente a la clase Conjunto)
  bool Buscar(const TIPOBASE& valor) const;
  //Metodo auxiliar para la sobrecarga de >> y para aniadir elementos a mi conjunto
  //(perteneciente a la clase Conjunto)
  void Inserta(const TIPOBASE& valor);
  //Metodo auxiliar para la sobrecarga del operador -  (perteneciente a la clase Conjunto)
  void BorrarElemento(const TIPOBASE& valor);

  //Sobrecarga del operador de asignacion (perteneciente a la clase Conjunto)
  const Conjunto& operator=(const Conjunto& otroconjunto);
  //Sobrecarga del operador << (perteneciente a la clase Conjunto)
  friend ostream& operator<<(ostream &os, const Conjunto &conjunto);
  //Sobrecarga del operador >> (perteneciente a la clase Conjunto)
  friend istream& operator>>(istream &is, Conjunto &conjunto);
  //Sobrecarga del operador == (perteneciente a la clase Conjunto)
  friend bool operator==(const Conjunto &un_conjunto1, const Conjunto &un_conjunto2);
  //Sobrecarga del operador != (perteneciente a la clase Conjunto)
	friend bool operator!=(const Conjunto &un_conjunto1, const Conjunto &un_conjunto2);
  //Sobrecarga del operador + (perteneciente a la clase Conjunto)
  friend Conjunto operator+(const Conjunto &un_conjunto1, const Conjunto &un_conjunto2);
  //Sobrecarga del operador - (perteneciente a la clase Conjunto)
	friend Conjunto operator-(const Conjunto &un_conjunto1, const Conjunto &un_conjunto2);
  //Sobrecarga del operador * (perteneciente a la clase Conjunto)
	friend Conjunto operator*(const Conjunto &un_conjunto1, const Conjunto &un_conjunto2);
};

#endif
