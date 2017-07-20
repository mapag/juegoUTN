#ifndef NIVEL1_H_INCLUDED
#define NIVEL1_H_INCLUDED

int nivel4(class Player *jugador, class Tiro *tiro){

    jugador->setX(20);
    jugador->setMoveSpeed(10);

    Enemigo1 en1[5];
    Enemigo2 en2;
    TiroEn tiroEn[8];
    int done = -2;
    bool draw = true, pasoElNivel = false;

    int fade = 0;
    int vidaParaInterfaz,xd,yd,numEn=0;
    int tempoTermino = 0;

    float acum = 0,acum2 = 0,acumTE1 = 0;
    bool invulnerable = 0;

    ALLEGRO_BITMAP *flecha = al_load_bitmap("imagenes/flecha.png");
    ALLEGRO_BITMAP *fader = al_load_bitmap("imagenes/fade.png");

    ALLEGRO_TIMER *timerJuego = al_create_timer(1.0 / 20);
    ALLEGRO_KEYBOARD_STATE keyState;

    ALLEGRO_EVENT_QUEUE *EventQueue = al_create_event_queue();

    al_convert_mask_to_alpha(flecha, al_map_rgb(255,255,255));

    al_register_event_source(EventQueue, al_get_timer_event_source(timerJuego));
    al_register_event_source(EventQueue, al_get_keyboard_event_source());

    if(en1[0].getEstado()==0){
        en1[0].setEstado(1);
        en1[0].setX(700);
        en1[0].setY(300);
    }

    std::vector< std::vector <int> > mapa;
    CargarMapa("mapas/mapa1.txt", mapa);

    al_start_timer(timerJuego);

    while(done == -2){
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
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if(Event.type == ALLEGRO_EVENT_TIMER){

                xd = rand()%700;
                yd = rand()%564;

                if(invulnerable == 1){
                    acum++;
                }
                if(acum >= 60){
                    invulnerable = 0;
                    acum = 0;
                }


                en2.disparar(&acumTE1);

                if(numEn!=5){
                acum2 += 0.05;
                if(acum2 >= 5){
                numEn++;
                en1[numEn].setEstado(1);
                acum2=0;
                en1[numEn].setX(720);
                en1[numEn].setY(300);}
                }

                al_get_keyboard_state(&keyState);
                jugador->movimiento(keyState);

                for(int i=0; i<5; i++){
                    if(en1[i].getEstado() == true){
                        en1[i].movimiento(jugador->getX(), jugador->getY());
                        en1[i].setSourceX();
                    }
                }

                jugador->setSourceX();

                tiro->tiroPared(); ///TIRO CHOCA CON PARED

                for(int i=0;i<8;i++){
                if(en2.getTiroEstate(i)){
                    if(en2.getTiroX(i)>=640 || en2.getTiroX(i) <= 0 || en2.getTiroY(i) >= 536 || en2.getTiroY(i) <= 0){
                       en2.setTiro(i,false);
                    }}}

                for(int i=0; i<5; i++){
                    ///COLISION TIRO CON ENEMIGO
                    if(en1[i].getEstado() == 1 && tiro->getEstado() == true && en1[i].ColisionaCon(tiro)){
                        if(en1[i].getVida()!=0){
                            en1[i].setVida(en1[i].getVida() - 1);
                        }
                        else{en1[i].setEstado(false);}
                        tiro->setEstado(0);
                    }
                }

                    for(int i=0;i<8;i++){///TIRO CHOCA CONTRA JUGADOR
                        if(en2.tiroEn[i].ColisionaCon(jugador) && en2.tiroEn[i].getEstate()==1){
                            if(!invulnerable){
                                if(en2.tiroEn[i].getEstado()){
                            en2.tiroEn[i].setEstado(0);
                            jugador->setVida(jugador->getVida()-1);
                            invulnerable = 1;
                            }}
                    }}

                    ///ENEM CHOCA CON JUGADOR
                    for(int i=0; i<5; i++){
                        if(en1[i].getEstado() == true && en1[i].ColisionaCon(jugador)){
                            if(invulnerable == 0){
                                jugador->setVida(jugador->getVida()-1); invulnerable = 1;
                            }
                        }
                    }

                ///MOVIMIENTO DE TIRO
                tiro->destino();

                if(en1[0].getEstado() == false && en1[1].getEstado() == false && en1[2].getEstado() == false && en1[3].getEstado() == false && en1[4].getEstado() == false && tempoTermino > 600){
                    pasoElNivel = true;
                }else{
                    tempoTermino++;
                }
                if(!pasoElNivel)
                    jugador->HLP();
                else{
                    if(jugador->getX()<= 1){
                        jugador->setX(jugador->getX()+10);
                    }
                    if(jugador->getY() >= 550){
                        jugador->setY(jugador->getY()-10);
                    }
                    if(jugador->getY() <=0){
                        jugador->setY(jugador->getY()+10);
                    }
                }
                vidaParaInterfaz=jugador->getVida();

        }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if(draw){
                DibujarMapa(mapa);
                if(pasoElNivel){
                    al_draw_bitmap(flecha, 200,150, NULL);
                    if(jugador->getX()>=640)
                    done = 3;
                }
                jugador->Dibujar();

                tiro->Dibujar();

                for(int i=0; i<5; i++){
                    if(en1[i].getEstado()){
                        en1[i].Dibujar();
                    }
                }


                if(en2.getEstado()==1){
                    en2.Dibujar();
                    for(int i=0;i<8;i++){
                        if(en2.tiroEn[i].getEstate()>0){
                            en2.tiroEn[i].dibujar();
                        }
                    }
                }

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
    al_destroy_bitmap(fader);
    al_destroy_bitmap(flecha);
    return done;
}

#endif // NIVEL1_H_INCLUDED
