
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

//*************************************************************************
// clase circulo Examen
//*************************************************************************

void Circle (GLfloat radio, GLfloat cx, GLfloat cy, GLfloat cz, GLint n, GLenum modo) {
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,modo);
	glBegin( GL_POLYGON );
		for (i=0;i<n;i++)
			glVertex3f( cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n), cz);
	glEnd();
}

//*************************************************************************
// dibujar en modo aristas con los vertices redondos de diferentes colores Examen
//*************************************************************************

void _triangulos3D::draw_circulos(float radio, float n, GLenum modo){
	for(int i = 0; i < caras.size(); i++)
	{
		glColor3f(colores[i].r, colores[i].g, colores[i].b);
		Circle (radio, vertices [i].x, vertices [i].y, vertices [i].z, n, modo);
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam){
	// Inicializar los vertices en el eje de coordenadas x,y,z
	_vertex3f v1,v2,v3,v4,v5,v6,v7,v8;

	v1.x = 0.0;
	v1.y = 0.0;
	v1.z = 0.0;

	v2.x = tam;
	v2.y = 0.0;
	v2.z = 0.0;

	v3.x = 0.0;
	v3.y = tam;
	v3.z = 0.0;

	v4.x = tam;
	v4.y = tam;
	v4.z = 0.0;

	v5.x = 0.0;
	v5.y = tam;
	v5.z = tam;

	v6.x = tam;
	v6.y = tam;
	v6.z = tam;

	v7.x = 0.0;
	v7.y = 0.0;
	v7.z = tam;

	v8.x = tam;
	v8.y = 0.0;
	v8.z = tam;

	//colores de cada vertice del cubo Examen
	colores.resize(8);

	colores[0].r = 1.0;
	colores[0].g = 0.7;
	colores[0].b = 0.4;

	colores[1].r = 0.0;
	colores[1].g = 0.7;
	colores[1].b = 0.4;

	colores[2].r = 1.0;
	colores[2].g = 0.0;
	colores[2].b = 0.4;

	colores[3].r = 1.0;
	colores[3].g = 0.7;
	colores[3].b = 0.0;

	colores[4].r = 1.0;
	colores[4].g = 1.0;
	colores[4].b = 0.4;

	colores[5].r = 1.0;
	colores[5].g = 0.7;
	colores[5].b = 1.0;

	colores[6].r = 0.7;
	colores[6].g = 0.7;
	colores[6].b = 0.4;

	colores[7].r = 0.0;
	colores[7].g = 0.7;
	colores[7].b = 0.9;

	//// Meterlos en el vector de vertices
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

	c1._0 = 0;
	c1._1 = 1;
	c1._2 = 2;

	c2._0 = 1;
	c2._1 = 3;
	c2._2 = 2;

	c3._0 = 1;
	c3._1 = 5;
	c3._2 = 3;

	c4._0 = 1;
	c4._1 = 7;
	c4._2 = 5;

	c5._0 = 6;
	c5._1 = 5;
	c5._2 = 7;

	c6._0 = 6;
	c6._1 = 4;
	c6._2 = 5;

	c7._0 = 0;
	c7._1 = 4;
	c7._2 = 6;

	c8._0 = 4;
	c8._1 = 0;
	c8._2 = 2;

	c9._0 = 5;
	c9._1 = 4;
	c9._2 = 2;

	c10._0 = 3;
	c10._1 = 5;
	c10._2 = 2;

	c11._0 = 7;
	c11._1 = 6;
	c11._2 = 0;

	c12._0 = 1;
	c12._1 = 7;
	c12._2 = 0;

	//// Meterlos en el vector de caras
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

	//colores de cada vertice de la piramide Examen
	colores.resize(5);

	colores[0].r = 1.0;
	colores[0].g = 0.7;
	colores[0].b = 0.4;

	colores[1].r = 0.0;
	colores[1].g = 0.7;
	colores[1].b = 0.4;

	colores[2].r = 1.0;
	colores[2].g = 0.0;
	colores[2].b = 0.4;

	colores[3].r = 1.0;
	colores[3].g = 0.7;
	colores[3].b = 0.0;

	colores[4].r = 1.0;
	colores[4].g = 1.0;
	colores[4].b = 0.4;

	// Meterlos en el vector de vertices
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);

	// Inicializar las caras en el eje de coordenadas x,y,z
	_vertex3i c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12;

	c1._0 = 1;
	c1._1 = 2;
	c1._2 = 0;

	c2._0 = 2;
	c2._1 = 4;
	c2._2 = 0;

	c3._0 = 3;
	c3._1 = 0;
	c3._2 = 4;

	c4._0 = 1;
	c4._1 = 0;
	c4._2 = 3;

	c5._0 = 4;
	c5._1 = 3;
	c5._2 = 1;

	c6._0 = 1;
	c6._1 = 2;
	c6._2 = 4;

	//// Meterlos en el vector de caras
	caras.push_back(c1);
	caras.push_back(c2);
	caras.push_back(c3);
	caras.push_back(c4);
	caras.push_back(c5);
	caras.push_back(c6);

}
