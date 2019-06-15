/* 
 * File:   css.hxx
 * Author: nestor
 *
 * Created on 29 de noviembre de 2015, 9:18
 */

#ifndef CSS_HXX
#define	CSS_HXX

#include "css.h"

bool OrdPQ::operator()(pair<ID, float> p1, pair<ID, float> p2) {
    return p1.second < p2.second;
}

CSS::CSS() {

}

CSS::CSS(const CSS & css) {
    (*this).DateAccess = css.DateAccess;
    (*this).IUCRAccess = css.IUCRAccess;
    (*this).baseDatos = css.baseDatos;
    (*this).index = css.index;
    (*this).posicionGeo = css.posicionGeo;
}

void CSS::load(string nombreDB) {
    ifstream fe;
    string cadena;
    long int contador = 0;

    cout << "Abrimos " << nombreDB << endl;
    fe.open(nombreDB.c_str(), ifstream::in);
    if (fe.fail()) {
        cerr << "Error al abrir el fichero " << nombreDB << endl;
    } else {
        //Leo la cabecera del fichero
        getline(fe, cadena, '\n');
        cout << cadena << endl;
        while (!fe.eof()) {
            getline(fe, cadena, '\n');
            if (!fe.eof()) {
                cout << contador << " leo: " << cadena << endl;
                Crimen aux(cadena);
                (*this).insert(aux);
                contador++;
            }
        }
        fe.close();
    }
    fe.close();
}

void CSS::insert(const Crimen& x) {

    (*this).baseDatos[x.getID()] = x;

    auto posicion = (*this).baseDatos.find(x.getID());
    pair<Date, map<ID, Crimen>::iterator> mi_par(x.getDate(), posicion);
    (*this).DateAccess.insert(mi_par);

    map<IUCR, set<ID> >::iterator it2 = (*this).IUCRAccess.find(x.getIUCR());
    if (it2 != (*this).IUCRAccess.end()) {
        it2->second.insert(x.getID());
    } else {
        set<ID> temp;
        temp.insert(x.getID());
        (*this).IUCRAccess.insert(make_pair(x.getIUCR(), temp));
    }

    //Dividir la descripcion en los términos separados por espacios y guardarlos
    //en un vector para luego ir procesándolos
    string description = x.getDescription();
    istringstream iss(description);
    vector<string> terminos{istream_iterator<string>
        {iss}, istream_iterator<string>
        {}};
    string actual;

    unordered_map<Termino, set<ID> >::iterator it3;
    for (int i = 0; i < terminos.size(); i++) {
        actual = terminos[i];
        it3 = (*this).index.find(actual);
        if (it3 != (*this).index.end()) {
            it3->second.insert(x.getID());
        } else {
            set<ID> temp2;
            temp2.insert(x.getID());
            (*this).index.insert(make_pair(actual, temp2));
        }
    }

    map<Longitud, multimap<Latitud, ID> >::iterator it4 = (*this).posicionGeo.find(x.getLongitude());
    if (it4 != (*this).posicionGeo.end()) {
        pair<Latitud, ID> mi_par2(x.getLatitude(), x.getID());
        it4->second.insert(mi_par2);
    } else {
        multimap<Latitud, ID> temp3;
        pair<Latitud, ID> mi_par3(x.getLatitude(), x.getID());
        temp3.insert(mi_par3);
        (*this).posicionGeo.insert(make_pair(x.getLongitude(), temp3));
    }

}

bool CSS::erase(unsigned int ID) {
    CSS::iterator it;
    bool encontrado = false;
    it.it = (*this).baseDatos.find(ID);
    if (it.it != (*this).baseDatos.end())
        encontrado = true;

    if (encontrado) {
        Date f = (it.it)->second.getDate();
        string iucr = (it.it)->second.getIUCR();
        string d = (it.it)->second.getDescription();
        double lat = (it.it)->second.getLatitude();
        double lon = (it.it)->second.getLongitude();

        bool borrado = false;

        multimap<Date, map<unsigned int, Crimen>::iterator>::iterator aux1 = (*this).DateAccess.begin();
        while (aux1 != (*this).DateAccess.end() && !borrado) {
            if (aux1->second == it.it) {
                (*this).DateAccess.erase(aux1);
                borrado = true;
            }
            aux1++;
        }

        map<IUCR, set<unsigned int>>::iterator it3 = (*this).IUCRAccess.find(iucr);
        it3->second.erase(ID);
        if (it3->second.size() == 0) {
            (*this).IUCRAccess.erase(it3);
        }

        //Dividir la descripcion en los términos separados por espacios y guardarlos
        //en un vector para luego ir procesándolos
        istringstream iss(d);
        vector<string> terminos{istream_iterator<string>
            {iss}, istream_iterator<string>
            {}};
        string actual;

        for (int i = 0; i < terminos.size(); i++) {
            actual = terminos[i];
            unordered_map<Termino, set < unsigned int>>::iterator it4 = (*this).index.find(actual);
            it4->second.erase(ID);
            if (it4->second.size() == 0) {
                (*this).index.erase(it4);
            }
        }

        borrado = false;
        map<Longitud, multimap<Latitud, unsigned int>>::iterator it5 = (*this).posicionGeo.find(lon);
        auto it6 = it5->second.lower_bound(lat);
        for (it6; it6 != it5->second.upper_bound(lat) && !borrado; it6++) {
            if (it6->second == ID) {
                it5->second.erase(it6);
                borrado = true;
                if (it5->second.size() == 0) {
                    (*this).posicionGeo.erase(it5);
                }
            }
        }

        (*this).baseDatos.erase(ID);

        return true;
    } else {
        return false;
    }
}

CSS::iterator CSS::find_ID(const unsigned int ID) {
    CSS::iterator it;
    it.it = (*this).baseDatos.find(ID);
    return it;
}

void CSS::setArrest(const unsigned int ID, bool value) {
    CSS::iterator it;
    it.it = (*this).baseDatos.find(ID);
    if (it.it != it.contenedor->baseDatos.end()) {
        (*it).second.setArrest(value);
    }
}

map<ID, float> CSS::unionPeso(const set<ID> & t1, const set<ID> &t2) {
    auto it = t1.begin();
    auto it2 = t2.begin();
    map<ID, float> salida;

    while (it != t1.end() && it2 != t2.end()) {
        if (*it == *it2) {
            salida[*it] = 2.0;
            it++;
            it2++;
        } else {
            if (*it<*it2) {
                salida[*it] = 1.0;
                it++;
            } else {
                salida[*it2] = 1.0;
                it2++;
            }
        }
    }

    if (it == t1.end()) {
        while (it2 != t2.end()) {
            salida[*it2] = 1.0;
            it2++;
        }
    } else {
        while (it != t1.end()) {
            salida[*it] = 1.0;
            it++;
        }
    }

    return salida;
}

void CSS::unionPeso(map<ID, float> & m, set<ID> & t_i) {
    set<ID>::iterator it;
    it = t_i.begin();
    while (it != t_i.end()) {
        m[*it]++;
        it++;
    }
}

vector<pair<ID, float>> CSS::Query(list<string> &q, int k) {
    vector <pair<ID, float>> salida;
    map<ID, float> mi_map;

    if (q.size() == 0) {
        return salida;
    } else {
        if (q.size() == 1) {
            auto it = (*this).index.find(*(q.begin()));
            for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                mi_map[*it2] = 1.0;
            }
        } else {
            list<string>::iterator it_string = q.begin();
            auto it = (*this).index.find(*it_string);
            it_string++;
            auto it2 = (*this).index.find(*it_string);
            it_string++;

            mi_map = (*this).unionPeso(it->second, it2->second);

            if (q.size() > 2) {
                while (it_string != q.end()) {
                    auto it3 = (*this).index.find(*it_string);
                    if (it3 != (*this).index.end())
                        (*this).unionPeso(mi_map, it3->second);
                    it_string++;
                }
            }
        }

        //Elegir los k mejores
        priority_queue<pair<ID, float>, deque<pair<ID, float>>, OrdPQ > pq;
        auto it_map = mi_map.begin();

        //Inserto los k primeros de mi map
        for (int insertados = 0; insertados < k && it_map != mi_map.end(); insertados++) {
            pq.push(*it_map);
            it_map++;
        }

        if (it_map != mi_map.end()) {
            for (int tamanio = k; tamanio < mi_map.size(); tamanio++) {
                if (it_map->second > pq.top().second) {
                    pq.pop();
                    pq.push(*it_map);
                }
                it_map++;
            }
        }

        while (pq.size() != 0) {
            salida.push_back(pq.top());
            pq.pop();
        }
    }

    return salida;
}

list<ID> CSS::inArea(Longitud x1, Latitud y1, Longitud x2, Latitud y2) {
    list<ID> salida;

    map<Longitud, multimap<Latitud, ID> >::iterator inicio, fin;
    multimap<Latitud, ID>::iterator inicio2, fin2;
    inicio = (*this).posicionGeo.lower_bound(x1);
    fin = (*this).posicionGeo.upper_bound(x2);

    for (inicio; inicio != fin; inicio++) {
        inicio2 = inicio->second.lower_bound(y1);
        fin2 = inicio->second.upper_bound(y2);
        for (inicio2; inicio2 != fin2; inicio2++) {
            salida.push_back(inicio2->second);
        }
    }

    return salida;
}

// =========================== ITERADORES ==============================================/

// =========================== ITERATOR ================================================/

CSS::iterator CSS::begin() {
    CSS::iterator salida;
    salida.it = (*this).baseDatos.begin();
    salida.contenedor = this;
    return salida;
}

CSS::iterator CSS::end() {
    CSS::iterator salida;
    salida.it = (*this).baseDatos.end();
    salida.contenedor = this;
    return salida;
}

CSS::iterator::iterator() {

}

CSS::iterator::iterator(const CSS::iterator & i) {
    (*this).it = i.it;
    (*this).contenedor = i.contenedor;
}

pair<const ID, Crimen > & CSS::iterator::operator*() {
    return *it;
}

CSS::iterator CSS::iterator::operator++(int) {
    CSS::iterator tmp(*this);
    ++(*this);
    return tmp;
}

CSS::iterator & CSS::iterator::operator++() {
    assert((*this).it != (*this).contenedor->baseDatos.end());
    (*this).it++;
    return (*this);
}

CSS::iterator CSS::iterator::operator--(int) {
    CSS::iterator tmp(*this);
    --(*this);
    return tmp;
}

CSS::iterator & CSS::iterator::operator--() {
    assert((*this).it != (*this).contenedor->baseDatos.begin());
    (*this).it--;
    return (*this);
}

bool CSS::iterator::operator==(const CSS::iterator & it) {
    return (*this).it == it.it;
}

bool CSS::iterator::operator!=(const CSS::iterator & it) {
    return (*this).it != it.it;
}

// =========================== IUCR_ITERATOR ===========================================/

CSS::IUCR_iterator CSS::ibegin() {
    CSS::IUCR_iterator salida;
    salida.it_m = (*this).IUCRAccess.begin();
    salida.it_s = (*this).IUCRAccess.begin()->second.begin();
    salida.contenedor = this;
    return salida;
}

CSS::IUCR_iterator CSS::iend() {
    CSS::IUCR_iterator salida;
    salida.it_m = (*this).IUCRAccess.end();
    salida.it_s = (--((*this).IUCRAccess.end()))->second.end();
    salida.contenedor = this;
    return salida;
}

CSS::IUCR_iterator CSS::lower_bound(IUCR i) {
    CSS::IUCR_iterator salida;
    salida = (*this).ibegin();

    map<IUCR, set<ID> >::iterator it;
    it = (*this).IUCRAccess.lower_bound(i);
    salida.it_m = it;
    salida.it_s = it->second.begin();
    salida.contenedor = this;

    return salida;
}

CSS::IUCR_iterator CSS::upper_bound(IUCR i) {
    CSS::IUCR_iterator salida;
    salida = (*this).ibegin();

    map<IUCR, set<ID> >::iterator it;
    it = (*this).IUCRAccess.upper_bound(i);
    salida.it_m = it;
    salida.it_s = it->second.begin();
    salida.contenedor = this;

    return salida;
}

CSS::IUCR_iterator::IUCR_iterator() {

}

CSS::IUCR_iterator::IUCR_iterator(const CSS::IUCR_iterator & it) {
    (*this).it_m = it.it_m;
    (*this).it_s = it.it_s;
    (*this).contenedor = it.contenedor;
}

pair<const ID, Crimen > & CSS::IUCR_iterator::operator*() {
    return *((*this).contenedor->baseDatos.find(*it_s));
}

CSS::IUCR_iterator CSS::IUCR_iterator::operator++(int) {
    CSS::IUCR_iterator tmp(*this);
    ++(*this);
    return tmp;
}

CSS::IUCR_iterator & CSS::IUCR_iterator::operator++() {
    assert((*this).it_m != (*this).contenedor->IUCRAccess.end() && (*this).it_s != (*this).contenedor->IUCRAccess.end()->second.end());
    if ((*this).it_s != (*this).it_m->second.end()) {
        (*this).it_s++;
    } else {
        (*this).it_m++;
        if ((*this).it_m != (*this).contenedor->IUCRAccess.end()) {
            (*this).it_s = (*this).it_m->second.begin();
        }
    }
    return (*this);
}

bool CSS::IUCR_iterator::operator==(const CSS::IUCR_iterator & it) {
    return ((*this).it_m == it.it_m && (*this).it_s == it.it_s);
}

bool CSS::IUCR_iterator::operator!=(const CSS::IUCR_iterator & it) {
    return ((*this).it_m != it.it_m || (*this).it_s != it.it_s);
}

// =========================== DATE_ITERATOR ===========================================/

CSS::Date_iterator CSS::dbegin() {
    CSS::Date_iterator salida;
    salida.it_mm = (*this).DateAccess.begin();
    salida.contenedor = this;
    return salida;
}

CSS::Date_iterator CSS::dend() {
    CSS::Date_iterator salida;
    salida.it_mm = (*this).DateAccess.end();
    salida.contenedor = this;
    return salida;

}

CSS::Date_iterator CSS::lower_bound(Date d) {
    CSS::Date_iterator salida;
    salida.it_mm = (*this).DateAccess.begin();
    salida.contenedor = this;

    multimap<Date, map<ID, Crimen>::iterator >::iterator it;
    it = (*this).DateAccess.lower_bound(d);
    salida.it_mm = it;
    salida.contenedor = this;
    return salida;
}

CSS::Date_iterator CSS::upper_bound(Date d) {
    CSS::Date_iterator salida;
    salida.it_mm = (*this).DateAccess.begin();
    salida.contenedor = this;

    multimap<Date, map<ID, Crimen>::iterator >::iterator it;
    it = (*this).DateAccess.upper_bound(d);
    salida.it_mm = it;
    salida.contenedor = this;
    return salida;
}

CSS::Date_iterator::Date_iterator() {

}

CSS::Date_iterator::Date_iterator(const CSS::Date_iterator & it) {
    (*this).it_mm = it.it_mm;
    (*this).contenedor = it.contenedor;
}

pair<const ID, Crimen > & CSS::Date_iterator::operator*() {
    return *(it_mm->second);
}

CSS::Date_iterator CSS::Date_iterator::operator++(int) {
    CSS::Date_iterator tmp(*this);
    ++(*this);
    return tmp;
}

CSS::Date_iterator & CSS::Date_iterator::operator++() {
    assert((*this).it_mm != (*this).contenedor->DateAccess.end());
    (*this).it_mm++;
    return (*this);
}

CSS::Date_iterator CSS::Date_iterator::operator--(int) {
    CSS::Date_iterator tmp(*this);
    --(*this);
    return tmp;
}

CSS::Date_iterator & CSS::Date_iterator::operator--() {
    assert((*this).it_mm != (*this).contenedor->DateAccess.begin());
    (*this).it_mm--;
    return (*this);
}

bool CSS::Date_iterator::operator==(const CSS::Date_iterator & it) {
    return (*this).it_mm == it.it_mm;
}

bool CSS::Date_iterator::operator!=(const CSS::Date_iterator & it) {
    return (*this).it_mm != it.it_mm;
}

ostream & operator<<(ostream & sal, const CSS & css) {
    sal << "Los crimenes de la base de datos son: " << endl;

    for (auto it = css.baseDatos.begin(); it != css.baseDatos.end(); it++) {
        cout << "El ID es: " << it->first << " y el crimen es: " << endl << it->second << endl;
    }

    return sal;
}

#endif	/* CSS_HXX */
