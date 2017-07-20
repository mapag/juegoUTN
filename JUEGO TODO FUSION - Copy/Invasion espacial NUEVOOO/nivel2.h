#ifndef NIVEL3_H_INCLUDED
#define NIVEL3_H_INCLUDED

int nivel2(class Player *jugador, class Tiro *tiro){

    jugador->setX(20);
    jugador->setY(288);

    Enemigo4 en4[6];

    jugador->setMoveSpeed(10);

    int done = 100;
    int fade = 0;
    bool draw = true;
    bool pasoElNivel = false;
    int vidaParaInterfaz;
    int invulnerable = 0, numEn = 0;
    float acum = 0,acum2 = 0,acumTE1 = 0;
    int tempoTermino = 0;


    ALLEGRO_TIMER *timerJuego = al_create_timer(1.0 / 20);
    ALLEGRO_KEYBOARD_STATE keyState;
    ALLEGRO_BITMAP *flecha = al_load_bitmap("imagenes/flecha.png");
    ALLEGRO_BITMAP *fader = al_load_bitmap("imagenes/fade.png");

    ALLEGRO_EVENT_QUEUE *EventQueue = al_create_event_queue();

    al_register_event_source(EventQueue, al_get_timer_event_source(timerJuego));
    al_register_event_source(EventQueue, al_get_keyboard_event_source());

    std::vector< std::vector <int> > mapa;
    CargarMapa("mapas/mapa3.txt", mapa);

    en4[0].setEstado(1);

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

            if(invulnerable == 1){
                acum++;
            }
            if(acum >= 50){
                invulnerable = 0;
                acum = 0;
            }

            if(numEn!=6){
                acum2 += 0.08;
                if(acum2 >= 5){
                numEn++;
                en4[numEn].setEstado(1);
                acum2=0;
                }
            }

            for(int i=0;i<6;i++){
                if(en4[i].getEstado()){
                    en4[i].tiroEnemigo.setEstado(1);
                    en4[i].disparar(jugador->getX(),jugador->getY());
                }else
                    en4[i].tiroEnemigo.setEstado(0);
            }


            for(int i=0;i<6;i++){///TIRO CHOCA CONTRA JUGADOR
                if(en4[i].tiroEnemigo.ColisionaCon(jugador) && en4[i].tiroEnemigo.getEstate()==1){
                    if(!invulnerable){
                        if(en4[i].tiroEnemigo.getEstado()){
                            en4[i].tiroEnemigo.setEstate(0);
                            jugador->setVida(jugador->getVida()-1);
                            invulnerable = 1;
                            }
                    }
                }
            }
            for(int i=0; i<6; i++){
                ///COLISION TIRO CON ENEMIGO
                if(en4[i].getEstado() == 1 && tiro->getEstado() == true && en4[i].ColisionaCon(tiro)){
                    if(en4[i].getVida()!=0){
                        en4[i].setVida(en4[i].getVida() - 1);
                    }
                    else{en4[i].setEstado(false);}
                    tiro->setEstado(0);
                }
            }

            if(en4[0].getEstado() == false && en4[1].getEstado() == false && en4[2].getEstado() == false && en4[3].getEstado() == false && en4[4].getEstado() == false && en4[5].getEstado() == false && tempoTermino >= 700){
                    pasoElNivel = true;
                }else{
                    tempoTermino++;
                }

            jugador->HLP();
            tiro->destino();
            tiro->tiroPared();

            if(en4[0].getEstado() == false && en4[1].getEstado() == false && en4[2].getEstado() == false && en4[3].getEstado() == false && en4[4].getEstado() == false && en4[5].getEstado() == false && tempoTermino > 600){
                    pasoElNivel = true;
                }else{
                    tempoTermino++;
                }

            vidaParaInterfaz=jugador->getVida();
        }

            if(draw){
                if(pasoElNivel){
                al_draw_bitmap(flecha, 200,150, NULL);
                if(jugador->getX()>=640)
                done = 5;
                }

                DibujarMapa(mapa);

                jugador->Dibujar();
                tiro->Dibujar();

                for(int i=0; i<6; i++){
                    en4[i].Dibujar();
                    en4[i].tiroEnemigo.dibujar();
                }

                interfaz1(vidaParaInterfaz);
                if(vidaParaInterfaz <= 0){
                    fade = fade+10;
                    if(fade > 255){
                        done = -1;
                    }
                }
                al_draw_tinted_bitmap(fader, al_map_rgba(0,0,0, fade), 0,0, NULL);

                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));
            }
    }
    al_destroy_bitmap(fader);
    al_destroy_timer(timerJuego);
    al_destroy_event_queue(EventQueue);
    return done;
}

#endif // NIVEL3_H_INCLUDED
