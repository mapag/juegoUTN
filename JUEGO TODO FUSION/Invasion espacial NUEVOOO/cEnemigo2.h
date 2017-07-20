#ifndef CENEMIGO2_H_INCLUDED
#define CENEMIGO2_H_INCLUDED

#include "cEntidad.h"
#include "cTiroEnemigo.h"

class Enemigo2 : public Entidad{
            int movSpeedTiro;
            int movY;
            int movX;
    public:
            TiroEn tiroEn[8];
            Enemigo2(){
            imagen = al_load_bitmap("imagenes/enemigo234.png");
            al_convert_mask_to_alpha(imagen, al_map_rgb(255,255,255));
            x = 384;
            y = 288;
            ancho = 32;
            alto = 32;
            estado = true;
            movY = 0;
            movX = 0;
            movSpeedTiro = 15;
        }
        ~Enemigo2(){
            al_destroy_bitmap(imagen);
            estado = false;
        }

        void Dibujar(){
            if(estado){
            al_draw_bitmap_region(imagen,0,0,32,32,x,y,NULL);
            }
            for(int i=0;i<8;i++){
            tiroEn[i].dibujar();
        }}

        void disparar(float *acumTiro){

        int cant=0;

        for(int i=0;i<8;i++){
            if(tiroEn[i].getEstate()==false){
                cant++;
            }
        }

        if(cant == 8){
            for(int i=0;i<8;i++){
                tiroEn[i].setEstate(3);
                tiroEn[i].setY(y);
                tiroEn[i].setX(x+4);
            }
        }

        if(tiroEn[1].getEstate()==3 || tiroEn[1].getEstate()==2){*acumTiro += 0.05;}

        if(*acumTiro >= 0.3){
            for(int i=0;i<8;i++){
                tiroEn[i].setEstate(2);
            }
        }

        if(*acumTiro >= 0.5){
            for(int i=0;i<8;i++){
                tiroEn[i].setEstate(1);
                *acumTiro = 0;
            }
        }

            if(tiroEn[0].getEstate()){
                tiroEn[0].setY(tiroEn[0].getY()-movSpeedTiro);}
               if(tiroEn[1].getEstate()){
                tiroEn[1].setY(tiroEn[1].getY()-movSpeedTiro);
                tiroEn[1].setX(tiroEn[1].getX()+movSpeedTiro);}
                if(tiroEn[2].getEstate()){
                    tiroEn[2].setX(tiroEn[2].getX()+movSpeedTiro);}
                if(tiroEn[3].getEstate()){
                    tiroEn[3].setY(tiroEn[3].getY()+movSpeedTiro);
                    tiroEn[3].setX(tiroEn[3].getX()+movSpeedTiro);}
                if(tiroEn[4].getEstate()){
                    tiroEn[4].setY(tiroEn[4].getY()+movSpeedTiro);}
                if(tiroEn[5].getEstate()){
                    tiroEn[5].setY(tiroEn[5].getY()+movSpeedTiro);
                    tiroEn[5].setX(tiroEn[5].getX()-movSpeedTiro);}
                if(tiroEn[6].getEstate()){
                   tiroEn[6].setX(tiroEn[6].getX()-movSpeedTiro);}
                   if(tiroEn[7].getEstate()){
                    tiroEn[7].setY(tiroEn[7].getY()-movSpeedTiro);
                    tiroEn[7].setX(tiroEn[7].getX()-movSpeedTiro);}

        }

        int getTiroX(int numero){
        return tiroEn[numero].getX();
        }
        int getTiroY(int numero){
        return tiroEn[numero].getY();
        }
        int getTiroEstate(int numero){
        return tiroEn[numero].getEstate();
        }

        void setTiro(int numero,int estado){
        tiroEn[numero].setEstate(estado);
        }
};
#endif // CENEMIGO2_H_INCLUDED
