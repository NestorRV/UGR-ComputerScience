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

void _triangulos3D::examen(float r1, float g1, float b1, float r2, float g2, float b2){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	int contador = 0;

		for(int i = 0; i < caras.size(); i++){
			if(contador == 4)
				contador = 0;
			if(contador < 2){
				glColor3f(r1, g1, b1);
				contador++;
			}
			else{
				glColor3f(r2, g2, b2);
				contador++;
			}
			if(i < (caras.size() - 10) && i >= (caras.size() - 20)){
				glColor3f(r1, g1, b1);
			}
			else if(i < caras.size() && i >= (caras.size() - 10)){
				glColor3f(r2, g2, b2);
			}
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

_objeto_ply::_objeto_ply(){

}

int _objeto_ply::parametros (char *archivo){
	int n_ver, n_car;
	vector<float> ver_ply;
	vector<int> car_ply;
	_file_ply ply;
	ply.open(archivo);
	ply.read(ver_ply, car_ply);
	n_ver = ver_ply.size()/3;
	n_car = car_ply.size()/3;
	cout << "Numero de vertices: " << n_ver << " Numero de caras: " << n_car << endl;

	vertices.resize(n_ver);
	caras.resize(n_car);

	_vertex3f ver_aux;
	_vertex3i car_aux;

	for (int i = 0; i<n_ver;i++){
		ver_aux.x = ver_ply[i*3];
		ver_aux.y = ver_ply[i*3+1];
		ver_aux.z = ver_ply[i*3+2];
		vertices[i] = ver_aux;
	}

	for (int i = 0; i<n_car;i++){
		car_aux.x = car_ply[i*3];
		car_aux.y = car_ply[i*3+1];
		car_aux.z = car_ply[i*3+2];
		caras[i]=car_aux;
	}
}

_rotacion::_rotacion(){}

void _rotacion::parametros(vector<_vertex3f> perfil, int num){
	int i, j, num_aux;
	_vertex3f vertice_aux, tapa_arriba, tapa_abajo;
	_vertex3i cara_aux, tapa_arriba_aux, tapa_abajo_aux;
	int v1, v2, v3, v4, v5, v6;

	num_aux = perfil.size();
	for(int i = 0; i<num; i++){
		for(int j = 0; j<num_aux; j++){
			vertice_aux.x = perfil[j].x*cos(2.0*M_PI*i/(1.0*num))-perfil[j].z*sin(2.0*M_PI*i/(1.0*num));
			vertice_aux.y = perfil[j].y;
			vertice_aux.z = perfil[j].x*sin(2.0*M_PI*i/(1.0*num))+perfil[j].z*cos(2.0*M_PI*i/(1.0*num));
			vertices.push_back(vertice_aux);
		}
	}

	//Tratamiento de las caras
	for(int i = 0; i < num_aux-1; i++){
		for(int j = 0; j < num-1; j++){
			v1 = i+j*num_aux;
			v2 = i+(j+1)*num_aux;
			v3 = (i+1)+j*num_aux;
			v4 = i+1+(j+1)*num_aux;

			cara_aux._0 = v1;
			cara_aux._1 = v2;
			cara_aux._2 = v3;
			caras.push_back(cara_aux);
			cara_aux._0 = v2;
			cara_aux._1 = v4;
			cara_aux._2 = v3;
			caras.push_back(cara_aux);
		}

		cara_aux._0 = v2;
		cara_aux._1 = i;
		cara_aux._2 = v4;
		caras.push_back(cara_aux);
		cara_aux._0 = v4;
		cara_aux._1 = i;
		cara_aux._2 = i+1;
		caras.push_back(cara_aux);
	}

	tapa_arriba.x = 0;
	tapa_arriba.y = perfil[0].y;
	tapa_arriba.z = 0;

	tapa_abajo.x = 0;
	tapa_abajo.y = perfil[perfil.size()-1].y;
	tapa_abajo.z = 0;

	vertices.push_back(tapa_arriba);
	vertices.push_back(tapa_abajo);

	//Tapa superior
	for(int i = 0; i < num; i++){
		v5 = i*num_aux;
		v6 = (i+1)*num_aux;
		tapa_arriba_aux._0 = v5;
		tapa_arriba_aux._1 = vertices.size()-2;
		tapa_arriba_aux._2 = v6;
		caras.push_back(tapa_arriba_aux);
	}

	tapa_arriba_aux._0 = v5;
	tapa_arriba_aux._1 = vertices.size()-2;
	tapa_arriba_aux._2 = 0;
	caras.push_back(tapa_arriba_aux);

	//Tapa inferior
	for(int i = 0; i < num; i++){
		v5 = num_aux*i-1;
		v6 = (num_aux*(i+1))-1;
		tapa_abajo_aux._0 = v6;
		tapa_abajo_aux._1 = vertices.size()-1;
		tapa_abajo_aux._2 = v5;
		caras.push_back(tapa_abajo_aux);
	}

	tapa_abajo_aux._0 = perfil.size()-1;
	tapa_abajo_aux._1 = vertices.size()-1;
	tapa_abajo_aux._2 = v6;
	caras.push_back(tapa_abajo_aux);
}
