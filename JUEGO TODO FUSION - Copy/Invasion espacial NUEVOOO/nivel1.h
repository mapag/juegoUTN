#ifndef NIVEL2_H_INCLUDED
#define NIVEL2_H_INCLUDED

int nivel1(class Player *jugador, class Tiro *tiro){

    jugador->setX(10);
    Enemigo2 en2[6];
    TiroEn3 tEn3[3];

    en2[0].setX(120);
    en2[0].setY(10);
    en2[1].setX(340);
    en2[1].setY(10);
    en2[2].setX(560);
    en2[2].setY(10);
    en2[3].setX(120);
    en2[3].setY(550);
    en2[4].setX(340);
    en2[4].setY(550);
    en2[5].setX(560);
    en2[5].setY(550);

    tEn3[0].setX(130);
    tEn3[0].setY(25);
    tEn3[1].setX(350);
    tEn3[1].setY(25);
    tEn3[2].setX(570);
    tEn3[2].setY(25);

    jugador->setMoveSpeed(20);

    int done = 100;
    int fade = 0;
    bool draw = true,pasoElNivel = false;
    int vidaParaInterfaz;
    srand( time( 0 ) );
    int invulnerable = 0, acum =0;
    int tempoTermino = 0;


    ALLEGRO_TIMER *timerJuego = al_create_timer(1.0 / 20);
    ALLEGRO_KEYBOARD_STATE keyState;

    ALLEGRO_BITMAP *fader = al_load_bitmap("imagenes/fade.png");

    ALLEGRO_EVENT_QUEUE *EventQueue = al_create_event_queue();

    al_register_event_source(EventQueue, al_get_timer_event_source(timerJuego));
    al_register_event_source(EventQueue, al_get_keyboard_event_source());

    std::vector< std::vector <int> > mapa;
    CargarMapa("mapas/prob.txt", mapa);

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

            if(invulnerable == 1){
                acum++;
            }
            if(acum >= 50){
                invulnerable = 0;
                acum = 0;
            }
            if(en2[0].getEstado() == false && en2[1].getEstado() == false && en2[2].getEstado() == false && en2[3].getEstado() == false && en2[4].getEstado() == false && en2[5].getEstado() == false && tempoTermino > 700){
                    pasoElNivel = true;
                }else{
                    tempoTermino++;
                }

            jugador->HLP();

            for(int i=0;i<3;i++){
                if(tEn3[i].ColisionaCon(jugador) && tEn3[i].getEstado() == true){
                    if(!invulnerable){
                        jugador->setVida(jugador->getVida()-1);
                        invulnerable = 1;
                    }

                }
            }

            vidaParaInterfaz=jugador->getVida();
        }

            if(draw){
                if(jugador->getX()>=640)
                    done = 4;
                DibujarMapa(mapa);
                for(int i=0; i<3; i++){
                    tEn3[i].dibujar();
                }
                for(int i=0; i<6; i++){
                en2[i].Dibujar();
                }
                jugador->Dibujar();

                interfaz1(vidaParaInterfaz);
                if(vidaParaInterfaz <= 0){
                    fade = fade+10;
                    if(fade > 255){
                        done =  -1;
                    }
                }
                al_draw_tinted_bitmap(fader, al_map_rgba(0,0,0, fade), 0,0, NULL);

                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));
            }

    }
    al_destroy_timer(timerJuego);
    al_destroy_event_queue(EventQueue);
    return done;
}

#endif // NIVEL2_H_INCLUDED
