//
// Created by Kevin Cordero Zúñiga on 9/17/2019.
//
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include <dumb.h>
#include <windows.h>
#include "gui.h"
#include "../logic/Game.h"
#include "../logic/entity/Fruit.h"
#include "../logic/lists/FruitNode.h"
#include "../logic/lists/KremlinNode.h"
#include "AllegroWindow.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

int init_game() {

    redraw = true;

    al_init();

    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();

    display = al_create_display(largoPantalla, anchoPantalla);


    al_flip_display();

    timer = al_create_timer(1.0 / 30);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    return 0;
}

int run(){
    int draw = 0;
    int action = -1;
    while(!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
            }
        }
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch (ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    action = 6;
                    break;
                case ALLEGRO_KEY_DOWN:
                    action = 7;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    action = 1;
                    break;
                case ALLEGRO_KEY_LEFT:
                    action = 2;
                    break;
                case ALLEGRO_KEY_SPACE:
                    action = 3;
                    break;
                case ALLEGRO_KEY_X:
                    action = 5;
                    break;
                case ALLEGRO_KEY_Z:
                    action = 4;
                    break;
            }
        }
        if (draw == 2){
            draw = 0;
            points = dibujarMatriz(action, display);
            if (points != 0){
                done = true;
            }
            action = -1;
            al_flip_display();
        }else{
            draw++;
        }
    }
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    return points;
}

int mainAllegro(int port) {
   setPort(port);
   init_game();
   init_matrix();
   struct Kremlin kremlin1 = {0, 1, 7, -1, -1, 1, 1, 0, 22, 0, 0};
   insertKremlin(&kremlin1);
   struct Kremlin kremlin2 = {1, 20, 8, -1, -1, 1, 1, 0 , 21, 0, 0};
   insertKremlin(&kremlin2);
   struct Kremlin kremlin3 = {2, 18, 5, -1, -1, 1, 1, 0 , 21, 0, 0};
   insertKremlin(&kremlin3);
   struct Fruit fruit1 = {1, 10, 6, 1, 100, 31, 0, 1};
   insertFruit(&fruit1);
   return run();
}

#pragma clang diagnostic pop
