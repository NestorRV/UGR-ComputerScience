#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <fstream>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;

// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar

// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}

/*********************
Funciones para calcular el numero de fichas seguidas en el tablero,
tanto en vertical, como en horizontal y en diagonal.
0 vacia, 1 jugador1, 2 jugador2, 4 bomba del jugador1, 5 bomba del jugador 2.
*********************/
int Horizontal(int jugador, const Environment &estado){
    int puntuacion = 0, seguidas = 0, bomba, enemigo, bomba_enemigo;
    if(jugador == 1){
        bomba = 4;
        enemigo = 2;
        bomba_enemigo = 5;
    }
    else{
        bomba = 5;
        enemigo = 1;
        bomba_enemigo = 4;
    }

    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++){
            if(estado.See_Casilla(i,j) == jugador || estado.See_Casilla(i,j) == bomba){
                seguidas++;
                if(seguidas == 2)
                    puntuacion = puntuacion + 2 * seguidas;
                else if(seguidas == 3)
                    puntuacion = puntuacion + 4 * seguidas;
                else
                    puntuacion += seguidas;
            }
            else if(estado.See_Casilla(i,j) == enemigo || estado.See_Casilla(i,j) == bomba_enemigo){
                if(seguidas == 2)
                    puntuacion = puntuacion - 2 * seguidas;
                else if(seguidas == 3)
                    puntuacion = puntuacion - 4 * seguidas;
                else
                    puntuacion -= seguidas;
                seguidas = 0;
            }
            else {
                seguidas = 0;
            }
        }
        seguidas = 0;
    }

    return puntuacion;
}

int Vertical(int jugador, const Environment &estado){
    int puntuacion = 0, seguidas = 0, bomba, enemigo, bomba_enemigo;
    if(jugador == 1){
        bomba = 4;
        enemigo = 2;
        bomba_enemigo = 5;
    }
    else{
        bomba = 5;
        enemigo = 1;
        bomba_enemigo = 4;
    }

    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++){
            if(estado.See_Casilla(j,j) == jugador || estado.See_Casilla(j,i) == bomba){
                seguidas++;
                if(seguidas == 2)
                    puntuacion = puntuacion + 2 * seguidas;
                else if(seguidas == 3)
                    puntuacion = puntuacion + 4 * seguidas;
                else
                    puntuacion += seguidas;
            }
            else if(estado.See_Casilla(j,i) == enemigo || estado.See_Casilla(j,i) == bomba_enemigo){
                if(seguidas == 2)
                    puntuacion = puntuacion - 2 * seguidas;
                else if(seguidas == 3)
                    puntuacion = puntuacion - 4 * seguidas;
                else
                    puntuacion -= seguidas;
                seguidas = 0;
            }
            else {
                seguidas = 0;
            }
        }
        seguidas = 0;
    }

    return puntuacion;
}

int Diagonal(int jugador, const Environment &estado){
    int puntuacion = 0, seguidas = 0, bomba, enemigo, bomba_enemigo;
    if(jugador == 1){
        bomba = 4;
        enemigo = 2;
        bomba_enemigo = 5;
    }
    else{
        bomba = 5;
        enemigo = 1;
        bomba_enemigo = 4;
    }

    // Derecha-abajo / izquierda-arriba.
    for(int i = 0; i < 4; i++) {
        for(int j = 3; j < 7; j++) {
            for(int k = 0; k < 4; k++) {
                if(estado.See_Casilla(i+k,j-k) == jugador || estado.See_Casilla(i+k,j-k) == bomba) {
                    seguidas++;
                    if(seguidas == 2)
                        puntuacion = puntuacion + 2 * seguidas;
                    else if(seguidas == 3)
                        puntuacion = puntuacion + 4 * seguidas;
                    else
                        puntuacion += seguidas;
                }
                else if(estado.See_Casilla(i+k,j-k) == enemigo || estado.See_Casilla(i+k,j-k) == bomba_enemigo){
                    if(seguidas == 2)
                        puntuacion = puntuacion - 2 * seguidas;
                    else if(seguidas == 3)
                        puntuacion = puntuacion - 4 * seguidas;
                    else
                        puntuacion -= seguidas;
                    seguidas = 0;
                }
                else {
                    seguidas = 0;
                }
            }
            seguidas = 0;
        }
    }

    // Derecha-arriba / izquierda-abajo.
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                if(estado.See_Casilla(j+k,i+k) == jugador || estado.See_Casilla(j+k,i+k) == bomba) {
                    seguidas++;
                    if(seguidas == 2)
                        puntuacion = puntuacion + 2 * seguidas;
                    else if(seguidas == 3)
                        puntuacion = puntuacion + 4 * seguidas;
                    else
                        puntuacion += seguidas;
                }
                else if(estado.See_Casilla(j+k,i+k) == enemigo || estado.See_Casilla(j+k,i+k) == bomba_enemigo){
                    if(seguidas == 2)
                        puntuacion = puntuacion - 2 * seguidas;
                    else if(seguidas == 3)
                        puntuacion = puntuacion - 4 * seguidas;
                    else
                        puntuacion -= seguidas;
                    seguidas = 0;
                }
                else {
                    seguidas = 0;
                }
            }
            seguidas = 0;
        }
    }

    return puntuacion;
}

/*********************
Funcion que devuelve el valor heursitico de un tablero.
*********************/
double Heuristica(int jugador, const Environment &estado){
    int enemigo;
    (jugador == 1) ? enemigo = 2 : enemigo = 1;

    int mi_h = Horizontal(jugador, estado);
    int op_h = Horizontal(enemigo, estado);
    int mi_v = Vertical(jugador, estado);
    int op_v = Vertical(enemigo, estado);
    int mi_d = Diagonal(jugador, estado);
    int op_d = Diagonal(enemigo, estado);

    return ((op_h + op_v + op_d) - (mi_h + mi_v + mi_d));
}

/*********************
Funcion para calcular la valoracion.
*********************/
double Valoracion(const Environment &estado, int jugador){
   int ganador = estado.RevisarTablero();

   if (ganador==jugador)
      return 99999999.0; // Gana el jugador que pide la valoracion
   else if (ganador!=0)
      return -99999999.0; // Pierde el jugador que pide la valoracion
   else if (estado.Get_Casillas_Libres()==0)
      return 0;  // Hay un empate global y se ha rellenado completamente el tablero
   else {
      //Si no he ganado ni perdido ni empatado aplicamos la heurística
      return Heuristica(jugador,estado);
   }
}

/*********************
Algoritmo de PodaAlfaBeta. Calcula el valor y asigna en accion la accion a realizar.
*********************/
double PodaAlfaBeta(const Environment & T, int jugador, int profundidad, double alpha, double beta, Environment::ActionType & accion, bool maxORmin, double & numNodos){
    if (profundidad == 0 || T.JuegoTerminado()){
        numNodos++;
        return Valoracion(T, jugador);
    }

    int ultacc = -1, num_hijos;
    Environment::ActionType acc_ant;
    double valor;
    Environment hijo = T.GenerateNextMove(ultacc);
    bool VecAct[8];
    num_hijos = T.possible_actions(VecAct);

    if (maxORmin) {
        for (int i = 0; i < num_hijos; i++){
            valor = PodaAlfaBeta(hijo, jugador, profundidad - 1, alpha, beta, acc_ant, false, numNodos);
            if (valor > alpha){
                alpha = valor;
                accion = static_cast <Environment::ActionType > (ultacc);
            }
            if (beta <= alpha)
                break;

            hijo = T.GenerateNextMove(ultacc);
        }
        return alpha;
    }
    else if (!maxORmin) {
        for (int i = 0; i < num_hijos; i++){
            valor = PodaAlfaBeta(hijo, jugador, profundidad - 1, alpha, beta, acc_ant, true, numNodos);
            if (valor < beta) {
               beta = valor;
               accion = static_cast <Environment::ActionType > (ultacc);
            }
            if (beta <= alpha)
                break;

            hijo = T.GenerateNextMove(ultacc);
        }
        return beta;
    }
}

/*********************
Invoca el siguiente movimiento del jugador.
*********************/
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // accion que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable aplicables[1]==true si PUT2 es aplicable aplicables[2]==true si PUT3 es aplicable aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable aplicables[5]==true si PUT6 es aplicable aplicables[6]==true si PUT7 es aplicable aplicables[7]==true si BOOM es aplicable

    double valor, numNodos = 0; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha, beta; // Cotas de la poda AlfaBeta
    int n_act; //Acciones posibles en el estado actual

    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;

    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------
    alpha = menosinf;
    beta = masinf;
    valor = PodaAlfaBeta(actual_, jugador_, PROFUNDIDAD_ALFABETA, alpha, beta, accion, true, numNodos);
    cout << "Valor: " << valor << "  Accion elegida: " << actual_.ActionStr(accion) << " Nodos evaludos: " << numNodos << endl;

    return accion;
}
