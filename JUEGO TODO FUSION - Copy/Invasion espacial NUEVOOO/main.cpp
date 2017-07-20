#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/timer.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


using namespace std;

#define Ancho 732
#define Alto 600
#define BlockSizeX 32
#define BlockSizeY 32


#include "menuPrincipal.h"
#include "juego.h"
#include "intro.h"
#include "opciones.h"

int main()
{
    al_init();
    al_init_image_addon();
    al_init_native_dialog_addon();
    al_init_ttf_addon();
    al_init_font_addon();
    al_init_primitives_addon();

    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_DISPLAY *ventana;
    bool flagIntro = true, flagTuto = true, flagSonido = true;
    int opc = 1;

    while(opc!=0){
        if(opc == 1){
            opc = menuPrincipal();
            al_set_new_display_flags(ALLEGRO_WINDOWED);
            ventana = al_create_display(Ancho,Alto);
        }

        if(opc == 2){
            opc = juego(ventana, flagSonido);
        }

        if(opc == 3){
            opc = secuenciador(flagTuto);
        }

        if(opc == 4){
            if(flagIntro)
                opc = intro(ventana);
            else
                opc = 3;
        }

        if(opc == 5){
            opc = opciones(&flagIntro, &flagTuto, &flagSonido);
        }
    }

    return 0;
    al_destroy_display(ventana);
}
