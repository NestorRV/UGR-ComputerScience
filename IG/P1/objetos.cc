#include "objetos.h"

//********************* Clase Puntos3D *********************

_puntos3D::_puntos3D(){}

void _puntos3D::draw_puntos(float r, float g, float b, int grosor){
	glPointSize(grosor);
	glColor3f(r, g, b);
	glBegin(GL_POINTS);

		for(int i = 0; i < vertices.size(); i++){
			glVertex3fv((GLfloat *) &vertices[i]);
		}

	glEnd();
}

//********************* Clase Triangulos3D *********************

_triangulos3D::_triangulos3D(){}

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor){
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(grosor);
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);

	for(int i = 0; i < caras.size(); i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}

	glEnd();
}

void _triangulos3D::draw_solido(float r, float g, float b){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
		for(int i = 0; i < caras.size(); i++){
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}

	glEnd();
}

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);

		for(int i = 0; i < caras.size(); i++){
			if(i % 2 == 0){
				glColor3f(r1, g1, b1);
			}
			else{
				glColor3f(r2, g2, b2);
			}
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}

	glEnd();
}

void _triangulos3D::draw_aleatorio(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	float r, g, b;

	glBegin(GL_TRIANGLES);
		for(int i = 0; i < caras.size(); i++){
			r = colores[i].x;
			g = colores[i].y;
			b = colores[i].z;
			glColor3f(r, g, b);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}

	glEnd();
}

//********************* Clase Tetraedro *********************

_tetraedro::_tetraedro(float tam) {
	vertices.resize(4);
	vertices[0].x = 0; vertices[0].y = 0; vertices[0].z = (sqrt(3)*tam)/3;
	vertices[1].x = tam/2; vertices[1].y = 0; vertices[1].z = -(sqrt(3)*(tam))/3;
	vertices[2].x = -tam/2; vertices[2].y = 0; vertices[2].z = -(sqrt(3)*(tam))/3;
	vertices[3].x = 0; vertices[3].y = (sqrt(6)/3)*tam; vertices[3].z = 0;

	caras.resize(4);
	caras[0]._0 = 0; caras[0]._1 = 1; caras[0]._2 = 3;
	caras[1]._0 = 1; caras[1]._1 = 2; caras[1]._2 = 3;
	caras[2]._0 = 2; caras[2]._1 = 0; caras[2]._2 = 3;
	caras[3]._0 = 1; caras[3]._1 = 0; caras[3]._2 = 2;
}

//********************* Clase Piramide *********************

_piramide::_piramide(float tam, float al) {
	vertices.resize(5);
	vertices[0].x = -tam; vertices[0].y = 0; vertices[0].z = tam;
	vertices[1].x = tam; vertices[1].y = 0; vertices[1].z = tam;
	vertices[2].x = tam; vertices[2].y = 0; vertices[2].z = -tam;
	vertices[3].x = -tam; vertices[3].y = 0; vertices[3].z = -tam;
	vertices[4].x = 0; vertices[4].y = al; vertices[4].z = 0;

	caras.resize(6);
	caras[0]._0 = 0; caras[0]._1 = 1; caras[0]._2 = 4;
	caras[1]._0 = 1; caras[1]._1 = 2; caras[1]._2 = 4;
	caras[2]._0 = 2; caras[2]._1 = 3; caras[2]._2 = 4;
	caras[3]._0 = 3; caras[3]._1 = 0; caras[3]._2 = 4;
	caras[4]._0 = 3; caras[4]._1 = 1; caras[4]._2 = 0;
	caras[5]._0 = 3; caras[5]._1 = 2; caras[5]._2 = 1;
}

//********************* Clase Cubo *********************

_cubo::_cubo(float tam){
	vertices.resize(8);

	vertices[0].x = tam/2; vertices[0].y = tam; vertices[0].z = tam/2;
	vertices[1].x = -tam/2; vertices[1].y = tam; vertices[1].z = tam/2;
	vertices[2].x = -tam/2; vertices[2].y = 0; vertices[2].z = tam/2;
	vertices[3].x = tam/2; vertices[3].y = 0; vertices[3].z = tam/2;
	vertices[4].x = tam/2; vertices[4].y = tam; vertices[4].z = -tam/2;
	vertices[5].x = -tam/2; vertices[5].y = tam; vertices[5].z = -tam/2;
	vertices[6].x = -tam/2; vertices[6].y = 0; vertices[6].z = -tam/2;
	vertices[7].x = tam/2; vertices[7].y = 0; vertices[7].z = -tam/2;

	caras.resize(12);
	caras[0]._0 = 3; caras[0]._1 = 0; caras[0]._2 = 1;
	caras[1]._0 = 3; caras[1]._1 = 1; caras[1]._2 = 2;
	caras[2]._0 = 7; caras[2]._1 = 4; caras[2]._2 = 0;
	caras[3]._0 = 7; caras[3]._1 = 0; caras[3]._2 = 3;
	caras[4]._0 = 6; caras[4]._1 = 5; caras[4]._2 = 4;
	caras[5]._0 = 6; caras[5]._1 = 4; caras[5]._2 = 7;
	caras[6]._0 = 2; caras[6]._1 = 1; caras[6]._2 = 5;
	caras[7]._0 = 2; caras[7]._1 = 5; caras[7]._2 = 6;
	caras[8]._0 = 4; caras[8]._1 = 5; caras[8]._2 = 1;
	caras[9]._0 = 0; caras[9]._1 = 5; caras[9]._2 = 1;
	caras[10]._0 = 2; caras[10]._1 = 6; caras[10]._2 = 7;
	caras[11]._0 = 2; caras[11]._1 = 7; caras[11]._2 = 3;
}

//********************* Clase Tronco Piramide *********************

_tronco_piramide::_tronco_piramide(float tam, float tam2, float altura){
	vertices.resize(8);
	vertices[0].x = -tam; vertices[0].y = 0; vertices[0].z = tam;
	vertices[1].x = tam; vertices[1].y = 0; vertices[1].z = tam;
	vertices[2].x = tam; vertices[2].y = 0; vertices[2].z = -tam;
	vertices[3].x = -tam; vertices[3].y = 0; vertices[3].z = -tam;

	vertices[4].x = -tam2; vertices[4].y = altura; vertices[4].z = tam2;
	vertices[5].x = tam2; vertices[5].y = altura; vertices[5].z = tam2;
	vertices[6].x = tam2; vertices[6].y = altura; vertices[6].z = -tam2;
	vertices[7].x = -tam2; vertices[7].y = altura; vertices[7].z = -tam2;


	caras.resize(16);
	//Frente
	caras[0]._0 = 0; caras[0]._1 = 1; caras[0]._2 = 4;
	caras[1]._0 = 1; caras[1]._1 = 5; caras[1]._2 = 4;
	//Derecha
	caras[2]._0 = 1; caras[2]._1 = 2; caras[2]._2 = 5;
	caras[3]._0 = 2; caras[3]._1 = 6; caras[3]._2 = 5;
	//Izquierda
	caras[4]._0 = 3; caras[4]._1 = 0; caras[4]._2 = 7;
	caras[5]._0 = 0; caras[5]._1 = 4; caras[5]._2 = 7;
	//Detras
	caras[6]._0 = 7; caras[6]._1 = 6; caras[6]._2 = 2;
	caras[7]._0 = 7; caras[7]._1 = 2; caras[7]._2 = 3;
	//Arriba
	caras[8]._0 = 4; caras[8]._1 = 5; caras[8]._2 = 7;
	caras[9]._0 = 5; caras[9]._1 = 6; caras[9]._2 = 7;
	//Abajo
	caras[10]._0 = 0; caras[10]._1 = 3; caras[10]._2 = 2;
	caras[11]._0 = 0; caras[11]._1 = 2; caras[11]._2 = 1;

	colores.resize(12);
	colores[0].x = rand()/(RAND_MAX + 1.0); colores[0].y = rand()/(RAND_MAX + 1.0); colores[0].z = rand()/(RAND_MAX + 1.0);
	colores[1].x = rand()/(RAND_MAX + 1.0); colores[1].y = rand()/(RAND_MAX + 1.0); colores[1].z = rand()/(RAND_MAX + 1.0);
	colores[2].x = rand()/(RAND_MAX + 1.0); colores[2].y = rand()/(RAND_MAX + 1.0); colores[2].z = rand()/(RAND_MAX + 1.0);
	colores[3].x = rand()/(RAND_MAX + 1.0); colores[3].y = rand()/(RAND_MAX + 1.0); colores[3].z = rand()/(RAND_MAX + 1.0);
	colores[4].x = rand()/(RAND_MAX + 1.0); colores[4].y = rand()/(RAND_MAX + 1.0); colores[4].z = rand()/(RAND_MAX + 1.0);
	colores[5].x = rand()/(RAND_MAX + 1.0); colores[5].y = rand()/(RAND_MAX + 1.0); colores[5].z = rand()/(RAND_MAX + 1.0);
	colores[6].x = rand()/(RAND_MAX + 1.0); colores[6].y = rand()/(RAND_MAX + 1.0); colores[6].z = rand()/(RAND_MAX + 1.0);
	colores[7].x = rand()/(RAND_MAX + 1.0); colores[7].y = rand()/(RAND_MAX + 1.0); colores[7].z = rand()/(RAND_MAX + 1.0);
	colores[8].x = rand()/(RAND_MAX + 1.0); colores[8].y = rand()/(RAND_MAX + 1.0); colores[8].z = rand()/(RAND_MAX + 1.0);
	colores[9].x = rand()/(RAND_MAX + 1.0); colores[9].y = rand()/(RAND_MAX + 1.0); colores[9].z = rand()/(RAND_MAX + 1.0);
	colores[10].x = rand()/(RAND_MAX + 1.0); colores[10].y = rand()/(RAND_MAX + 1.0); colores[10].z = rand()/(RAND_MAX + 1.0);
	colores[11].x = rand()/(RAND_MAX + 1.0); colores[11].y = rand()/(RAND_MAX + 1.0); colores[11].z = rand()/(RAND_MAX + 1.0);
}
