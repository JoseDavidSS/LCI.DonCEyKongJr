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
ALLEGRO_BITMAP* bitmap;
static int* gameMatrix[24][16];
static int previousIntI = -1;
static int previousIntJ = -1;
/// Inicia los componestes de la pantalla
void init_screen();
void init_matrix();
void dibujarMatriz(int direction, ALLEGRO_DISPLAY* display);
void dibujarPiso();
void dibujarLiana();
void dibujarDKJr();
void dibujarKremlin();
void dibujarFruta();
void dibujarMarioyDK();
int calculateXposition(int i);
int calculateYposition(int j);




#endif //DONCEYKONGJR_GUI_H