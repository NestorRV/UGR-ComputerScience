#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "conjunto.h"
#include "cdconjuntos.h"
using namespace std;

//Constructor (perteneciente a la clase ConjuntoDeConjuntos)
ConjuntoDeConjuntos::ConjuntoDeConjuntos(){
  conjuntodeconjuntos=0;
  elementos=0;
}

//Contructor de copia (perteneciente a la clase ConjuntoDeConjuntos)
ConjuntoDeConjuntos::ConjuntoDeConjuntos(const ConjuntoDeConjuntos &otro_cdc){
  //Obtener el numero de elementos
  elementos=otro_cdc.elementos;
  //Reservar memoria
  conjuntodeconjuntos=new Conjunto [elementos];
  //Copiar conjunto a conjunto
  for(int i=0; i<elementos; i++)
    conjuntodeconjuntos[i]=otro_cdc.conjuntodeconjuntos[i];
}

//Metodo auxiliar para el destructor (perteneciente a la clase ConjuntoDeConjuntos)
void ConjuntoDeConjuntos::DestruirCDC(){
  //Destruir conjunto a conjunto
  for(int i=0; i<elementos; i++)
    (conjuntodeconjuntos[i]).Destruir();
  //Destruir el vector que almacena cada objeto Conjunto
  delete [] conjuntodeconjuntos;
  //Actualizar el numero de elementos
  elementos=0;
}

//Destructor (perteneciente a la clase ConjuntoDeConjuntos)
ConjuntoDeConjuntos::~ConjuntoDeConjuntos(){
  DestruirCDC();
}

//Consultar el tamanio del conjunto (perteneciente a la clase ConjuntoDeConjuntos)
int ConjuntoDeConjuntos::Tamanio() const{
  return elementos;
}

//Aniade conjunto a nuestro conjuntodeconjuntos
//(perteneciente a la clase ConjuntoDeConjuntos)
void ConjuntoDeConjuntos::Aniadir(const Conjunto &conjunto){
  //Reservo el espacio necesario
  Conjunto *aux=new Conjunto [elementos+1];
  //Copio los elementos ya existentes
  for(int i=0; i<elementos; i++)
    aux[i]=conjuntodeconjuntos[i];
  //Aniadir el nuevo elemento
  aux[elementos]=conjunto;
  //Destruir el conjuntodeconjuntos anterior
  for(int i=0; i<elementos; i++)
    (conjuntodeconjuntos[i]).Destruir();
  delete [] conjuntodeconjuntos;
  //Apuntar a la nueva zona de memoria
  conjuntodeconjuntos=aux;
  //Para evitar hacer uso de aux
  aux=0;
  //Actualizar el numero de elementos
  elementos=elementos+1;
}

//Borrar conjunto de nuestro conjuntodeconjuntos
//(perteneciente a la clase ConjuntoDeConjuntos)
void ConjuntoDeConjuntos::BorrarConjunto(int posicion){
  //if(posicion>0 && posicion<elementos){
    //Reservar memoria
    Conjunto *aux=new Conjunto [elementos-1];
    //Copiar conjunto a conjunto hasta llegar al que se desea eliminar
    for(int i=0; i<posicion; i++)
      aux[i]=conjuntodeconjuntos[i];
    //Seguir copiando desde el conjunto siguiente al que se desea eliminar
    for(int j=posicion+1; j<elementos; j++)
      aux[j-1]=conjuntodeconjuntos[j];
    //Destruir el conjuntodeconjuntos anterior
    for(int k=0; k<elementos; k++)
      (conjuntodeconjuntos[k]).Destruir();
    delete [] conjuntodeconjuntos;
    //Apuntar a la nueva zona de memoria
    conjuntodeconjuntos=aux;
    //Para evitar hacer uso de aux
    aux=0;
    //Actualizar el numero de elementos
    elementos=elementos-1;
  //}
}

//Metodo para obtener un conjunto de nuestro conjuntodeconjuntos
//perteneciente a la clase ConjuntoDeConjuntos)
Conjunto ConjuntoDeConjuntos::Get(int i) const{
    return conjuntodeconjuntos[i];
}

//Metodo que devuelve un conjunto formado por la interseccon de los
//conjuntos que forman conjuntodeconjuntos
//perteneciente a la clase ConjuntoDeConjuntos)
Conjunto ConjuntoDeConjuntos::Interseccion() const{
  //Asigno al conjunto interseccion el primer conjunto del conjuntodeconjuntos
  Conjunto interseccion=(*this).Get(0);
  //Interseccion (*) de lo que ya hay en interseccion con el resto de conjuntos
  //en conjunto de conjuntos uno a uno
  for (int i=1; i<(*this).Tamanio(); i++)
    interseccion=interseccion*((*this).Get(i));
  //Devolver el conjunto interseccion
  return interseccion;
}

//Metodo para calcular un numero aleatorio
int ConjuntoDeConjuntos::Aleatorio(int i) const{
  int aleatorio;
  time_t t;
  srand ((int) time(&t));
  aleatorio=(int)abs((1.0*(i+i)*rand()/(RAND_MAX+1.0)-i));
  return aleatorio;
}

//Metodo que devuelve el siguiente conjunto a aniadir
int ConjuntoDeConjuntos::ConjuntoAniadir(ConjuntoDeConjuntos &solucion) const{
  int elegido, v_elementos=0, cardinal_auxiliar=0, cardinal_maximo=0;
  int tamanio=(*this).Tamanio();
  //Vector para almacenar los conjuntos de igual cardinal
  int *v=new int [tamanio];
  for(int i=0; i<(*this).elementos; i++){
    //Si no he añadido ninguno todavía:
    if(solucion.Tamanio()==0)
      //solo me interesa el cardinal del propio conjunto
      cardinal_auxiliar=(conjuntodeconjuntos[i]).Tamanio();
    //Si ya he añadido alguno:
    else
      //me interesa el cardinal de la interseccion del conjunto con los conjuntos
      //de la solucion
      cardinal_auxiliar=(conjuntodeconjuntos[i]*solucion.Interseccion()).Tamanio();
    if(cardinal_auxiliar>=cardinal_maximo){
      //Si el cardinal es mayor que los que tengo, borro el vector
      //que usaba para almacenar los conjuntos de igual cardinal y añado
      //el conjunto seleccionado
      if(cardinal_auxiliar>cardinal_maximo){
        cardinal_maximo=cardinal_auxiliar;
        delete [] v;
        v=new int [tamanio];
        v_elementos=0;
        v[v_elementos]=i;
        v_elementos++;
      }
      //Si el cardinal es igual a los que ya tengo, añado la poscion del
      //conojunto con dicho cardinal al vector para luego seleccionar uno
      //aleatoriamente
      else{
        v[v_elementos]=i;
        v_elementos++;
      }
    }
  }
  //Selecciono el conjunto definitivo a añadir de forma aleatoria entre los
  //que he seleccionado anteriormente
  int num;
  num=Aleatorio(v_elementos);
  elegido=v[num];
  delete [] v;
  //Devuelvo el conjunto a añadir en la solucion
  return elegido;
}

//Metodo para editar la solucion y el conjunto original
void ConjuntoDeConjuntos::Editar(ConjuntoDeConjuntos &solucion){
  int elegido=ConjuntoAniadir(solucion);
  solucion.Aniadir((*this).Get(elegido));
  (*this).BorrarConjunto(elegido);
}

//Metodo para resolver nuestro problema (perteneciente a la clase ConjuntoDeConjuntos)
ConjuntoDeConjuntos ConjuntoDeConjuntos::Solucion(int k){
    ConjuntoDeConjuntos solucion;
    int cardinal_c=(*this).Tamanio();
    //Si no queremos ningun conjunto (k=0), aniadir un conjunto vacio
    if(k==0){
      Conjunto auxiliar;
      solucion.Aniadir(auxiliar);
    }
    //Si k!=0, aniadir el conjunto de mayor cardinal
    else{
      Editar(solucion);
      //Si k>1, aniadir el resto de conjuntos conforme a los requisitos del problema
      if(k>1)
        //Mientras no se han aniadido suficientes (solucion.Tamanio()<k) y mientas
        //no hemos aniadido todos los conjuntos de c (solucion.Tamanio()<cardinal_c)
        while(solucion.Tamanio()<k && solucion.Tamanio()<cardinal_c)
          Editar(solucion);
    }
    return solucion;
}

//Sobrecarga del operador de asignacion (perteneciente a la clase ConjuntoDeConjuntos)
const ConjuntoDeConjuntos& ConjuntoDeConjuntos::operator=(const ConjuntoDeConjuntos& otro_cdc){
  if(this!=&otro_cdc){
    if((*this).elementos!=0)
      (*this).~ConjuntoDeConjuntos();
    elementos=otro_cdc.elementos;
    conjuntodeconjuntos=new Conjunto [elementos];
    for(int i=0; i<elementos; i++)
      conjuntodeconjuntos[i]=otro_cdc.conjuntodeconjuntos[i];
  }
  return *this;
}

//Sobrecarga del operador << (perteneciente a la clase ConjuntoDeConjuntos)
ostream& operator<<(ostream &os, const ConjuntoDeConjuntos &otro_cdc){
  for (int i=0; i<otro_cdc.elementos; i++){
    os << otro_cdc.conjuntodeconjuntos[i] << endl;
  }
  return os;
}
