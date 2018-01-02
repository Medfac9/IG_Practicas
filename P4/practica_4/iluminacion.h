#ifndef _ILUMINACION_H
#define _ILUMINACION_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

class Iluminacion
{
  private:
    bool encendida;
    GLenum luz;
    GLfloat ambiente[4];
    GLfloat especular[4];
    GLfloat difuso[4];
    GLfloat posicion[4];

  public:

  	Iluminacion(int num);
    void encender(); 
    void apagar(); 
    void conmutar();
    void setAmbiente(GLfloat ambiente[4]);
    void setEspecular(GLfloat especular[4]);
    void setDifuso(GLfloat difuso[4]);
    void setPosicion(GLfloat posicion[4]);
    void setValoresIniciales();
    void posicionar();
    void rotar(GLfloat Luz_angle_x, GLfloat Luz_angle_y);

};
#endif
