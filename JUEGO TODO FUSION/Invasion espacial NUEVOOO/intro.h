#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED

int intro(ALLEGRO_DISPLAY *ventana){

    al_reserve_samples(2);

    ALLEGRO_SAMPLE *song = al_load_sample("intro.wav");

    ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(song);
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);

    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());


    int done = 100;
    bool dibujar = true;
    int fade = 0;
    bool cambia= false;
    int timer=0;

    ALLEGRO_BITMAP *intro1,*intro2,*intro3,*intro4,*intro5,*intro6,*fader;

    intro1 = al_load_bitmap("imagPrev/intro1.png");
    intro2 = al_load_bitmap("imagPrev/intro2.png");
    intro3 = al_load_bitmap("imagPrev/intro3.png");
    intro4 = al_load_bitmap("imagPrev/intro4.png");
    intro5 = al_load_bitmap("imagPrev/intro5.png");
    intro6 = al_load_bitmap("imagPrev/intro6.jpg");
    fader = al_load_bitmap("imagenes/fade.png");

    ALLEGRO_KEYBOARD_STATE keyState;
    ALLEGRO_TIMER *tempo;
    ALLEGRO_EVENT_QUEUE *cola;

    tempo = al_create_timer(1.0/60);
    cola = al_create_event_queue();

    al_register_event_source(cola,al_get_keyboard_event_source());
    al_register_event_source(cola,al_get_timer_event_source(tempo));
    al_register_event_source(cola,al_get_display_event_source(ventana));

    al_play_sample_instance(songInstance);

    al_start_timer(tempo);

    while(done == 100){
        ALLEGRO_EVENT evento;
        al_wait_for_event(cola,&evento);
        al_get_keyboard_state(&keyState);

        if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = 0;

        if(al_key_down(&keyState,ALLEGRO_KEY_ESCAPE))
            done = 0;

        if(evento.type == ALLEGRO_EVENT_TIMER){
            timer++;
        }

        if(dibujar){
            if(timer < 250){
                al_draw_bitmap(intro1, 0,0,NULL);
            }
            else if(timer < 700){
                al_draw_bitmap(intro2, 0,0,NULL);
            }
            else if(timer < 1500){
                al_draw_bitmap(intro3, 0,0,NULL);
            }
            else if(timer < 2000){
                al_draw_bitmap(intro4, 0,0,NULL);
            }
            else if(timer < 2500){
                al_draw_bitmap(intro5, 0,0,NULL);
            }
            else if(timer < 3000){
                al_draw_bitmap(intro6, 0,0,NULL);
            }
            else if(timer < 3500){
                done = 1;
            }

            if(timer == 199 || timer == 649 || timer == 1449 || timer == 1949 || timer == 2449 || timer == 2949 || timer == 3449){
                cambia = true;
            }

            if(cambia){
                if(fade<255)
                    fade = fade + 5;
                else if(fade == 255){
                    fade = 0;
                    cambia = false;
                }
            }

            al_draw_tinted_bitmap(fader,al_map_rgba(0,0,0,fade),0,0,NULL);

            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));

        }
    }

    al_destroy_sample(song);
    al_destroy_sample_instance(songInstance);

    al_destroy_bitmap(intro1);
    al_destroy_bitmap(intro2);
    al_destroy_bitmap(intro3);
    al_destroy_bitmap(intro4);
    al_destroy_bitmap(intro5);
    al_destroy_bitmap(intro6);
    al_destroy_bitmap(fader);

    al_destroy_timer(tempo);
    al_destroy_event_queue(cola);

    return 3;
}

#endif // INTRO_H_INCLUDED
