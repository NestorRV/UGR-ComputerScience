#include <vector>
#include <GL/glu.h>
#include "vertex.h"
#include <stdlib.h>
#include <cmath>
#include "objetos.h"
#include <unistd.h> //usleep

class _modelo {
public:
   _modelo();
   //Elementos básicos
   void Cubo(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor);
   void Cilindro(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor);
   //Dibujar la escena
   void Brazo1(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor);
   void Brazo2(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor);
   void Base(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor);
   void drawModelo(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor);
   //Controlar movimiento
   void rotacionCuboMas();
   void rotacionCuboMenos();
   void anguloPenduloMas();
   void anguloPenduloMenos();
   void subirEstructura();
   void bajarEstructura();
   void rotarBrazoMas();
   void rotarBrazoMenos();
   void setMovimiento(bool mov);

   //Variables para controlar el movimiento
   int rotacionCubo;
   int angulo;
   double altura;
   int rotacionBrazo;
   bool movimiento;
};
