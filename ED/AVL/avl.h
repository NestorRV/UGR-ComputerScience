/* 
 * File:   avl.h
 * Author: nestor
 *
 * Created on 8 de enero de 2016, 11:54
 */

#ifndef AVL_H
#define	AVL_H

#include <functional>
#include <utility>
#include <iterator> //Distance - advance
#include "bintree.h"
#include <queue>
#include <stdlib.h> //abs

using namespace std;

typedef int altura;

template <typename T, class comparar = less<T> >
class AVL {
public:
    //Declaracion previa de los iteradores
    class iterator;
    class reverse_iterator;
    class const_iterator;
    class const_reverse_iterator;

    /** @brief Constructor por defecto*/
    AVL();
    /** @brief Constructor de copia*/
    AVL(const AVL &a);
    /** @brief Operador de asignacion*/
    AVL & operator=(const AVL<T, comparar> &a);

    /** @brief Método que nos devuelve si el AVL esta vacío o no
     @return Devuelve true si esta vacío, falso en caso contrario*/
    bool empty();
    /** @brief Método que devuelve el número de elementos del AVL*/
    int size();

    /** @brief Inserta x en el AVL y devuelve un par con un iterador y un bool.
     Si se ha insertado el bool vale true y el iterador apunta a dicho elemento*/
    pair<iterator, bool> insert(const T &x);
    /** @brief Elimina x del AVL y devuelve el número de elementos borrados.*/
    int erase(const T &x);
    /** @brief Intercambia los elementos de dos AVL*/
    void swap(AVL<T, comparar> &a);
    /** @brief Vacía el arbol*/
    void clear();

    /** @brief Método auxiliar para find*/
    bool encontrar(const T& val, typename bintree <pair<T, altura> >::node &n, typename bintree <pair<T, altura> >::node &n_padre) const;
    /** @brief Busca val en el AVL y devuelve un iterador a dicho elemento si se ha encontrado
     o al end si no se ha encontrado*/
    const_iterator find(const T& val) const;
    /** @brief Devuelve un iterador al primer elemento en el contenedor que no precede a x en el conjunto,
    esto es, es equivalente a x o le sigue según la relacion de orden definida por cmp. Esta función utiliza
    el functor interno devolviendo un iterador al primer elemento, e, para el que se satisface que comp(e,x) es falso.
     */
    const_iterator lower_bound(const T& val);
    /** @brief Devuelve un iterador al primer elemento que sigue a x según la relacion de orden definida por CMP.
    Esta función utiliza el functor interno devolviendo un iterador al primer elemento, e, para el que se satisface
    que comp(x,e) es cierto.
     */
    const_iterator upper_bound(const T& val);

    // =========================== ITERADORES ==============================================/

    // =========================== ITERATOR ================================================/

    /** @brief Devuelve el iterador correspondiente al primer elemento que se encuentra según el criterio
    que sobre el que se itera.
     */
    iterator begin();
    /** @brief Devuelve el iterador que apunta al elemento siguiente al último delito en el AVL según el
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
        @return una referencia constante a un elemento
         */
        T & operator*();
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
        /**@brief Sobrecarga del operador ==
         */
        bool operator==(const iterator & it);
        /**@brief Sobrecarga del operador !=
         */
        bool operator!=(const iterator & it);
    private:
        friend class AVL<T, comparar>;
        /* @brief it itera sobre el bintree 
         */
        typename bintree <pair<T, altura> >::inorder_iterator it;
    };

    // =========================== CONST_ITERATOR ==========================================/

    /** @brief Devuelve el iterador correspondiente al primer elemento que se encuentra según el criterio
    que sobre el que se itera.
     */
    const_iterator cbegin();
    /** @brief Devuelve el iterador que apunta al elemento siguiente al último delito en el AVL según el
    criterio sobre el que se está itera.
     */
    const_iterator cend() const;

    class const_iterator {
    public:
        /**@brief constructor por defecto
         */
        const_iterator();
        /**@brief constructor de copia
         */
        const_iterator(const const_iterator & it);
        /**@brief permite acceder al elemento apuntado por el iterador
        @return una referencia constante a un elemento
         */
        const T & operator*() const;
        /**@brief Sobrecarga del operador ++ (postincremento)
         */
        const_iterator operator++(int);
        /**@brief Sobrecarga del operador ++ (preincremento)
         */
        const_iterator & operator++();
        /**@brief Sobrecarga del operador -- (postdecremento)
         */
        const_iterator operator--(int);
        /**@brief Sobrecarga del operador -- (predecremento)
         */
        const_iterator & operator--();
        /**@brief Sobrecarga del operador ==
         */
        bool operator==(const const_iterator & it);
        /**@brief Sobrecarga del operador !=
         */
        bool operator!=(const const_iterator & it);
    private:
        friend class AVL<T, comparar>;
        /* @brief it itera sobre el bintree 
         */
        typename bintree <pair<T, altura> >::const_inorder_iterator it;
    };

    // =========================== REVERSE_ITERATOR =========================================/

    /** @brief Devuelve el iterador correspondiente al primer elemento que se encuentra según el criterio
    que sobre el que se itera.
     */
    reverse_iterator rbegin();
    /** @brief Devuelve el iterador que apunta al elemento siguiente al último delito en el AVL según el
    criterio sobre el que se está itera.
     */
    reverse_iterator rend();

    class reverse_iterator {
    public:
        /**@brief constructor por defecto
         */
        reverse_iterator();
        /**@brief constructor de copia
         */
        reverse_iterator(const reverse_iterator & it);
        /**@brief permite acceder al elemento apuntado por el iterador
        @return una referencia constante a un elemento
         */
        T & operator*();
        /**@brief Sobrecarga del operador ++ (postincremento)
         */
        reverse_iterator operator++(int);
        /**@brief Sobrecarga del operador ++ (preincremento)
         */
        reverse_iterator & operator++();
        /**@brief Sobrecarga del operador -- (postdecremento)
         */
        reverse_iterator operator--(int);
        /**@brief Sobrecarga del operador -- (predecremento)
         */
        reverse_iterator & operator--();
        /**@brief Sobrecarga del operador ==
         */
        bool operator==(const reverse_iterator & it);
        /**@brief Sobrecarga del operador !=
         */
        bool operator!=(const reverse_iterator & it);
    private:
        friend class AVL;
        /* @brief it itera sobre el bintree
         */
        typename bintree <pair<T, altura> >::inorder_iterator it;
    };

    // =========================== CONST_REVERSE_ITERATOR ===================================/

    /** @brief Devuelve el iterador correspondiente al primer elemento que se encuentra según el criterio
    que sobre el que se itera.
     */
    const_reverse_iterator crbegin();
    /** @brief Devuelve el iterador que apunta al elemento siguiente al último delito en el AVL según el
    criterio sobre el que se está itera.
     */
    const_reverse_iterator crend();

    class const_reverse_iterator {
    public:
        /**@brief constructor por defecto
         */
        const_reverse_iterator();
        /**@brief constructor de copia
         */
        const_reverse_iterator(const const_reverse_iterator & it);
        /**@brief permite acceder al elemento apuntado por el iterador
        @return una referencia constante a un elemento
         */
        const T & operator*() const;
        /**@brief Sobrecarga del operador ++ (postincremento)
         */
        const_reverse_iterator operator++(int);
        /**@brief Sobrecarga del operador ++ (preincremento)
         */
        const_reverse_iterator & operator++();
        /**@brief Sobrecarga del operador -- (postdecremento)
         */
        const_reverse_iterator operator--(int);
        /**@brief Sobrecarga del operador -- (predecremento)
         */
        const_reverse_iterator & operator--();
        /**@brief Sobrecarga del operador ==
         */
        bool operator==(const const_reverse_iterator & it);
        /**@brief Sobrecarga del operador !=
         */
        bool operator!=(const const_reverse_iterator & it);
    private:
        friend class AVL;
        /* @brief it itera sobre el bintree
         */
        typename bintree <pair<T, altura> >::const_inorder_iterator it;
    };

private:
    //Metodos privados
    altura h(typename bintree<pair<T, altura> >::node & n);
    altura h(typename bintree<pair<T, altura> >::const_node & n);
    //Representacion
    bintree <pair<T, altura> > el_avl;

    /** @brief Metodo auxiliar para erase*/
    bool Borrar(const T & x);
    /** @brief Método que actualiza la altura de un nodo, util en las rotaciones*/
    void ActAltura(typename bintree <pair<T, altura> >::node &n);
    /** @brief Rotacion Simple Derecha sobre n*/
    void SimpleDerecha(typename bintree <pair<T, altura> >::node &n);
    /** @brief Rotacion Simple Izquierda sobre n*/
    void SimpleIzquierda(typename bintree <pair<T, altura> >::node &n);
    /** @brief Rotacion Simple Derecha sobre n.right() y Rotacio Simple Izquierda sobre n*/
    void DobleDerechaIzquierda(typename bintree <pair<T, altura> >::node &n);
    /** @brief Rotacion Simple Izquierda sobre n.left() y Rotacio Simple Derecha sobre n*/
    void DobleIzquierdaDerecha(typename bintree <pair<T, altura> >::node &n);

    unsigned int tama;
    comparar cmp;

    friend class iterator;
    friend class reverse_iterator;
    friend class const_iterator;
    friend class const_reverse_iterator;
};

#include "avl.hxx"

#endif	/* AVL_H */
