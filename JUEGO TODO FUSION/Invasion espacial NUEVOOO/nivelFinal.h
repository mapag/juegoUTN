#ifndef NIVELFINAL_H_INCLUDED
#define NIVELFINAL_H_INCLUDED

int Final(class Player *jugador){
    jugador->setX(332);
    jugador->setY(500);
    jugador->setDir(3);
    jugador->setMoveSpeed(10);

    int done = 100;
    int fade = 0;
    bool draw = true;
    int vidaParaInterfaz;

    ALLEGRO_TIMER *timerJuego = al_create_timer(1.0 / 20);
    ALLEGRO_KEYBOARD_STATE keyState;

    ALLEGRO_BITMAP *fader = al_load_bitmap("imagenes/fade.png");
    ALLEGRO_BITMAP *apagar = al_load_bitmap("imagenes/apagar.png");
    al_convert_mask_to_alpha(apagar,al_map_rgb(255,255,255));

    ALLEGRO_EVENT_QUEUE *EventQueue = al_create_event_queue();

    al_register_event_source(EventQueue, al_get_timer_event_source(timerJuego));
    al_register_event_source(EventQueue, al_get_keyboard_event_source());

    std::vector< std::vector <int> > mapa;
    CargarMapa("mapas/mapfi.txt", mapa);

    al_start_timer(timerJuego);

    while(done == 100){
        ALLEGRO_EVENT Event;
        al_wait_for_event(EventQueue, &Event);

        if(Event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(Event.keyboard.keycode){
            case ALLEGRO_KEY_ESCAPE:
                done = 0;
            }
        }

        else if(Event.type == ALLEGRO_EVENT_TIMER){
            al_get_keyboard_state(&keyState);

            jugador->movimiento(keyState);
            jugador->setSourceX();
            jugador->HLP();

            vidaParaInterfaz=jugador->getVida();

            if(jugador->getY() < 150){
                fade = fade+10;
                    if(fade > 255){
                        done =  0;
                }
            }
        }

            if(draw){
                DibujarMapa(mapa);

                al_draw_bitmap(apagar,332, 100, NULL);

                jugador->Dibujar();

                interfaz1(vidaParaInterfaz);

                al_draw_tinted_bitmap(fader, al_map_rgba(0,0,0, fade), 0,0, NULL);

                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));
            }

    }
    al_destroy_timer(timerJuego);
    al_destroy_bitmap(fader);
    al_destroy_bitmap(apagar);
    al_destroy_event_queue(EventQueue);
    return done;
}

#endif // NIVELFINAL_H_INCLUDED
