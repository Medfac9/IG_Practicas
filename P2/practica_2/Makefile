# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica2

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuraci�n
#
CFLAGS=    -g -I/usr/include -I.
CXXFLAGS=  -g -I/usr/include -I.

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
#LDFLAGS=  -lGLU -lGL -lglut
LDFLAGS= -framework GLUT -framework OpenGL -framework Cocoa
# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
default : $(TARGETS)

# regla de ejecucion
#
$(TARGETS) : objetos.o solidoRevolucion.o file_ply_stl.o practica2.o
	$(CC) -o $@ $(CXXFLAGS) objetos.o solidoRevolucion.o file_ply_stl.o practica2.o $(LDFLAGS)

#
#
clean:
	rm -f *.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *
