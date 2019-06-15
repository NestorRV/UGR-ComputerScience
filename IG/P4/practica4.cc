//**************************************************************************
// Práctica 4
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <ctype.h>
#include "modelo.h"
#include <unistd.h>

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=700,UI_window_height=700;

char modo;
int objeto;
_cubo cubo(2);
char archivo[]= "beethoven.ply";
_objeto_ply objeto_ply(archivo);
_rotacion rotacion;
vector<_vertex3f> perfil, perfil_peon;
_modelo modelo;
float r1 = 100.0, g1 = 0.0, b1 = 30.0, r2 = 0.0, g2 = 0.0, b2 = 0.0;
int grosor = 2.0;
bool subir = true;
bool alejar = true;
bool p4 = false;

char peon[]= "peon.ply";
_objeto_ply ply_peon(peon);
char lata_inf[]= "lata-pinf.ply";
_objeto_ply ply_lata_pinf(lata_inf);
char lata_sup[]= "lata-psup.ply";
_objeto_ply ply_lata_psup(lata_sup);
char lata[]= "lata-pcue.ply";
_objeto_ply ply_lata_pcue(lata);

_rotacion peon_madera(ply_peon.vertices,30);
_rotacion peon_blanco(ply_peon.vertices,30);
_rotacion peon_negro(ply_peon.vertices,30);

_rotacion_tex lata_cuello(ply_lata_pcue.vertices, 40);
_rotacion_tex lata_superior(ply_lata_psup.vertices, 40);
_rotacion_tex lata_inferior(ply_lata_pinf.vertices, 40);

textura cocacola("text-lata-1.jpg");
textura madera("text-madera.jpg");

GLuint ident = 1;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
	if(p4){
		switch(objeto){
			case 1:
				objeto_ply.draw_iluminacion_suave(); break;
			case 2:
				objeto_ply.draw_iluminacion_plana(); break;
			case 3:
				objeto_ply.draw_textura(1, cocacola.imagen); break;
			case 5:
				objeto_ply.draw_textura_ilum_suave(1, cocacola.imagen); break;
			case 6:
				//Lata
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glScalef(3,3,3);
				lata_cuello.draw_textura_ilum_suave(1, cocacola.imagen);
				glPopMatrix();

				glPushMatrix();
				glScalef(3,3,3);
				lata_superior.draw_iluminacion_suave();
				glPopMatrix();
				glPushMatrix();
				glScalef(3,3,3);
				lata_inferior.draw_iluminacion_suave();
				glPopMatrix();

				peon_blanco.setAmbienteDifusa(_vertex4f(1.0,1.0,1.0,1)); // Super difuso
				peon_blanco.setEspecular(_vertex4f(0.0,0.0,0.0,1)); // No hay brillos especulares
				peon_blanco.setBrillo(20);

				peon_negro.setAmbienteDifusa(_vertex4f(0.0,0.0,0.0,1)); // No difusa
				peon_negro.setEspecular(_vertex4f(1.0,1.0,1.0,1)); // Brillos especularas
				peon_negro.setBrillo(20);

				//peon_madera
				glPushMatrix();
				glTranslatef(1.5,0.7,2.0);
				glScalef(0.5,0.5,0.5);
				peon_madera.draw_textura_ilum_suave(1, madera.imagen);
				glPopMatrix();

				//peon_negro
				glPushMatrix();
				glTranslatef(-1.5,0.7,2.0);
				glScalef(0.5,0.5,0.5);
				peon_negro.draw_iluminacion_suave();
				glPopMatrix();

				//peon_madera
				glPushMatrix();
				glTranslatef(0,0.7,2.0);
				glScalef(0.5,0.5,0.5);
				peon_blanco.draw_iluminacion_suave();
				glPopMatrix();
				break;
			case 7:
				objeto_ply.draw_normales_vertices();
				objeto_ply.draw_textura_ilum_suave(1, cocacola.imagen); break;
			case 8:
				objeto_ply.draw_normales_caras();
				objeto_ply.draw_textura_ilum_plana(1, cocacola.imagen); break;
		}
	}
	else if(!p4){
		switch (objeto){
			case 1:
				objeto_ply.draw_triangulos(modo, r1, g1, b1, r2, g2, b2, grosor);
				break;
			case 2:
				rotacion.draw_triangulos(modo, r1, g1, b1, r2, g2, b2, grosor);
				break;
			case 3:
				modelo.drawModelo(modo, r1, g1, b1, r2, g2, b2, grosor);
				break;
		}
	}
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}

void autoMovimiento(int n) {
	if (n) {
		if(modelo.altura < 4.9 && subir)
			modelo.altura += 0.1;
		else
			subir = false;

		if(modelo.altura > 3 && !subir)
			modelo.altura -= 0.1;
		else
			subir = true;

		if(modelo.angulo > -45 && alejar)
			modelo.angulo -= 5;
		else
			alejar = false;

		if(modelo.angulo < 45 && !alejar)
			modelo.angulo += 5;
		else
			alejar = true;

		modelo.rotacionCubo += 30;
		modelo.rotacionBrazo += 8;
		glutPostRedisplay();
	}
	glutTimerFunc(100, autoMovimiento, modelo.movimiento);
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************
void normal_keys(unsigned char Tecla1,int x,int y)
{
	if(p4){
		if (toupper(Tecla1)=='Q') exit(0);
		else if (Tecla1 == '4')
			p4 = false;
		else if (Tecla1 == '1' || Tecla1 == '2' || Tecla1 == '3' || Tecla1 == '5' || Tecla1 == '6' || Tecla1 == '7' || Tecla1 == '8')
			objeto = (int)Tecla1 - 48;
	}
	else if(!p4){
		if (toupper(Tecla1)=='Q') exit(0);
		else if (Tecla1 == '4')
			p4 = true;
		else if (Tecla1 == '1' || Tecla1 == '2' || Tecla1 == '3')
			objeto = (int)Tecla1 - 48;
		else if (toupper(Tecla1)=='P')
			modo = 'p';
		else if (toupper(Tecla1)=='L')
			modo = 'l';
		else if (toupper(Tecla1)=='S')
			modo = 's';
		else if (toupper(Tecla1)=='A')
			modo = 'a';
		else if (Tecla1=='Z')
			modelo.rotacionCuboMas();
		else if (Tecla1=='z')
			modelo.rotacionCuboMenos();
		else if (Tecla1=='X')
			modelo.anguloPenduloMas();
		else if (Tecla1=='x')
			modelo.anguloPenduloMenos();
		else if (Tecla1=='C')
			modelo.subirEstructura();
		else if (Tecla1=='c')
			modelo.bajarEstructura();
		else if (Tecla1=='V')
			modelo.rotarBrazoMas();
		else if (Tecla1=='v')
			modelo.rotarBrazoMenos();
		else if (Tecla1=='m')
			modelo.setMovimiento(true);
		else if (toupper(Tecla1)=='D')
			modelo.setMovimiento(false);
	}

	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Práctica 4");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

perfil.resize(9);
perfil[0].x = 1.0; perfil[0].y = 5.0; perfil[0].z = 0.0;
perfil[1].x = 2.0; perfil[1].y = 4.5; perfil[1].z = 0.0;
perfil[2].x = 1.5; perfil[2].y = 4.0; perfil[2].z = 0.0;
perfil[3].x = 2.0; perfil[3].y = 3.5; perfil[3].z = 0.0;
perfil[4].x = 1.0; perfil[4].y = 2.5; perfil[4].z = 0.0;
perfil[5].x = 3.5; perfil[5].y = 2.5; perfil[5].z = 0.0;
perfil[6].x = 3.5; perfil[6].y = 2.0; perfil[6].z = 0.0;
perfil[7].x = 1.0; perfil[7].y = 1.5; perfil[7].z = 0.0;
perfil[8].x = 2.0; perfil[8].y = 0.0; perfil[8].z = 0.0;
rotacion.parametros(perfil, 10);

glutTimerFunc(100, autoMovimiento, modelo.movimiento);
// inicio del bucle de eventos
glutMainLoop();
return 0;
}
