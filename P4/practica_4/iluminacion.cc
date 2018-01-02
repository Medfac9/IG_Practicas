#include "iluminacion.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;

Iluminacion::Iluminacion(int num){
    if (num == 0){
        luz = GL_LIGHT0;
    }
    else if (num == 1){
        luz = GL_LIGHT1;
    }
    else if (num == 2){
        luz = GL_LIGHT2;
    }
    else if (num == 3){
        luz = GL_LIGHT3;
    }
    else if (num == 4){
        luz = GL_LIGHT4;
    }
    else if (num == 5){
        luz = GL_LIGHT5;
    }
    else if (num == 6){
        luz = GL_LIGHT6;
    }
    else {
        luz = GL_LIGHT7;
    }

    setValoresIniciales();
}

void Iluminacion::encender(){
    encendida = true;
    glLightfv(luz, GL_POSITION, ambiente);
    glLightfv(luz, GL_POSITION, especular);
    glLightfv(luz, GL_POSITION, difuso);
    glLightfv(luz, GL_POSITION, posicion);
    glEnable(luz);
} 

void Iluminacion::apagar(){
    encendida = false;
    glDisable(luz);
}

void Iluminacion::conmutar(){
    if (encendida){
        apagar();
    }
    else {
        encender();
    }
}

void Iluminacion::setAmbiente(GLfloat _ambiente[4]){
    for (int i = 0; i < 4; i ++){
        ambiente[i] = _ambiente[i];
    }
    glLightfv(luz, GL_AMBIENT, ambiente);
}

void Iluminacion::setEspecular(GLfloat _especular[4]){
for (int i = 0; i < 4; i ++){
        especular[i] = _especular[i];
    }
    glLightfv(luz, GL_SPECULAR, especular);
}

void Iluminacion::setDifuso(GLfloat _difuso[4]){
    for (int i = 0; i < 4; i ++){
        difuso[i] = _difuso[i];
    }
    glLightfv(luz, GL_DIFFUSE, difuso);
}

void Iluminacion::setPosicion(GLfloat _posicion[4]){
    for (int i = 0; i < 4; i ++){
        posicion[i] = _posicion[i];
    }
    glLightfv(luz, GL_POSITION, posicion);
}

void Iluminacion::setValoresIniciales(){

    ambiente[0] = 1;
    ambiente[1] = 1;
    ambiente[2] = 1;
    ambiente[3] = 1;

    especular[0] = 1;
    especular[1] = 1;
    especular[2] = 1;
    especular[3] = 1;

    difuso[0] = 1;
    difuso[1] = 1;
    difuso[2] = 1;
    difuso[3] = 1;

    posicion[0] = 5;
    posicion[1] = 5;
    posicion[2] = 5;
    posicion[3] = 1;

}

void Iluminacion::posicionar(){
    glLightfv(luz, GL_POSITION, posicion);
}

void Iluminacion::rotar(GLfloat Luz_angle_x, GLfloat Luz_angle_y){
    glPushMatrix();
        glRotatef(Luz_angle_x,1,0,0);
        glRotatef(Luz_angle_y,0,1,0);
    glPopMatrix();
}