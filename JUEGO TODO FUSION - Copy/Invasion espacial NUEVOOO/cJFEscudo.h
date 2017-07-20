#ifndef CJFESCUDO_H_INCLUDED
#define CJFESCUDO_H_INCLUDED

#include "cEntidad.h"

class JFEscudo : public Entidad{
public:
    JFEscudo(){
        imagen = al_load_bitmap("imagenes/escudo.png");
        al_convert_mask_to_alpha(imagen, al_map_rgb(255,255,255));
        x = 0;
        y = 0;
        ancho = 150;
        alto = 65;
        estado = true;
    }

    void dibujar(){
        if(estado)
            al_draw_bitmap(imagen,x,y,NULL);
    }

    ~JFEscudo(){
        al_destroy_bitmap(imagen);
        estado = false;
    }
};


#endif // CJFESCUDO_H_INCLUDED
