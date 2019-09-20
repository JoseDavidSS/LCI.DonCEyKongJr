//
// Created by Kevin Cordero Zúñiga on 9/17/2019.
//
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include <dumb.h>
#include "gui.h"
#include "logic/Game.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};

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

    timer = al_create_timer(1.0 / 13);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    return 0;
}



int run(){
    int action = -1;
    ALLEGRO_KEYBOARD_STATE keyboardState;
    while(!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
            }
        }
        if(ev.type == ALLEGRO_EVENT_TIMER ) {
            al_get_keyboard_state(&keyboardState);
            if (al_key_down(&keyboardState, ALLEGRO_KEY_UP)){
                action = 6;
            }else if (al_key_down(&keyboardState,ALLEGRO_KEY_DOWN)){
                action = 7;
            }else if (al_key_down(&keyboardState,ALLEGRO_KEY_RIGHT)){
                action = 1;
            }else if (al_key_down(&keyboardState,ALLEGRO_KEY_LEFT)){
                action = 2;
            }else if (al_key_down(&keyboardState,ALLEGRO_KEY_SPACE)){
                action = 3;
            }else if (al_key_down(&keyboardState,ALLEGRO_KEY_X)){
                action = 5;
            }else if (al_key_down(&keyboardState,ALLEGRO_KEY_Z)){
                action = 4;
            }
            redraw = true;
        }
        if (redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            dibujarMatriz(action, display);
            action = -1;
            al_flip_display();
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
   run();

    return 0;
}

#pragma clang diagnostic pop
