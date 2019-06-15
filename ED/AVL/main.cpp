/* 
 * File:   main.cpp
 * Author: nestor
 *
 * Created on 8 de enero de 2016, 11:46
 */

#include "avl.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    AVL<int> mi;
    typename AVL<int>::iterator it;

    mi.insert(50);
    mi.insert(3);
    mi.insert(60);
    mi.insert(30);
    mi.insert(70);
    mi.insert(65);
    mi.insert(2);
    mi.insert(16);
    mi.insert(11);
    mi.insert(45);
    mi.insert(22);
    mi.insert(1);
    
    cout << "El AVL es: " << endl;
    for (it = mi.begin(); it != mi.end(); it++)
        cout << (*it) << " ";
    cout << endl;
    
    typename AVL<int>::const_iterator it2 = mi.lower_bound(16);
    typename AVL<int>::const_iterator it3 = mi.upper_bound(70);
    
    cout << "El lower_bound de 16 es: " << (*it2) << endl;
    cout << "El upper_bound de 11 es: " << (*it3) << endl;

    mi.erase(0);
    mi.erase(16);
    mi.erase(50);

    cout << "El nuevo AVL es: " << endl;
    for (it = mi.begin(); it != mi.end(); it++)
        cout << (*it) << " ";
    cout << endl;
}