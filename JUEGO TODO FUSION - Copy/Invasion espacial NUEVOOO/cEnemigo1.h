#ifndef CENEMIGO1_H_INCLUDED
#define CENEMIGO1_H_INCLUDED

#include "cEntidad.h"
#include "cJugador.h"
class Enemigo1 : public Entidad{
    private:
            ALLEGRO_BITMAP*vidas;
    public:
        Enemigo1(){
            imagen = al_load_bitmap("imagenes/enemigo1.png");
            vidas = al_load_bitmap("imagenes/vidas.png");
            al_convert_mask_to_alpha(vidas, al_map_rgb(255,255,255));
            al_convert_mask_to_alpha(imagen, al_map_rgb(255,255,255));
            x = 300;
            y = 300;
            ancho = 32;
            alto = 32;
            dir = LEFT;
            moveSpeed = 5;
            estado = false;
            vida = 3;
        }
        ~Enemigo1(){
            al_destroy_bitmap(imagen);
            al_destroy_bitmap(vidas);
            estado = false;
        }

        void Dibujar(){
            if(estado){
            al_draw_bitmap_region(imagen,sourceX,dir*32.3,32.3,32,x,y,NULL);
            al_draw_bitmap_region(vidas,0,(al_get_bitmap_height(vidas)/5-1)*vida,102,35.6,x,y-40,0);
            }
        }

        void Dibujar(int sX){
            if(estado){
            al_draw_bitmap_region(imagen,sX,dir*32.3,32.3,32,x,y,NULL);
            al_draw_bitmap_region(vidas,0,(al_get_bitmap_height(vidas)/5-1)*vida,102,35.6,x,y-40,0);
            }
        }

        void setSourceX(){
            if(estado){
            sourceX += al_get_bitmap_width(imagen) / 3;
            }
            else{
                sourceX = 0;
            }
            if(sourceX >= al_get_bitmap_width(imagen) - al_get_bitmap_width(imagen)/3){
               sourceX = 0;
            }
        }

        void movimiento(int xJugador, int yJugador){
            if(x > xJugador){
                dir = 1;
                x = x - moveSpeed;
            }
            if(x < xJugador){
                dir = 2;
                x = x + moveSpeed;
            }
            if(y > yJugador){
                dir = 3;
                y = y - moveSpeed;
            }
            if(y < yJugador){
                dir = 0;
                y = y + moveSpeed;
                }
        }

};

#endif // CENEMIGO1_H_INCLUDED
