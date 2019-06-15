/* 
 * File:   Crimen.h
 * Author: nestor
 *
 * Created on 29 de noviembre de 2015, 9:13
 */

#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "date.h"

using namespace std;

#ifndef CRIMEN_H
#define CRIMEN_H

//! Clase crimen, asociada a la definición de un crimen

/*! Crimen::Crimen,  .....
 * Descripción contiene toda la información asociada a un crimen.
 */

class Crimen {
public:
    /** @brief constructor primitivo.
     */
    Crimen();
    /** @brief constructor de copia
    @param x crimen a copiar
     */
    Crimen(const Crimen& x);
    /** @brief operador de asignación
    @param s strind a copiar (método usado principalmente para la lectura de la base de datos).
    Crea un crimen a partir de s.
     */
    Crimen(const string & s);
    /** @brief Asigna el identificador
    @param id es el identificador a asignar
     */
    void setID(const long int &id);
    /** @brief Asigna el numero de caso
    @param s es el numero de caso a asignar
     */
    void setCaseNumber(const string & s);
    /** @brief Asigna la fecha
    @param d es la fecha a asignar
     */
    void setDate(const Date & d);
    /** @brief Asigna el Código del tipo de delito según Illinois Uniform Crime Reporting, IUCR
    @param s string que indica el codigo
     */
    void setIUCR(const string &s);
    /** @brief Asigna la descripcion
    @param s string que indica la descripcion
     */
    void setDescription(const string &s);
    /** @brief Asigna si está arrestado o no
    @param a es el bool a asignar
     */
    void setArrest(bool a);
    /** @brief Asigna si el crimen es doméstico o no
    @param d es el bool a asignar
     */
    void setDomestic(bool d);
    /** @brief Asigna la latitud
    @param d double que indica la latitud
     */
    void setLatitude(const double &d);
    /** @brief Asigna la longitud
    @param d double que indica la longitud
     */
    void setLongitude(const double &d);
    /** @brief Devuelve el identificador del crimen
    @return Devuelve el identificador del crimen
     */
    long int getID() const;
    /** @brief Devuelve el numero del crimen
    @return Devuelve el numero del crimen
     */
    string getCaseNumber() const;
    /** @brief Devuelve la fecha del crimen
    @return Devuelve la fecha del crimen
     */
    Date getDate() const;
    /** @brief Devuelve el Código del tipo de delito según Illinois Uniform Crime Reporting, IUCR
    @return Devuelve el Código del tipo de delito según Illinois Uniform Crime Reporting, IUCR
     */
    string getIUCR() const;
    /** @brief Devuelve la descripcion del delito
    @return Devuelve la descripcion del delito
     */
    string getDescription() const;
    /** @brief Devuelve si ha habido arrestados o no
    @return true si ha habido arrestados, false en caso contrario
     */
    bool getArrest() const;
    /** @brief Devuelve si el crimen ha sido domestico o no
    @return true si el crimen ha sido domestico, false en caso contrario
     */
    bool getDomestic() const;
    /** @brief Devuelve la latitud del delito
    @return Devuelve la latitud del delito
     */
    double getLatitude() const;
    /** @brief Devuelve la longitud del delito
    @return Devuelve la longitud del delito
     */
    double getLongitude() const;
    /** @brief operador de asignación
    @param c crimen a copiar.
    Crea un crimen duplicado exacto de c.
     */
    Crimen & operator=(const Crimen & c);
    /** @brief operador de comparación
    @param x crimen con el que comparar.
    @return true si los crimenes son iguales, false en caso contrario
     */
    bool operator==(const Crimen & x) const;
    /** @brief operador de comparación
    @param x crimen con el que comparar.
    @return true si el crimen es menor que x, false en caso contrario
     */
    bool operator<(const Crimen & x) const;
    /** @brief operador de comparación
    @param x crimen con el que comparar.
    @return true si el crimen es mayor que x, false en caso contrario
     */
    bool operator>(const Crimen & x) const;
private:
    //Declaracion del operator<< como metodo amigo
    friend ostream& operator<<(ostream &os, const Crimen & c);
    //Atributos
    long int ID;
    string case_number;
    Date date;
    string IUCR;
    string description;
    bool arrest;
    bool domestic;
    double latitude;
    double longitude;
};

/** @brief imprime todas los datos de un crimen
@post  No se modifica el crimen.
 */
ostream& operator<<(ostream &os, const Crimen &c);

#include "crimen.hxx"
#endif /* CRIMEN_H */