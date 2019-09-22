//
// Created by Kevin Cordero Zúñiga on 9/17/2019.
//
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include <dumb.h>
#include <windows.h>
#include "gui.h"
#include "logic/Game.h"
#include "logic/entity/Fruit.h"
#include "logic/lists/FruitNode.h"
#include "logic/lists/KremlinNode.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

static int largoPantalla = 700;
static int anchoPantalla = 700;
static volatile int test = 0;

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_BITMAP  *background = NULL;
ALLEGRO_THREAD* thread = NULL;
bool redraw;
bool done;

int init_game() {

    redraw = true;

    al_init();

    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();

    display = al_create_display(largoPantalla, anchoPantalla);

    background = al_load_bitmap("../src/imagenes/fondo.png");

    al_draw_bitmap(background,0,0,0);


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
            test += 10;
        }
    }
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    return 0;
}

static void* Func_Thread(ALLEGRO_THREAD *thr, void* arg){
    int i = 0;
    while (i == 0){
        printf("%d \n", test);
    }
}

int main() {
   thread = al_create_thread(Func_Thread, "");
   al_start_thread(thread);
   init_game();
   init_matrix();
   struct Kremlin kremlin1 = {0, 1, 7, -1, -1, 1, 1, 0, 22, 0, 0};
   insertKremlin(&kremlin1);
   struct Fruit fruit1 = {1, 10, 6, 1, 100, 31, 0};
   insertFruit(&fruit1);
   run();

   return 0;
}

#pragma clang diagnostic pop
