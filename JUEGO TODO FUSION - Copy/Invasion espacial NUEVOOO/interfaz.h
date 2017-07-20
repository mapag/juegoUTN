#ifndef INTERFAZ_H_INCLUDED
#define INTERFAZ_H_INCLUDED

void interfaz1(int vidaJugador){
    ALLEGRO_BITMAP *imagen;
    imagen = al_load_bitmap("imagenes/vidaJugador.png");
    al_convert_mask_to_alpha(imagen, al_map_rgb(255,255,255));

    if(vidaJugador == 5){
        al_draw_bitmap_region(imagen, 0,0, al_get_bitmap_width(imagen),al_get_bitmap_height(imagen)/6,550, 50, NULL);
    }
    else if(vidaJugador == 4){
        al_draw_bitmap_region(imagen, 0,24, al_get_bitmap_width(imagen),al_get_bitmap_height(imagen)/6,550, 50, NULL);
    }
    else if(vidaJugador == 3){
        al_draw_bitmap_region(imagen, 0,48, al_get_bitmap_width(imagen),al_get_bitmap_height(imagen)/6,550, 50, NULL);
    }
    else if(vidaJugador == 2){
        al_draw_bitmap_region(imagen, 0,72, al_get_bitmap_width(imagen),al_get_bitmap_height(imagen)/6,550, 50, NULL);
    }
    else if(vidaJugador == 1){
        al_draw_bitmap_region(imagen, 0,96, al_get_bitmap_width(imagen),al_get_bitmap_height(imagen)/6,550, 50, NULL);
    }
    else if(vidaJugador <= 0){
        al_draw_bitmap_region(imagen, 0,120, al_get_bitmap_width(imagen),al_get_bitmap_height(imagen)/6,550, 50, NULL);
    }
    al_destroy_bitmap(imagen);
}


void vidaJF(int vidaJefe){
    ALLEGRO_BITMAP *imagen2;
    imagen2 = al_load_bitmap("imagenes/vidaJF.png");
    al_convert_mask_to_alpha(imagen2, al_map_rgb(0,0,0));

    if(vidaJefe == 10 || vidaJefe == 9){
        al_draw_bitmap_region(imagen2, 0,0, al_get_bitmap_width(imagen2), al_get_bitmap_height(imagen2)/6, 100,50, NULL);
    }
    else if(vidaJefe == 8 || vidaJefe == 7){
        al_draw_bitmap_region(imagen2,0,32, al_get_bitmap_width(imagen2), al_get_bitmap_height(imagen2)/6, 100,50, NULL);
    }
    else if(vidaJefe == 6 || vidaJefe == 5){
        al_draw_bitmap_region(imagen2,0,64, al_get_bitmap_width(imagen2), al_get_bitmap_height(imagen2)/6, 100,50, NULL);
    }
    else if(vidaJefe == 4 || vidaJefe == 3){
        al_draw_bitmap_region(imagen2,0,96, al_get_bitmap_width(imagen2), al_get_bitmap_height(imagen2)/6, 100,50, NULL);
    }
    else if(vidaJefe == 2 || vidaJefe == 1){
        al_draw_bitmap_region(imagen2,0,128, al_get_bitmap_width(imagen2), al_get_bitmap_height(imagen2)/6, 100,50, NULL);
    }
    else if(vidaJefe == 0){
        al_draw_bitmap_region(imagen2,0,160, al_get_bitmap_width(imagen2), al_get_bitmap_height(imagen2)/6, 100,50, NULL);
    }

    al_destroy_bitmap(imagen2);
}
#endif // INTERFAZ_H_INCLUDED
