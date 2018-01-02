#include "textura.h"
#include "Clmg.h"

Textura::Textura(){

}

    void cargar (const char * fichero){
        CImg<unsigned char> logo;
        logo.load(fichero);

        // empaquetamos bien los datos
        for (long y = 0; y < logo.height(); y ++)
            for (long x = 0; x < logo.width(); x ++)
            {
            unsigned char *r = logo.data(x, y, 0, 0);
            unsigned char *g = logo.data(x, y, 0, 1);
            unsigned char *b = logo.data(x, y, 0, 2);
            data.push_back(*r);
            data.push_back(*g);
            data.push_back(*b);
            }

        glGenTextures(1, &textura_id);
        glBindTexture(GL_TEXTURE_2D, textura_id);

        glActiveTexture(GL_TEXTURE0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // TRASFIERE LOS DATOS A GPU
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, logo.width(), logo.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
    }

    void activar() const {
        glEnable(GL_TEXTURE_2D);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textura_id);
    }