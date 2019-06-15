/* 
 * File:   css.h
 * Author: nestor
 *
 * Created on 29 de noviembre de 2015, 9:18
 */

#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <string>
#include <vector>
#include <queue>
#include <utility> //pair
#include <iterator> //dividir terminos
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <assert.h>
#include "date.h"
#include "crimen.h"

using namespace std;

#ifndef CSS_H
#define	CSS_H

typedef float Longitud;
typedef float Latitud;
typedef unsigned int ID;
typedef string Termino;
typedef string IUCR;

class CSS {
public:
    //Declaracion previa de los iteradores
    class iterator;
    class IUCR_iterator;
    class Date_iterator;

    /** @brief Constructor por defecto.*/
    CSS();
    /** @brief Constructor de copia.*/
    CSS(const CSS & css);
    /** @brief Se encarga de leer los elementos de un fichero dado por el argumento nombreDB,
    e insertar toda la información en la base de datos. Recordad que para esta práctica se os
    pide que extendáis el campo descripción a todas las descripciones que se encuentra en la
    base de datos. Pare ello será necesario modificar la clase crimen utilizada en la práctica
    anterior.*/
    void load(string nombreDB);
    /** @brief Este método se encarga de insertar un nuevo crimen en CSS. Como prerrequisito
    se asume que el crimen no está ya almacenado en el conjunto. */
    void insert(const Crimen & x);
    /** @brief En este caso, se trata de borrar un crimen de la base de datos dado su ID.
    Devuelve verdadero si el crimen ha sido borrado correctamente, falso en caso contrario.
    No sólo borra el crimen del repositorio principal de datos en CSS sino que además se 
    encarga de borrar toda referencia a dicho crimen dentro de él.*/
    bool erase(unsigned int ID);
    /** @brief Busca el crimen con identificador ID dentro de CSS, si no lo encuentra devuelve
    end()*/
    iterator find_ID(const unsigned int ID);
    /** @brief Modifica el campo arrest de un crimen identificado por ID. Será necesario cuando
    se detenga un criminal con posterioridad a la inserción del delito en CSS.*/
    void setArrest(const unsigned int ID, bool value);
    /** @brief Dada una consulta, expresada mediante un conjunto de términos en q, el sistema
    devuelve un vector ordenado con los k mejores ID (aquellos con mayor peso, definido como el
    número de términos de q que están en la descripción del delito), con sus respectivos pesos.
    Cómo implementar esta función se explica en la sección “Consulta Libre” de este documento.*/
    vector<pair<ID, float> > Query(list<string> & q, int k);
    /** @brief Dada dos coordenadas geográficas, x e y, donde se asume que x1 < x2 e y1 > y2, nos
    devuelve la lista de ID que representan delitos que han sido cometidos dentro del área geográfica
    delimitada por las coordenadas.*/
    list<ID> inArea(Longitud x1, Latitud y1, Longitud x2, Latitud y2);

    // =========================== ITERADORES ==============================================/

    // =========================== ITERATOR ================================================/

    /** @brief Devuelve el iterador correspondiente al primer delito que se encuentra según el criterio
    que sobre el que se itera.
     */
    iterator begin();
    /** @brief Devuelve el iterador que apunta al elemento siguiente al último delito en CSS según el
    criterio sobre el que se está itera.
     */
    iterator end();

    class iterator {
    public:
        /**@brief constructor por defecto
         */
        iterator();
        /**@brief constructor de copia
         */
        iterator(const iterator & it);
        /**@brief permite acceder al elemento apuntado por el iterador
        @return una referencia constante a un conjunto::entrada (un crimen)
         */
        pair<const ID, Crimen > & operator*();
        /**@brief Sobrecarga del operador ++ (postincremento)
         */
        iterator operator++(int);
        /**@brief Sobrecarga del operador ++ (preincremento)
         */
        iterator & operator++();
        /**@brief Sobrecarga del operador -- (postdecremento)
         */
        iterator operator--(int);
        /**@brief Sobrecarga del operador -- (predecremento)
         */
        iterator & operator--();
        /**@sobrecarda del operador ==
         */
        bool operator==(const iterator & it);
        /**@sobrecarda del operador !=
         */
        bool operator!=(const iterator & it);
    private:
        friend class CSS;
        /* @brief it  itera sobre los ID del map 
         */
        map<ID, Crimen>::iterator it;
        CSS *contenedor;
    };

    // =========================== IUCR_ITERATOR ===========================================/

    /** @brief Devuelve el iterador correspondiente al primer delito que se encuentra según el criterio
    que sobre el que se itera.
     */
    IUCR_iterator ibegin();
    /** @brief Devuelve el iterador que apunta al elemento siguiente al último delito en CSS según el
    criterio sobre el que se está itera.
     */
    IUCR_iterator iend();
    /** @brief Devuelve el iterador que apunta primer delito con IUCR mayor o igual a i
    @post no modifica el conjunto.
     */
    IUCR_iterator lower_bound(IUCR i);
    /** @brief Devuelve el primer delito con IUCR estrictamente mayor que i
    @post no modifica el conjunto.
     */
    IUCR_iterator upper_bound(IUCR i);

    class IUCR_iterator {
    public:
        /**@brief constructor por defecto
         */
        IUCR_iterator();
        /**@brief constructor de copia
         */
        IUCR_iterator(const IUCR_iterator & it);
        /**@brief permite acceder al elemento apuntado por el iterador
        @return una referencia constante a un conjunto::entrada (un crimen)
         */
        pair<const ID, Crimen > & operator*();
        /**@brief Sobrecarga del operador ++ (postincremento)
         */
        IUCR_iterator operator++(int);
        /**@brief Sobrecarga del operador ++ (preincremento)
         */
        IUCR_iterator & operator++();
        /**@sobrecarda del operador ==
         */
        bool operator==(const IUCR_iterator & it);
        /**@sobrecarda del operador !=
         */
        bool operator!=(const IUCR_iterator & it);
    private:
        friend class CSS;
        /* @brief it_m itera sobre los IUCR del map 
         */
        map<IUCR, set<ID> >::iterator it_m;
        /* @brief it_s itera sobre los ID del set 
         */
        set<ID>::iterator it_s;
        CSS *contenedor;
    };

    // =========================== DATE_ITERATOR ===========================================/

    /** @brief Devuelve el iterador correspondiente al primer delito que se encuentra según el criterio
    que sobre el que se itera.
     */
    Date_iterator dbegin();
    /** @brief Devuelve el iterador que apunta al elemento siguiente al último delito en CSS según el
    criterio sobre el que se está itera.
     */
    Date_iterator dend();
    /** @brief Devuelve el iterador que apunta primer delito con Date mayor o igual a d
    @post no modifica el conjunto.
     */
    Date_iterator lower_bound(Date d);
    /** @brief Devuelve el primer delito con Date estrictamente mayor que d
    @post no modifica el conjunto.
     */
    Date_iterator upper_bound(Date d);

    class Date_iterator {
    public:
        /**@brief constructor por defecto
         */
        Date_iterator();
        /**@brief constructor de copia
         */
        Date_iterator(const Date_iterator & it);
        /**@brief permite acceder al elemento apuntado por el iterador
        @return una referencia constante a un conjunto::entrada (un crimen)
         */
        pair<const ID, Crimen > & operator*();
        /**@brief Sobrecarga del operador ++ (postincremento)
         */
        Date_iterator operator++(int);
        /**@brief Sobrecarga del operador ++ (preincremento)
         */
        Date_iterator & operator++();
        /**@brief Sobrecarga del operador -- (postdecremento)
         */
        Date_iterator operator--(int);
        /**@brief Sobrecarga del operador -- (predecremento)
         */
        Date_iterator & operator--();
        /**@sobrecarda del operador ==
         */
        bool operator==(const Date_iterator & it);
        /**@sobrecarda del operador !=
         */
        bool operator!=(const Date_iterator & it);
    private:
        friend class CSS;
        multimap<Date, map<ID, Crimen>::iterator >::iterator it_mm;
        CSS *contenedor;
    };

private:
    /** @biref Los distintos delitos se almacenan por orden creciente de ID en un 
    diccionario (map), que llamaremos baseDatos, donde la clave será el ID (ya que
    asumimos que no hay dos delitos con el mismo valor de ID), y en la descripción
    tenemos almacenada toda la información relativa al Crimen. 
    Es importante destacar que la inserción y borrado de elementos en el map no invalida
    los iteradores. Esto nos facilitará las labores de implementación de los métodos.*/
    map<ID, Crimen> baseDatos;
    /** @brief Esta estructura se utilizará para permitir un acceso eficiente por
    Date. Como es importante la secuencia cronológica, consideraremos un contenedor
    asociativo. Además, como puede haber más de un Crimen en la misma Date hemos 
    seleccionado como estructura el multimap. En el campo definición solamente almacenamos 
    un iterador que apunta a la dirección del map donde se encuentra el elemento.
    Cuando un nuevo Crimen se inserta en baseDatos debemos de insertar la posición en la
    que se insertó en el multimap y en el caso de borrarlo de la base de datos, también
    debe ser borrado del multimap.*/
    multimap<Date, map<ID, Crimen>::iterator > DateAccess;
    /** Esta estructura se utiliza para facilitar el acceso por IUCR, en este caso para
    cada IUCR tenemos el conjunto de delitos, representados por su ID, que han sido clasificados
    mediante dicho código. Utilizamos un map por ser importante el orden de los delitos dentro
    del conjunto.
    Esta estructura se actualiza cada vez que se inserta o borra un nuevo delito.*/
    map<IUCR, set<ID> > IUCRAccess;
    /** @brief En este caso, para cada termino en la descripción de un delito almacenamos en
    un conjunto ordenado los IDs de los delitos que han sido descritos mediante dicho termino.
    Esta estructura se actualiza cada vez que se inserta o borra un nuevo delito.*/
    unordered_map<Termino, set<ID> > index;
    /** @brief En este caso la posición geográfica la almacenamos en una estructura ordenada
    donde la clave, que asumimos única, se corresponde con la longitud donde se produce el
    delito. En este caso, los delitos están ordenados en orden creciente por este valor de
    coordenada. Para cada una de ellas almacenamos las coordenadas de latitud donde se cometió
    el delito. Como para una misma coordenada x,y puede haber más de un delito en el tiempo,
    se considera una estructura de multimap.
    Esta estructura se actualiza cada vez que se inserta o borra un nuevo delito.*/
    map<Longitud, multimap<Latitud, ID> > posicionGeo;

    /** @brief Método auxiliar para la implementación del método Query.*/
    map<ID, float> unionPeso(const set<ID> & t1, const set<ID> &t2);
    /** @brief Método auxiliar para la implementación del método Query.*/
    void unionPeso(map<ID, float> & m, set<ID> & t_i);

    friend class iterator;
    friend class IUCR_iterator;
    friend class Date_iterator;

    /** @brief Sobrecarga del operador de extracción (solo muestra baseDatos).*/
    friend ostream & operator<<(ostream & sal, const CSS & css);
};

/** @brief Clase usada para el método Query. (Functor para la priority_queue)*/
class OrdPQ {
public:
    bool operator()(pair<ID, float> p1, pair<ID, float> p2);
};

#include "css.hxx"

#endif	/* CSS_H */