#ifndef _SOLIDOREVOLUCION_H
#define _SOLIDOREVOLUCION_H

#include <vector>
#include <stdlib.h>
#include "vertex.h"
#include "objetos.h"
#include <file_ply_stl.h>

//*************************************************************************
// clase revolucionar
//*************************************************************************

class solidoRevolucion: public _triangulos3D
{
public:

	solidoRevolucion();

	solidoRevolucion(vector <_vertex3f> perfil, int n);

  double gradosRadianes(double grados);

  _vertex3f rotarY (_vertex3f p, float ang);

	void revolucionar(vector <_vertex3f> perfil, int n);

};
#endif
