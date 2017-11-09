//**************************************************************************
// Práctica 2
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "solidoRevolucion.h"
#include "escabadora.h"
// tamaño de los ejes
//const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

// declarar variables globales
_cubo c;
_piramide p;
solidoRevolucion solido = solidoRevolucion();
solidoRevolucion solidoRev;
Escabadora esc;

int objeto = 1; //1 = tetraedro, 2 = cubo, 3 = PLY, 4 = revolucion, 5 = objeto jerarquico
int modo = 0; //0 = puntos, 1 = alambre, 2 = solido, 3 = ajedrez
int movimiento = 1; //1 = mover pala , 2 = alargar brazo, 3 = mover primer brazo, 4 = mover segundo brazo, 5 = girar cubo arriba
double a = -45;
double b = -45;
double d = 120;
double e = 0;
double l = 0.5;
int sentidoPala = -1;
int sentidoAlargamiento = -1;
int sentidoPaloCorto = -1;
int sentidoPaloLargo = 0;
int sentidoCuboAriba = -1;

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
	if (objeto == 1){ //Tetraedro
		if (modo == 0){ //Puntos
			p.draw_puntos(1.0,0,0,4);
		}
		else if (modo == 1){ //Lineas
			p.draw_aristas(1.0,0,0,1);
		}
		else if (modo == 2) { //Solido
			p.draw_solido(1.0,0,0);
		}
		else if (modo == 3) { //Ajedrez
			p.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
		}

	}
	else if (objeto == 2){ // Cubo
		if (modo == 0){ //Puntos
			c.draw_puntos(1.0,0,0,4);
		}
		else if (modo == 1){ //Lineas
			c.draw_aristas(1.0,0,0,1);
		}
		else if (modo == 2) { //Solido
			c.draw_solido(1.0,0,0);
		}
		else if (modo == 3) { //Ajedrez
			c.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
		}
	}
	else if (objeto == 3){ // PLY
		if (modo == 0){ //Puntos
			solido.draw_puntos(1.0,0,0,4);
		}
		else if (modo == 1){ //Lineas
			solido.draw_aristas(1.0,0,0,1);
		}
		else if (modo == 2) { //Solido
			solido.draw_solido(1.0,0,0);
		}
		else if (modo == 3) { //Ajedrez
			solido.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
		}
	}
	else if (objeto == 4){ // Revolucion
		if (modo == 0){ //Puntos
			solidoRev.draw_puntos(1.0,0,0,4);
		}
		else if (modo == 1){ //Lineas
			solidoRev.draw_aristas(1.0,0,0,1);
		}
		else if (modo == 2) { //Solido
			solidoRev.draw_solido(1.0,0,0);
		}
		else if (modo == 3) { //Ajedrez
			solidoRev.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
		}
	}
	else if (objeto == 5){ // Objeto jerarquico
		esc.dibujar(a, b, d, e, l, modo);
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

if (toupper(Tecla1)=='Q') exit(0);    //Salir de la ventana
if (toupper(Tecla1)=='1') objeto = 1; // Tetraedro
if (toupper(Tecla1)=='2') objeto = 2; // Cubo
if (toupper(Tecla1)=='3') objeto = 3; // PLY
if (toupper(Tecla1)=='4') objeto = 4; //Revolución
if (toupper(Tecla1)=='5') objeto = 5; //Objeto jerarquico
if (toupper(Tecla1)=='P') modo = 0;   // Puntos
if (toupper(Tecla1)=='L') modo = 1;   // Lineas
if (toupper(Tecla1)=='F') modo = 2;   // Solido
if (toupper(Tecla1)=='A') modo = 3;   // Ajedrez
if (toupper(Tecla1)=='Z'){
	movimiento = 1;   // Mover pala
	if (Tecla1 == 'Z'){
		if(a >= 0)
			a = a;
		else
			a ++;
	}
	else{
		if(a <= -80)
			a = a;
		else
			a --;
	}
}
if (toupper(Tecla1)=='X'){
	movimiento = 2;   // Alargar brazo
	if (Tecla1 == 'X'){
		if(l >= 2)
			l = l;
		else
			l = l + 0.1;
	}
	else{
		if(l <= 0.5)
			l = l;
		else
			l = l - 0.1;
	}
}
if (toupper(Tecla1)=='C'){
	movimiento = 3;   // Mover primer brazo
	if (Tecla1 == 'C'){
		if(b >= 0)
			b = b;
		else
			b ++;
	}
	else{
		if(b <= -60)
			b = b;
		else
			b --;
	}
}
if (toupper(Tecla1)=='V'){
	movimiento = 4;   // Mover segundo brazo
	if (Tecla1 == 'V'){
		if(d >= 130)
			d = d;
		else
			d ++;
	}
	else{
		if(d <= 90)
			d = d;
		else
			d --;
	}
}
if (toupper(Tecla1)=='B'){
	movimiento = 5;   // Girar cubo arriba
	if (Tecla1 == 'B'){
		e ++;
	}
	else{
		e --;
	}
}
if (toupper(Tecla1)=='+') Observer_distance/=1.2;   // Acercar
if (toupper(Tecla1)=='-') Observer_distance*=1.2;   // Alejar
glutPostRedisplay();
}

//***************************************************************************
// Animacion
//***************************************************************************

void animacion(){
	//Espera de tiempo controlada

	//Movimiento palo largo
	if(sentidoPaloLargo == 1){
		d ++;
		if (d == 130) {
			sentidoPaloLargo = 0;
		}
	}
	if(sentidoPaloLargo == 0){
		d --;
		if (d == 90) {
			sentidoPaloLargo = 1;
		}
	}

	//Movimiento pala
	if(sentidoPala == 1){
		a ++;
		if (a == 0) {
			sentidoPala = 0;
		}
	}
	if(sentidoPala == 0){
		a --;
		if (a == -80) {
			sentidoPala = 1;
		}
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
	//case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	//case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
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

_file_ply File_ply;

vector<_vertex3f> Vertices;
vector<_vertex3i> Triangles;
_vertex3f v;
vector<_vertex3f> vertices;

if (File_ply.open("peon.ply")){
	File_ply.read(Vertices,Triangles);
	File_ply.close();

	for(int i = 0; i < Vertices.size(); i ++){
		v.x = Vertices[i].x;
		v.y = Vertices[i].y;
		v.z = Vertices[i].z;

		vertices.push_back(v);
	}

	std::cout << "File read correctly" << std::endl;
}
else
	std::cout << "File can't be opened" << std::endl;

solidoRev = solidoRevolucion(Vertices, 6);
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
glutCreateWindow("Práctica 3");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

glutIdleFunc(animacion);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
