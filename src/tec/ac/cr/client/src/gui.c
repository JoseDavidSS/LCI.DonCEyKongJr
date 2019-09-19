//
// Created by josed on 18/9/2019.
//

#include "gui.h"

void init_screen(){
    pantalla = al_create_display(ANCHO_PANTALLA, ALTO_PANTALLA);
    fondo = al_load_bitmap("C:\\Users\\josed\\CLionProjects\\DonCEy-Kong-Jr\\src\\tec\\ac\\cr\\client\\src\\imagenes\\fondomenu.png");
    al_draw_bitmap(fondo, 0, 0, 0);
    al_set_target_bitmap(al_get_backbuffer(pantalla));
    assert(fondo != NULL);
}