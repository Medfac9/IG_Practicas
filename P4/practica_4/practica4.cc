//**************************************************************************
// Práctica 4
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "solidoRevolucion.h"
#include "escabadora.h"
#include "iluminacion.h"
// tamaño de los ejes
//const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

float Luz_angle_x_0 = 5;
float Luz_angle_y_0 = 5;
float Luz_angle_x_1 = -5;
float Luz_angle_y_1 = 5;

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
Iluminacion i0 = Iluminacion(0);
Iluminacion i1 = Iluminacion(1);

int objeto = 1; //1 = tetraedro, 2 = cubo, 3 = PLY, 4 = revolucion, 5 = objeto jerarquico, 6 = tablero
int modo = 0; //0 = puntos, 1 = alambre, 2 = solido, 3 = ajedrez
double a = -45;
double b = -45;
double d = 120;
double e = 0;
double l = 0.7;
int sentidoPala = -1;
int sentidoAlargamiento = -1;
int sentidoPaloCorto = -1;
int sentidoPaloLargo = 0;
int sentidoCuboAriba = -1;
int cont = 0;
int cont2 = 0;
int activarIluminacion = 0;
int activarTextura = 0;
int activarSombra = 0;
int activarLuz0 = 0;
int activarLuz1 = 0;
int sentido1 = 0;
int sentido2 = 0;


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

	GLfloat posicionX[4];
	posicionX[0] = Luz_angle_x_0;
	posicionX[1] = Luz_angle_x_1;
	posicionX[2] = 5;
	posicionX[3] = 1;
	i0.setPosicion(posicionX);
	
	GLfloat posicionY[4];
	posicionY[0] = Luz_angle_y_0;
	posicionY[1] = Luz_angle_y_1;
	posicionY[2] = 5;
	posicionY[3] = 1;
	i1.setPosicion(posicionY);

	i0.rotar(Luz_angle_x_0, Luz_angle_y_0);
	i1.rotar(Luz_angle_x_1, Luz_angle_y_1);

	i0.posicionar();
	i1.posicionar();
	
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
	else if (objeto == 6){ // Tablero
		
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

if (toupper(Tecla1)=='Q') exit(0);    // Salir de la ventana
if (toupper(Tecla1)=='1') objeto = 1; // Tetraedro
if (toupper(Tecla1)=='2') objeto = 2; // Cubo
if (toupper(Tecla1)=='3') objeto = 3; // PLY
if (toupper(Tecla1)=='4') objeto = 4; // Revolución
if (toupper(Tecla1)=='5') objeto = 5; // Objeto jerarquico
if (toupper(Tecla1)=='6') objeto = 6; // Tablero
if (toupper(Tecla1)=='P') modo = 0;   // Puntos
if (toupper(Tecla1)=='L') modo = 1;   // Lineas
if (toupper(Tecla1)=='F') modo = 2;   // Solido
if (toupper(Tecla1)=='A') modo = 3;   // Ajedrez
if (toupper(Tecla1)=='Z'){
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
	if (Tecla1 == 'B'){
		e ++;
	}
	else{
		e --;
	}
}
if (toupper(Tecla1)=='I'){
	if(activarIluminacion == 0){
		glEnable(GL_LIGHTING);
		activarIluminacion = 1;
		i0.encender();
		i1.encender();
	}
	else {
		glDisable(GL_LIGHTING);
		activarIluminacion = 0;
		i0.apagar();
		i1.apagar();
	}
}
if (toupper(Tecla1)=='T'){
	if (activarTextura == 0){
		activarTextura = 1;
	}
	else{
		activarTextura = 0;
	}
}
if (toupper(Tecla1)=='S'){
	if (activarSombra == 0){
		glShadeModel(GL_FLAT);
		activarSombra = 1;
	}
	else{
		glShadeModel(GL_SMOOTH);
		activarSombra = 0;
	}
}
if (toupper(Tecla1)=='M'){
	if (activarLuz0 == 0){
		activarLuz0 = 1;
		i0.conmutar();
	}
	else{
		activarLuz0 = 0;
		i0.conmutar();
	}
}
if (toupper(Tecla1)=='N'){
	if (activarLuz1 == 0){
		activarLuz1 = 1;
		i1.conmutar();
	}
	else{
		activarLuz1 = 0;
		i1.conmutar();
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
			sentidoPaloLargo = -1;
			if (cont2 % 2 == 0) {
				sentidoCuboAriba = 1;
			}
			else{
				sentidoCuboAriba = 0;
			}
			cont2 ++;
		}
	}
	if(sentidoPaloLargo == 0){
		d --;
		if (d == 90) {
			sentidoPaloLargo = -1;
			if (cont % 2 == 0) {
				sentidoPaloCorto = 0;
			}
			else {
				sentidoPala = 1;
			}
			cont ++;
		}
	}
/*
	//Movimiento extendedor
	if(sentidoAlargamiento == 1){
		l = l + 0.01;
		if (l == 2) {
			sentidoAlargamiento = 0;
		}

	}
	if(sentidoAlargamiento == 0){
		l  = l - 0.001;
		if (l == 0.499) {
			sentidoAlargamiento = 1;
		}
	}
*/
	//Movimiento palo corto
	if(sentidoPaloCorto == 1){
		b ++;
		if (b == 0) {
			sentidoPaloCorto = 0;
		}
	}
	if(sentidoPaloCorto == 0){
		b --;
		if (b == -60) {
			sentidoPaloCorto = -1;
			sentidoPala = 0;
			b ++;
		}
	}

	//Movimiento pala
	if(sentidoPala == 1){
		a ++;
		if (a == 0) {
			sentidoPala = -1;
			sentidoPaloLargo = 1;
		}
	}
	if(sentidoPala == 0){
		a --;
		if (a == -80) {
			sentidoPala = -1;
			sentidoPaloLargo = 1;
		}
	}

	//Movimiento Cubo
	if(sentidoCuboAriba == 0){
		e ++;
		if (e == 0) {
			sentidoCuboAriba = -1;
			sentidoPaloLargo = 0;
		}
	}
	if(sentidoCuboAriba == 1){
		e --;
		if (e == -80) {
			sentidoCuboAriba = -1;
			sentidoPaloLargo = 0;
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
	case GLUT_KEY_F1:
		if(Luz_angle_x_0 <= 100 && sentido1 == 0){
			if(Luz_angle_x_0 == 100)
				sentido1 = 1;
			else{
				Luz_angle_x_0++;
				Luz_angle_y_0++;
			}
		}
		else
			if(Luz_angle_x_0 == 0)
				sentido1 = 0;
			else
				Luz_angle_x_0--;
				Luz_angle_y_0--;
		break;
	case GLUT_KEY_F2:
		if(Luz_angle_x_1 <= 100 && sentido2 == 0){
			if(Luz_angle_x_1 == 100)
				sentido2 = 1;
			else{
				Luz_angle_x_1++;
				Luz_angle_y_1++;
			}
		}
		else
			if(Luz_angle_x_1 == 0)
				sentido2 = 0;
			else
				Luz_angle_x_1--;
				Luz_angle_y_1--;
		break;
	//case GLUT_KEY_F5:CambiaMaterialUno;break;
	//case GLUT_KEY_F6:CambiaMaterialDos;break;
	//case GLUT_KEY_F7:CambiaMaterialTres;break;
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

GLfloat ambiente[4];
GLfloat especular[4];
GLfloat difuso[4];
GLfloat posicion[4];

ambiente[0] = 0;
ambiente[1] = 0;
ambiente[2] = 1;
ambiente[3] = 1;

especular[0] = 0;
especular[1] = 0;
especular[2] = 1;
especular[3] = 1;

difuso[0] = 0;
difuso[1] = 0;
difuso[2] = 1;
difuso[3] = 1;

posicion[0] = Luz_angle_x_0;
posicion[1] = Luz_angle_x_1;
posicion[2] = 5;
posicion[3] = 1;

i0.setAmbiente(ambiente);
i0.setEspecular(especular);
i0.setDifuso(difuso);
i0.setPosicion(posicion);

ambiente[0] = 1;
ambiente[1] = 0;
ambiente[2] = 0;
ambiente[3] = 1;

especular[0] = 1;
especular[1] = 0;
especular[2] = 0;
especular[3] = 1;

difuso[0] = 1;
difuso[1] = 0;
difuso[2] = 0;
difuso[3] = 1;

posicion[0] = Luz_angle_x_1;
posicion[1] = Luz_angle_y_1;
posicion[2] = 5;
posicion[3] = 1;

i1.setAmbiente(ambiente);
i1.setEspecular(especular);
i1.setDifuso(difuso);
i1.setPosicion(posicion);

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
glutCreateWindow("Práctica 4");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);
//Animacion
glutIdleFunc(animacion);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
