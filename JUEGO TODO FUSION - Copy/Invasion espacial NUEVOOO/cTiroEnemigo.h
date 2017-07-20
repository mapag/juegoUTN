#ifndef CTIROENEMIGO_H_INCLUDED
#define CTIROENEMIGO_H_INCLUDED

#include "cEntidad.h"

class TiroEn: public Entidad{
private:
    float Acum;
    int Estate;
    int movX;
    int movY;
public:
    TiroEn(){
    Estate = false;
    imagen = al_load_bitmap("imagenes/tiroenemigo.png");
    estado=true;
    ancho = 13;
    alto = 13;
    sourceX = 23;
    sourceY = 0;
    Acum = 0;
    movX = 0;
    movY = 0;
    al_convert_mask_to_alpha(imagen, al_map_rgb(255,255,255));
    }

    ~TiroEn(){
            al_destroy_bitmap(imagen);
            estado = false;
        }

    void setAcum(float A){
    Acum = A;}

    float getAcum(){
    return Acum;}

    void setSourceX(float sx){
    sourceX = sx;
    }

    void setMovX(int m){
    movX = m;}

    void setMovY(int m){
    movY = m;}

    int getMovX(){
    return movX;}

    int getMovY(){
    return movY;}

    void setEstate(int E){
    Estate = E;}

    int getEstate(){
    return Estate;}

    void dibujar(){
    if(estado){
    if(Estate == 3){
    al_draw_bitmap_region(imagen,sourceX*2,sourceY,23,27.5,x,y,0);}
    else if(Estate == 2){
    al_draw_bitmap_region(imagen,sourceX*1,sourceY,23,27.5,x,y,0);}
    else if(Estate == 1){
    al_draw_bitmap_region(imagen,sourceX*0,sourceY,23,27.5,x,y,0);}
    }}

    void setSourceY(int Y){
    sourceY = Y;}
};

#endif // CTIROENEMIGO_H_INCLUDED
