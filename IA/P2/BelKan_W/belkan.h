
#ifndef AGENT__
#define AGENT__

#include <string>
#include <iostream>
#include <cstdlib>
#include "conexion.h"
#include <time.h>
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
	    srand(time(NULL));
	    //Variables de estado
        x_= 99; y_= 99;
		orientacion_=3;
		role_="PlYR";
		last_accion_=3;
		REINICIADO_=false; FIN_JUEGO_=false;
		size_=200;
        //Variables para huir del oso
        huir_oso = false; huir_oso2 = false; huir_oso3 = false;
        //Variables para encontrar los PK
        PK1_d = false; PK2_d = false; PK3_d = false;
		PK1_i = false; PK2_i = false; PK3_i = false;
        //Variables para guardar los PK
        primerPK = false; segundoPK = false;
		primera_vez = false; rotado = false;
        PK1_fila = -1; PK1_columna = -1;
        PK2_fila = -1; PK2_columna = -1;
        myPK1_fila = -1; myPK1_columna = -1;
        myPK2_fila = -1; myPK2_columna = -1;
        //Variables para orientar el mapa
        PKListos = false;
        iteracion = 0; orientacion_real = -1;
        //Variables de movimiento
        izquierda = 30000; derecha = 30000; frente = 30000;
		ninguna_opcion = false;
        //Variables de objetos
        objeto_cogido = false;
        obj1_d = false; obj2_d = false; obj3_d = false;
        obj1_i = false; obj2_i = false; obj3_i = false;
        num_objetos = 0;
        //Variables de personajes
        pj1_d = false; pj2_d = false; pj3_d = false;
        pj1_i = false; pj2_i = false; pj3_i = false;
        he_sacado = false;

		for (int i=0;i<200;i++)
		    for(int j=0;j<200;j++){
		      mapa_entorno_[i][j]='?';
		      mapa_objetos_[i][j]='?';
		      mapa_temporal_[i][j]='?';
		      mapa_aux_[i][j]='?';
		      pulgarcito[i][j] = 0;
		    }
        for (int i=0;i<100;i++)
		    for(int j=0;j<100;j++)
                mapa_solucion_[i][j] = '?';
	}

	enum ActionType
	{
	    actFORWARD, // avanzar
	    actTURN_L,  // Girar Izquierda
	    actTURN_R,  // Girar Derecha
	    actIDLE,    // No hacer nada
	    actPICKUP,  // Recoger un objeto
	    actPUTDOWN, // Soltar un objeto
	    actPUSH,    // Meter en la mochila
	    actPOP,     // Sacar de la mochila
	    actGIVE,	// Dar un objeto a un personaje
	    actTHROW	// Lanzar un objeto

	};

	void Perceive(Environment &env);
	bool Perceive_Remote(conexion_client &Cliente, Environment &env);
	void ActualizarInformacion(Environment *env);
	ActionType Think();
	void FixLastAction(Agent::ActionType x){last_accion_=x;};
	void GuardarMapa();
	void RellenarMapa();
	void EscribirFichero();

	char mapa_entorno_[200][200]; // mapa que muestra el tipo de terreno
	char mapa_objetos_[200][200]; // mapa que muestra los objetos que estan encima del terreno
	char mapa_temporal_[200][200]; // mapa temporal para realizar las roatciones
	char mapa_aux_[200][200]; // mapa auxiliar para las rotaciones
	char mapa_solucion_[100][100]; // mapa que almacena la solucion que el alumno propone
	int pulgarcito[200][200];// mapa que almacena la iteracion en la cual hemos pasado por cada casilla
	// Funciones de acceso a los datos
	void GetCoord(int &fila, int &columna, int &brujula){fila=y_;columna=x_;brujula=orientacion_;};


private:
	//Variables de interaccion con el entorno grafico
	int size_;

	//SENSORES
	char VISTA_[10];
	char SURFACE_[10];
	bool REINICIADO_;
	string MENSAJE_;
	char EN_USO_;
	char MOCHILLA_[5];
	char PUNTUACION_[9];
	bool FIN_JUEGO_;
	char SALUD_;

	//Variables de estado
	int x_,y_, orientacion_;
	int last_accion_;
	string role_;
    //Variables para huir del oso
    bool huir_oso, huir_oso2, huir_oso3;
	//Variables para encontrar los PK
	bool PK1_d, PK2_d, PK3_d, PK1_i, PK2_i, PK3_i;
	//Variables para guardar los PK
    bool primerPK, segundoPK, primera_vez, rotado;
    int PK1_fila, PK2_fila, PK1_columna, PK2_columna;
    int myPK1_fila, myPK2_fila, myPK1_columna, myPK2_columna;
    //Variables para orientar el mapa
    bool PKListos;
    int iteracion, orientacion_real;
    //Variables de movimiento
	double izquierda, derecha, frente;
    bool ninguna_opcion;
    //Variables de objetos
    bool objeto_cogido;
    bool obj1_d, obj2_d, obj3_d, obj1_i, obj2_i, obj3_i;
    int num_objetos;
    //Variables de personajes
    bool pj1_d, pj2_d, pj3_d, pj1_i, pj2_i, pj3_i;
    bool he_sacado;
};

string ActionStr(Agent::ActionType);

#endif
