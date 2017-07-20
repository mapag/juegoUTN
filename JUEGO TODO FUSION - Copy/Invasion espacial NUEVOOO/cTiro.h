#ifndef CTIRO_H_INCLUDED
#define CTIRO_H_INCLUDED

#include "cEntidad.h"

class Tiro: public Entidad{
    public:
        Tiro(){
            estado=false;
            moveSpeed = 20;
            imagen = al_load_bitmap("imagenes/tiros player.png");
            ancho = al_get_bitmap_width(imagen);
            alto = al_get_bitmap_height(imagen)/4;
            al_convert_mask_to_alpha(imagen, al_map_rgb(255,255,255));
        }

        void Dibujar(){
            if(estado)
                al_draw_bitmap_region(imagen,0,dir*27.5,27,32,x,y,NULL);
        }

        ~Tiro(){
        al_destroy_bitmap(imagen);
        }

        void destino(){
            if(estado){
                if(dir==0){
                    y += moveSpeed;
                }

                if(dir==1){
                    x -= moveSpeed;
                }

                if(dir==2){
                    x += moveSpeed;
                }

                if(dir==3){
                    y -= moveSpeed;
                }
            }
        }

        void tiroPared(){
            if(estado){
            if(x >=640 || x <=10 || y >= 536 || y <=10)
                estado = 0;
            }
        }
};

#endif // CTIRO_H_INCLUDED
