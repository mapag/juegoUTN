#ifndef CJEFEFINAL_H_INCLUDED
#define CJEFEFINAL_H_INCLUDED

#include "cEntidad.h"
#include "cJFEscudo.h"
#include "cTiroBoss.h"

class JefeFinal : public Entidad{
    private:
        bool izq, der;
        int tempo;
        int acum;
        bool murio;
    public:
        JFEscudo Escudo;
        TiroBoss tiroBoss[3];
        JefeFinal(){
            imagen = al_load_bitmap("imagenes/jf.png");
            x = 350;
            y = 100;
            ancho = 64;
            alto = 64;
            moveSpeed = 10;
            estado = true;
            dir = DOWN;
            izq = true;
            der = false;
            tempo = 0;
            acum = 0;
            vida = 10;
            murio = false;
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

    void setSourceY(){
        sourceY = dir * 64;
    }

    ~JefeFinal(){
        al_destroy_bitmap(imagen);
        estado = false;
    }

    void dibujar(){
        if(!murio)
            al_draw_bitmap_region(imagen,sourceX, sourceY,ancho,alto,x,y,NULL);
    }

    void dibujarTiro(){
        for(int i=0;i<3;i++){
    tiroBoss[i].dibujar();}}

    void movimiento(float xj,float yj){

        if(izq){
            if(x > 100){
                dir= LEFT;
                x = x - moveSpeed;
            }
            else if(x == 100){
                dir = DOWN;
                estado = false;
                if(tempo < 300){
                    tempo = tempo +5;
                }else{
                    tempo = 0;
                    izq = false;
                    der = true;
                    estado = true;
                }
            }
        }
        else if(der){
            if(x < 500){
                dir = RIGHT;
                x = x + moveSpeed;
            }
            else if(x == 500){
                dir = DOWN;
                estado = false;
                if(tempo < 300){
                    tempo = tempo +5;
                }else{
                estado = true;
                tempo = 0;
                izq = true;
                der = false;
                }
            }
        }

        if(estado){
                for(int i=0;i<3;i++){
                tiroBoss[i].setSourceX(0);
                tiroBoss[i].setSourceY(tiroBoss[i].getSourceY() + 38);
                if(tiroBoss[i].getSourceY()>= 152){tiroBoss[i].setSourceY(0);}
                tiroBoss[i].setAcum(0);
                tiroBoss[i].setX(x);
                tiroBoss[i].setY(y);
                tiroBoss[0].setXmov((xj - x)/tiroBoss[i].getMoveSpeed());
                tiroBoss[0].setYmov((yj - y)/tiroBoss[i].getMoveSpeed());
                tiroBoss[1].setXmov((xj - (x-50))/tiroBoss[i].getMoveSpeed());
                tiroBoss[1].setYmov((yj - y)/tiroBoss[i].getMoveSpeed());
                tiroBoss[2].setXmov((xj - (x+50))/tiroBoss[i].getMoveSpeed());
                tiroBoss[2].setYmov((yj - y)/tiroBoss[i].getMoveSpeed());
                }
            }

        Escudo.setX(x-45);
        Escudo.setY(y+50);

        if(dir == DOWN)
            for(int i=0;i<3;i++){
            tiroBoss[i].setEstado(1);}
        else
            for(int i=0;i<3;i++){
            tiroBoss[i].setEstado(0);}

        if(dir == DOWN)
            Escudo.setEstado(1);
        else
            Escudo.setEstado(0);

for(int i=0;i<3;i++){
    if(tiroBoss[i].getEstado()){
        tiroBoss[i].setAcum(tiroBoss[i].getAcum()+4);
        if(tiroBoss[i].getAcum() == 0){
            tiroBoss[i].setSourceX(tiroBoss[i].getSourceX()+32);
        }
        if(tiroBoss[i].getAcum() == 12){
            tiroBoss[i].setSourceX(tiroBoss[i].getSourceX()+32);
        }
        if(tiroBoss[i].getAcum() == 24){
            tiroBoss[i].setSourceX(tiroBoss[i].getSourceX()+32);
        }
        if(tiroBoss[i].getAcum() == 36){
            tiroBoss[i].setSourceX(tiroBoss[i].getSourceX()+32);
        }
        if(tiroBoss[i].getAcum() == 48){
            tiroBoss[i].setSourceX(tiroBoss[i].getSourceX()+32);
        }
        if(tiroBoss[i].getAcum() == 60){
            tiroBoss[i].setSourceX(tiroBoss[i].getSourceX()+32);
        }
        if(tiroBoss[i].getAcum() == 72){
            tiroBoss[i].setSourceX(tiroBoss[i].getSourceX()+32);
        }
        if(tiroBoss[i].getAcum() == 84){
            tiroBoss[i].setSourceX(tiroBoss[i].getSourceX()+32);
        }
        if(tiroBoss[i].getAcum() == 96){
            tiroBoss[i].setSourceX(tiroBoss[i].getSourceX()+32);
        }
        if(tiroBoss[i].getAcum() == 108){
            tiroBoss[i].setSourceX(tiroBoss[i].getSourceX()+32);
        }
        if(tiroBoss[i].getAcum() == 120){
            tiroBoss[i].setSourceX(tiroBoss[i].getSourceX()+32);
        }

        tiroBoss[i].setX(tiroBoss[i].getX() + tiroBoss[i].getXmov());
        tiroBoss[i].setY(tiroBoss[i].getY() + tiroBoss[i].getYmov());
    }}

        if(vida <= 0)
            murio = true;
    }

    bool getMurio(){
        return murio;
    }

};


#endif // CJEFEFINAL_H_INCLUDED
