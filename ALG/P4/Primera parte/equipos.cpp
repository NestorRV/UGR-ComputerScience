#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <stack>
#include "time.h"

using namespace std;

struct Jugador{
   int ID;
   int competicion;
};

vector<Jugador> BackTracking(vector<Jugador> & jugadores){
   vector<Jugador> solucionParcial;
   vector<Jugador> mejorSolucion = jugadores;
   int meta = 0;
   for(int i = 0; i < jugadores.size(); i++)
      meta += jugadores[i].competicion;

   meta = meta/2;
   // Profundidad del algoritmo
   int mejorPuntuacion = meta * 2;
   int ultimoJugador = jugadores.back().ID;

   int puntuacion = jugadores[0].competicion;
   solucionParcial.push_back(jugadores[0]);

   while (!solucionParcial.empty()) {
      // Si hemos alcanzado la puntuacion objetivo (meta), el algoritmo termina.
      if (puntuacion == meta){
         return solucionParcial;
      }
      else if (abs(meta - puntuacion) < abs(meta - mejorPuntuacion)){
         mejorSolucion = solucionParcial;
         mejorPuntuacion = puntuacion;
      }

      int actualID = solucionParcial.back().ID;

      if (actualID != ultimoJugador){
         Jugador aniadir = jugadores[actualID + 1];
         solucionParcial.push_back(aniadir);
      }
      else {
         int ultIDusado = ultimoJugador;
         while (ultIDusado == ultimoJugador && solucionParcial.size() > 1) {
            solucionParcial.pop_back();
            puntuacion -= jugadores[ultIDusado].competicion;
            ultIDusado = solucionParcial.back().ID;
         }
         puntuacion -= jugadores[ultIDusado].competicion;
         solucionParcial.pop_back();

         if (solucionParcial.empty())
            continue;

         solucionParcial.push_back(jugadores[ultIDusado + 1]);
      }

      puntuacion += solucionParcial.back().competicion;
   }

   return mejorSolucion;
}

vector<Jugador> BranchBound(vector<Jugador> jugadores){
   vector<Jugador> solucionParcial, mejorSolucion;
   stack<int> auxiliar;
   int meta = 0;
   for(int i = 0; i < jugadores.size(); i++)
      meta += jugadores[i].competicion;
   meta = meta / 2;
   int mejorPuntuacion = 0, puntuacion = 0;
   int ultimoJugador = jugadores.back().ID;

   Jugador jug;
   for (auto i = 0; i < jugadores.size(); i++) {
      jug = jugadores[i];
      // Pila de IDs
      auxiliar.push(jug.ID);
      solucionParcial.push_back(jug);
      puntuacion = jug.competicion;
      while(!auxiliar.empty()){
         if (puntuacion == meta){
            return solucionParcial;
         }
         else if (abs(meta - puntuacion) < abs(meta - mejorPuntuacion)){
            mejorSolucion = solucionParcial;
            mejorPuntuacion = puntuacion;
         }

         int actualID = solucionParcial.back().ID;

         if (actualID != ultimoJugador && puntuacion < meta) {
            Jugador aniadir = jugadores[actualID + 1];
            solucionParcial.push_back(aniadir);
            auxiliar.push(aniadir.ID);
            puntuacion += aniadir.competicion;
         }
         else {
         	int ultIDusado;
            do {
               ultIDusado = auxiliar.top();
               puntuacion -= solucionParcial.back().competicion;
               solucionParcial.pop_back();
               auxiliar.pop();
            } while(ultIDusado == ultimoJugador && !auxiliar.empty());

            if (auxiliar.empty())
               break;

            Jugador aniadir = jugadores[ultIDusado + 1];
            solucionParcial.push_back(aniadir);
            auxiliar.push(aniadir.ID);
            puntuacion += aniadir.competicion;
         }
      }
   }
   return mejorSolucion;
}

int main(int argc, char **argv){
   int tamanio = atoi(argv[1]);
   vector<Jugador> jugadores, equipo1, equipo2;
   Jugador j;
   srand(time(NULL));

   chrono::high_resolution_clock::time_point tantes, tdespues;
   chrono::duration<double> transcurrido;

   if (argc != 2) {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
   }

   for(int i = 0; i < tamanio; i++){
      j.ID = i;
      j.competicion = (rand() % 50) + 1;
      jugadores.push_back(j);
   }


   tantes = chrono::high_resolution_clock::now();
   equipo1 = BackTracking(jugadores);
   tdespues = chrono::high_resolution_clock::now();
   transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
   cout << tamanio << " " << transcurrido.count() << endl;

   /*for (int i = 0; i < equipo1.size(); i++)
      cout << equipo1[i].ID << ": " << equipo1[i].competicion << endl;*/

   return 0;
}
