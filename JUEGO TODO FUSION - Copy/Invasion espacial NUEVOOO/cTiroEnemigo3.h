#ifndef CTIROENEMIGO3_H_INCLUDED
#define CTIROENEMIGO3_H_INCLUDED

class TiroEn3 : public Entidad{
    private:
    int tempo;
    public:
    TiroEn3(){
        imagen = al_load_bitmap("imagenes/laser.png");
        al_convert_mask_to_alpha(imagen,al_map_rgb(0,0,0));
        x = 0;
        y = 0;
        ancho = 10;
        alto = 550;
        tempo = 0;
        estado = false;
    }

    void dibujar(){
        if(tempo >= 100){
            estado = true;
            al_draw_bitmap(imagen,x,y, NULL);
        }
        if(tempo == 200){
            tempo = 0;
            estado = false;
        }
        else
            tempo= tempo +5;

    }
};

#endif // CTIROENEMIGO3_H_INCLUDED
