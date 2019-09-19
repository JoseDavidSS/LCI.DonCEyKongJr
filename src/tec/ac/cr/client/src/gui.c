//
// Created by josed on 18/9/2019.
//

#include "gui.h"

void init_screen(){

    pantalla = al_create_display(LARGO_PANTALLA, ANCHO_PANTALLA);

    int largoXsprite = largo / 16;
    int anchoYsprite = ancho / 24;

    printf("%d" , largoXsprite);
    printf("%d" , anchoYsprite);

    fondo = al_load_bitmap("C:\\Users\\josed\\CLionProjects\\DonCEy-Kong-Jr\\src\\tec\\ac\\cr\\client\\src\\imagenes\\fondomenu.png");

    al_draw_bitmap(fondo, 0, 0, 0);
    al_set_target_bitmap(al_get_backbuffer(pantalla));
    assert(fondo != NULL);

}
void dibujarMatriz(){
    for(int i=0; i<=24; i++){
        for(int j=0; i<=16; j++){
            if (gameMatrix[i][j] == 0){
                printf("buscar en lista de lie");
            }
            if (gameMatrix[i][j] == 211){
                printf("pintar enemigo 1");
            }
            if (gameMatrix[i][j] == 212){
                printf("pintar enemigo 2");
            }
            if (gameMatrix[i][j] == 3){
                printf("pintar negro fondo");
            }
            if (gameMatrix[i][j] == 4){
                printf("pintar negro fondo");
            }
            if (gameMatrix[i][j] == 5){
                printf("pintar negro fondo");
            }
            if (gameMatrix[i][j] == 6){
                printf("pintar negro fondo");
            }
            if (gameMatrix[i][j] == 7){
                printf("pintar negro fondo");
            }
            if (gameMatrix[i][j] == 8){
                printf("pintar negro fondo");
            }
            if (gameMatrix[i][j] == 9){
                printf("pintar negro fondo");
            }
            if (gameMatrix[i][j] == 10){
                printf("pintar negro fondo");
            }
        }
    }


}