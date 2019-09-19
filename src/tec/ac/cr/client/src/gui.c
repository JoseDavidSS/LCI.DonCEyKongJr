//
// Created by josed on 18/9/2019.
//

#include "gui.h"

void init_screen(){
    pantalla = al_create_display(ANCHO_PANTALLA, ALTO_PANTALLA);
    fondo = al_load_bitmap("src/imagenes/fondomenu.jpg");
}