#include "modelo.h"

_modelo::_modelo() {
    rotacionCubo = 0;
    angulo = 0;
    altura = 3;
    rotacionBrazo = 0;
    movimiento = false;
}

void _modelo::Cubo(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor) {
    glPushMatrix();
    _cubo cubo(1);
    cubo.draw_triangulos(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
}

void _modelo::Cilindro(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor) {
    _rotacion cilindro;
    vector<_vertex3f> perfil;
    glPushMatrix();
    perfil.resize(2);
    perfil[0].x = 0.5;
    perfil[0].y = 1.0;
    perfil[0].z = 0.0;
    perfil[1].x = 0.5;
    perfil[1].y = 0.0;
    perfil[1].z = 0.0;
    cilindro.parametros(perfil, 15);
    cilindro.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
}

void _modelo::Brazo1(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor) {
    glPushMatrix();
    glTranslatef(0, -2.4, 0);
    glScalef(0.6, 0.6, 0.6);
    glRotatef(rotacionCubo, 0, 1, 0);
    Cubo(modo, 0.298, 0.0, 0.6, 1.0, 0.501, 0.0, grosor);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 2, 0.1);
    glRotatef(-180, 0, 0, 1);
    Cilindro(modo, 0.0, 0.0, 0.0, 0.2, 1.0, 0.0, grosor);
    glPopMatrix();
}

void _modelo::Brazo2(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor) {
    glPushMatrix();
    glTranslatef(2.4, 0, 0);
    glRotatef(angulo, 0, 0, 1);
    Brazo1(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
    glScalef(2.5, 0.25, 0.25);
    glRotatef(-90, 0, 0, 1);
    Cilindro(modo, 0.0, 1.0, 1.0, 0.8, 0.0, 0.4, grosor);
    glPopMatrix();
}

void _modelo::Base(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor) {
    glPushMatrix();
    //glScalef(0.25, altura, 0.25);
    glScalef(0.25, 5, 0.25);
    Cilindro(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
    glScalef(3, 0.2, 3);
    Cilindro(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
}

void _modelo::drawModelo(char modo, float r1, float g1, float b1, float r2, float g2, float b2, int grosor) {
    glPushMatrix();
    glTranslatef(0, altura, 0);
    glRotatef(rotacionBrazo, 0, 1, 0);
    Brazo2(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
    glPushMatrix();
    Base(modo, 1.0, 0.0, 0.0, 0.752, 0.752, 0.752, grosor);
    glPopMatrix();
}

void _modelo::rotacionCuboMas() {
    rotacionCubo += 5;
}

void _modelo::rotacionCuboMenos() {
    rotacionCubo -= 5;
}

void _modelo::anguloPenduloMas() {
    if (angulo > -45)
        angulo -= 5;
}

void _modelo::anguloPenduloMenos() {
    if (angulo < 45)
        angulo += 5;
}

void _modelo::subirEstructura() {
    if (altura < 5)
        altura += 0.2;
}

void _modelo::bajarEstructura() {
    if (altura > 3)
        altura -= 0.2;
}

void _modelo::rotarBrazoMas() {
    rotacionBrazo += 5;
}

void _modelo::rotarBrazoMenos() {
    rotacionBrazo -= 5;
}

void _modelo::setMovimiento(bool mov) {
    movimiento = mov;
}
