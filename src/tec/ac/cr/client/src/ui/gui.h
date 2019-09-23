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
static ALLEGRO_THREAD* thread = NULL;
static int firstTime = 0;
static volatile int* gameMatrix[24][16];
static int previousIntI = -1;
static int previousIntJ = -1;
static volatile char* receivedJson = NULL;
static volatile char* serverIp = "127.0.0.1";
static volatile int port = 0;
static int flag = 0;

/// Inicia los componestes de la pantalla
void init_matrix();
int dibujarMatriz(int direction, ALLEGRO_DISPLAY* display);
void dibujarPiso();
void dibujarLiana();
void dibujarDKJr();
void dibujarKremlin();
void dibujarFruta();
void dibujarMarioyDK();
int calculateXposition(int i);
int calculateYposition(int j);
static void* Func_Thread(ALLEGRO_THREAD *thr, void* arg);
void setPort(int nport);




#endif //DONCEYKONGJR_GUI_H