#ifndef NIVELTUTO2_H_INCLUDED
#define NIVELTUTO2_H_INCLUDED

int nivelTuto2(class Player *jugador, class Tiro *tiro){

    jugador->setX(100);
    jugador->setY(400);
    jugador->setDir(2);

    Enemigo1 en1;
    en1.setEstado(1);
    en1.setX(500);
    en1.setY(400);

    int done = -1;
    bool draw = true;
    bool disparo = false;
    int vidaParaInterfaz;

    ALLEGRO_BITMAP *fondo = al_load_bitmap("imagPrev/tuto2.1.png");
    ALLEGRO_BITMAP *fondo2 = al_load_bitmap("imagPrev/tuto2.2.png");

    ALLEGRO_BITMAP *flecha = al_load_bitmap("imagenes/flecha.png");
    al_convert_mask_to_alpha(flecha,al_map_rgb(255,255,255));

    ALLEGRO_TIMER *timerJuego = al_create_timer(1.0 / 20);

    ALLEGRO_KEYBOARD_STATE keyState;

    ALLEGRO_EVENT_QUEUE *EventQueue = al_create_event_queue();

    al_register_event_source(EventQueue, al_get_timer_event_source(timerJuego));
    al_register_event_source(EventQueue, al_get_keyboard_event_source());

    al_start_timer(timerJuego);

    while(done == -1){
        ALLEGRO_EVENT Event;
        al_wait_for_event(EventQueue, &Event);

        if(Event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(Event.keyboard.keycode){
            case ALLEGRO_KEY_ESCAPE:
                done = 0;
            }
        }

        if(Event.type == ALLEGRO_EVENT_KEY_DOWN){
            if(Event.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    if(tiro->getEstado() == false){

                    tiro->setDir(jugador->getDir());

                    if(tiro->getDir()==0){
                    tiro->setX(jugador->getX()+18);
                    tiro->setY(jugador->getY()+38);
                    }
                    if(tiro->getDir()==1){
                    tiro->setX(jugador->getX()-20);
                    tiro->setY(jugador->getY()+22);
                    }
                    if(tiro->getDir()==2){
                    tiro->setX(jugador->getX()+40);
                    tiro->setY(jugador->getY()+21);
                    }
                    if(tiro->getDir()==3){
                    tiro->setX(jugador->getX()+16);
                    tiro->setY(jugador->getY()-18);
                    }
                    tiro->setEstado(1);
                    }
            }
        }

        else if(Event.type == ALLEGRO_EVENT_TIMER){

            al_get_keyboard_state(&keyState);
            jugador->movimiento(keyState);
            jugador->setSourceX();

            tiro->tiroPared(); ///TIRO CHOCA CON PARED

            ///COLISION TIRO CON ENEMIGO
            if(en1.getEstado() == 1 && tiro->getEstado() == true && en1.ColisionaCon(tiro)){
                if(en1.getVida()!=0){
                    en1.setVida(en1.getVida() - 1);
                }
                else{en1.setEstado(false);}
                tiro->setEstado(0);
            }

            ///MOVIMIENTO DE TIRO
            if(tiro->getEstado()){
                tiro->destino();
            }

            jugador->HLP();
            if(jugador->getX() > 630){
                done = 9;
            }

            vidaParaInterfaz=jugador->getVida();

            if(tiro->getEstado() == true){
                disparo = true;
            }
        }

            if(draw){
                if(!disparo)
                    al_draw_bitmap(fondo,0,0,NULL);
                else{
                    al_draw_bitmap(fondo2,0,0,NULL);
                    en1.Dibujar(0);
                }

                if(en1.getEstado() == 0){
                    al_draw_bitmap(flecha,450,150,NULL);
                }

                jugador->Dibujar();
                if(tiro->getEstado()){
                    tiro->Dibujar();
                }

                interfaz1(vidaParaInterfaz);

                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));
            }

    }
    al_destroy_bitmap(fondo);
    al_destroy_bitmap(fondo2);
    al_destroy_bitmap(flecha);
    al_destroy_timer(timerJuego);
    al_destroy_event_queue(EventQueue);
    return done;
}

#endif // NIVELTUTO2_H_INCLUDED
