#ifndef PERDER_H_INCLUDED
#define PERDER_H_INCLUDED

int perder(){
    bool dibujar = true;

    ALLEGRO_BITMAP *fondo = al_load_bitmap("imagenes/gameOver.png");
    ALLEGRO_BITMAP *fondoInt = al_load_bitmap("imagenes/Intentar.png");
    ALLEGRO_BITMAP *fondoMenu = al_load_bitmap("imagenes/menuGO.png");
    ALLEGRO_BITMAP *cursor = al_load_bitmap("imagenes/cursor.bmp");

    ALLEGRO_EVENT_QUEUE *EventQueue = al_create_event_queue();
    ALLEGRO_MOUSE_STATE mouseState1;

    ALLEGRO_TIMER *tempo;
    tempo = al_create_timer(1.0/60);

    al_convert_mask_to_alpha(cursor,al_map_rgb(0,0,0));

    al_register_event_source(EventQueue, al_get_keyboard_event_source());
    al_register_event_source(EventQueue,al_get_mouse_event_source());
    al_register_event_source(EventQueue, al_get_timer_event_source(tempo));

    int done = -1;
    int m1, x, y;

    al_start_timer(tempo);

    while(done == -1){
        m1=0;
        ALLEGRO_EVENT Event;
        al_wait_for_event(EventQueue, &Event);
        al_get_mouse_state(&mouseState1);

        if(Event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(Event.keyboard.keycode){
            case ALLEGRO_KEY_ESCAPE:
                done = 0;
            }
        }

        if(Event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(Event.mouse.button == 1){
                m1=1;
            }
        }/*
        if(Event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if(Event.mouse.button == 1){
                m1=0;
            }
        }*/

        if(Event.type == ALLEGRO_EVENT_TIMER){
            x = mouseState1.x;
            y = mouseState1.y;
            dibujar = true;
        }

        if(dibujar){
            if(x < 350 && y > 400){
                al_draw_bitmap(fondoInt, 0,0,NULL);
                if(m1 == 1){
                    done = 1;
                }
            }
            else if(x > 400 && y > 400){
                al_draw_bitmap(fondoMenu,0,0,NULL);
                if(m1 == 1){
                    done = -2;
                }
            }
            else
                al_draw_bitmap(fondo, 0,0, NULL);
        ///

        al_draw_bitmap(cursor,x,y,NULL);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        }
    }

    al_destroy_timer(tempo);
    al_destroy_bitmap(fondo);
    return done;
}

#endif // PERDER_H_INCLUDED
