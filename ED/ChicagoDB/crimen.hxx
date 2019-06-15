/* 
 * File:   Crimen.hxx
 * Author: nestor
 *
 * Created on 29 de noviembre de 2015, 9:14
 */

/** @brief fichero de implementacion de la clase Crimen.hxx
 */

#ifndef CRIMEN_HXX
#define	CRIMEN_HXX

Crimen::Crimen() {
    ID = 0;
    case_number = "";
    date = "00/00/0000 00:00:00 AM";
    IUCR = "";
    description = "";
    arrest = false;
    domestic = false;
    latitude = 0.0;
    longitude = 0.0;
}

Crimen::Crimen(const Crimen& x) {
    (*this).ID = x.ID;
    (*this).case_number = x.case_number;
    (*this).date = x.date;
    (*this).IUCR = x.IUCR;
    (*this).description = x.description;
    (*this).arrest = x.arrest;
    (*this).domestic = x.domestic;
    (*this).latitude = x.latitude;
    (*this).longitude = x.longitude;
}

Crimen::Crimen(const string & s) {
    //Para saber que cadena se ha leido
    int n_string_leido = 0;
    //Para dar formato a la descripcion
    char espacio = ' ';

    int inicio = 0;
    int final = s.find_first_of(",");
    string aux = s.substr(inicio, final - inicio + 1);
    ID = atoi(aux.c_str());
    n_string_leido++;

    inicio = final + 1;
    final = s.find_first_of(",", inicio);
    aux = s.substr(inicio, final - inicio);
    case_number = aux;
    n_string_leido++;

    inicio = final + 1;
    final = s.find_first_of(",", inicio);
    aux = s.substr(inicio, final - inicio);
    date = aux;
    n_string_leido++;

    inicio = final + 1;
    final = s.find_first_of(",", inicio);
    n_string_leido++;

    inicio = final + 1;
    final = s.find_first_of(",", inicio);
    aux = s.substr(inicio, final - inicio);
    IUCR = aux;
    n_string_leido++;

    inicio = final + 1;
    final = s.find_first_of(",", inicio);
    aux = s.substr(inicio, final - inicio);
    description = aux;
    n_string_leido++;

    //Si el siguiente caracter es una comilla, tengo que buscar una comilla
    //si no, tengo que buscar una coma
    if (s.at(final + 1) == '\"') {
        inicio = s.find_first_of("\"", final) + 1;
        final = s.find_first_of("\"", inicio);

    } else {
        inicio = s.find_first_of(",", final) + 1;
        final = s.find_first_of(",", inicio);
    }
    aux = s.substr(inicio, final - inicio);
    description.push_back(espacio);
    description.append(aux);
    n_string_leido++;

    //La variable aqui es para indicar si hemos entrado en el caso de las comillas
    //o no
    bool aqui;
    if (s.at(final + 1) == '\"') {
        inicio = s.find_first_of("\"", final) + 1;
        final = s.find_first_of("\"", inicio);
        aqui = true;

    } else {
        inicio = s.find_first_of(",", final) + 1;
        final = s.find_first_of(",", inicio);
        aqui = false;
    }
    aux = s.substr(inicio, final - inicio);
    description.push_back(espacio);
    description.append(aux);
    n_string_leido++;

    //Si hemos entrado en el caso de las comillas, inicio debe avanzar dos
    //posiciones, la de las comillas y la de la coma. En caso contrario,
    //solo debe avanzar una posicion, la de la coma
    if (aqui) {
        inicio = final + 2;
        final = s.find_first_of(",", inicio);

    } else {
        inicio = final + 1;
        final = s.find_first_of(",", inicio);
    }
    aux = s.substr(inicio, final - inicio);
    if (aux == "false")
        arrest = false;
    else if (aux == "true")
        arrest = true;
    n_string_leido++;

    inicio = final + 1;
    final = s.find_first_of(",", inicio);
    aux = s.substr(inicio, final - inicio);

    if (aux == "false")
        domestic = false;
    else if (aux == "true")
        domestic = true;
    n_string_leido++;

    //Leo para avanzar hasta llegar a longitud y latitud pero no guardo
    //ya que no necesito ninguno de los campos que hay en la base de datos
    //para mi Crimen
    while (n_string_leido < 19) {
        inicio = s.find_first_of(",", final);
        final = s.find_first_of(",", inicio + 1);
        n_string_leido++;
    }

    if (s.at(final + 1) == '\"') {
        inicio = s.find_first_of("\"", final) + 1;
        final = s.find_first_of("\"", inicio);
    } else {
        inicio = s.find_first_of(",", final) + 1;
        final = s.find_first_of(",", inicio);
    }
    //Convertir el string a double
    aux = s.substr(inicio, final - inicio + 1);
    double latitude_aux;
    stringstream convert(aux);
    if (!(convert >> latitude_aux)) {
        latitude_aux == 0;
    }
    latitude = latitude_aux;
    n_string_leido++;

    if (s.at(final + 1) == '\"') {
        inicio = s.find_first_of("\"", final) + 1;
        final = s.find_first_of("\"", inicio);
    } else {
        inicio = s.find_first_of(",", final) + 1;
        final = s.find_first_of(",", inicio);
    }
    aux = s.substr(inicio, final - inicio + 1);
    //Convertir el string a double
    double longitude_aux;
    stringstream convert2(aux);
    if (!(convert2 >> longitude_aux)) {
        longitude_aux == 0;
    }
    longitude = longitude_aux;
    n_string_leido++;
}

void Crimen::setID(const long int &id) {
    ID = id;
}

void Crimen::setCaseNumber(const string & s) {
    case_number = s;
}

void Crimen::setDate(const Date & d) {
    date = d;
}

void Crimen::setIUCR(const string &s) {
    IUCR = s;
}

void Crimen::setDescription(const string &s) {
    description = s;
}

void Crimen::setArrest(bool a) {
    arrest = a;
}

void Crimen::setDomestic(bool d) {
    domestic = d;
}

void Crimen::setLatitude(const double &d) {
    latitude = d;
}

void Crimen::setLongitude(const double &d) {
    longitude = d;
}

long int Crimen::getID() const {
    return ID;
}

string Crimen::getCaseNumber() const {
    return case_number;
}

Date Crimen::getDate() const {
    return date;
}

string Crimen::getIUCR() const {
    return IUCR;
}

string Crimen::getDescription() const {
    return description;
}

bool Crimen::getArrest() const {
    return arrest;
}

bool Crimen::getDomestic() const {
    return domestic;
}

double Crimen::getLatitude() const {
    return latitude;
}

double Crimen::getLongitude() const {
    return longitude;
}

Crimen & Crimen::operator=(const Crimen & c) {
    if (this != &c) {
        (*this).ID = c.ID;
        (*this).case_number = c.case_number;
        (*this).date = c.date;
        (*this).IUCR = c.IUCR;
        (*this).description = c.description;
        (*this).arrest = c.arrest;
        (*this).domestic = c.domestic;
        (*this).latitude = c.latitude;
        (*this).longitude = c.longitude;
    }
    return *this;
}

bool Crimen::operator==(const Crimen & x) const {
    bool son_iguales = true;

    if (son_iguales) {
        if ((*this).ID != x.ID) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).case_number != x.case_number) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).date != x.date) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).IUCR != x.IUCR) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).description != x.description) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).arrest != x.arrest) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).domestic != x.domestic) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).latitude != x.latitude) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).longitude != x.longitude) {
            son_iguales = false;
        }
    }

    return son_iguales;
}

bool Crimen::operator<(const Crimen & x) const {
    return (*this).ID < x.ID;
}

bool Crimen::operator>(const Crimen & x) const {
    return (*this).ID > x.ID;
}

ostream& operator<<(ostream &os, const Crimen &c) {
    os << "ID: " << c.ID << "." << endl
            << "Numero de caso: " << c.case_number << "." << endl
            << "Fecha: " << c.date << "." << endl
            << "IUCR: " << c.IUCR << "." << endl
            << "Descripcion: " << c.description << "." << endl;

    if (c.arrest == true)
        os << "Hay arrestados." << endl;
    else
        os << "No hay arrestados." << endl;
    if (c.domestic == true)
        os << "Es crimen doméstico." << endl;
    else
        os << "No es crimen domestico." << endl;

    os << "Latitud: " << c.latitude << "." << endl
            << "Longitud: " << c.longitude << "." << endl;
    return os;
}

#endif	/* CRIMEN_HXX */