//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "vertex.h"
#include <stdlib.h>
#include <cmath>
#include "file_ply_stl.h"
#include "jpg_imagen.hpp"

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
		void draw_iluminacion_plana();
		void draw_iluminacion_suave();
		void calcular_normales_caras();
		void calcular_normales_vertices();

		void draw_textura(GLuint ident_textura, jpg::Imagen * imagen);
		void draw_textura_ilum_plana(GLuint ident_textura, jpg::Imagen * imagen);
		void draw_textura_ilum_suave(GLuint ident_textura, jpg::Imagen * imagen);
		void setAmbienteDifusa(const _vertex4f &amb);
		void setEspecular(const _vertex4f &esp);
		void setBrillo(const float &bri);

		void draw_normales_caras();
		void draw_normales_vertices();

		bool b_normales_caras, b_normales_vertices, b_textura_coord;
		vector<_vertex3i> caras;
		vector<_vertex3f> normales_caras;
		vector<_vertex3f> normales_vertices;
		vector<_vertex2f> text_coord;
		vector<pair<_vertex3f,_vertex3f> > normales_caras_dibujados;
    	vector<pair<_vertex3f,_vertex3f> > normales_vertices_dibujados;

		_vertex4f ambiente_difusa, especular;
		float brillo;
		bool modo_text;
		GLfloat plano_s[4], plano_t[4];
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
	_objeto_ply(char *archivo);
};

//*************************************************************************
// clase rotacion
//*************************************************************************

class _rotacion : public _triangulos3D{
public:
	_rotacion();
	//num1 : numero de gajos del objeto por revolución
	_rotacion(vector<_vertex3f> perfil1, int num1);
	void parametros(vector<_vertex3f> perfil1, int num1);
	void draw(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor);
	vector<_vertex3f> perfil;
	int num;
};

//*************************************************************************
// clase rotacion_tex
//*************************************************************************

class _rotacion_tex : public _triangulos3D {
public:
  _rotacion_tex();
  _rotacion_tex(vector<_vertex3f> ver, int num_caras);
};

//*************************************************************************
// clase textura
//*************************************************************************

class textura : public _triangulos3D{
public:
	textura();
	textura(const char * archivoJPG);

	GLuint ident_textura;
	jpg::Imagen * imagen;
};
