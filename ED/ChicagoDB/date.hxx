/* 
 * File:   date.hxx
 * Author: nestor
 *
 * Created on 29 de noviembre de 2015, 9:14
 */

/** @brief fichero de implementacion de la clase Date
 */

#ifndef DATE_HXX
#define DATE_HXX

#include "date.h"

Date::Date() {
    sec = 0;
    min = 0;
    hour = 0;
    mday = 1;
    mon = 0;
    year = 2000;
}

Date::Date(const Date & x) {
    (*this) = x;
}

Date::Date(const string &s) { // s es un string con el formato mm/dd/aaaa hh:mm:ss AM/PM
    (*this) = s;
}

int Date::getSec() {
    return sec;
}

int Date::getMin() {
    return min;
}

int Date::getHour() {
    return hour;
}

int Date::getMday() {
    return mday;
}

int Date::getMon() {
    return mon + 1;
}

int Date::getYear() {
    return year;
}

void Date::setSec(const int &x) {
    sec = x;
}

void Date::setMin(const int &x) {
    min = x;
}

void Date::setHour(const int &x) {
    hour = x;
}

void Date::setMday(const int &x) {
    mday = x;
}

void Date::setMon(const int &x) {
    mon = x - 1;
}

void Date::setYear(const int &x) {
    year = x;
}

string Date::toString() const {
    stringstream s;
    s << (*this);
    return s.str();
}

Date & Date::operator=(const Date & f) {
    if (this != &f) {
        sec = f.sec;
        min = f.min;
        hour = f.hour;
        mday = f.mday;
        mon = f.mon;
        year = f.year;
    }
    return *this;
}

Date & Date::operator=(const string & s) {
    string trozo;
    trozo = s.substr(0, 2);
    mon = atoi(trozo.c_str()) - 1;
    trozo = s.substr(3, 2);
    mday = atoi(trozo.c_str());
    trozo = s.substr(6, 4);
    year = atoi(trozo.c_str());
    trozo = s.substr(11, 2);
    hour = atoi(trozo.c_str());
    trozo = s.substr(14, 2);
    min = atoi(trozo.c_str());
    trozo = s.substr(17, 2);
    sec = atoi(trozo.c_str());
    trozo = s.substr(20, 2);
    if (trozo == "PM")
        hour += 12;
    return *this;
}

bool Date::operator==(const Date & f) const {
    bool son_iguales = true;

    if (son_iguales) {
        if ((*this).sec != f.sec) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).min != f.min) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).hour != f.hour) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).mday != f.mday) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).mon != f.mon) {
            son_iguales = false;
        }
    }
    if (son_iguales) {
        if ((*this).year != f.year) {
            son_iguales = false;
        }
    }
    return son_iguales;
}

bool Date::operator<(const Date & f) const {
    if (year < f.year)
        return true;
    else if (year > f.year)
        return false;

    if (mon < f.mon)
        return true;
    else if (mon > f.mon)
        return false;

    if (mday < f.mday)
        return true;
    else if (mday > f.mday)
        return false;

    if (hour < f.hour)
        return true;
    else if (hour > f.hour)
        return false;

    if (min < f.min)
        return true;
    else if (min > f.min)
        return false;

    if (sec < f.sec)
        return true;
    else if (sec > f.sec)
        return false;
}

bool Date::operator>(const Date & f) const {
    bool mayor = true;

    if ((*this) < f || (*this) == f) {
        mayor = false;
    }
    return mayor;
}

bool Date::operator<=(const Date & f) const {
    bool menor_igual = false;

    if ((*this) == f || (*this) < f) {
        menor_igual = true;
    }
    return menor_igual;
}

bool Date::operator>=(const Date & f) const {
    bool mayor_igual = false;

    if ((*this) == f || (*this) > f) {
        mayor_igual = true;
    }
    return mayor_igual;
}

bool Date::operator!=(const Date & f) const {
    if ((*this) == f)
        return false;
    else
        return true;
}

ostream& operator<<(ostream& os, const Date & f) {
    if (f.mon < 9) {
        os << "0" << (f.mon + 1) << "/";
    } else {
        os << (f.mon + 1) << "/";
    }

    if (f.mday < 10) {
        os << "0" << f.mday << "/";
    } else {
        os << f.mday << "/";
    }
    os << f.year << " ";

    if (f.hour < 10) {
        os << "0" << f.hour << ":";
    } else {
        os << f.hour << ":";
    }

    if (f.min < 10) {
        os << "0" << f.min << ":";
    } else {
        os << f.min << ":";
    }

    if (f.sec < 10) {
        os << "0" << f.sec;
    } else {
        os << f.sec;
    }

    return os;
}

#endif	/* DATE_HXX */