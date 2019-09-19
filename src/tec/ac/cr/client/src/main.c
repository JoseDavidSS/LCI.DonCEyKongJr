//
// Created by Kevin Cordero Zúñiga on 9/17/2019.
//
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include "gui.h"

int main() {
    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    init_screen();

    ALLEGRO_EVENT_QUEUE *queue;
    queue = al_create_event_queue();

    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(pantalla));

    ALLEGRO_BITMAP * fondo2 = NULL;
    al_init_image_addon();
    fondo2 = al_load_bitmap("src/imagenes/fondomenu.jpg");
    assert(fondo2 != NULL);

    bool corriendo = true;
    while (corriendo){

        al_draw_bitmap(fondo2, 0, 0, 0);

        al_clear_to_color(al_map_rgb(255, 0, 255));
        al_set_target_bitmap(al_get_backbuffer(pantalla));

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_flip_display();

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_KEY_UP || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            corriendo = false;
    }
    al_destroy_bitmap(fondo);
    al_destroy_display(pantalla);
}
