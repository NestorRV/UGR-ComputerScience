/* 
 * File:   date.h
 * Author: nestor
 *
 * Created on 29 de noviembre de 2015, 9:14
 */

#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

#ifndef DATE_H
#define DATE_H

//! Clase Date, asociada a la

/*! Date::Date,  .....
 * Descripción contiene toda la información asociada a una Date con el formato  mm/dd/aaaa hh:mm:ss AM/PM
 */

class Date {
public:
    /** @brief constructor primitivo.
     */
    Date(); //Constructor de Date por defecto
    /** @brief constructor a partir de un string con el formato mm/dd/aaaa  hh:mm:ss AM/PM
    @param s Date a copiar
     */
    Date(const string & s); // s es un string con el formato mm/dd/aaaa  hh:mm:ss AM/PM
    /** @brief constructor de copia
    @param x Date a copiar
     */
    Date(const Date & x); //Constructor de copia

    /** @brief operador de asignación
    @param f Date a copiar.
    Crea un conjunto duplicado exacto de f.
     */
    Date & operator=(const Date & f);
    /** @brief operador de asignación a partir de un string con el formato mm/dd/aaaa  hh:mm:ss AM/PM
    @param s Date a copiar.
    Crea un conjunto duplicado exacto de s.
     */
    Date & operator=(const string & s); // s es un string con el formato mm/dd/aaaa hh:mm:ss AM/PM
    /** @brief Devuelve los un string con los datos de la Date
    @return Devuelve los un string con los datos de la Date
     */
    string toString() const; //convierte la Date a un string

    /** @brief Devuelve los segundos de la Date
    @return Devuelve los segundos de la Date
     */
    int getSec();
    /** @brief Devuelve los minutos de la Date
    @return Devuelve los minutos de la Date
     */
    int getMin();
    /** @brief Devuelve las horas de la Date
    @return Devuelve las horas de la Date
     */
    int getHour();
    /** @brief Devuelve el día del mes de la Date
    @return Devuelve el día del mes de la Date
     */
    int getMday();
    /** @brief Devuelve el mes de la Date
    @return Devuelve el mes de la Date
     */
    int getMon();
    /** @brief Devuelve el año de la Date
    @return Devuelve el año de la Date
     */
    int getYear();

    /** @brief Asigna los segundos
    @param x entero que indica los segundos
     */
    void setSec(const int &x);
    /** @brief Asigna los minutos
    @param x entero que indica los minutos
     */
    void setMin(const int &x);
    /** @brief Asigna las horas
    @param x entero que indica las horas
     */
    void setHour(const int &x);
    /** @brief Asigna el día del mes
    @param x entero que indica el día del mes
     */
    void setMday(const int &x);
    /** @brief Asigna el mes
    @param x entero que indica el mes
     */
    void setMon(const int &x);
    /** @brief Asigna el año
    @param x entero que indica el año
     */
    void setYear(const int &x);

    //Operadores relacionales

    /** @brief operador de comparación
    @param f Date con el que comparar.
    @return true si las Dates son iguales, false en caso contrario
     */
    bool operator==(const Date & f) const;
    /** @brief operador de comparación
    @param f Date con el que comparar.
    @return true si la Date es menor que f, false en caso contrario
     */
    bool operator<(const Date & f)const;
    /** @brief operador de comparación
    @param f Date con el que comparar.
    @return true si la Date es mayor que f, false en caso contrario
     */
    bool operator>(const Date & f) const;
    /** @brief operador de comparación
    @param f Date con el que comparar.
    @return true si la Date es menor o igual que f, false en caso contrario
     */
    bool operator<=(const Date & f)const;
    /** @brief operador de comparación
    @param f Date con el que comparar.
    @return true si la Date es mayor o igual que f, false en caso contrario
     */
    bool operator>=(const Date & f) const;
    /** @brief operador de comparación
    @param f Date con el que comparar.
    @return true si la Date es distinta que f, false en caso contrario
     */
    bool operator!=(const Date & f)const;

private:
    int sec; // seconds of minutes from 0 to 59
    int min; // minutes of hour from 0 to 59
    int hour; // hours of day from 0 to 24
    int mday; // day of month from 1 to 31
    int mon; // month of year from 0 to 11
    int year; // year since 2000

    /** @brief imprime Date
     */
    friend ostream& operator<<(ostream& os, const Date &f);
};

/** @brief imprime Date con el formato  mm/dd/aaaa hh:mm:ss AM/PM
 */
ostream& operator<<(ostream& os, const Date & f);

#include "date.hxx" // Incluimos la implementacion.
#endif	/* DATE_H */