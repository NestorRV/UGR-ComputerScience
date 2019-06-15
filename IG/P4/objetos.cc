#include "objetos.h"

//********************* Clase Puntos3D *********************

_puntos3D::_puntos3D(){}

//********************* Clase Triangulos3D *********************

_triangulos3D::_triangulos3D(){
	b_normales_caras = false;
	b_normales_vertices = false;
	b_textura_coord = false;

	ambiente_difusa._0 = 1.0;
	ambiente_difusa._1 = 1.0;
	ambiente_difusa._2 = 1.0;
	ambiente_difusa._3 = 1.0;
	especular._0 = 1.0;
	especular._1 = 1.0;
	especular._2 = 1.0;
	especular._3 = 1.0;
	brillo = 35;
	modo_text = true;
	for(int i = 0; i< 4;i++){
		plano_s[i]=0.0;
		plano_t[i]=0.0;
	}

	plano_t[1] = 1.0;
	plano_s[0] = 1.0;
}

void _triangulos3D::draw_triangulos(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor){
		switch (modo) {
			case 'p':
				glPointSize(grosor);
				glColor3f(r1, g1, b1);
				glBegin(GL_POINTS);
				for(int i = 0; i < vertices.size(); i++)
					glVertex3fv((GLfloat *) &vertices[i]);
				glEnd();
				break;
			case 'l':
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glLineWidth(grosor);
				glColor3f(r1, g1, b1);
				glBegin(GL_TRIANGLES);
				for(int i = 0; i < caras.size(); i++){
					glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
					glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
					glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
				}
				glEnd();
				break;
			case 's':
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glColor3f(r1, g1, b1);
				glBegin(GL_TRIANGLES);
				for(int i = 0; i < caras.size(); i++){
					glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
					glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
					glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
				}
				glEnd();
				break;
			case 'a':
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
				break;
		}
}

void _triangulos3D::calcular_normales_caras(){
	_vertex3f v1, v2, p_vect;
	vector<pair<_vertex3f,_vertex3f> > v_aux2(caras.size());
	float modulo;
	normales_caras.resize(caras.size());
	for (int i=0; i<caras.size();i++){
		v1 = vertices[caras[i]._1] - vertices[caras[i]._0];
		v2 = vertices[caras[i]._2] - vertices[caras[i]._0];
		p_vect = v1.cross_product(v2);

		modulo = sqrt(p_vect.x*p_vect.x + p_vect.y*p_vect.y + p_vect.z*p_vect.z);
		normales_caras[i] = _vertex3f(p_vect.x/modulo, p_vect.y/modulo, p_vect.z/modulo);

		// Calculo centroide
		v_aux2[i].first.x = (vertices[caras[i]._0].x + vertices[caras[i]._1].x + vertices[caras[i]._2].x)/3;
		v_aux2[i].first.y = (vertices[caras[i]._0].y + vertices[caras[i]._1].y + vertices[caras[i]._2].y)/3;
		v_aux2[i].first.z = (vertices[caras[i]._0].z + vertices[caras[i]._1].z + vertices[caras[i]._2].z)/3;
		// Calculo punto que pase por la normal y el centroide
		v_aux2[i].second.x = v_aux2[i].first.x + 0.5*normales_caras[i].x;
		v_aux2[i].second.y = v_aux2[i].first.y + 0.5*normales_caras[i].y;
		v_aux2[i].second.z = v_aux2[i].first.z + 0.5*normales_caras[i].z;
	}
	b_normales_caras=true;
	normales_caras_dibujados = v_aux2;
}

void _triangulos3D::calcular_normales_vertices(){
	_vertex3f aux(0,0,0);   // vertex nulo (posicionado en el origen)
	pair<_vertex3f,_vertex3f> aux2; aux2.first = aux; aux2.second = aux;

  normales_vertices.resize(vertices.size());
  vector<pair<_vertex3f,_vertex3f> > v_aux2(vertices.size());

  if (b_normales_caras == false)
	  calcular_normales_caras();

  for (int i=0; i<vertices.size(); i++){
	  normales_vertices[i].x = 0.0;
	  normales_vertices[i].y = 0.0;
	  normales_vertices[i].z = 0.0;
  }

  for (int i=0; i<caras.size(); i++){
	  normales_vertices[caras[i]._0] += normales_caras[i];
	  normales_vertices[caras[i]._1] += normales_caras[i];
	  normales_vertices[caras[i]._2] += normales_caras[i];
  }

  for(int i=0; i<vertices.size(); i++){
		normales_vertices[i].normalize();
		// Calculo centroide, en caso de los puntos, el propio punto
		v_aux2[i].first.x = vertices[i].x;
		v_aux2[i].first.y = vertices[i].y;
		v_aux2[i].first.z = vertices[i].z;
		// Calculo punto que pase por la normal y el centroide
		v_aux2[i].second.x = v_aux2[i].first.x + 0.5*normales_vertices[i].x;
		v_aux2[i].second.y = v_aux2[i].first.y + 0.5*normales_vertices[i].y;
		v_aux2[i].second.z = v_aux2[i].first.z + 0.5*normales_vertices[i].z;
  }
  b_normales_vertices=true;
  normales_vertices_dibujados = v_aux2;
}

void _triangulos3D::draw_iluminacion_plana(){
	if(b_normales_caras==false)
		calcular_normales_caras();
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glShadeModel(GL_FLAT);
 	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
		for(int i=0; i<caras.size(); i++){
			glNormal3fv((GLfloat *) &normales_caras[i]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
	glDisable(GL_LIGHTING);
}

void _triangulos3D::draw_iluminacion_suave(){
	if(b_normales_vertices==false)
		calcular_normales_vertices();
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
		for(int i=0; i<caras.size(); i++)		{
			glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
	glDisable(GL_LIGHTING);
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

_objeto_ply::_objeto_ply(char *file){
	vector<float> v;
	vector<int> c;
	_file_ply fichero;
	fichero.open(file);
	fichero.read(v,c);

	_vertex3f vert;
	for (int i=0; i<v.size(); i+=3){
		vert.x = v[i];
		vert.y = v[i+1];
		vert.z = v[i+2];
		vertices.push_back(vert);
	}

	_vertex3i car;
	for (int i=0; i<c.size(); i+=3){
		car.x = c[i];
		car.y = c[i+1];
		car.z = c[i+2];
		caras.push_back(car);
	}

	float max_x, min_x, max_y, min_y;
	max_x = min_x = vertices[0].x;
	max_y = min_y = vertices[0].y;

	for (int i=0; i<v.size(); i++){
		if(vertices[i].x > max_x)
			max_x=vertices[i].x;
		if(vertices[i].x < min_x)
			min_x=vertices[i].x;
		if(vertices[i].y > max_y)
			max_y=vertices[i].y;
		if(vertices[i].y < min_y)
			min_y=vertices[i].y;
	}

	plano_s[0] /= (max_x-min_x);
	plano_t[1] /= (max_y-min_y);
}

_rotacion::_rotacion(){}

_rotacion::_rotacion(vector<_vertex3f> perfil, int num){
	int i, j, num_aux;
	_vertex3f vertice_aux;
	_vertex3i caras_aux;

	num_aux = perfil.size();
	vertices.resize(num_aux * num);
	for(j = 0; j < num; j++) {
		for(i = 0; i < num_aux; i++) {
			vertice_aux.x = perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
			vertice_aux.y = perfil[i].y;
			vertice_aux.z = perfil[i].z*cos(2.0*M_PI*j/(1.0*num))-perfil[i].x*sin(2.0*M_PI*j/(1.0*num));
			vertices[i+j*num_aux] = vertice_aux;
		}
	}

	// caras
	for(j=0; j<num; j++){
		for(i=0; i<num_aux-1; i++){
			caras_aux._0=i+((j+1)%num)*num_aux;
			caras_aux._1=i+1+((j+1)%num)*num_aux;
			caras_aux._2=i+1+j*num_aux;
			caras.push_back(caras_aux);

			caras_aux._0=i+1+j*num_aux;
			caras_aux._1=i+j*num_aux;
			caras_aux._2=i+((j+1)%num)*num_aux;
			caras.push_back(caras_aux);
		}
	}

	// tapa inferior
	if (fabs(perfil[num_aux-1].x)>0.0) {
		vertice_aux.y=perfil[num_aux-1].y;
		vertice_aux.x=0.0;
		vertice_aux.z=0.0;
		vertices.push_back(vertice_aux);

		caras_aux._0=num_aux*num;

		for (int i=0; i<num; i++) {
			caras_aux._1=(i+1)*num_aux-1;
			caras_aux._2=((i+1)%num)*num_aux+num_aux-1;
			caras.push_back(caras_aux);
		}
	}

	// tapa superior
	if (fabs(perfil[0].x) > 0.0) {
		vertice_aux.y=perfil[0].y;
		vertice_aux.x=0.0;
		vertice_aux.z=0.0;
		vertices.push_back(vertice_aux);

		caras_aux._0=num_aux*num+1;

		for (int i=0; i<num; i++) {
			caras_aux._1=((i+1)%num)*num_aux;
			caras_aux._2=i*num_aux;
			caras.push_back(caras_aux);
		}
	}
}

void _rotacion::parametros(vector<_vertex3f> perfil, int num){
	int i, j, num_aux;
	_vertex3f vertice_aux;
	_vertex3i caras_aux;

	num_aux = perfil.size();
	vertices.resize(num_aux * num);
	for(j = 0; j < num; j++) {
		for(i = 0; i < num_aux; i++) {
			vertice_aux.x = perfil[i].x * cos(2.0*M_PI*j/(1.0*num))+perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
			vertice_aux.y = perfil[i].y;
			vertice_aux.z = perfil[i].z * cos(2.0*M_PI*j/(1.0*num))-perfil[i].x*sin(2.0*M_PI*j/(1.0*num));
			vertices[i+j*num_aux] = vertice_aux;
		}
	}

	// caras
	for(j=0; j<num; j++){
		for(i=0; i<num_aux-1; i++){
			caras_aux._0=i+((j+1)%num)*num_aux;
			caras_aux._1=i+1+((j+1)%num)*num_aux;
			caras_aux._2=i+1+j*num_aux;
			caras.push_back(caras_aux);

			caras_aux._0=i+1+j*num_aux;
			caras_aux._1=i+j*num_aux;
			caras_aux._2=i+((j+1)%num)*num_aux;
			caras.push_back(caras_aux);
		}
	}

	// tapa inferior
	if (fabs(perfil[num_aux-1].x)>0.0) {
		vertice_aux.y=perfil[num_aux-1].y;
		vertice_aux.x=0.0;
		vertice_aux.z=0.0;
		vertices.push_back(vertice_aux);

		caras_aux._0=num_aux*num;

		for (int i=0; i<num; i++) {
			caras_aux._1=(i+1)*num_aux-1;
			caras_aux._2=((i+1)%num)*num_aux+num_aux-1;
			caras.push_back(caras_aux);
		}
	}

	// tapa superior
	if (fabs(perfil[0].x) > 0.0) {
		vertice_aux.y=perfil[0].y;
		vertice_aux.x=0.0;
		vertice_aux.z=0.0;
		vertices.push_back(vertice_aux);

		caras_aux._0=num_aux*num+1;

		for (int i=0; i<num; i++) {
			caras_aux._1=((i+1)%num)*num_aux;
			caras_aux._2=i*num_aux;
			caras.push_back(caras_aux);
		}
	}
}

void _rotacion::draw(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor){
	draw_triangulos(modo, r1, g1, b1, r2, g2, b2, grosor);
}

_rotacion_tex::_rotacion_tex(){}

_rotacion_tex::_rotacion_tex(vector<_vertex3f> ver, int num_caras){
	_vertex3f vertices_aux;
	_vertex3i caras_aux;
	_vertex2f tex_aux;
	int num_aux;
	vector <float> distancias;
	float alfa = 2*3.1416/num_caras;
	float alfa_aux = 2*3.1416/num_caras;
	float distancia_total = 0.0;

	num_aux = ver.size();

	for(int i=0; i<num_aux-1; ++i) {
	distancias.push_back(distancia_total);
	distancia_total += sqrt((ver[i].x-ver[i+1].x)*(ver[i].x-ver[i+1].x)+
			           (ver[i].y-ver[i+1].y)*(ver[i].y-ver[i+1].y)+
			           (ver[i].z-ver[i+1].z)*(ver[i].z-ver[i+1].z));
	}

	for(int i=0;i<num_aux-1;++i) {
		distancias[i] = 1.0-distancias[i]/distancia_total;
	}

	distancias[0] = 1.0;
	distancias.push_back(0.0);

	for(int j=0; j<num_caras+1; ++j) {
		tex_aux.s=j/(1.0*num_caras);
		for(int i=0; i<num_aux; i++) {
			vertices_aux.x = ver[i].x * cos(alfa);
			vertices_aux.z = -ver[i].x * sin(alfa);
			vertices_aux.y = ver[i].y;
			vertices.push_back(vertices_aux);

			tex_aux.t=distancias[i];
			text_coord.push_back(tex_aux);
		}
		alfa += alfa_aux;
	}

	// Asignación manual de coordenadas de textura
	modo_text = false;
	b_textura_coord = true;

	// Tratamiento de las caras
	for(int j=0; j<num_caras; j++) {
	for(int i=0; i<num_aux-1; i++) {
	caras_aux._0=i+(j+1)*num_aux;
	caras_aux._1=i+1+(j+1)*num_aux;
	caras_aux._2=i+1+j*num_aux;
	caras.push_back(caras_aux);

	caras_aux._0=i+1+j*num_aux;
	caras_aux._1=i+j*num_aux;
	caras_aux._2=i+(j+1)*num_aux;
	caras.push_back(caras_aux);
	}
	}
}

void _triangulos3D::draw_textura(GLuint ident_textura, jpg::Imagen * imagen){
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,ident_textura);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

   if(modo_text) {
     glEnable(GL_TEXTURE_GEN_S);
     glEnable(GL_TEXTURE_GEN_T);
     glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
     glTexGenfv(GL_S,GL_EYE_PLANE,plano_s);
     glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
     glTexGenfv(GL_T,GL_EYE_PLANE,plano_t);
   }

   glColor3f(1.0,1.0,1.0);
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   glBegin(GL_TRIANGLES);

   for(int i=0; i<caras.size(); ++i) {
     if (b_textura_coord)
       glTexCoord2f(text_coord[caras[i]._0].s,text_coord[caras[i]._0].t);
     glVertex3fv((GLfloat *) &vertices[caras[i]._0]);

     if (b_textura_coord)
       glTexCoord2f(text_coord[caras[i]._1].s,text_coord[caras[i]._1].t);
     glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

     if (b_textura_coord)
       glTexCoord2f(text_coord[caras[i]._2].s,text_coord[caras[i]._2].t);
     glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
   }

   glEnd();

   glDisable(GL_TEXTURE_2D);
   glDisable(GL_TEXTURE_GEN_S);
   glDisable(GL_TEXTURE_GEN_T);
}

void _triangulos3D::draw_textura_ilum_plana(GLuint ident_textura, jpg::Imagen * imagen){
	  glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());
	  GLfloat material_blanco[4] = {1,1,1,1};

	  if(b_normales_caras == false)
	    calcular_normales_caras();

	  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	  glShadeModel(GL_FLAT);
	  glEnable(GL_LIGHTING);
	  glEnable(GL_LIGHT0);
	  glEnable(GL_LIGHT1);
	  glEnable(GL_NORMALIZE);

	  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material_blanco);
	  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
	  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

	  glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D,ident_textura);
	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	  if(modo_text) {
	    glEnable(GL_TEXTURE_GEN_S);
	    glEnable(GL_TEXTURE_GEN_T);
	    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
	    glTexGenfv(GL_S,GL_EYE_PLANE,plano_s);
	    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
	    glTexGenfv(GL_T,GL_EYE_PLANE,plano_t);
	  }

	  glColor3f(1.0,1.0,1.0);

	  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	  glBegin(GL_TRIANGLES);

	  for(int i =0; i<caras.size();++i) {
		 glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
	    if (b_textura_coord)
	      glTexCoord2f(text_coord[caras[i]._0].s,text_coord[caras[i]._0].t);
	    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);

		 glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
	    if (b_textura_coord)
	      glTexCoord2f(text_coord[caras[i]._1].s,text_coord[caras[i]._1].t);
	    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

		 glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
	    if (b_textura_coord)
	      glTexCoord2f(text_coord[caras[i]._2].s,text_coord[caras[i]._2].t);
	    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	  }

	  glEnd();
	  glDisable(GL_TEXTURE_2D);
	  glDisable(GL_TEXTURE_GEN_S);
	  glDisable(GL_TEXTURE_GEN_T);
	  glDisable(GL_LIGHTING);
}

void _triangulos3D::draw_textura_ilum_suave(GLuint ident_textura, jpg::Imagen * imagen){
	  glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());
	  GLfloat material_blanco[4] = {1,1,1,1};

	  if(b_normales_vertices == false)
	    calcular_normales_vertices();

	  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	  glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	  glShadeModel(GL_SMOOTH);
	  glEnable(GL_LIGHTING);
	  glEnable(GL_LIGHT0);
	  glEnable(GL_LIGHT1);
	  glEnable(GL_NORMALIZE);

	  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material_blanco);
	  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
	  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

	  glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D,ident_textura);
	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	  if(modo_text) {
	    glEnable(GL_TEXTURE_GEN_S);
	    glEnable(GL_TEXTURE_GEN_T);
	    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
	    glTexGenfv(GL_S,GL_EYE_PLANE,plano_s);
	    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
	    glTexGenfv(GL_T,GL_EYE_PLANE,plano_t);
	  }

	  glColor3f(1.0,1.0,1.0);

	  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	  glBegin(GL_TRIANGLES);

	  for(int i=0; i<caras.size();++i) {
		 glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
	    if (b_textura_coord)
	      glTexCoord2f(text_coord[caras[i]._0].s,text_coord[caras[i]._0].t);
	    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);

		 glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
	    if (b_textura_coord)
	      glTexCoord2f(text_coord[caras[i]._1].s,text_coord[caras[i]._1].t);
	    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

		 glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
	    if (b_textura_coord)
	      glTexCoord2f(text_coord[caras[i]._2].s,text_coord[caras[i]._2].t);
	    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	  }

	  glEnd();
	  glDisable(GL_TEXTURE_2D);
	  glDisable(GL_TEXTURE_GEN_S);
	  glDisable(GL_TEXTURE_GEN_T);
	  glDisable(GL_LIGHTING);
}

void _triangulos3D::setAmbienteDifusa(const _vertex4f &amb){
	ambiente_difusa=amb;
}

void _triangulos3D::setEspecular(const _vertex4f &esp){
	especular=esp;
}

void _triangulos3D::setBrillo(const float &bri){
	brillo=bri;
}

void _triangulos3D::draw_normales_caras() {
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_LINES);
    for(unsigned int i=0;i< normales_caras_dibujados.size();i++){
        glVertex3f(normales_caras_dibujados[i].first.x, normales_caras_dibujados[i].first.y, normales_caras_dibujados[i].first.z);
        glVertex3f(normales_caras_dibujados[i].second.x, normales_caras_dibujados[i].second.y, normales_caras_dibujados[i].second.z);
    }
    glEnd();
}

void _triangulos3D::draw_normales_vertices() {
    glColor3f(0.5,0.5,1);
    glBegin(GL_LINES);
    for(unsigned int i=0;i< normales_vertices_dibujados.size();i++){
        glVertex3f(normales_vertices_dibujados[i].first.x, normales_vertices_dibujados[i].first.y, normales_vertices_dibujados[i].first.z);
        glVertex3f(normales_vertices_dibujados[i].second.x, normales_vertices_dibujados[i].second.y, normales_vertices_dibujados[i].second.z);
    }
    glEnd();
}

textura::textura(){}

textura::textura(const char *archivoJPG) {
	imagen = new jpg::Imagen(archivoJPG);
}
