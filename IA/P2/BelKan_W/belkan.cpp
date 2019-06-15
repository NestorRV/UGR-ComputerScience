#include "belkan.h"
#include "conexion.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cstring>
#include <sstream>
#include <fstream>

using namespace std;



// -----------------------------------------------------------
void PasarVectoraMapaCaracteres(int fila, int columna, char m[200][200], char *v, int brujula){
  m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]=v[5+j];
		}
	        break;
	case 1: // Orientacion Este
		m[fila][columna+1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]=v[5+j];
		}
	        break;
        case 2: // Orientacion Sur
		m[fila+1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=v[5+j];
		}
		                break;
        case 3: // Orientacion Oeste
		m[fila][columna-1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]=v[5+j];
		}

                break;
    }

}


// -----------------------------------------------------------
void Agent::Perceive(Environment &env)
{
	env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, false);

}


bool Agent::Perceive_Remote(conexion_client &Cliente, Environment &env)
{
	bool actualizado=false;


	actualizado = env.Perceive_Remote(Cliente);
	if (actualizado)
		env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, true);

    return actualizado;
}


// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actIDLE: return "IDLE";
	case Agent::actPICKUP: return "PICK UP";
	case Agent::actPUTDOWN: return "PUT DOWN";
	case Agent::actPUSH: return "PUSH";
	case Agent::actPOP: return "POP";
	case Agent::actGIVE: return "GIVE";
	case Agent::actTHROW: return "THROW";
	default: return "????";
	}
}

// -----------------------------------------------------------
void Agent::ActualizarInformacion(Environment *env){
	// Actualizar mi informacion interna
	if (REINICIADO_){
        if(PKListos)
            GuardarMapa();
		//Variables de estado
        x_= 99; y_= 99;
		orientacion_=3;
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
        iteracion = 0;
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
	}

	switch(last_accion_){
	  case 0: //avanzar
	  switch(orientacion_){
	    case 0: // norte
		    y_--;
		    break;
	    case 1: // este
		    x_++;
		    break;
	    case 2: // sur
		    y_++;
		    break;
	    case 3: // este
		    x_--;
		    break;
	  }
	  break;
	  case 1: // girar izq
		  orientacion_=(orientacion_+3)%4;
		  break;
	  case 2: // girar dch
		  orientacion_=(orientacion_+1)%4;
		  break;
	}

	// Comprobacion para no salirme del rango del mapa
	bool algo_va_mal=false;
	if (y_<0){
		y_=0;
		algo_va_mal=true;
	}
	else if (y_>199){
		y_=199;
		algo_va_mal=true;
	}
	if (x_<0){
		x_=0;
		algo_va_mal=true;
	}
	else if (x_>199){
		x_=199;
		algo_va_mal=true;
	}

	if (algo_va_mal){
		cout << "CUIDADO: NO ESTAS CONTROLANDO BIEN LA UBICACION DE TU AGENTE\n";
	}


	PasarVectoraMapaCaracteres(y_,x_,mapa_entorno_,VISTA_,orientacion_);
	PasarVectoraMapaCaracteres(y_,x_,mapa_objetos_,SURFACE_,orientacion_);

	env->ActualizarMatrizUsuario(mapa_entorno_);

}

// -----------------------------------------------------------

void Agent::GuardarMapa(){
    if(orientacion_real == 0){
        for(int i = 0; i < 200; i++){
            for(int j = 0; j < 200; j++){
                mapa_temporal_[i][j] = mapa_entorno_[i][j];
            }
        }
    }
    else if (orientacion_real == 1){
        int t;
        for(int i = 0; i < 200; i++){
            t = 0;
            for(int j = 199; j >= 0; --j){
                mapa_aux_[i][t] = mapa_entorno_[j][i];
                t++;
            }
        }

        for(int i = 0; i < 200; i++){
            t = 0;
            for(int j = 199; j >= 0; --j){
                mapa_temporal_[i][t] = mapa_aux_[j][i];
                t++;
            }
        }
    }
    else if (orientacion_real == 2){
        int t;
        for(int i = 0; i < 200; i++){
            t = 0;
            for(int j = 199; j >= 0; --j){
                mapa_temporal_[i][t] = mapa_entorno_[j][i];
                t++;
            }
        }
    }
    else if (orientacion_real == 3){
        int t = 0;
        for(int i = 199; i >= 0; --i){
            for(int j = 0; j < 200; j++){
                mapa_temporal_[t][j] = mapa_entorno_[j][i];
            }
            t++;
        }
    }

    int PKfila, PKcolumna, AGfila, AGcolumna;
    PKfila = PK1_fila;
    PKcolumna = PK1_columna;
    AGfila = myPK1_fila;
    AGcolumna = myPK1_columna;

    for(int i = PKfila; i < 100; i++){
        AGcolumna = myPK1_columna;
        for(int j = PKcolumna; j < 100; j++){
            if(mapa_solucion_[i][j] == '?')
                mapa_solucion_[i][j] = mapa_temporal_[AGfila][AGcolumna];
            AGcolumna++;
        }
        AGfila++;
    }

    PKfila = PK1_fila;
    PKcolumna = PK1_columna;
    AGfila = myPK1_fila;
    AGcolumna = myPK1_columna;
    for(int i = PKfila; i >= 0; i--){
        AGcolumna = myPK1_columna;
        for(int j = PKcolumna; j >= 0; j--){
            if(mapa_solucion_[i][j] == '?')
                mapa_solucion_[i][j] = mapa_temporal_[AGfila][AGcolumna];
            AGcolumna--;
        }
        AGfila--;
    }

    PKfila = PK1_fila;
    PKcolumna = PK1_columna;
    AGfila = myPK1_fila;
    AGcolumna = myPK1_columna;
    for(int i = PKfila; i >= 0; i--){
        AGcolumna = myPK1_columna;
        for(int j = PKcolumna; j < 100; j++){
            if(mapa_solucion_[i][j] == '?')
                mapa_solucion_[i][j] = mapa_temporal_[AGfila][AGcolumna];
            AGcolumna++;
        }
        AGfila--;
    }

    PKfila = PK1_fila;
    PKcolumna = PK1_columna;
    AGfila = myPK1_fila;
    AGcolumna = myPK1_columna;
    for(int i = PKfila; i < 100; i++){
        AGcolumna = myPK1_columna;
        for(int j = PKcolumna; j >= 0; j--){
            if(mapa_solucion_[i][j] == '?')
                mapa_solucion_[i][j] = mapa_temporal_[AGfila][AGcolumna];
            AGcolumna--;
        }
        AGfila++;
    }

    EscribirFichero();
}

void Agent::RellenarMapa(){
    //Relleno los precipicios
    for(int i = 0; i < 100; i++){
        mapa_solucion_[0][i] = 'P'; mapa_solucion_[1][i] = 'P'; mapa_solucion_[2][i] = 'P';
        mapa_solucion_[97][i] = 'P'; mapa_solucion_[98][i] = 'P'; mapa_solucion_[99][i] = 'P';
    }

    for(int i = 0; i < 100; i++){
        mapa_solucion_[i][0] = 'P'; mapa_solucion_[i][1] = 'P'; mapa_solucion_[i][2] = 'P';
        mapa_solucion_[i][97] = 'P'; mapa_solucion_[i][98] = 'P'; mapa_solucion_[i][99] = 'P';
    }

    //Relleno las casillas vacias
    char anterior, siguiente, actual;
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            anterior = mapa_solucion_[i][j-1];
            siguiente = mapa_solucion_[i][j];
            actual = mapa_solucion_[i][j+1];
            if(actual == '?' && (anterior == 'B' || anterior == 'A')){
                while (siguiente == '?'){
                    mapa_solucion_[i][j] = anterior;
                    siguiente = mapa_solucion_[i][j+1];
                    j++;
                }
            }
        }
    }

    for(int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            if(mapa_solucion_[i][j] == '?')
                mapa_solucion_[i][j] = 'S';
        }
    }

    EscribirFichero();
}

void Agent::EscribirFichero(){
    cout << "Estas seguro de que todo esta bien? Vamos a verlo en un fichero! (salida.txt)" << endl;

    ofstream f;
    f.open("salida.txt");

    for(int i = 0; i < 200; i++){
        for(int j = 0; j < 200; j++)
            f << mapa_entorno_[i][j];
        f << endl;
    }
    f << endl << endl << endl;
    for(int i = 0; i < 200; i++){
        for(int j = 0; j < 200; j++)
            f << mapa_temporal_[i][j];
        f << endl;
    }
    f << endl << endl << endl;
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++)
            f << mapa_solucion_[i][j];
        f << endl;
    }
}

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	Agent::ActionType accion = actFORWARD; // Por defecto avanza

	if(PKListos && !rotado){
        cout << "Ya tengo los PKs listos" << endl;
        //ORIENTAR EL MAPA
        int f1, f2, c1, c2, aux;
        f1 = PK1_fila - PK2_fila;
        f2 = myPK1_fila - myPK2_fila;
        c1 = PK1_columna - PK2_columna;
        c2 = myPK1_columna - myPK2_columna;

        if(f1 == f2){
            orientacion_real = 0;
        }
        else if (f1 == -f2){
            cout << "Estamos al reves." << endl;
            orientacion_real = 1;

            myPK1_fila = 199 - myPK1_fila;
            myPK1_columna = 199 - myPK1_columna;
        }
        else if (f1 == c2){
            cout << "Girar 90 grados a la derecha." << endl;
            orientacion_real = 2;

            aux = myPK1_fila;
            myPK1_fila = myPK1_columna;
            myPK1_columna = aux;
            myPK1_columna = 199 - myPK1_columna;
        }
        else if (f1 == -c2){
            cout << "Girar 90 grados a la izquierda." << endl;
            orientacion_real = 3;

            aux = myPK1_fila;
            myPK1_fila = myPK1_columna;
            myPK1_columna = aux;
            myPK1_fila = 199 - myPK1_fila;
        }

        rotado = true;

        GuardarMapa();

        goto RestoMovimientos;
    }
    else if (SURFACE_[1] == 'q' || SURFACE_[2] == 'q' || SURFACE_[3] == 'q' ||
             SURFACE_[4] == 'q' || SURFACE_[5] == 'q' || SURFACE_[6] == 'q' ||
             SURFACE_[7] == 'q' || SURFACE_[8] == 'q' || SURFACE_[9] == 'q'){

        accion = actTURN_R;
        huir_oso = true;
        huir_oso2 = false;
        huir_oso3 = false;

        if (PKListos){
            GuardarMapa();
        }
    }
    else if(huir_oso){
        accion = actTURN_R;
        huir_oso = false;
        huir_oso2 = true;
        huir_oso3 = false;
    }
    else if (huir_oso2){
        if ((VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q')){
            accion = actFORWARD;
        }
        else{
            accion = actTURN_R;
        }

        huir_oso = false;
        huir_oso2 = false;
        huir_oso3 = true;
    }
    else if (huir_oso3){
        if (last_accion_ == actTURN_R && ((VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q'))){
            accion = actFORWARD;
        }
        else{
            huir_oso = false;
            huir_oso2 = false;
            huir_oso3 = false;
            goto RestoMovimientos;
        }
    }
    //PKs
    else if (VISTA_[0]=='K' && (last_accion_ != actTURN_L && last_accion_ != actTURN_R) && !PKListos){
        istringstream iss(MENSAJE_);
        string cad1, cad2, cad3;
        int f, c;
        iss >> cad1 >> cad2 >> f >> cad3 >> c;
        primerPK = true;

        if(primerPK && !primera_vez){
            PK1_fila = f;
            PK1_columna = c;
            myPK1_fila = y_;
            myPK1_columna = x_;
            cout << "PK1_fila " << PK1_fila << " PK1_columna " << PK1_columna << " myPK1_fila " << myPK1_fila << " myPK1_columna " << myPK1_columna << endl;
            primera_vez = true; primerPK = false; segundoPK = true;
        }
        else if (segundoPK){
            if(PK1_fila != f && PK1_columna != c){
                PK2_fila = f;
                PK2_columna = c;
                myPK2_fila = y_;
                myPK2_columna = x_;
                cout << "PK2_fila " << PK2_fila << " PK2_columna " << PK2_columna << " myPK2_fila " << myPK2_fila << " myPK2_columna " << myPK2_columna << endl;
                primerPK = false; segundoPK = false; PKListos = true;
            }
        }

        if(VISTA_[1]=='B' || VISTA_[1]=='P' || VISTA_[1]=='A' || VISTA_[1]=='M' || VISTA_[1]=='D'){
            if(rand()%2==0)
                accion = actTURN_R;
            else
                accion = actTURN_L;
        }
        else {
            accion = actFORWARD;
        }
    }
    else if ((VISTA_[1]=='K' || VISTA_[3]=='K' || VISTA_[7]=='K') && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q') && !PKListos){
        accion = actFORWARD;
    }
    else if ((VISTA_[4]=='K' || VISTA_[8]=='K' || VISTA_[9]=='K') && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q') && !PKListos){
        accion = actFORWARD;
        PK1_d = true;  PK2_d = false; PK3_d = false;
        PK1_i = false; PK2_i = false; PK3_i = false;
    }
    else if ((VISTA_[2]=='K' || VISTA_[5]=='K' || VISTA_[6]=='K') && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q') && !PKListos){
        accion = actFORWARD;
        PK1_d = false; PK2_d = false; PK3_d = false;
        PK1_i = true;  PK2_i = false; PK3_i = false;
    }
    //EL PK ESTA A LA DERECHA
    else if (PK1_d && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && !PKListos){
        accion = actTURN_R;
        PK1_d = false; PK2_d = true;  PK3_d = false;
        PK1_i = false; PK2_i = false; PK3_i = false;
    }
    else if (PK2_d && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q') && !PKListos){
        accion = actFORWARD;
        PK1_d = false; PK2_d = false; PK3_d = true;
        PK1_i = false; PK2_i = false; PK3_i = false;
    }
    else if (PK3_d && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && !PKListos){
        accion = actTURN_L;
        PK1_d = false; PK2_d = false; PK3_d = false;
        PK1_i = false; PK2_i = false; PK3_i = false;
    }
    //EL PK ESTA A LA IZQUIERDA
    else if (PK1_i && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && !PKListos){
        accion = actTURN_L;
        PK1_d = false; PK2_d = false; PK3_d = false;
        PK1_i = false; PK2_i = true;  PK3_i = false;
    }
    else if (PK2_i && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q') && !PKListos){
        accion = actFORWARD;
        PK1_d = false; PK2_d = false; PK3_d = false;
        PK1_i = false; PK2_i = false; PK3_i = true;
    }
    else if (PK3_i && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && !PKListos){
        accion = actTURN_R;
        PK1_d = false; PK2_d = false; PK3_d = false;
        PK1_i = false; PK2_i = false; PK3_i = false;
    }
    //COGER OBJETOS
    else if (objeto_cogido){
        accion = actPUSH;
        objeto_cogido = false;
        num_objetos++;
    }
	else if ((SURFACE_[0]=='4' || SURFACE_[0]=='5' || SURFACE_[0]=='8' || SURFACE_[0]=='9') && num_objetos < 4){
        accion = actPICKUP;
		objeto_cogido = true;
    }
    else if (((SURFACE_[1]=='4' || SURFACE_[1]=='5' || SURFACE_[1]=='8' || SURFACE_[1]=='9') ||
              (SURFACE_[3]=='4' || SURFACE_[3]=='5' || SURFACE_[3]=='8' || SURFACE_[3]=='9') ||
              (SURFACE_[7]=='4' || SURFACE_[7]=='5' || SURFACE_[7]=='8' || SURFACE_[7]=='9')) && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q') && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos < 4){
        accion = actFORWARD;
    }
	else if (((SURFACE_[4]=='4' || SURFACE_[4]=='5' || SURFACE_[4]=='8' || SURFACE_[1]=='9') ||
              (SURFACE_[8]=='4' || SURFACE_[8]=='5' || SURFACE_[8]=='8' || SURFACE_[8]=='9') ||
              (SURFACE_[9]=='4' || SURFACE_[9]=='5' || SURFACE_[9]=='8' || SURFACE_[9]=='9')) && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q') && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos < 4){
        accion = actFORWARD;
        obj1_d = true;  obj2_d = false; obj3_d = false;
        obj1_i = false; obj2_i = false; obj3_i = false;
    }
	else if (((SURFACE_[2]=='4' || SURFACE_[2]=='5' || SURFACE_[2]=='8' || SURFACE_[2]=='9') ||
              (SURFACE_[5]=='4' || SURFACE_[5]=='5' || SURFACE_[5]=='8' || SURFACE_[5]=='9') ||
              (SURFACE_[6]=='4' || SURFACE_[6]=='5' || SURFACE_[6]=='8' || SURFACE_[6]=='9')) && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q') && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos < 4){
        accion = actFORWARD;
        obj1_d = false; obj2_d = false; obj3_d = false;
        obj1_i = true;  obj2_i = false; obj3_i = false;
    }
    //EL OBJETO ESTA A LA DERECHA
    else if (obj1_d && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos < 4){
        accion = actTURN_R;
        obj1_d = false; obj2_d = true;  obj3_d = false;
        obj1_i = false; obj2_i = false; obj3_i = false;
    }
    else if (obj2_d && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos < 4 && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q')){
        accion = actFORWARD;
        obj1_d = false; obj2_d = false; obj3_d = true;
        obj1_i = false; obj2_i = false; obj3_i = false;
    }
    else if (obj3_d && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos < 4){
        accion = actTURN_L;
        obj1_d = false; obj2_d = false; obj3_d = false;
        obj1_i = false; obj2_i = false; obj3_i = false;
    }
    //EL OBJETO ESTA A LA IZQUIERDA
    else if (obj1_i && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos < 4){
        accion = actTURN_L;
        obj1_d = false; obj2_d = false; obj3_d = false;
        obj1_i = false; obj2_i = true;  obj3_i = false;
    }
    else if (obj2_i && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos < 4 && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q')){
        accion = actFORWARD;
        obj1_d = false; obj2_d = false; obj3_d = false;
        obj1_i = false; obj2_i = false; obj3_i = true;
    }
    else if (obj3_i && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos < 4){
        accion = actTURN_R;
        obj1_d = false; obj2_d = false; obj3_d = false;
        obj1_i = false; obj2_i = false; obj3_i = false;
    }
    //ENTREGAR OBJETOS
    else if ((SURFACE_[1] >= 'g' && SURFACE_[1] <= 'p') && num_objetos > 0 && he_sacado){
        accion = actGIVE;
        num_objetos--;
        he_sacado = false;
	}
	else if (MENSAJE_ == "No hay nadie a quien darle eso. "){
        accion = actPUSH;
        num_objetos++;
        he_sacado = false;
	}
    else if ((SURFACE_[1] >= 'g' && SURFACE_[1] <= 'p') && num_objetos > 0){
		accion = actPOP;
		he_sacado = true;
	}
	else if (((SURFACE_[3] >= 'g' && SURFACE_[3] <= 'p') || (SURFACE_[7] >= 'g' && SURFACE_[7] <= 'p')) && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos > 0){
        accion = actFORWARD;
    }
	else if (((SURFACE_[4] >= 'g' && SURFACE_[4] <= 'p') || (SURFACE_[8] >= 'g' && SURFACE_[8] <= 'p') || (SURFACE_[9] >= 'g' && SURFACE_[9] <= 'p')) && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos > 0){
        accion = actFORWARD;
        pj1_d = true;  pj2_d = false; pj3_d = false;
        pj1_i = false; pj2_i = false; pj3_i = false;
    }
	else if (((SURFACE_[2] >= 'g' && SURFACE_[2] <= 'p') || (SURFACE_[5] >= 'g' && SURFACE_[5] <= 'p') || (SURFACE_[6] >= 'g' && SURFACE_[6] <= 'p')) && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos > 0){
        accion = actFORWARD;
        pj1_d = false; pj2_d = false; pj3_d = false;
        pj1_i = true;  pj2_i = false; pj3_i = false;
    }
    //EL PERONAJE ESTA A LA DERECHA
    else if (pj1_d && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos > 0){
        accion = actTURN_R;
        pj1_d = false; pj2_d = true;  pj3_d = false;
        pj1_i = false; pj2_i = false; pj3_i = false;
    }
    else if (pj2_d && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos > 0 && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q')){
        accion = actFORWARD;
        pj1_d = false; pj2_d = false; pj3_d = true;
        pj1_i = false; pj2_i = false; pj3_i = false;
    }
    else if (pj3_d && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos > 0){
        accion = actTURN_L;
        pj1_d = false; pj2_d = false; pj3_d = false;
        pj1_i = false; pj2_i = false; pj3_i = false;
    }
    //EL PERONAJE ESTA A LA IZQUIERDA
    else if (pj1_i && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos > 0){
        accion = actTURN_L;
        pj1_d = false; pj2_d = false; pj3_d = false;
        pj1_i = false; pj2_i = true;  pj3_i = false;
    }
    else if (pj2_i && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos > 0 && (SURFACE_[1] < 'e' || SURFACE_[1] > 'q')){
        accion = actFORWARD;
        pj1_d = false; pj2_d = false; pj3_d = false;
        pj1_i = false; pj2_i = false; pj3_i = true;
    }
    else if (pj3_i && (VISTA_[1]!='B' && VISTA_[1]!='P' && VISTA_[1]!='A' && VISTA_[1]!='M' && VISTA_[1]!='D') && num_objetos > 0){
        accion = actTURN_R;
        pj1_d = false; pj2_d = false; pj3_d = false;
        pj1_i = false; pj2_i = false; pj3_i = false;
    }
    //RESTO DE ACCIONES
    //PULGARCITO NO HA PODIDO ELEGIR NINGUNA OPCION
    else if (ninguna_opcion){
        if (rand() % 2 == 0)
            accion = actTURN_L;
        else
            accion = actTURN_R;
        ninguna_opcion = false;
	}
    else {
        RestoMovimientos:
        izquierda = 30000;
        derecha = 30000;
        frente = 30000;

        if(orientacion_ == 0){
            if(mapa_entorno_[y_][x_-1] == 'B' || mapa_entorno_[y_][x_-1] == 'P' || mapa_entorno_[y_][x_-1] == 'A' ||
               mapa_entorno_[y_][x_-1] == 'M' || mapa_entorno_[y_][x_-1] == 'D' || (mapa_objetos_[y_][x_-1] >= 'e' && mapa_objetos_[y_][x_-1] <= 'q'))
                izquierda = 30000;
            else if(mapa_entorno_[y_][x_-1] == '?' && mapa_objetos_[y_][x_-1])
                izquierda = 0;
            else
                izquierda = pulgarcito[y_][x_-1];

            if(mapa_entorno_[y_][x_+1] == 'B' || mapa_entorno_[y_][x_+1] == 'P' || mapa_entorno_[y_][x_+1] == 'A' ||
               mapa_entorno_[y_][x_+1] == 'M' || mapa_entorno_[y_][x_+1] == 'D' || (mapa_objetos_[y_][x_+1] >= 'e' && mapa_objetos_[y_][x_+1] <= 'q'))
                derecha = 30000;
            else if(mapa_entorno_[y_][x_+1] == '?' && mapa_objetos_[y_][x_+1])
                derecha = 0;
            else
                derecha = pulgarcito[y_][x_+1];


            if(mapa_entorno_[y_-1][x_] == 'B' || mapa_entorno_[y_-1][x_] == 'P' || mapa_entorno_[y_-1][x_] == 'A' ||
               mapa_entorno_[y_-1][x_] == 'M' || mapa_entorno_[y_-1][x_] == 'D' || (mapa_objetos_[y_-1][x_] >= 'e' && mapa_objetos_[y_-1][x_] <= 'q'))
                frente = 30000;
            else if(mapa_entorno_[y_-1][x_] == '?' && mapa_objetos_[y_-1][x_])
                frente = 0;
            else
                frente = pulgarcito[y_-1][x_];
        }
        else if(orientacion_ == 1){
            if(mapa_entorno_[y_-1][x_] == 'B' || mapa_entorno_[y_-1][x_] == 'P' || mapa_entorno_[y_-1][x_] == 'A' ||
               mapa_entorno_[y_-1][x_] == 'M' || mapa_entorno_[y_-1][x_] == 'D' || (mapa_objetos_[y_-1][x_] >= 'e' && mapa_objetos_[y_-1][x_] <= 'q'))
                izquierda = 30000;
            else if(mapa_entorno_[y_-1][x_] == '?' && mapa_objetos_[y_-1][x_])
                izquierda = 0;
            else
                izquierda = pulgarcito[y_-1][x_];

            if(mapa_entorno_[y_+1][x_] == 'B' || mapa_entorno_[y_+1][x_] == 'P' || mapa_entorno_[y_+1][x_] == 'A' ||
               mapa_entorno_[y_+1][x_] == 'M' || mapa_entorno_[y_+1][x_] == 'D' || (mapa_objetos_[y_+1][x_] >= 'e' && mapa_objetos_[y_+1][x_] <= 'q'))
                derecha = 30000;
            else if(mapa_entorno_[y_+1][x_] == '?' && mapa_objetos_[y_+1][x_])
                derecha = 0;
            else
                derecha = pulgarcito[y_+1][x_];

            if(mapa_entorno_[y_][x_+1] == 'B' || mapa_entorno_[y_][x_+1] == 'P' || mapa_entorno_[y_][x_+1] == 'A' ||
               mapa_entorno_[y_][x_+1] == 'M' || mapa_entorno_[y_][x_+1] == 'D' || (mapa_objetos_[y_][x_+1] >= 'e' && mapa_objetos_[y_][x_+1] <= 'q'))
                frente = 30000;
            else if(mapa_entorno_[y_][x_+1] == '?' && mapa_objetos_[y_][x_+1])
                frente = 0;
            else
                frente = pulgarcito[y_][x_+1];
        }
        else if(orientacion_ == 2){
            if(mapa_entorno_[y_][x_+1] == 'B' || mapa_entorno_[y_][x_+1] == 'P' || mapa_entorno_[y_][x_+1] == 'A' ||
               mapa_entorno_[y_][x_+1] == 'M' || mapa_entorno_[y_][x_+1] == 'D' || (mapa_objetos_[y_][x_+1] >= 'e' && mapa_objetos_[y_][x_+1] <= 'q'))
                izquierda = 30000;
            else if(mapa_entorno_[y_][x_+1] == '?' && mapa_objetos_[y_][x_+1])
                izquierda = 0;
            else
                izquierda = pulgarcito[y_][x_+1];

            if(mapa_entorno_[y_][x_-1] == 'B' || mapa_entorno_[y_][x_-1] == 'P' || mapa_entorno_[y_][x_-1] == 'A' ||
               mapa_entorno_[y_][x_-1] == 'M' || mapa_entorno_[y_][x_-1] == 'D' || (mapa_objetos_[y_][x_-1] >= 'e' && mapa_objetos_[y_][x_-1] <= 'q'))
                derecha = 30000;
            else if(mapa_entorno_[y_][x_-1] == '?' && mapa_objetos_[y_][x_-1])
                derecha = 0;
            else
                derecha = pulgarcito[y_][x_-1];

            if(mapa_entorno_[y_+1][x_] == 'B' || mapa_entorno_[y_+1][x_] == 'P' || mapa_entorno_[y_+1][x_] == 'A' ||
               mapa_entorno_[y_+1][x_] == 'M' || mapa_entorno_[y_+1][x_] == 'D' || (mapa_objetos_[y_+1][x_] >= 'e' && mapa_objetos_[y_+1][x_] <= 'q'))
                frente = 30000;
            else if(mapa_entorno_[y_+1][x_] == '?' && mapa_objetos_[y_+1][x_])
                frente = 0;
            else
                frente = pulgarcito[y_+1][x_];
        }
        else if (orientacion_ == 3){
            if(mapa_entorno_[y_+1][x_] == 'B' || mapa_entorno_[y_+1][x_] == 'P' || mapa_entorno_[y_+1][x_] == 'A' ||
               mapa_entorno_[y_+1][x_] == 'M' || mapa_entorno_[y_+1][x_] == 'D' || (mapa_objetos_[y_+1][x_] >= 'e' && mapa_objetos_[y_+1][x_] <= 'q'))
                izquierda = 30000;
            else if(mapa_entorno_[y_+1][x_] == '?' && mapa_objetos_[y_+1][x_])
                izquierda = 0;
            else
                izquierda = pulgarcito[y_+1][x_];

            if(mapa_entorno_[y_-1][x_] == 'B' || mapa_entorno_[y_-1][x_] == 'P' || mapa_entorno_[y_-1][x_] == 'A' ||
               mapa_entorno_[y_-1][x_] == 'M' || mapa_entorno_[y_-1][x_] == 'D' || (mapa_objetos_[y_-1][x_] >= 'e' && mapa_objetos_[y_-1][x_] <= 'q'))
                derecha = 30000;
            else if(mapa_entorno_[y_-1][x_] == '?' && mapa_objetos_[y_-1][x_])
                derecha = 0;
            else
                derecha = pulgarcito[y_-1][x_];


            if(mapa_entorno_[y_][x_-1] == 'B' || mapa_entorno_[y_][x_-1] == 'P' || mapa_entorno_[y_][x_-1] == 'A' ||
               mapa_entorno_[y_][x_-1] == 'M' || mapa_entorno_[y_][x_-1] == 'D' || (mapa_objetos_[y_][x_-1] >= 'e' && mapa_objetos_[y_][x_-1] <= 'q'))
                frente = 30000;
            else if(mapa_entorno_[y_][x_-1] == '?' && mapa_objetos_[y_][x_-1])
                frente = 0;
            else
                frente = pulgarcito[y_][x_-1];
        }

        string puntos;
        for(int i = 0; i < 9; i++)
            if(PUNTUACION_[i] != NULL)
                puntos = puntos + PUNTUACION_[i];

        //Ya he comprobado el valor de pulgarcito para cada casilla, ahora decido a donde ir
        //pero si no puedo ir a ningun sitio, doy la vuelta
        if(frente == 30000 && izquierda == 30000 && derecha == 30000){
            if(rand() % 2 == 0)
                accion = actTURN_L;
            else
                accion = actTURN_R;
            ninguna_opcion = true;
        }
        else if (frente <= izquierda && frente <= derecha){
            accion = actFORWARD;
            cout << "IT: " << iteracion << ". PUNTUACION: " << puntos << ". MOV: REC. (I, D, F) = (" << izquierda << ", " << derecha << ", " << frente << ")" << endl;
        }
        else if(izquierda <= derecha && izquierda < frente){
            accion = actTURN_L;
            cout << "IT: " << iteracion << ". PUNTUACION: " << puntos << ". MOV: IZQ. (I, D, F) = (" << izquierda << ", " << derecha << ", " << frente << ")" << endl;
        }
        else if(derecha <= izquierda && derecha < frente){
            accion = actTURN_R;
            cout << "IT: " << iteracion << ". PUNTUACION: " << puntos << ". MOV: DER. (I, D, F) = (" << izquierda << ", " << derecha << ", " << frente << ")" << endl;
        }
    }

    if(accion == actFORWARD)
        pulgarcito[y_][x_]=iteracion;

    if (iteracion == 10000 || iteracion == 19998){
        cout << "Estamos acabando, a guardar el trabajo realizado!" << endl;
        if(PKListos){
            GuardarMapa();
        }
    }

    if (iteracion == 19998){
        cout << "Trabajo guardado! Ahora vamos a ganar unos puntos extras!" << endl;
        RellenarMapa();
    }

	// recuerdo la ultima accion realizada
	last_accion_ = accion;

	iteracion++;

	return accion;

}
