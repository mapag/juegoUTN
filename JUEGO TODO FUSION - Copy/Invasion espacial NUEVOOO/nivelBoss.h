#ifndef NIVELBOSS_H_INCLUDED
#define NIVELBOSS_H_INCLUDED

int nivelBoss(class Player *jugador, class Tiro *tiro){

    jugador->setX(350);
    jugador->setY(500);
    jugador->setDir(3);

    jugador->setMoveSpeed(10);

    tiro->setMoveSpeed(30);

    JefeFinal JF;

    int done = 100;
    bool draw = true;
    int fade = 0;
    int vidaParaInterfaz;
    int vidaJFparaInterfaz=0;
    srand( time( 0 ) );
    int invulnerable = 0, acum =0;

    ALLEGRO_TIMER *timerJuego = al_create_timer(1.0 / 40);
    ALLEGRO_KEYBOARD_STATE keyState;

    ALLEGRO_BITMAP *pinches = al_load_bitmap("imagenes/pinche.png");
    ALLEGRO_BITMAP *fader = al_load_bitmap("imagenes/fade.png");

    al_convert_mask_to_alpha(pinches, al_map_rgb(255,255,255));

    ALLEGRO_EVENT_QUEUE *EventQueue = al_create_event_queue();

    al_register_event_source(EventQueue, al_get_timer_event_source(timerJuego));
    al_register_event_source(EventQueue, al_get_keyboard_event_source());

    std::vector< std::vector <int> > mapa;
    CargarMapa("mapas/mapaBoss.txt", mapa);

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

            JF.setSourceX();
            JF.setSourceY();
            JF.movimiento(jugador->getX(),jugador->getY());

            tiro->destino();
            tiro->tiroPared();

            if(invulnerable == 1){
                acum += 1;
            }
            if(acum >= 50){
                invulnerable = 0;
                acum = 0;
            }

            ///COLISION TIRO CON ESCUDO
            if(JF.Escudo.ColisionaCon(tiro) && JF.Escudo.getEstado() == true){
                tiro->setEstado(0);
            }

            ///COLISION TIRO CON BOSS
            if(JF.ColisionaCon(tiro) && tiro->getEstado() == true){
                JF.setVida(JF.getVida()-1);
                tiro->setEstado(0);
            }

            for(int i=0; i<3; i++){ ///COLISION TIRO A JUGADOR
                if(JF.tiroBoss[i].ColisionaCon(jugador) && !JF.getMurio()){
                    if(!invulnerable){
                        jugador->setVida(jugador->getVida() - 1);
                        invulnerable = 1;
                    }
                }
            }



            jugador->HLP();

            if(!JF.getMurio()){
                if(jugador->getY() < 300){
                    jugador->setY(jugador->getY() + jugador->getMoveSpeed());
                }
            }else{
                JF.Escudo.setEstado(0);
            }
            vidaParaInterfaz=jugador->getVida();
            vidaJFparaInterfaz = JF.getVida();
        }

            if(draw){
                DibujarMapa(mapa);
                if(!JF.getMurio()){
                    al_draw_bitmap(pinches,32,300,NULL);
                    JF.dibujar();
                    JF.Escudo.dibujar();
                    JF.dibujarTiro();
                }
                jugador->Dibujar();
                tiro->Dibujar();

                if(jugador->getY() < 50){
                        done = 6;
                }

                interfaz1(vidaParaInterfaz);
                if(vidaParaInterfaz <= 0){
                    fade = fade+10;
                    if(fade > 255){
                        done =  -1;
                    }
                }

                vidaJF(vidaJFparaInterfaz);

                al_draw_tinted_bitmap(fader, al_map_rgba(0,0,0, fade), 0,0, NULL);

                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));
            }

    }
    al_destroy_timer(timerJuego);

    al_destroy_bitmap(pinches);
    al_destroy_bitmap(fader);
    al_destroy_event_queue(EventQueue);
    return done;

}
#endif // NIVELBOSS_H_INCLUDED
