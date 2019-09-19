//
// Created by josed on 18/9/2019.
//

#ifndef DONCEYKONGJR_GUI_H
#define DONCEYKONGJR_GUI_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"

///Inicio de varibales de la pantalla
#define ANCHO_PANTALLA 640
#define ALTO_PANTALLA 400
ALLEGRO_DISPLAY *pantalla;
ALLEGRO_BITMAP * fondo;

/// Inicia los componestes de la pantalla
void init_screen();

#endif //DONCEYKONGJR_GUI_H


