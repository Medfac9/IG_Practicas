#ifndef _TEXTURA_H
#define _TEXTURA_H

#include <OpenGL/gl.h>
#include <vector>

class Textura
{
  private:
    std::vector<unsigned char> data;
    GLuint textura_id;

  public:

  	Textura();
    void cargar (const char * fichero);
    void activar() const;

};
#endif
