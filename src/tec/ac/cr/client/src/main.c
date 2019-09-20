//
// Created by Kevin Cordero Zúñiga on 9/17/2019.
//
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include <dumb.h>
#include "gui.h"
#include "logic/Game.h"

int main() {

    al_init();

    init_matrix();

    al_init_primitives_addon();
    al_init_image_addon();
    init_screen();

    ALLEGRO_EVENT_QUEUE *queue;
    queue = al_create_event_queue();

    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(pantalla));

    createVines();
    createBlueKremlins();
    createRedKremlins();
    createFruits();
    createFloors();

    bool corriendo = true;
    while (corriendo){

        al_flip_display();

        //ALLEGRO_EVENT event;
        //al_wait_for_event(queue, &event);
        //if (event.type == ALLEGRO_EVENT_KEY_UP || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
          //  corriendo = false;
        dibujarMatriz();
    }
    al_destroy_display(pantalla);
}
