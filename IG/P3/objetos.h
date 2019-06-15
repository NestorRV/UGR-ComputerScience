//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include <cmath>
#include "file_ply_stl.h"

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D {
	public:
		_puntos3D();
		vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D : public _puntos3D {
	public:
		_triangulos3D();
		void draw_triangulos(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor);
		vector<_vertex3i> caras;
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
// clase objeto_ply
//*************************************************************************

class _objeto_ply : public _triangulos3D {
public:
	_objeto_ply();
	int parametros (char *archivo);
};

//*************************************************************************
// clase rotacion
//*************************************************************************

class _rotacion : public _triangulos3D{
public:
	_rotacion();
	//num1 : numero de gajos del objeto por revolución
	void parametros(vector<_vertex3f> perfil1, int num1);
	void draw(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor);
	vector<_vertex3f> perfil;
	int num;
};
