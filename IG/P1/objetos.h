//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include <cmath>

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D {
	public:
		_puntos3D();
		void draw_puntos(float r, float g, float b, int grosor);
		vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D : public _puntos3D {
	public:
		_triangulos3D();
		void draw_aristas(float r, float g, float b, int grosor);
		void draw_solido(float r, float g, float b);
		void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
		void draw_aleatorio();
		vector<_vertex3i> caras;
		vector<_vertex3f> colores;

};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo : public _triangulos3D {
	public:
		_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide : public _triangulos3D {
	public:
		_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase tetraedro
//*************************************************************************

class _tetraedro : public _triangulos3D {
	public:
		_tetraedro(float tam=0.5);
};

//*************************************************************************
// clase tronco_piramide
//*************************************************************************

class _tronco_piramide : public _triangulos3D {
	public:
		_tronco_piramide(float tam=1, float tam2=0.3, float altura=1);
};
