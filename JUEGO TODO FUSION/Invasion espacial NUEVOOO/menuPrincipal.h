#ifndef MENUPRINCIPAL_H_INCLUDED
#define MENUPRINCIPAL_H_INCLUDED

int menuPrincipal(){
        ALLEGRO_DISPLAY *ventana;
        ALLEGRO_EVENT_QUEUE *cola = al_create_event_queue();
        ALLEGRO_TIMER *tempo;
        ALLEGRO_KEYBOARD_STATE keyState;
        ALLEGRO_MOUSE_STATE mouseState1;
        al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
        ventana = al_create_display(1024,491);
        /**
        HWND hidden_window;
        AllocConsole();
        hidden_window=FindWindowA("ConsoleWindowClass",NULL);
        ShowWindow(hidden_window,NULL);
        /*/

        bool dibujar=true;
        int x,y,retorno=100,m1=0;

        ALLEGRO_BITMAP *fondo,*menu,*cursor;

        fondo = al_load_bitmap("imagPrev/fondo.png");
        menu = al_load_bitmap("imagenes/menu.png");
        cursor = al_load_bitmap("imagenes/cursor.bmp");

        tempo = al_create_timer(1.0/60);

        al_register_event_source(cola,al_get_keyboard_event_source());
        al_register_event_source(cola,al_get_mouse_event_source());
        al_register_event_source(cola,al_get_timer_event_source(tempo));
        al_register_event_source(cola,al_get_display_event_source(ventana));

        al_convert_mask_to_alpha(menu,al_map_rgb(0,0,0));
        al_convert_mask_to_alpha(cursor,al_map_rgb(0,0,0));

        al_hide_mouse_cursor(ventana);

        al_start_timer(tempo);


    while(retorno == 100){
        ALLEGRO_EVENT evento;
        al_wait_for_event(cola,&evento);
        al_get_keyboard_state(&keyState);
        al_get_mouse_state(&mouseState1);

        if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        retorno = 0;}

        if(al_key_down(&keyState,ALLEGRO_KEY_ESCAPE)){
        retorno = 0;}


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

            if(x > 700 && x < 910 && y > 400 && y < 440){
                al_draw_bitmap_region(menu,0,80,226,40,700,400,NULL);
                if(m1 == 1){
                    retorno = 2;
                }
            }
            else
                al_draw_bitmap_region(menu,0,20,226,40,700,400,NULL);

            if(x > 700 && x < 815 && y > 450 && y < 500){
                al_draw_bitmap_region(menu,0,440,226,40,700,450,NULL);
                if(m1 == 1){
                    retorno = 0;
                }
            }
            else
                al_draw_bitmap_region(menu,0,380,226,40,700,450,NULL);

            al_draw_bitmap(cursor,x,y,NULL);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }

    al_destroy_bitmap(cursor);
    al_destroy_bitmap(fondo);
    al_destroy_bitmap(menu);
    al_destroy_timer(tempo);
    al_destroy_event_queue(cola);
    al_destroy_display(ventana);

    return retorno;
}

#endif // MENUPRINCIPAL_H_INCLUDED
