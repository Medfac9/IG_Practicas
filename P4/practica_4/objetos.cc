
#include "objetos.h"
#include <math.h>

//*************************************************************************
// clase punto
//*************************************************************************

_puntos3D::_puntos3D(){

}

//*************************************************************************
// dibujar punto
//************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor){
	glColor3f(r,g,b);
	glPointSize(grosor);
  glBegin(GL_POINTS);
	for(int i = 0; i < vertices.size(); i++){
		//glNormal3f();                           Hay que ponerlo en todos con las normales
		glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
  }
	glEnd();
}

//*************************************************************************
// clase triángulo
//*************************************************************************

_triangulos3D::_triangulos3D(){

}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor){
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glColor3f(r,g,b);
	glPointSize(grosor);
  glBegin(GL_TRIANGLES);
	for(int i = 0; i < caras.size(); i++)
	{
		glVertex3f(vertices[caras[i].x].x,vertices[caras[i].x].y,vertices[caras[i].x].z);
		glVertex3f(vertices[caras[i].y].x,vertices[caras[i].y].y,vertices[caras[i].y].z);
		glVertex3f(vertices[caras[i].z].x,vertices[caras[i].z].y,vertices[caras[i].z].z);
	}
	glEnd();

	//dibujarNormales();
}

void _triangulos3D::dibujarNormales(){
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_LINES);
	for(int i = 0; i < caras.size(); i++)
	{
		_vertex3f baricentro = (vertices[caras[i]._0] + vertices[caras[i]._1] + vertices[caras[i]._2])/3.0;

		_vertex3f p = baricentro + normalCaras[i];
		
		_vertex3f v = vertices[i] + normalVertices[i];

		glVertex3f(baricentro.x, baricentro.y, baricentro.z);
		glVertex3f(p.x, p.y, p.z);

		glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
		glVertex3f(v.x, v.y, v.z);
		
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b){
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
	for(int i = 0; i < caras.size(); i++)
	{
		glVertex3f(vertices[caras[i].x].x,vertices[caras[i].x].y,vertices[caras[i].x].z);
		glVertex3f(vertices[caras[i].y].x,vertices[caras[i].y].y,vertices[caras[i].y].z);
		glVertex3f(vertices[caras[i].z].x,vertices[caras[i].z].y,vertices[caras[i].z].z);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2){
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);
	for(int i = 0; i < caras.size(); i++)
	{
    if(i % 2 == 0){
      glColor3f(r1,g1,b1);
    }
    else{
      glColor3f(r2,g2,b2);
    }
		glVertex3f(vertices[caras[i].x].x,vertices[caras[i].x].y,vertices[caras[i].x].z);
		glVertex3f(vertices[caras[i].y].x,vertices[caras[i].y].y,vertices[caras[i].y].z);
		glVertex3f(vertices[caras[i].z].x,vertices[caras[i].z].y,vertices[caras[i].z].z);
	}
	glEnd();
}

_vertex3f _triangulos3D::productoVectorial(_vertex3f p, _vertex3f q)
{
  return _vertex3f(p.y*q.z - p.z*q.y, p.z*q.x - p.x*q.z, p.x*q.y - p.y*q.x);
}

_vertex3f _triangulos3D::productoVectorial(_vertex3f v1, _vertex3f v2, _vertex3f v3)
{
  // En base a los tres puntos, calculamos los vectores
  _vertex3f p, q;

  p.x = v2.x - v1.x;
  p.y = v2.y - v1.y;
  p.z = v2.z - v1.z;
  q.x = v3.x - v1.x;
  q.y = v3.y - v1.y;
  q.z = v3.z - v1.z;

  return productoVectorial(p, q);
}

void _triangulos3D::getNormalCaras(){
	normalCaras.clear();
	normalVertices.clear();

	inicializarVector();
	
	//Calculamos la normal de cada cara
	for (int i = 0; i < caras.size(); i++) {
		normalCaras.push_back(normalizar(productoVectorial(vertices[caras[i]._0], vertices[caras[i]._1], vertices[caras[i]._2])));
	}
}

_vertex3f _triangulos3D::normalizar(_vertex3f v){

	float modulo = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	
	v.x = v.x / modulo;
	v.y = v.y / modulo;
	v.z = v.z / modulo;
    
	return v;
}

void _triangulos3D::inicializarVector(){
	for (int i = 0; i < caras.size(); i++) {
		normalVertices.push_back(0);
	}
}

void _triangulos3D::getNormalVertices(){
	//Calculamos la normal de cada vertice
	for (int i = 0; i < caras.size(); i++) {
		normalVertices[caras[i]._0].x += normalCaras[i].x;
		normalVertices[caras[i]._0].y += normalCaras[i].y;
		normalVertices[caras[i]._0].z += normalCaras[i].z;
		normalVertices[caras[i]._1].x += normalCaras[i].x;
		normalVertices[caras[i]._1].y += normalCaras[i].y;
		normalVertices[caras[i]._1].z += normalCaras[i].z;
		normalVertices[caras[i]._2].x += normalCaras[i].x;
		normalVertices[caras[i]._2].y += normalCaras[i].y;
		normalVertices[caras[i]._2].z += normalCaras[i].z;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam){
	// Inicializar los vertices en el eje de coordenadas x,y,z
	_vertex3f v1,v2,v3,v4,v5,v6,v7,v8;

	v1.x = -0.5;
	v1.y = -0.5;
	v1.z = -0.5;

	v2.x = tam/2;
	v2.y = -0.5;
	v2.z = -0.5;

	v3.x = -0.5;
	v3.y = tam/2;
	v3.z = -0.5;

	v4.x = tam/2;
	v4.y = tam/2;
	v4.z = -0.5;

	v5.x = -0.5;
	v5.y = tam/2;
	v5.z = tam/2;

	v6.x = tam/2;
	v6.y = tam/2;
	v6.z = tam/2;

	v7.x = -0.5;
	v7.y = -0.5;
	v7.z = tam/2;

	v8.x = tam/2;
	v8.y = -0.5;
	v8.z = tam/2;

	//Metemos los vertices
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);
	vertices.push_back(v8);

	// Inicializar las caras en el eje de coordenadas x,y,z
	_vertex3i c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12;

	c1._0 = 2;
	c1._1 = 1;
	c1._2 = 0;

	c2._0 = 2;
	c2._1 = 3;
	c2._2 = 1;

	c3._0 = 3;
	c3._1 = 5;
	c3._2 = 1;

	c4._0 = 5;
	c4._1 = 7;
	c4._2 = 1;

	c5._0 = 7;
	c5._1 = 5;
	c5._2 = 6;

	c6._0 = 5;
	c6._1 = 4;
	c6._2 = 6;

	c7._0 = 6;
	c7._1 = 4;
	c7._2 = 0;

	c8._0 = 2;
	c8._1 = 0;
	c8._2 = 4;

	c9._0 = 2;
	c9._1 = 4;
	c9._2 = 5;

	c10._0 = 2;
	c10._1 = 5;
	c10._2 = 3;

	c11._0 = 7;
	c11._1 = 6;
	c11._2 = 0;

	c12._0 = 1;
	c12._1 = 7;
	c12._2 = 0;

	//Metemos las caras
	caras.push_back(c1);
	caras.push_back(c2);
	caras.push_back(c3);
	caras.push_back(c4);
	caras.push_back(c5);
	caras.push_back(c6);
	caras.push_back(c7);
	caras.push_back(c8);
	caras.push_back(c9);
	caras.push_back(c10);
	caras.push_back(c11);
	caras.push_back(c12);

	//Calcular normales
	getNormalCaras();
	getNormalVertices();
}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al){
	// Inicializar los vertices en el eje de coordenadas x,y,z
	_vertex3f v1,v2,v3,v4,v5;

	v1.x = tam/2;
	v1.y = al;
	v1.z = tam/2;

	v2.x = 0.0;
	v2.y = 0.0;
	v2.z = 0.0;

	v3.x = tam;
	v3.y = 0.0;
	v3.z = 0.0;

	v4.x = 0.0;
	v4.y = 0.0;
	v4.z = tam;

	v5.x = tam;
	v5.y = 0.0;
	v5.z = tam;

	//Meter vertices
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);

	// Inicializar las caras en el eje de coordenadas x,y,z
	_vertex3i c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12;

	c1._0 = 0;
	c1._1 = 2;
	c1._2 = 1;

	c2._0 = 0;
	c2._1 = 4;
	c2._2 = 2;

	c3._0 = 4;
	c3._1 = 0;
	c3._2 = 3;

	c4._0 = 3;
	c4._1 = 0;
	c4._2 = 1;

	c5._0 = 4;
	c5._1 = 3;
	c5._2 = 1;

	c6._0 = 1;
	c6._1 = 2;
	c6._2 = 4;

	//Metemos las caras
	caras.push_back(c1);
	caras.push_back(c2);
	caras.push_back(c3);
	caras.push_back(c4);
	caras.push_back(c5);
	caras.push_back(c6);

	//Calcular normales
	getNormalCaras();
	getNormalVertices();
}
