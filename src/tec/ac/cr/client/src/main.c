//
// Created by Kevin Cordero Zúñiga on 9/17/2019.
//
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include <dumb.h>
#include "gui.h"
#include "logic/Game.h"
#include "logic/entity/Fruit.h"
#include "logic/lists/FruitNode.h"
#include "logic/lists/KremlinNode.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

static int largoPantalla = 700;
static int anchoPantalla = 700;

bool key[5];
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;
bool redraw;
bool done;

int init_game() {

    key[1] = false;
    key[2] = false;
    key[3] = false;
    key[4] = false;
    key[5] = false;
    redraw = true;

    al_init();

    display = al_create_display(largoPantalla, anchoPantalla);
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();

    al_flip_display();

    timer = al_create_timer(1.0 / 15);
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
            dibujarMatriz(action, display);
            action = -1;
            al_flip_display();
        }else{
            draw++;
        }
    }
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    return 0;
}

int main() {

   init_game();
   init_matrix();
   struct Kremlin kremlin = {0, 3, 5, -1, -1, 1, 1, 0, 21, 0};
   insertKremlin(&kremlin);
   run();

   return 0;
}

#pragma clang diagnostic pop
