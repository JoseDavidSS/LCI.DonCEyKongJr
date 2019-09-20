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
#define LARGO_PANTALLA 700
#define ANCHO_PANTALLA 700

static int largo = LARGO_PANTALLA;
static int ancho = ANCHO_PANTALLA;
ALLEGRO_DISPLAY *pantalla;
ALLEGRO_BITMAP * fondo;


static int gameMatrix[24][16] = {{0,1,2,3,4,5,6,7,8,9,1,1,1,1,1,1},
                          {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                          {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                          {3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                          {4,3,3,3,3,3,3,3,211,212,3,3,3,3,3,3},
                          {5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                          {6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                          {7,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                          {8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                          {9,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                          {0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                          {1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                          {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                          {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                          {4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                          {5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                          {6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                          {7,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                          {8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                          {9,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                          {0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                          {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                          {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                          {3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}};

/// Inicia los componestes de la pantalla
void init_screen();
void dibujarMatriz();
void createVines();
void createBlueKremlins();
void createRedKremlins();
void createFruits();
void createFloor();
int calculateXposition(int i);
int calculateYposition(int j);




#endif //DONCEYKONGJR_GUI_H