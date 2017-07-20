#ifndef CJUGADOR_H_INCLUDED
#define CJUGADOR_H_INCLUDED

#include "cEntidad.h"

class Player : public Entidad{
private:
    bool invulnerable;
public:
    Player(){
        imagen = al_load_bitmap("imagenes/player.png");
        al_convert_mask_to_alpha(imagen, al_map_rgb(255,255,255));
        x = 20;
        y = 300;
        ancho = 52;//al_get_bitmap_width(imagen)/8;
        alto = 49;//al_get_bitmap_height(imagen)/4;
        dir = RIGHT;
        moveSpeed = 10;
        vida = 5;
        invulnerable = false;
        estado = false;
    }
    ~Player(){
        al_destroy_bitmap(imagen);
    }

    void Dibujar(){
        al_draw_bitmap_region(imagen,sourceX,dir*52,49.25,52,x,y,NULL);
    }

    void setInvulnerable(bool i){invulnerable = i;}
    bool getInvulnerable(){return invulnerable;}

    void setSourceX(){
        if(estado){
        sourceX += al_get_bitmap_width(imagen) / 8;
        }
        else{
            sourceX = 0;
        }
        if(sourceX >= al_get_bitmap_width(imagen) - al_get_bitmap_width(imagen)/8){
           sourceX = 0;
        }
    }

    void movimiento(ALLEGRO_KEYBOARD_STATE &keyState){
        estado = true;
        if(al_key_down(&keyState, ALLEGRO_KEY_S)){
            y = y + moveSpeed;
            dir = 0;
        }
        else if(al_key_down(&keyState, ALLEGRO_KEY_W)){
            y = y - moveSpeed;
            dir = 3;
        }
        else if(al_key_down(&keyState, ALLEGRO_KEY_D)){
            x = x + moveSpeed;
            dir = 2;
        }
        else if(al_key_down(&keyState, ALLEGRO_KEY_A)){
            x = x - moveSpeed;
            dir = 1;
        }
        else
            estado = false;
    }

    void HLP(){
        if(x >=670){
            x = x - moveSpeed;
        }
        if(x <= 1){
            x = x + moveSpeed;
        }
        if(y >= 536){
            y = y - moveSpeed;
        }
        if(y <= 0){
            y = y + moveSpeed;
        }
    }

};

#endif // CJUGADOR_H_INCLUDED
