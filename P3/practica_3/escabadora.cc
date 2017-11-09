#include "escabadora.h"
#include <GL/glut.h>

Escabadora::Escabadora(){

}

void Escabadora::dibujar (double a, double b, double d, double e, double l, int estilo){
  //Union ruedas
  glPushMatrix();

    //Union cubo abajo
    glPushMatrix();
      glTranslatef(0,0.33,0);
      glTranslatef(0,2.5,0);

      //Union cubo arriba
      glPushMatrix();
        glTranslatef(0,2.5,0);
        glRotatef(e,0,1,0);
        glTranslatef(0,2,0);

        //Union con bola
        glPushMatrix();
          glTranslatef(3,0,0);

          //Union con palo largo
          glPushMatrix();
            glRotatef(d,0,0,1);
            glTranslatef(0,-5,0);

            //Union con bola
            glPushMatrix();
              glTranslatef(0,-5,0);

              //Union pala + palo extendedor
              glPushMatrix();
                glRotatef(b,0,0,1);
                glTranslatef(0,(-2.5)*l,0);

                //Pala
                glPushMatrix();
                  glTranslatef(0,(-2.5)*l,0);
                  glRotatef(a,0,0,1);
                  glTranslatef(0,-1.5,0);
                  glScalef(0.33,3,3);

                  if (estilo == 0)
                    c.draw_puntos(1.0,0,0,4);
                  else if (estilo == 1)
                    c.draw_aristas(1.0,0,0,1);
                  else if (estilo == 2)
                    c.draw_solido(0.462746,0.235294,0.156863);
                  else if (estilo == 3)
                    c.draw_solido_ajedrez(1.0,0,0,0,1.0,0);

                glPopMatrix();

                //Palo extendedor
                glPushMatrix();
                  glScalef(0.33,5*l,0.33);

                  if (estilo == 0)
                    c.draw_puntos(1.0,0,0,4);
                  else if (estilo == 1)
                    c.draw_aristas(1.0,0,0,1);
                  else if (estilo == 2)
                    c.draw_solido(0.6,0.6,0.6);
                  else if (estilo == 3)
                    c.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
                glPopMatrix();
              glPopMatrix();

              //Esfera
              glPushMatrix();
                glScalef(0.7,0.7,0.7);

                if (estilo == 0)
                  c.draw_puntos(1.0,0,0,4);
                else if (estilo == 1)
                  c.draw_aristas(1.0,0,0,1);
                else if (estilo == 2)
                  c.draw_solido(0,0,0);
                else if (estilo == 3)
                  c.draw_solido_ajedrez(1.0,0,0,0,1.0,0);

                //glutSolidSphere (0.5, 20, 20);
              glPopMatrix();
            glPopMatrix();

            //Palo largo
            glPushMatrix();
              glScalef(0.33,10,0.33);

              if (estilo == 0)
                c.draw_puntos(1.0,0,0,4);
              else if (estilo == 1)
                c.draw_aristas(1.0,0,0,1);
              else if (estilo == 2)
                c.draw_solido(0.6,0.6,0.6);
              else if (estilo == 3)
                c.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
            glPopMatrix();
          glPopMatrix();

          //Esfera
          glPushMatrix();
            glScalef(0.7,0.7,0.7);

            if (estilo == 0)
              c.draw_puntos(1.0,0,0,4);
            else if (estilo == 1)
              c.draw_aristas(1.0,0,0,1);
            else if (estilo == 2)
              c.draw_solido(0,0,0);
            else if (estilo == 3)
              c.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
            //glColor3f()
            //glutSolidSphere (0.5, 20, 20);
          glPopMatrix();
        glPopMatrix();

        //Cubo arriba
        glPushMatrix();
          glScalef(6,4,4);

          if (estilo == 0)
            c.draw_puntos(1.0,0,0,4);
          else if (estilo == 1)
            c.draw_aristas(1.0,0,0,1);
          else if (estilo == 2)
            c.draw_solido(1.0,0.82353,0.00392);
          else if (estilo == 3)
            c.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
        glPopMatrix();
      glPopMatrix();

      //Cubo abajo
      glPushMatrix();
        glScalef(8,5,5);

        if (estilo == 0)
          c.draw_puntos(1.0,0,0,4);
        else if (estilo == 1)
          c.draw_aristas(1.0,0,0,1);
        else if (estilo == 2)
          c.draw_solido(1.0,0.643137,0.1254902);
        else if (estilo == 3)
          c.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
      glPopMatrix();
    glPopMatrix();

    //Rueda derecha
    glPushMatrix();
      glTranslatef(0,0,-2.5);
      glScalef(12,0.66,1.32);

      if (estilo == 0)
        c.draw_puntos(1.0,0,0,4);
      else if (estilo == 1)
        c.draw_aristas(1.0,0,0,1);
      else if (estilo == 2)
        c.draw_solido(0.305882,0.329412,0.321569);
      else if (estilo == 3)
        c.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
    glPopMatrix();

    //Rueda izquierda
    glPushMatrix();
      glTranslatef(0,0,2.5);
      glScalef(12,0.66,1.32);

      if (estilo == 0)
        c.draw_puntos(1.0,0,0,4);
      else if (estilo == 1)
        c.draw_aristas(1.0,0,0,1);
      else if (estilo == 2)
        c.draw_solido(0.305882,0.329412,0.321569);
      else if (estilo == 3)
        c.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
    glPopMatrix();
  glPopMatrix();
}
