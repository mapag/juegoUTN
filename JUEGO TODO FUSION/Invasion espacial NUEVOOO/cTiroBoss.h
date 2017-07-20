#ifndef CTIROBOSS_H_INCLUDED
#define CTIROBOSS_H_INCLUDED

#include "cEntidad.h"a
#include "cJugador.h"

class TiroBoss : public Entidad{
private:
    int Xmov;
    int Ymov;
    int acum;
public:
    TiroBoss(){
        imagen = al_load_bitmap("imagenes/tiroBoss.png");
        al_convert_mask_to_alpha(imagen, al_map_rgb(0,0,0));
        x = 0;
        y = 0;
        ancho = 21;
        alto = 17;
        estado = true;
        moveSpeed = 25;
        dir = DOWN;
        Xmov = 0;
        Ymov = 0;
        sourceX = 0;
        sourceY = 0;
        acum = 0;
    }


    void dibujar(){
        if(estado){
            al_draw_bitmap_region(imagen,sourceX,sourceY,32,38,x,y,NULL);
        }
    }

    ~TiroBoss(){
        al_destroy_bitmap(imagen);
        estado = false;
    }

    void setAcum(int n){
    acum = n;}

    int getAcum(){
    return acum;}

    void setSourceX(float n){
    sourceX = n;}

    void setSourceY(int n){
    sourceY = n;}

    void setXmov(int n){
    Xmov = n;}

    void setYmov(int n){
    Ymov = n;}

    float getSourceX(){
    return sourceX;}

    float getSourceY(){
    return sourceY;}

    int getXmov(){
    return Xmov;}

    int getYmov(){
    return Ymov;}

};

#endif // CTIROBOSS_H_INCLUDED
