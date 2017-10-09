
EJECUTABLE= practica_0
MODULOS=  $(EJECUTABLE).o

#  CFLAGS= Parametros para el compilador de C/C++
CFLAGS=    -g -I/usr/include -I.
CXXFLAGS=  -g -I/usr/include -I.

#  LDFLAGS= Parametros para el linkador
#LDFLAGS=   -L/usr/lib
LDFLAGS= -framework GLUT -framework OpenGL -framework Cocoa

#  LIBS= librerias a usar.
#LIBS=    -lglut -lGLU  -lGL -lX11 -lXext  -lc -lm

#  CC= orden de UNIX que invoca al compilador de C/C++ de GNU
CC=        g++

# archivo ejecutable a generar
$(EJECUTABLE): $(MODULOS)
	$(CC)  -o$(EJECUTABLE) $(LDFLAGS) $(MODULOS)  $(LIBS)
