#ifndef CENTIDAD_H_INCLUDED
#define CENTIDAD_H_INCLUDED

class Entidad{
    protected:
        float x, y;
        float ancho, alto;
        float moveSpeed;
        enum Direction {DOWN, LEFT, RIGHT, UP};
        int dir, sourceX,sourceY;
        ALLEGRO_BITMAP *imagen;
        bool estado;
        int vida;

    public:
        void setX(float xr){x = xr;}
        void setY(float yr){ y = yr;}
        void setMoveSpeed(float mS){moveSpeed = mS;}
        void setDir(int d){dir = d;}
        void setVida(int v){vida = v;}

        float anchoBitmap(){
        return al_get_bitmap_width(imagen)/8;}

        float altoBitmap(){
        return al_get_bitmap_height(imagen)/4;}

        void setEstado(bool x){estado=x;}
        bool getEstado(){return estado;}

        float getX(){return x;}
        float getY(){return y;}
        float getMoveSpeed(){return moveSpeed;}
        int getDir(){return dir;}
        int getVida(){return vida;}

        bool ColisionaCon(class Entidad *b){
            if(this->x + this->ancho < b->x || this->x > b->x+ b->ancho || this->y + this->alto < b->y || this->y > b->y + b->alto){
                return false;
                }
            return true;
        }
};

#endif // CENTIDAD_H_INCLUDED
