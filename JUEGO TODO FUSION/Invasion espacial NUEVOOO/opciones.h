#ifndef OPCIONES_H_INCLUDED
#define OPCIONES_H_INCLUDED

int opciones(bool *flagIntro, bool *flagTuto, bool *flagSonido){
        ALLEGRO_EVENT_QUEUE *cola = al_create_event_queue();
        ALLEGRO_TIMER *tempo;
        ALLEGRO_KEYBOARD_STATE keyState;
        ALLEGRO_MOUSE_STATE mouseState1;

        bool dibujar=true;
        int x,y,retorno=100,m1=0;

        ALLEGRO_BITMAP *fondo,*op10, *op01 ,*cursor;

        fondo = al_load_bitmap("imagPrev/opciones.jpg");
        op10= al_load_bitmap("imagPrev/op10.png");
        op01= al_load_bitmap("imagPrev/op01.png");
        cursor = al_load_bitmap("imagenes/cursor.bmp");

        tempo = al_create_timer(1.0/60);

        al_register_event_source(cola,al_get_keyboard_event_source());
        al_register_event_source(cola,al_get_mouse_event_source());
        al_register_event_source(cola,al_get_timer_event_source(tempo));

        al_convert_mask_to_alpha(cursor,al_map_rgb(0,0,0));

        al_start_timer(tempo);


    while(retorno == 100){
        ALLEGRO_EVENT evento;
        al_wait_for_event(cola,&evento);
        al_get_keyboard_state(&keyState);
        al_get_mouse_state(&mouseState1);

        if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        retorno = 0;}

        if(al_key_down(&keyState,ALLEGRO_KEY_ESCAPE)){
        retorno = 2;}


        if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            if(evento.mouse.button == 1){
                m1=1;
            }
        }
        if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if(evento.mouse.button == 1){
                m1=0;
            }
        }

        if(evento.type == ALLEGRO_EVENT_TIMER){

            x = mouseState1.x;
            y = mouseState1.y;
            dibujar = true;
        }

        if(dibujar){
            dibujar = false;
            al_draw_bitmap(fondo,0,0,NULL);

            if(*flagIntro)
                al_draw_bitmap(op01,545,185,NULL);
            else
                al_draw_bitmap(op10,545,185,NULL);

            if(x > 545 && x < 690 && y > 185 && y < 220){
                if(m1 == 1){
                    if(*flagIntro)
                        *flagIntro = false;
                    else
                        *flagIntro = true;
                }
            }
            ///
            if(*flagTuto)
                al_draw_bitmap(op01,545,255,NULL);
            else
                al_draw_bitmap(op10,545,255,NULL);

            if(x > 545 && x < 690 && y > 255 && y < 295){
                if(m1 == 1){
                    if(*flagTuto)
                        *flagTuto = false;
                    else
                        *flagTuto = true;
                }
            }

            if(*flagSonido)
                al_draw_bitmap(op01,545,335,NULL);
            else
                al_draw_bitmap(op10,545,335,NULL);

            if(x > 545 && x < 690 && y > 340 && y < 375){
                if(m1 == 1){
                    if(*flagSonido)
                        *flagSonido = false;
                    else
                        *flagSonido = true;
                }
            }

            if(x > 530 && x < 732 && y > 540 && y < 600){
                if(m1 == 1){
                    retorno = 2;
                }
            }

            al_draw_bitmap(cursor,x,y,NULL);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }

    al_destroy_bitmap(cursor);
    al_destroy_bitmap(fondo);
    al_destroy_bitmap(op10);
    al_destroy_bitmap(op01);

    al_destroy_timer(tempo);

    al_destroy_event_queue(cola);

    return retorno;
}

#endif // OPCIONES_H_INCLUDED
