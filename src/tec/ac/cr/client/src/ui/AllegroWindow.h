//
// Created by Kevin Cordero Zuniga on 9/22/2019.
//

#ifndef DONCEYKONGJR_ALLEGROWINDOW_H
#define DONCEYKONGJR_ALLEGROWINDOW_H

#include <allegro5/allegro.h>

static int largoPantalla = 700;
static int anchoPantalla = 700;

static ALLEGRO_DISPLAY* display = NULL;
static ALLEGRO_EVENT_QUEUE* event_queue = NULL;
static ALLEGRO_TIMER* timer = NULL;
static ALLEGRO_BITMAP  *background = NULL;
static bool redraw;
static bool done;
static int points = 0;

int init_game();
int run();
int mainAllegro(int port);

#endif //DONCEYKONGJR_ALLEGROWINDOW_H
