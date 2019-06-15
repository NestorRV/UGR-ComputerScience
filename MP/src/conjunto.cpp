#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "conjunto.h"
using namespace std;

//Constructor (perteneciente a la clase Conjunto)
Conjunto::Conjunto(){
  l=0;
  ultimo=0;
  elementos=0;
}

//Crea un conjunto con un unico elemento, valor (perteneciente a la clase Conjunto)
Conjunto::Conjunto(TIPOBASE valor){
  Celda *p;
  p=new Celda;
  p->info=valor;
  p->sig=0;
  l=p;
  ultimo=p;
  elementos=1;
}

//Constructor de copia (perteneciente a la clase Conjunto)
Conjunto::Conjunto(const Conjunto& otroconjunto){
  l=0;
  CopiarConjunto(otroconjunto);
}

//Destructor (perteneciente a la clase Conjunto)
Conjunto::~Conjunto(){
  Destruir();
}

//Ver si el conjunto esta vacio (perteneciente a la clase Conjunto)
bool Conjunto::Vacio() const{
  return (elementos==0);
}

//Consultar el tamanio del conjunto (perteneciente a la clase Conjunto)
int Conjunto::Tamanio() const{
  return elementos;
}

//Metodo auxiliar para el destructor (perteneciente a la clase Conjunto)
void Conjunto::Destruir(){
  Celda *aux;
  //Mientras el conjjunto no esta vacio
  while (l!=0){
    //Avanzar aux
    aux=l;
    //Avanzar l
    l=l->sig;
    //Liberar la memoria apuntada por aux
    delete aux;
  }
  ultimo=0;
  elementos=0;
}

//Metodo auxiliar para la asignacion y el constructor de copia
// (perteneciente a la clase Conjunto)
void Conjunto::CopiarConjunto(const Conjunto& otroconjunto){
  Celda *aux;
  Celda *p;
  //Vaciar el conjunto donde se va a copiar
  if (l!=0)
    Destruir();
  //Si otroconjunto esta vacio, solo hay que "copiar" el valor de los
  //punteros y de elementos
  if (otroconjunto.l==0){
    l=0;
    ultimo=0;
    elementos=0;
  }
  else{
    p=otroconjunto.l; //p apunta a el conjunto a copiar
    elementos=otroconjunto.elementos;
    //Copiar la primera celda
    l=new Celda;
    l->info=p->info;
    l->sig=0;
    ultimo=l;
    p=p->sig;
    //Copiar el resto
    while (p!=0){
      aux = new Celda;
      aux->info=p->info;
      aux->sig=0;
      ultimo->sig=aux;
      ultimo=aux;
      p=p->sig;
    }
  }
}

//Buscar un elemento en el conjunto (perteneciente a la clase Conjunto)
bool Conjunto::Buscar(const TIPOBASE& valor) const{
  bool encontrado=false;
  Celda *p;
  p=l;
  //Recorrer el conjunto mientras no se ha encontrado el valor y
  //no se ha recorrido el conjunto entero
  while (p!=0 && !encontrado)
    if (p->info==valor)
      encontrado=true;
    else
      p=p->sig;
  //Comprobacion
  if (encontrado)
    encontrado=(p->info==valor);
  return encontrado;
}

//Metodo auxiliar para la sobrecarga de >> y para aniadir elementos a mi conjunto
//(perteneciente a la clase Conjunto)
void Conjunto::Inserta(const TIPOBASE& valor){
  Celda *p;
  Celda *pant;
  Celda *nuevo;
  bool encontrado;
  if(!(*this).Buscar(valor)){
    //Crear la celda para el nuevo valor y rellenarla
    nuevo=new Celda;
    nuevo->info=valor;
    nuevo->sig=0;
    //El conjunto esta vacio
    if (l==0){
      l=nuevo;
      ultimo=nuevo;
      elementos++;
    }
    else{
      p=l;
      encontrado=false;
      //Recorrer el conjunto
      while (p!=0 && !encontrado){
        if (p->info>valor)
          encontrado=true;
        else{
          pant=p;
          p=p->sig;
        }
      }
      //valor debe ir al principio
      if (p==l){
        nuevo->sig=l;
        l=nuevo;
        elementos++;
      }
      //valor no va al principio
      else{
        pant->sig=nuevo;
        nuevo->sig=p;
          if (p==0)
            ultimo=nuevo;
        elementos++;
      }
    }
  }
}

//Metodo auxiliar para la sobrecarga del operador - (perteneciente a la clase Conjunto)
void Conjunto::BorrarElemento(const TIPOBASE& valor){
  Celda *p;
  Celda *pant;
  bool encontrado;
  if(l!=0){
    p=l;
    encontrado=false;
    while (p!=0 && !encontrado){ //Buscar en el conjunto
      if (p->info>=valor)
        encontrado = true;
      else{
        pant=p;
        p=p->sig;
      }
    }
    if (encontrado){
      //El elemento a borrar es el primero
      if (l==p){
        l=l->sig;
        if (l==0)
          ultimo=0;
        delete p;
      }
      else{
        //El elemento esta en el conjunto
        pant->sig=p->sig;
        if (p==ultimo)
          ultimo=pant;
        delete p;
      }
      //Actualizar el numero de elementos del conjunto
      elementos--;
    }
  }
}

//Sobrecarga del operador de asignacion (perteneciente a la clase Conjunto)
const Conjunto& Conjunto::operator=(const Conjunto& otroconjunto){
  if (this!=&otroconjunto){
    CopiarConjunto(otroconjunto);
  }
  return *this;
}

//Sobrecarga del operador << (perteneciente a la clase Conjunto)
ostream & operator<<(ostream &os, const Conjunto &conjunto){
  Celda *p=conjunto.l;
  while (p!=0){
    os << p->info << "\t";
    p=p->sig;
  }
  return os;
}

//Sobrecarga del operador >> (perteneciente a la clase Conjunto)
istream & operator>>(istream &is, Conjunto &conjunto){
  TIPOBASE x;
  is >> x;
  while (x!=0){
    conjunto.Inserta(x);
    is >> x;
  }
  return is;
}

//Sobrecarga del operador == (perteneciente a la clase Conjunto)
bool operator==(const Conjunto &un_conjunto1, const Conjunto &un_conjunto2){
  bool iguales=true;
  if(un_conjunto1.Tamanio()!=un_conjunto2.Tamanio())
    iguales=false;
  if(iguales){
    Celda *p;
    Celda *r;
    p=un_conjunto1.l;
    r=un_conjunto2.l;
    //Comprobar elemento a elemento
    while(p!=0 && r!=0 && iguales){
      //Si algun elemento es distinto, los conjuntos son distintos
      if(p->info!=r->info)
        iguales=false;
      else{
        p=p->sig;
        r=r->sig;
      }
    }
  }
  return iguales;
}

//Sobrecarga del operador != (perteneciente a la clase Conjunto)
bool operator!=(const Conjunto &un_conjunto1, const Conjunto &un_conjunto2){
  //Si son iguales, no son distintos
  if(un_conjunto1==un_conjunto2)
    return false;
  else
    return true;
}

//Sobrecarga del operador + (perteneciente a la clase Conjunto)
Conjunto operator+(const Conjunto &un_conjunto1, const Conjunto &un_conjunto2){
  Conjunto suma;
  //Añadir un_conjunto1
  Celda *p=un_conjunto1.l;
  while(p!=0){
    suma.Inserta(p->info);
    p=p->sig;
  }
  //Añiadir los elementos de un_conjunto2 que no estén ya
  Celda *r=un_conjunto2.l;
  while(r!=0){
    if(!suma.Buscar(r->info))
      suma.Inserta(r->info);
    r=r->sig;
  }
  return suma;
}

//Sobrecarga del operador - (perteneciente a la clase Conjunto)
Conjunto operator-(const Conjunto &un_conjunto1, const Conjunto &un_conjunto2){
  Conjunto resta;
  //Añadir un_conjunto1
  Celda *p=un_conjunto1.l;
  while(p!=0){
    resta.Inserta(p->info);
    p=p->sig;
  }
  //Eliminar los que estan en un_conjunto2
  Celda *r=un_conjunto2.l;
  while(r!=0){
    if(resta.Buscar(r->info))
      resta.BorrarElemento(r->info);
    r=r->sig;
  }
  return resta;
}

//Sobrecarga del operador * (perteneciente a la clase Conjunto)
Conjunto operator*(const Conjunto &un_conjunto1, const Conjunto &un_conjunto2){
  Conjunto interseccion;
  //Si son iguales, la interseccion es cualquiera de los dos
  if(un_conjunto1==un_conjunto2)
    interseccion=un_conjunto1;
  else{
    //Recorrer un_conjunto1 y busco si esta en un_conjunto2
    Celda *p=un_conjunto1.l;
    while(p!=0){
      if(un_conjunto2.Buscar(p->info))
        //Si esta, añadir a la interseccion
        interseccion.Inserta(p->info);
      p=p->sig;
    }
  }
  return interseccion;
}
