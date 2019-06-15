/* 
 * File:   main.cpp
 * Author: nestor
 *
 * Created on 29 de noviembre de 2015, 9:13
 */

#include "crimen.h"
#include "date.h"
#include "css.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    CSS ChicagoDB;
    ChicagoDB.load("crimenes-10.csv");

    cout << "============================== setArrest ===========================" << endl;
    ChicagoDB.setArrest(10231208, true);

    cout << "============================== erase ===============================" << endl;
    ChicagoDB.erase(10231208);

    list<ID> inArea = ChicagoDB.inArea(-87.70, 40, -87.6577798, 103);
    cout << "============================== inArea ==============================" << endl;
    for (auto list_it = inArea.begin(); list_it != inArea.end(); list_it++)
        cout << *list_it << endl;

    cout << "============================== Query ===============================" << endl;
    list<string> q;
    q.push_back("BATTERY");
    q.push_back("RESIDENTIAL");
    q.push_back("IDENTITY");
    q.push_back("VEHICLE");
    q.push_back("SIMPLE");
    q.push_back("INJURY");
    q.push_back("SERIOUS");

    vector<pair<ID, float>> v = ChicagoDB.Query(q, 5);

    return 0;
}