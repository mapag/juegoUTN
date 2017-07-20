#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "secuenciador.h"


int juego(ALLEGRO_DISPLAY *ventana, bool flagSonido){
        al_install_audio();
        al_init_acodec_addon();

        al_reserve_samples(2);

        ALLEGRO_SAMPLE *song = al_load_sample("Out_Of_Time.ogg");

        ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(song);
        al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);

        al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

        ALLEGRO_KEYBOARD_STATE keyState;
        ALLEGRO_MOUSE_STATE mouseState;
        ALLEGRO_TIMER *tempo;
        ALLEGRO_EVENT_QUEUE *cola;

        bool dibujar=true;
        bool pasa = false;
        int x,y,done = 100,m1 = 0;
        int fade = 0;

        ALLEGRO_BITMAP *menu, *menuA, *menuB, *menuC, *cursor;
        ALLEGRO_BITMAP *fader = al_load_bitmap("imagenes/fade.png");

        menu = al_load_bitmap("imagPrev/menu.jpg");
        menuA = al_load_bitmap("imagPrev/menuA.jpg");
        menuB = al_load_bitmap("imagPrev/menuB.jpg");
        menuC = al_load_bitmap("imagPrev/menuC.jpg");

        cursor = al_load_bitmap("imagenes/cursor.bmp");

        tempo = al_create_timer(1.0/60);
        cola = al_create_event_queue();

        al_register_event_source(cola,al_get_keyboard_event_source());
        al_register_event_source(cola,al_get_mouse_event_source());
        al_register_event_source(cola,al_get_timer_event_source(tempo));
        al_register_event_source(cola,al_get_display_event_source(ventana));

        al_convert_mask_to_alpha(cursor,al_map_rgb(0,0,0));

        al_hide_mouse_cursor(ventana);

        if(flagSonido)
            al_play_sample_instance(songInstance);

        al_start_timer(tempo);


    while(done == 100){

       ALLEGRO_EVENT evento;
       al_wait_for_event(cola,&evento);
       al_get_keyboard_state(&keyState);
       al_get_mouse_state(&mouseState);

        if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        done = 0;}

        if(al_key_down(&keyState,ALLEGRO_KEY_ESCAPE)){
        done = 0;}

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

        x = mouseState.x;
        y = mouseState.y;
        dibujar = true;
       }

       if(dibujar){
        dibujar = false;

        if(y > 180 && y < 220 && x > 390 && x < 580){
            al_draw_bitmap(menuA, 0,0, NULL);
            if(m1 == 1){
                pasa = true;
            }
        }
        else if(y > 260 && y < 290 && x > 390 && x < 565){
        al_draw_bitmap(menuB, 0,0, NULL);
        if(m1 == 1){
        done = 5;}}
        else if(y > 315 && y < 355 && x > 390 && x < 480){
        al_draw_bitmap(menuC, 0,0, NULL);
        if(m1 == 1){
        done = 0;}}
        else{
            al_draw_bitmap(menu,0,0,NULL);
        }


        if(pasa){
            if(fade<255)
                fade = fade + 5;
            else
                done = 4; /// 4 PARA INTRO, 3 DERECHO A JUEGO
        }

        al_draw_tinted_bitmap(fader, al_map_rgba(0,0,0, fade), 0,0, NULL);

        al_draw_bitmap(cursor,x,y,NULL);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
       }
}
al_destroy_sample(song);
al_destroy_sample_instance(songInstance);

al_destroy_bitmap(cursor);

al_destroy_timer(tempo);
al_destroy_event_queue(cola);

al_destroy_bitmap(menu);
al_destroy_bitmap(menuA);
al_destroy_bitmap(menuB);
al_destroy_bitmap(menuC);

al_destroy_bitmap(fader);

return done;
}














#endif // JUEGO_H_INCLUDED
