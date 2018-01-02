#ifndef _OBJETOS_H
#define _OBJETOS_H

//**************************************************************************
// Práctica 4
//**************************************************************************

#include <vector>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "vertex.h"
#include <stdlib.h>

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

	_puntos3D();
	void draw_puntos(float r, float g, float b, int grosor);

	vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
	void draw_aristas(float r, float g, float b, int grosor);
	void draw_solido(float r, float g, float b);
	void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

	_vertex3f productoVectorial(_vertex3f p, _vertex3f q);
	_vertex3f productoVectorial(_vertex3f v1, _vertex3f v2, _vertex3f v3);
	void dibujarNormales();

	void getNormalCaras();
	void getNormalVertices();
	_vertex3f normalizar(_vertex3f v);
	void inicializarVector();

	vector<_vertex3i> caras;
	vector<_vertex3f> normalCaras;
	vector<_vertex3f> normalVertices;
};

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=1);
};

//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=3, float al=5);
};

#endif
