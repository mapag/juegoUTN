#ifndef CENEMIGO3_H_INCLUDED
#define CENEMIGO3_H_INCLUDED

#include "cEntidad.h"
#include "cTiroEnemigo3.h"

class Enemigo3 : public Entidad{
    private:
            ALLEGRO_BITMAP*vidas;
            int movSpeedTiro;
            int movX;
            int movY;
    public:
            TiroEn tiroEnemigo;
            Enemigo3(){
            imagen = al_load_bitmap("imagenes/enemigo4.png");
            vidas = al_load_bitmap("imagenes/vidas.png");
            al_convert_mask_to_alpha(vidas, al_map_rgb(255,255,255));
            x = 720;
            y = 300;
            ancho = 26;
            alto = 32;
            dir = DOWN;
            moveSpeed = 3;
            estado = false;
            sourceY = 27.5;
            vida = 2;
            movX = 0;
            movY = 0;
            movSpeedTiro = 25;
        }
        ~Enemigo3(){
            al_destroy_bitmap(imagen);
            al_destroy_bitmap(vidas);
            estado = false;
        }

        void Dibujar(){
            if(estado){
            al_draw_bitmap_region(imagen,sourceX,dir*32.3,32.3,32,x,y,NULL);
            al_draw_bitmap_region(vidas,0,(al_get_bitmap_height(vidas)/5-1)*vida,102,35.6,x,y-40,0);
            }
            tiroEnemigo.dibujar();
        }

        int getTiroEstate(){
        return tiroEnemigo.getEstate();
        }

        void disparar(int xj,int yj){

        tiroEnemigo.setSourceY(27.5 * 1);

        if(tiroEnemigo.getEstate()>1){
            tiroEnemigo.setAcum(tiroEnemigo.getAcum()+0.05);
        }


        if(tiroEnemigo.getAcum() >= 0.3){tiroEnemigo.setEstate(2);}
        if(tiroEnemigo.getAcum() >= 0.5){tiroEnemigo.setEstate(1);tiroEnemigo.setAcum(0);}



        if(estado){
            sourceX += al_get_bitmap_width(imagen) / 3;
            }
            else{
                sourceX = 0;
            }
            if(sourceX >= al_get_bitmap_width(imagen) - al_get_bitmap_width(imagen)/3){
               sourceX = 0;
            }

            if(x > xj){
                dir = 1;
                x = x - moveSpeed;
            }
            if(x < xj){
                dir = 2;
                x = x + moveSpeed;
            }
            if(y > yj){
                dir = 3;
                y = y - moveSpeed;
            }
            if(y < yj){
                dir = 0;
                y = y + moveSpeed;
                }

        if(!tiroEnemigo.getEstate()){
            movX = (xj - x)/movSpeedTiro;
            movY = (yj - y)/movSpeedTiro;
            tiroEnemigo.setX(x);
            tiroEnemigo.setY(y);
            tiroEnemigo.setEstate(3);
        }

        if(tiroEnemigo.getEstate()){
            tiroEnemigo.setX(tiroEnemigo.getX()+movX);
            tiroEnemigo.setY(tiroEnemigo.getY()+movY);
            if(tiroEnemigo.getX() >=640 || tiroEnemigo.getX() <=1 || tiroEnemigo.getY() >= 536 || tiroEnemigo.getY() <=0)
            tiroEnemigo.setEstate(0);
            }
        }
};

#endif // CENEMIGO3_H_INCLUDED
