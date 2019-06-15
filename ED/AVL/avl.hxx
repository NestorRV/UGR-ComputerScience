/* 
 * File:   avl.hxx
 * Author: nestor
 *
 * Created on 8 de enero de 2016, 12:56
 */

#ifndef AVL_HXX
#define	AVL_HXX

#include "avl.h"

template <typename T, class comparar>
AVL<T, comparar>::AVL() {
    tama = 0;
}

template <typename T, class comparar>
AVL<T, comparar>::AVL(const AVL &a) {
    el_avl = a.el_avl;
    tama = a.tama;
    cmp = a.cmp;
}

template <typename T, class comparar>
AVL<T, comparar> & AVL<T, comparar>::operator=(const AVL<T, comparar> &a) {
    if (this != &a) {
        el_avl = a.el_avl;
        tama = a.tama;
        cmp = a.cmp;
    }
    return *this;
}

template <typename T, class comparar>
bool AVL<T, comparar>::empty() {
    return tama == 0;
}

template <typename T, class comparar>
int AVL<T, comparar>::size() {
    return tama;
}

template <typename T, class comparar>
altura AVL<T, comparar>::h(typename bintree<pair<T, altura> >::node & n) {
    if (n.null()) {
        return -1;
    }
    if (n.left().null() && n.right().null()) {
        return 0;
    } else if (n.left().null()) {
        typename bintree<pair<T, altura> >::node aux(n.right());
        return 1 + h(aux);
    } else if (n.right().null()) {
        typename bintree<pair<T, altura> >::node aux(n.left());
        return 1 + h(aux);
    } else {
        typename bintree<pair<T, altura> >::node aux(n.right());
        typename bintree<pair<T, altura> >::node aux2(n.left());
        return 1 + std::max(h(aux), h(aux2));
    }
}

template <typename T, class comparar>
altura AVL<T, comparar>::h(typename bintree<pair<T, altura> >::const_node & n) {
    if (n.null()) {
        return -1;
    }
    if (n.left().null() && n.right().null()) {
        return 0;
    } else if (n.left().null()) {
        typename bintree<pair<T, altura> >::node aux(n.right());
        return 1 + h(aux);
    } else if (n.right().null()) {
        typename bintree<pair<T, altura> >::node aux(n.left());
        return 1 + h(aux);
    } else {
        typename bintree<pair<T, altura> >::node aux(n.right());
        typename bintree<pair<T, altura> >::node aux2(n.left());
        return 1 + std::max(h(aux), h(aux2));
    }
}

template <typename T, class comparar>
void AVL<T, comparar>::ActAltura(typename bintree <pair<T, altura> >::node &n) {
    typename bintree<pair<T, altura> >::node aux, aux2;
    aux = n.right();
    aux2 = n.left();
    (*n).second = std::max(h(aux), h(aux2)) + 1;
}

template <typename T, class comparar>
void AVL<T, comparar>::SimpleDerecha(typename bintree <pair<T, altura> >::node &n) {
    typename bintree <pair<T, altura> >::node izquierda = n.left();
    typename bintree <pair<T, altura> >::node izquierdaDerecha = izquierda.right();
    typename bintree <pair<T, altura> >::node padre = n.parent();

    izquierda.parent(padre);
    izquierda.right(n);
    n.left(izquierdaDerecha);
    n.parent(izquierda);

    if (!izquierdaDerecha.null()) {
        izquierdaDerecha.parent(n);
    }

    if (n == el_avl.root()) {
        el_avl.setRoot(izquierda);
    } else if (padre.left() == n) {
        padre.left(izquierda);
    } else {
        padre.right(izquierda);
    }

    ActAltura(izquierda);
    ActAltura(n);
}

template <typename T, class comparar>
void AVL<T, comparar>::SimpleIzquierda(typename bintree <pair<T, altura> >::node &n) {
    typename bintree <pair<T, altura> >::node derecha = n.right();
    typename bintree <pair<T, altura> >::node derechaIzquierda = derecha.left();
    typename bintree <pair<T, altura> >::node padre = n.parent();

    derecha.parent(padre);
    derecha.left(n);
    n.right(derechaIzquierda);
    n.parent(derecha);

    if (!derechaIzquierda.null()) {
        derechaIzquierda.parent(n);
    }

    if (n == el_avl.root()) {
        el_avl.setRoot(derecha);
    } else if (padre.right() == n) {
        padre.right(derecha);
    } else {
        padre.left(derecha);
    }

    ActAltura(derecha);
    ActAltura(n);
}

template <typename T, class comparar>
void AVL<T, comparar>::DobleDerechaIzquierda(typename bintree <pair<T, altura> >::node &n) {
    typename bintree <pair<T, altura> >::node aux(n.right());
    SimpleDerecha(aux);
    SimpleIzquierda(n);
}

template <typename T, class comparar>
void AVL<T, comparar>::DobleIzquierdaDerecha(typename bintree <pair<T, altura> >::node &n) {
    typename bintree <pair<T, altura> >::node aux(n.left());
    SimpleIzquierda(aux);
    SimpleDerecha(n);
}

template <typename T, class comparar>
pair<typename AVL<T, comparar>::iterator, bool> AVL<T, comparar>::insert(const T &x) {
    typename AVL<T, comparar>::iterator iter;
    pair<typename AVL<T, comparar>::iterator, bool> salida;

    typename bintree<pair<T, altura> >::node nodo, nodo_padre;
    bool encontrado = (*this).encontrar(x, nodo, nodo_padre);

    if (!encontrado) {
        if (el_avl.root().null()) {
            pair <T, altura> auxiliar(x, 0);
            bintree <pair<T, altura> > inicio(auxiliar);
            el_avl = inicio;
            tama++;

            typename bintree <pair<T, altura> >::inorder_iterator it(el_avl.root());
            iter.it = it;
            salida.first = iter;
            salida.second = true;
        } else {
            if (cmp(x, (*nodo_padre).first)) {
                el_avl.insert_left(nodo_padre, pair<T, altura>(x, 0));
            } else {
                el_avl.insert_right(nodo_padre, pair<T, altura>(x, 0));
            }
            tama++;

            // Ya esta insertado, ahora debo subir hasta que no haga falta
            // hacer rotaciones

            //En nodo_padre esta el padre del recien insertado

            typename bintree<pair<T, altura> >::node aux, aux2, aux3, aux4, actual;
            actual = nodo_padre;
            while (!actual.null()) {
                if (cmp(x, (*actual).first)) { // En el subarbol izquierdo
                    aux = nodo_padre.left();
                    aux2 = nodo_padre.right();
                    // Hay que hacer rotaciones
                    if ((h(aux) - h(aux2)) == 2) {
                        aux3 = nodo_padre.left().left();
                        aux4 = nodo_padre.left().right();
                        if (h(aux3) > h(aux4)) {
                            SimpleDerecha(nodo_padre);
                        } else {
                            DobleIzquierdaDerecha(nodo_padre);
                        }
                    }

                } else { // En el subarbol derecho
                    aux = nodo_padre.left();
                    aux2 = nodo_padre.right();
                    // Hay que hacer rotaciones
                    if ((h(aux) - h(aux2)) == -2) {
                        aux3 = nodo_padre.right().right();
                        aux4 = nodo_padre.right().left();
                        if (h(aux3) > h(aux4)) {
                            SimpleIzquierda(nodo_padre);
                        } else {
                            DobleDerechaIzquierda(nodo_padre);
                        }
                    }
                }
                // Actualizamos las alturas
                ActAltura(nodo_padre);
                actual = actual.parent();
                nodo_padre = actual;
            }

            // Una vez hechas las rotaciones, vemos donde ha quedado el nodo
            encontrar(x, nodo, nodo_padre);
            if (cmp(x, (*nodo_padre).first)) {
                typename bintree <pair<T, altura> >::inorder_iterator it(nodo_padre.left());
                iter.it = it;

            } else {
                typename bintree <pair<T, altura> >::inorder_iterator it(nodo_padre.right());
                iter.it = it;
            }
            salida.first = iter;
            salida.second = true;
        }
    } else {
        salida.first = end();
        salida.second = false;
    }

    return salida;
}

template <typename T, class comparar>
bool AVL<T, comparar>::Borrar(const T & x) {
    typename bintree<pair<T, altura> >::node nodo, nodo_padre;
    bintree<pair<T, altura> > Taux;
    bool encontrado = encontrar(x, nodo, nodo_padre);

    if (encontrado) {
        if (nodo.left().null() && nodo.right().null()) {
            if (nodo_padre.null())
                el_avl.clear();
            else {
                if (nodo_padre.left() == nodo) {
                    el_avl.prune_left(nodo_padre, Taux);
                } else {
                    el_avl.prune_right(nodo_padre, Taux);
                }
                Taux.clear();
            }

        } else if (nodo.left().null() || nodo.right().null()) {
            if (!nodo.left().null()) {
                el_avl.prune_left(nodo, Taux);
            } else {
                el_avl.prune_right(nodo, Taux);
            }
            if (nodo_padre.null())
                el_avl = Taux;
            else if (nodo_padre.left() == nodo) {
                el_avl.insert_left(nodo_padre, Taux);
            } else {
                el_avl.insert_right(nodo_padre, Taux);
            }
        } else {
            typename bintree<pair<T, altura> >::node pred;
            pred = nodo.left();
            while (!pred.right().null())
                pred = pred.right();

            pair<T, altura> valor_pred(*pred);
            typename bintree<pair<T, altura> >::node nodo_a_borrar = nodo;
            Borrar((*pred).first);
            *nodo_a_borrar = valor_pred;
        }
        return true;
    } else {
        return false;
    }
}

// NO EMPEZAR EN EL PADRE; SINO UNO MAS ABAJO

template <typename T, class comparar>
int AVL<T, comparar>::erase(const T & x) {
    if (!el_avl.root().null()) {
        typename bintree<pair<T, altura> >::node nodo, nodo_padre;
        bintree<pair<T, altura> > Taux;
        bool encontrado = encontrar(x, nodo, nodo_padre);

        bool borrado = Borrar(x);
        if (borrado) {
            typename bintree<pair<T, altura> >::node aux, aux2, aux3, aux4, actual, inicio;
            // Bajo hasta el hijo más abajo para subir y realizar el balanceo
            while (!nodo_padre.null()) {
                inicio = nodo_padre;
                if (cmp(x, (*nodo_padre).first))
                    nodo_padre = nodo_padre.left();
                else if (cmp((*nodo_padre).first, x))
                    nodo_padre = nodo_padre.right();
            }

            actual = inicio;
            nodo_padre = inicio;
            while (!actual.null()) {
                if (cmp(x, (*actual).first)) { // En el subarbol izquierdo
                    aux = nodo_padre.left();
                    aux2 = nodo_padre.right();
                    if ((h(aux) - h(aux2)) == 2) {
                        aux3 = nodo_padre.left().left();
                        aux4 = nodo_padre.left().right();
                        if (h(aux3) > h(aux4)) {
                            SimpleDerecha(nodo_padre);
                        } else {
                            DobleIzquierdaDerecha(nodo_padre);
                        }
                        break;
                    }
                } else { // En el subarbol derecho
                    aux = nodo_padre.left();
                    aux2 = nodo_padre.right();
                    if ((h(aux) - h(aux2)) == -2) {
                        aux3 = nodo_padre.right().right();
                        aux4 = nodo_padre.right().left();
                        if (h(aux3) > h(aux4)) {
                            SimpleIzquierda(nodo_padre);
                        } else {
                            DobleDerechaIzquierda(nodo_padre);
                        }
                        break;
                    }
                }
                ActAltura(nodo_padre);
                actual = actual.parent();
                nodo_padre = actual;
            }
            return 1;
        } else
            return 0;
    }
    return 0;
}

template <typename T, class comparar>
void AVL<T, comparar>::swap(AVL<T, comparar> &a) {
    std::swap((*this), a);
}

template <typename T, class comparar>
void AVL<T, comparar>::clear() {
    el_avl.clear();
    tama = 0;
}

template <typename T, class comparar>
bool AVL<T, comparar>::encontrar(const T& val, typename bintree <pair<T, altura> >::node &n, typename bintree <pair<T, altura> >::node & n_padre) const {
    bool encontrado = false;
    n = (*this).el_avl.root();
    n_padre = n;
    while (!n.null() && !encontrado) {
        if (!cmp((*n).first, val) && !cmp(val, (*n).first)) {
            encontrado = true;
        } else {
            n_padre = n;
            if (cmp(val, (*n).first)) {
                n = n.left();
            } else {
                n = n.right();
            }
        }
    }
    return encontrado;
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_iterator AVL<T, comparar>::find(const T & val) const {
    typename bintree <pair<T, altura> >::node nodo, nodo_padre;
    typename AVL<T, comparar>::const_iterator salida;
    bool enc = (*this).encontrar(val, nodo, nodo_padre);
    if (enc == true) {
        int valor = (*nodo_padre).first;
        if (!cmp(val, valor) && !cmp(valor, val)) {
            typename bintree <pair<T, altura> >::const_inorder_iterator it(nodo_padre);
            salida.it = it;
            return salida;
        } else if (cmp(val, (*nodo_padre).first)) {
            typename bintree <pair<T, altura> >::const_inorder_iterator it(nodo_padre.left());
            salida.it = it;
        } else {
            typename bintree <pair<T, altura> >::const_inorder_iterator it(nodo_padre.right());
            salida.it = it;
        }
        return salida;
    } else {
        salida.it = el_avl.end_inorder();
        return salida;
    }
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_iterator AVL<T, comparar>::lower_bound(const T & val) {
    typename AVL<T, comparar>::const_iterator salida;
    typename bintree <pair<T, altura> >::node n, n_padre;
    bool encontrado = false;

    n = el_avl.root();
    n_padre = n;
    while (!n.null() && !encontrado) {
        if (!cmp((*n).first, val) && !cmp(val, (*n).first)) {
            encontrado = true;
        } else {
            n_padre = n;
            if (cmp(val, (*n).first)) {
                n = n.left();
            } else {
                n = n.right();
            }
        }
    }

    // Si lo encuentro
    if (encontrado) {
        int valor = (*n_padre).first;
        // Y  es la raiz
        if (!cmp(val, valor) && !cmp(valor, val)) {
            // Devuelvo n_padre, que está en la raiz
            typename bintree <pair<T, altura> >::const_inorder_iterator it(n_padre);
            salida.it = it;
            return salida;
        } else if (cmp(val, (*n_padre).first)) {
            // Si es menor/mayor que el n_padre, devuelvo el de la izquierda
            typename bintree <pair<T, altura> >::const_inorder_iterator it(n_padre.left());
            salida.it = it;
            return salida;
        } else {
            // Si es mayor/menor que el n_padre, devuelvo el de la derecha
            typename bintree <pair<T, altura> >::const_inorder_iterator it(n_padre.right());
            salida.it = it;
            return salida;
        }
    } else {
        typename bintree <pair<T, altura> >::const_inorder_iterator it(n_padre);
        if (cmp(val, (*n_padre).first)) {
            salida.it = it;
            return salida;
        } else {
            it++;
            salida.it = it;
            return salida;
        }
    }
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_iterator AVL<T, comparar>::upper_bound(const T & val) {
    typename AVL<T, comparar>::const_iterator salida;
    typename bintree <pair<T, altura> >::node n, n_padre;
    bool encontrado = false;

    n = el_avl.root();
    n_padre = n;
    while (!n.null() && !encontrado) {
        if (!cmp((*n).first, val) && !cmp(val, (*n).first)) {
            encontrado = true;
        } else {
            n_padre = n;
            if (cmp(val, (*n).first)) {
                n = n.left();
            } else {
                n = n.right();
            }
        }
    }

    if (!encontrado) {
        typename bintree <pair<T, altura> >::const_inorder_iterator it(n_padre);
        if (cmp(val, (*n_padre).first)) {
            salida.it = it;
            return salida;
        } else {
            it++;
            salida.it = it;
            return salida;
        }
    } else {
        typename bintree <pair<T, altura> >::const_inorder_iterator it2(n);
        it2++;
        salida.it = it2;
        return salida;
    }
}

// =========================== ITERADORES ==============================================/

// =========================== ITERATOR ================================================/

template <typename T, class comparar>
typename AVL<T, comparar>::iterator AVL<T, comparar>::begin() {
    typename AVL<T, comparar>::iterator salida;
    salida.it = el_avl.begin_inorder();
    return salida;
}

template <typename T, class comparar>
typename AVL<T, comparar>::iterator AVL<T, comparar>::end() {
    typename AVL<T, comparar>::iterator salida;
    salida.it = el_avl.end_inorder();
    return salida;
}

template <typename T, class comparar >
AVL<T, comparar>::iterator::iterator() {

}

template <typename T, class comparar >
AVL<T, comparar>::iterator::iterator(const AVL<T, comparar>::iterator & it) {
    (*this).it = it.it;
}

template <typename T, class comparar >
T & AVL<T, comparar>::iterator::operator*() {
    return (*it).first;
}

template <typename T, class comparar>
typename AVL<T, comparar>::iterator AVL<T, comparar>::iterator::operator++(int) {
    AVL<T, comparar>::iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T, class comparar>
typename AVL<T, comparar>::iterator & AVL<T, comparar>::iterator::operator++() {
    (*this).it++;
    return (*this);
}

template <typename T, class comparar>
typename AVL<T, comparar>::iterator AVL<T, comparar>::iterator::operator--(int) {
    AVL<T, comparar>::iterator tmp(*this);
    --(*this);
    return tmp;
}

template <typename T, class comparar>
typename AVL<T, comparar>::iterator & AVL<T, comparar>::iterator::operator--() {
    (*this).it--;
    return (*this);
}

template <typename T, class comparar>
bool AVL<T, comparar>::iterator::operator==(const AVL<T, comparar>::iterator & it) {
    return (*this).it == it.it;
}

template <typename T, class comparar>
bool AVL<T, comparar>::iterator::operator!=(const AVL<T, comparar>::iterator & it) {
    return (*this).it != it.it;
}

// =========================== CONST_ITERATOR ==========================================/

template <typename T, class comparar>
typename AVL<T, comparar>::const_iterator AVL<T, comparar>::cbegin() {
    typename AVL<T, comparar>::const_iterator salida;
    salida.it = el_avl.begin_inorder();
    return salida;
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_iterator AVL<T, comparar>::cend() const {
    typename AVL<T, comparar>::const_iterator salida;
    salida.it = el_avl.end_inorder();
    return salida;
}

template <typename T, class comparar >
AVL<T, comparar>::const_iterator::const_iterator() {

}

template <typename T, class comparar >
AVL<T, comparar>::const_iterator::const_iterator(const AVL<T, comparar>::const_iterator & it) {
    (*this).it = it.it;
}

template <typename T, class comparar>
const T & AVL<T, comparar>::const_iterator::operator*() const {
    return (*it).first;
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_iterator AVL<T, comparar>::const_iterator::operator++(int) {
    AVL<T, comparar>::const_iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_iterator & AVL<T, comparar>::const_iterator::operator++() {
    (*this).it++;
    return (*this);
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_iterator AVL<T, comparar>::const_iterator::operator--(int) {
    AVL<T, comparar>::const_iterator tmp(*this);
    --(*this);
    return tmp;
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_iterator & AVL<T, comparar>::const_iterator::operator--() {
    (*this).it--;
    return (*this);
}

template <typename T, class comparar>
bool AVL<T, comparar>::const_iterator::operator==(const AVL<T, comparar>::const_iterator & it) {
    return (*this).it == it.it;
}

template <typename T, class comparar>
bool AVL<T, comparar>::const_iterator::operator!=(const AVL<T, comparar>::const_iterator & it) {
    return (*this).it != it.it;
}

// =========================== REVERSE_ITERATOR =========================================/

template <typename T, class comparar>
typename AVL<T, comparar>::reverse_iterator AVL<T, comparar>::rbegin() {
    typename AVL<T, comparar>::reverse_iterator salida;
    typename bintree<pair<T, altura> >::node nodo, nodo_padre;
    nodo = el_avl.root();
    nodo_padre = nodo;
    while (!nodo.null()) {
        nodo_padre = nodo;
        nodo = nodo.right();
    }
    typename bintree<pair<T, altura> >::inorder_iterator it(nodo_padre);
    salida.it = it;
    return salida;
}

template <typename T, class comparar>
typename AVL<T, comparar>::reverse_iterator AVL<T, comparar>::rend() {
    typename AVL<T, comparar>::reverse_iterator salida;
    return salida;
}

template <typename T, class comparar >
AVL<T, comparar>::reverse_iterator::reverse_iterator() {

}

template <typename T, class comparar >
AVL<T, comparar>::reverse_iterator::reverse_iterator(const AVL<T, comparar>::reverse_iterator & it) {
    (*this).it = it.it;
}

template <typename T, class comparar >
T & AVL<T, comparar>::reverse_iterator::operator*() {
    return *it;
}

template <typename T, class comparar>
typename AVL<T, comparar>::reverse_iterator AVL<T, comparar>::reverse_iterator::operator++(int) {
    AVL<T, comparar>::reverse_iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T, class comparar>
typename AVL<T, comparar>::reverse_iterator & AVL<T, comparar>::reverse_iterator::operator++() {
    (*this).it--;
    return (*this);
}

template <typename T, class comparar>
typename AVL<T, comparar>::reverse_iterator AVL<T, comparar>::reverse_iterator::operator--(int) {
    AVL<T, comparar>::reverse_iterator tmp(*this);
    --(*this);
    return tmp;
}

template <typename T, class comparar>
typename AVL<T, comparar>::reverse_iterator & AVL<T, comparar>::reverse_iterator::operator--() {
    (*this).it++;
    return (*this);
}

template <typename T, class comparar>
bool AVL<T, comparar>::reverse_iterator::operator==(const AVL<T, comparar>::reverse_iterator & it) {
    return (*this).it == it.it;
}

template <typename T, class comparar>
bool AVL<T, comparar>::reverse_iterator::operator!=(const AVL<T, comparar>::reverse_iterator & it) {
    return (*this).it != it.it;
}

// =========================== CONST_REVERSE_ITERATOR ===================================/

template <typename T, class comparar>
typename AVL<T, comparar>::const_reverse_iterator AVL<T, comparar>::crbegin() {
    typename AVL<T, comparar>::const_reverse_iterator salida;
    typename bintree<pair<T, altura> >::node nodo, nodo_padre;
    nodo = el_avl.root();
    nodo_padre = nodo;
    while (!nodo.null()) {
        nodo_padre = nodo;
        nodo = nodo.right();
    }
    typename bintree<pair<T, altura> >::inorder_iterator it(nodo_padre);
    salida.it = it;
    return salida;
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_reverse_iterator AVL<T, comparar>::crend() {
    typename AVL<T, comparar>::const_reverse_iterator salida;
    return salida;
}

template <typename T, class comparar >
AVL<T, comparar>::const_reverse_iterator::const_reverse_iterator() {

}

template <typename T, class comparar >
AVL<T, comparar>::const_reverse_iterator::const_reverse_iterator(const AVL<T, comparar>::const_reverse_iterator & it) {
    (*this).it = it.it;
}

template <typename T, class comparar >
const T & AVL<T, comparar>::const_reverse_iterator::operator*() const {
    return *it;
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_reverse_iterator AVL<T, comparar>::const_reverse_iterator::operator++(int) {
    AVL<T, comparar>::const_reverse_iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_reverse_iterator & AVL<T, comparar>::const_reverse_iterator::operator++() {
    (*this).it--;
    return (*this);
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_reverse_iterator AVL<T, comparar>::const_reverse_iterator::operator--(int) {
    AVL<T, comparar>::const_reverse_iterator tmp(*this);
    --(*this);
    return tmp;
}

template <typename T, class comparar>
typename AVL<T, comparar>::const_reverse_iterator & AVL<T, comparar>::const_reverse_iterator::operator--() {
    (*this).it++;
    return (*this);
}

template <typename T, class comparar>
bool AVL<T, comparar>::const_reverse_iterator::operator==(const AVL<T, comparar>::const_reverse_iterator & it) {
    return (*this).it == it.it;
}

template <typename T, class comparar>
bool AVL<T, comparar>::const_reverse_iterator::operator!=(const AVL<T, comparar>::const_reverse_iterator & it) {
    return (*this).it != it.it;
}

#endif	/* AVL_HXX */