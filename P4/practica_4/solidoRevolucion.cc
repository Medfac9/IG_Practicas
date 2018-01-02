
#include "solidoRevolucion.h"
#include <math.h>

const double PI = 3.14159;

solidoRevolucion::solidoRevolucion(){
  _file_ply File_ply;

  vector<_vertex3f> Vertices;
  vector<_vertex3i> Triangles;
	_vertex3f v;
	_vertex3i c;

  if (File_ply.open("beethoven.ply")){
    File_ply.read(Vertices,Triangles);
    File_ply.close();

    for(int i = 0; i < Vertices.size(); i ++){
  		v.x = Vertices[i].x;
      v.y = Vertices[i].y;
  		v.z = Vertices[i].z;

  		vertices.push_back(v);
  	}

		for(int i=0; i<Triangles.size(); i ++){
      c.x = Triangles[i].x;
      c.y = Triangles[i].y;
  		c.z = Triangles[i].z;

			caras.push_back(c);
		}

    //Calcular normales
  	getNormalCaras();
    getNormalVertices();

    std::cout << "File read correctly" << std::endl;
  }
  else std::cout << "File can't be opened" << std::endl;
}

solidoRevolucion::solidoRevolucion(vector <_vertex3f> perfil, int numero_rev){
  bool hayTapaArriba = false;
  bool hayTapaAbajo = false;
  bool quieroPonerlaArriba = false;
  bool quieroPonerlaAbajo = false;
  _vertex3f primerVertice;
  _vertex3f ultimoVertice;

  if(perfil[numero_rev].x == 0){//primer vertice perfil esta en el eje y
    hayTapaArriba = true;
    //primerVertice = perfil[numero_rev]; //lo guardamos en una variable
		//perfil.erase(perfil.begin());//lo quitamos del prefil
  }
  else {
    hayTapaArriba = false;
    quieroPonerlaArriba = true;
    //generamos un nuevo vertice sobre el eje y (basandose en el primer vertice del prefil)
    primerVertice.x = 0;
		primerVertice.y = perfil.back().y;
		primerVertice.z = 0;
  }

  if(perfil.back().x == 0){//ultimo vertice perfil esta en el eje y
    hayTapaAbajo = true;
    //ultimoVertice = perfil.back(); //lo guardamos en una variable
		//perfil.erase(perfil.end());//lo quitamos del prefil
  }
  else {
    hayTapaAbajo = false;
    quieroPonerlaAbajo = true;
    //generamos un nuevo vertice sobre el eje y (basandose en el ultimo vertice del prefil)
    ultimoVertice.x = 0;
		ultimoVertice.y = perfil[0].y;
		ultimoVertice.z = 0;
  }

  //revolucionar de manera normal
  revolucionar(perfil, numero_rev);

  if(hayTapaAbajo || quieroPonerlaAbajo){
    vertices.push_back(ultimoVertice); //añadimos el primer vertice a los vertices
    //generamos las caras que unan al vertice que acabamos de añadir con el resto de vertices
		for(int i = 0; i < vertices.size() - perfil.size(); i = i + perfil.size())
		{
			_vertex3i c;

			c.x = i + perfil.size();
			c.y = i;
			c.z = vertices.size() - 1;

			caras.push_back(c);
		}
    //Calcular normales
  	getNormalCaras();
    getNormalVertices();
  }
  if(hayTapaArriba || quieroPonerlaArriba){
    vertices.push_back(primerVertice);//añadimos el ultimo vertice a los vertices
    //generamos las caras que unan al vertice que acabamos de añadir con el resto de vertices
    for(int i = perfil.size() - 1; i < vertices.size() - perfil.size(); i = i + perfil.size())
    {
      _vertex3i c;

      c.x = i + perfil.size();
      c.y = i ;
      c.z = vertices.size() - 1;

      caras.push_back(c);
    }
    //Calcular normales
  	getNormalCaras();
    getNormalVertices();
  }

}

double solidoRevolucion::gradosRadianes(double grados){
    return grados * PI / 180.0;
}

//Funcion para rotar x grados
_vertex3f solidoRevolucion::rotarY (_vertex3f p, float angulo){
  _vertex3f rotado;
  rotado.x = cos(angulo)*p.x + sin(angulo)*p.z;
  rotado.y = p.y;
  rotado.z = - sin(angulo)*p.x + cos(angulo)*p.z;
  return rotado;
}

void solidoRevolucion::revolucionar(vector<_vertex3f> perfil, int numero_rev){
  vertices.clear();
  caras.clear();
  vertices = perfil; //repite vertices

  double angulo = gradosRadianes(360.0 / numero_rev);
  double anguloActual = angulo;

  vertices.resize(perfil.size() * (numero_rev + 1));
  int k = perfil.size();

  for(int j = 0; j < numero_rev; j ++)
	{
		perfil[0] = rotarY(perfil[0], angulo);
		vertices[k ++] = perfil[0];

		for(int i = 1; i < perfil.size(); i ++)
		{
			perfil[i] = rotarY(perfil[i], angulo);
			vertices[k] = (perfil[i]);

			_vertex3i v;

			v.x = k;
			v.y = k - perfil.size();
			v.z = k - perfil.size() - 1;

			caras.push_back(v);

			v.x = k;
			v.y = k - perfil.size() - 1;
			v.z = k - 1;

			caras.push_back(v);

			k ++;
		}
	}
}
