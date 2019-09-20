//
// Created by josed on 18/9/2019.
//

#include "gui.h"
#include "bitmapNode.h"
#include "logic/Game.h"

void init_screen(){

    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    pantalla = al_create_display(LARGO_PANTALLA, ANCHO_PANTALLA);

    int largoXsprite = largo / 16;
    int anchoYsprite = ancho / 24;

   // printf("%d" , largoXsprite);
  //  printf("%d" , anchoYsprite);

}

void init_matrix(){
    initializeGameMatrix(gameMatrix);
}

void dibujarMatriz(int direction, ALLEGRO_DISPLAY* display) {

    int vine = 0;
    int floor = 0;
    int fruit = 0;
    int redKremlin = 0;
    int blueKremlin = 0;
    ALLEGRO_BITMAP *bitmap;
    al_hold_bitmap_drawing(true);
    float start_time = al_get_time();
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 16; j++) {

            // Paint tree
            if (gameMatrix[i][j] == (int*) 11) {
                bitmap = al_load_bitmap("../src/imagenes/floor.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                floor++;
            }
            // Paint floor
            if (gameMatrix[i][j] == (int*) 12) {
                bitmap = al_load_bitmap("../src/imagenes/floor.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                floor++;

            }
            // Paint vine
            if (gameMatrix[i][j] == (int*) 13) {
                bitmap = al_load_bitmap("../src/imagenes/vine.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                vine++;
            }

            //Movimineto del kremlin rojo
            if (gameMatrix[i][j] == (int*) 2111) {
                bitmap = al_load_bitmap("../src/imagenes/redcroc_onvine_down_open.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                redKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2112) {
                bitmap = al_load_bitmap("../src/imagenes/redcroc_onvine_up.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                redKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2121) {
                bitmap = al_load_bitmap("../src/imagenes/redcroc_onvine_down_open.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                redKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2122) {
                bitmap = al_load_bitmap("../src/imagenes/redcroc_onvine_down.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                redKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2131) {
                bitmap = al_load_bitmap("../src/imagenes/redcroc_open_left.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                redKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2132) {
                bitmap = al_load_bitmap("../src/imagenes/redcroc_left.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                redKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2141) {
                bitmap = al_load_bitmap("../src/imagenes/redcroc_open.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                redKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2142) {
                bitmap = al_load_bitmap("../src/imagenes/redcroc.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                redKremlin++;
            }

            //Movimineto del kremlin azul
            if (gameMatrix[i][j] == (int*) 2211) {
                bitmap = al_load_bitmap("../src/imagenes/bluecroc_onvine_up_open.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                blueKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2212) {
                bitmap = al_load_bitmap("../src/imagenes/bluecroc_onvine_up.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                blueKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2221) {
                bitmap = al_load_bitmap("../src/imagenes/bluecroc_onvine_down_open.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                blueKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2222) {
                bitmap = al_load_bitmap("../src/imagenes/bluecroc_onvine_down.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                blueKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2231) {
                bitmap = al_load_bitmap("../src/imagenes/bluecroc_open_left.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                blueKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2232) {
                bitmap = al_load_bitmap("../src/imagenes/bluecroc_left.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                blueKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2241) {
                bitmap = al_load_bitmap("../src/imagenes/bluecroc_open.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                blueKremlin++;
            }
            if (gameMatrix[i][j] == (int*) 2242) {
                bitmap = al_load_bitmap("../src/imagenes/bluecroc.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                blueKremlin++;
            }

            // Frutas de tres tipos
            if (gameMatrix[i][j] == (int*) 311) {
                bitmap = al_load_bitmap("../src/imagenes/apple.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                fruit++;
            }
            if (gameMatrix[i][j] == (int*) 312) {
                bitmap = al_load_bitmap("../src/imagenes/apple_onvine.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                fruit++;
            }
            if (gameMatrix[i][j] == (int*) 321) {
                bitmap = al_load_bitmap("../src/imagenes/banana.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                fruit++;
            }
            if (gameMatrix[i][j] == (int*) 322) {
                bitmap = al_load_bitmap("../src/imagenes/banana_onvine.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                fruit++;
            }
            if (gameMatrix[i][j] == (int*) 331) {
                bitmap = al_load_bitmap("../src/imagenes/mango.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                fruit++;
            }
            if (gameMatrix[i][j] == (int*) 332) {
                bitmap = al_load_bitmap("../src/imagenes/mango_onvine.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
                fruit++;
            }

            //Movimiento del mono
            if (gameMatrix[i][j] == (int*) 411) {
                bitmap = al_load_bitmap("../src/imagenes/walk_right1.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
            }
            if (gameMatrix[i][j] == (int*) 412) {
                bitmap = al_load_bitmap("../src/imagenes/walk_right2.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
            }
            if (gameMatrix[i][j] == (int*) 413) {
                dkjrbitmap = al_load_bitmap("../src/imagenes/walk_right3.png");
                al_draw_bitmap(dkjrbitmap, calculateXposition(j), calculateYposition(i), 0);
            }
            if (gameMatrix[i][j] == (int*) 421) {
                bitmap = al_load_bitmap("../src/imagenes/walk_left1.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
            }
            if (gameMatrix[i][j] == (int*) 422) {
                bitmap = al_load_bitmap("../src/imagenes/walk_left2.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
            }
            if (gameMatrix[i][j] == (int*) 423) {
                bitmap = al_load_bitmap("../src/imagenes/walk_left3.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
            }
            if (gameMatrix[i][j] == (int*) 431) {
                bitmap = al_load_bitmap("../src/imagenes/onvine.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
            }
            if (gameMatrix[i][j] == (int*) 432) {
                bitmap = al_load_bitmap("../src/imagenes/onvine.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
            }
            if (gameMatrix[i][j] == (int*) 441) {
                bitmap = al_load_bitmap("../src/imagenes/jumpright.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
            }
            if (gameMatrix[i][j] == (int*)442) {
                bitmap = al_load_bitmap("../src/imagenes/jumpleft.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
            }if(gameMatrix[i][j] == (int*)0) {
                bitmap = al_load_bitmap("../src/imagenes/empty.png");
                al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(i), 0);
            }
        }
    }
    al_hold_bitmap_drawing(false);
    al_flip_display();
   // al_set_target_bitmap(al_get_backbuffer(display));
    updateGameMatrix(direction, gameMatrix);
    printMatrix(gameMatrix);

    float framerate = 1 / (al_get_time() - start_time);
    printf("%f, ", framerate);
}

void createVines() {
        ALLEGRO_BITMAP *vine0;
        vine0 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine0);

        ALLEGRO_BITMAP *vine1;
        vine1 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine1);

        ALLEGRO_BITMAP *vine2;
        vine2 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine2);

        ALLEGRO_BITMAP *vine3;
        vine3 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine3);

        ALLEGRO_BITMAP *vine4;
        vine4 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine4);

        ALLEGRO_BITMAP *vine5;
        vine5 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine5);

        ALLEGRO_BITMAP *vine6;
        vine6 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine6);

        ALLEGRO_BITMAP *vine7;
        vine7 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine7);

        ALLEGRO_BITMAP *vine8;
        vine8 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine8);

        ALLEGRO_BITMAP *vine9;
        vine9 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine9);

        ALLEGRO_BITMAP *vine10;
        vine10 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine10);

        ALLEGRO_BITMAP *vine11;
        vine11 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine11);

        ALLEGRO_BITMAP *vine12;
        vine12 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine12);

        ALLEGRO_BITMAP *vine13;
        vine13 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine13);

        ALLEGRO_BITMAP *vine14;
        vine14 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine14);

        ALLEGRO_BITMAP *vine15;
        vine15 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine15);

        ALLEGRO_BITMAP *vine16;
        vine16 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine16);

        ALLEGRO_BITMAP *vine17;
        vine17 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine17);

        ALLEGRO_BITMAP *vine18;
        vine18 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine18);

        ALLEGRO_BITMAP *vine19;
        vine19 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine19);

        ALLEGRO_BITMAP *vine20;
        vine20 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine20);

        ALLEGRO_BITMAP *vine21;
        vine21 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine21);

        ALLEGRO_BITMAP *vine22;
        vine22 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine22);

        ALLEGRO_BITMAP *vine23;
        vine23 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine23);

        ALLEGRO_BITMAP *vine24;
        vine24 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine24);

        ALLEGRO_BITMAP *vine25;
        vine25 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine25);

        ALLEGRO_BITMAP *vine26;
        vine26 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine26);

        ALLEGRO_BITMAP *vine27;
        vine27 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine27);

        ALLEGRO_BITMAP *vine28;
        vine28 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine28);

        ALLEGRO_BITMAP *vine29;
        vine29 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine29);

        ALLEGRO_BITMAP *vine30;
        vine30 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine30);

        ALLEGRO_BITMAP *vine31;
        vine31 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine31);

        ALLEGRO_BITMAP *vine32;
        vine32 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine32);

        ALLEGRO_BITMAP *vine33;
        vine33 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine33);

        ALLEGRO_BITMAP *vine34;
        vine34 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine34);

        ALLEGRO_BITMAP *vine35;
        vine35 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine35);

        ALLEGRO_BITMAP *vine36;
        vine36 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine36);

        ALLEGRO_BITMAP *vine37;
        vine37 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine37);

        ALLEGRO_BITMAP *vine38;
        vine38 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine38);

        ALLEGRO_BITMAP *vine39;
        vine39 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine39);

        ALLEGRO_BITMAP *vine40;
        vine40 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine40);

        ALLEGRO_BITMAP *vine41;
        vine41 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine41);

        ALLEGRO_BITMAP *vine42;
        vine42 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine42);

        ALLEGRO_BITMAP *vine43;
        vine43 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine43);

        ALLEGRO_BITMAP *vine44;
        vine44 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine44);

        ALLEGRO_BITMAP *vine45;
        vine45 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine45);

        ALLEGRO_BITMAP *vine46;
        vine46 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine46);

        ALLEGRO_BITMAP *vine47;
        vine47 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine47);

        ALLEGRO_BITMAP *vine48;
        vine48 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine48);

        ALLEGRO_BITMAP *vine49;
        vine49 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine49);

        ALLEGRO_BITMAP *vine50;
        vine50 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine50);

        ALLEGRO_BITMAP *vine51;
        vine51 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine51);

        ALLEGRO_BITMAP *vine52;
        vine52 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine52);

        ALLEGRO_BITMAP *vine53;
        vine53 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine53);

        ALLEGRO_BITMAP *vine54;
        vine54 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine54);

        ALLEGRO_BITMAP *vine55;
        vine55 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine55);

        ALLEGRO_BITMAP *vine56;
        vine56 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine56);

        ALLEGRO_BITMAP *vine57;
        vine57 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine57);

        ALLEGRO_BITMAP *vine58;
        vine58 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine58);

        ALLEGRO_BITMAP *vine59;
        vine59 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine59);

        ALLEGRO_BITMAP *vine60;
        vine60 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine60);

        ALLEGRO_BITMAP *vine61;
        vine61 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine61);

        ALLEGRO_BITMAP *vine62;
        vine62 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine62);

        ALLEGRO_BITMAP *vine63;
        vine63 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine63);

        ALLEGRO_BITMAP *vine64;
        vine64 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine64);

        ALLEGRO_BITMAP *vine65;
        vine65 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine65);

        ALLEGRO_BITMAP *vine66;
        vine66 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine66);

        ALLEGRO_BITMAP *vine67;
        vine67 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine67);

        ALLEGRO_BITMAP *vine68;
        vine68 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine68);

        ALLEGRO_BITMAP *vine69;
        vine69 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine69);

        ALLEGRO_BITMAP *vine70;
        vine70 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine70);

        ALLEGRO_BITMAP *vine71;
        vine71 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine71);

        ALLEGRO_BITMAP *vine72;
        vine72 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine72);

        ALLEGRO_BITMAP *vine73;
        vine73 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine73);

        ALLEGRO_BITMAP *vine74;
        vine74 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine74);

        ALLEGRO_BITMAP *vine75;
        vine75 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine75);

        ALLEGRO_BITMAP *vine76;
        vine76 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine76);

        ALLEGRO_BITMAP *vine77;
        vine77 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine77);

        ALLEGRO_BITMAP *vine78;
        vine78 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine78);

        ALLEGRO_BITMAP *vine79;
        vine79 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine79);

        ALLEGRO_BITMAP *vine80;
        vine80 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine80);

        ALLEGRO_BITMAP *vine81;
        vine81 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine81);

        ALLEGRO_BITMAP *vine82;
        vine82 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine82);

        ALLEGRO_BITMAP *vine83;
        vine83 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine83);

        ALLEGRO_BITMAP *vine84;
        vine84 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine84);

        ALLEGRO_BITMAP *vine85;
        vine85 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine85);

        ALLEGRO_BITMAP *vine86;
        vine86 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine86);

        ALLEGRO_BITMAP *vine87;
        vine87 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine87);

        ALLEGRO_BITMAP *vine88;
        vine88 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine88);

        ALLEGRO_BITMAP *vine89;
        vine89 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine89);

        ALLEGRO_BITMAP *vine90;
        vine90 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine90);

        ALLEGRO_BITMAP *vine91;
        vine91 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine91);

        ALLEGRO_BITMAP *vine92;
        vine92 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine92);

        ALLEGRO_BITMAP *vine93;
        vine93 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine93);

        ALLEGRO_BITMAP *vine94;
        vine94 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine94);

        ALLEGRO_BITMAP *vine95;
        vine95 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine95);

        ALLEGRO_BITMAP *vine96;
        vine96 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine96);

        ALLEGRO_BITMAP *vine97;
        vine97 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine97);

        ALLEGRO_BITMAP *vine98;
        vine98 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine98);

        ALLEGRO_BITMAP *vine99;
        vine99 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine99);

        ALLEGRO_BITMAP *vine100;
        vine100 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine100);

        ALLEGRO_BITMAP *vine101;
        vine101 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine101);

        ALLEGRO_BITMAP *vine102;
        vine102 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine102);

        ALLEGRO_BITMAP *vine103;
        vine103 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine103);

        ALLEGRO_BITMAP *vine104;
        vine104 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine104);

        ALLEGRO_BITMAP *vine105;
        vine105 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine105);

        ALLEGRO_BITMAP *vine106;
        vine106 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine106);

        ALLEGRO_BITMAP *vine107;
        vine107 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine107);

        ALLEGRO_BITMAP *vine108;
        vine108 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine108);

        ALLEGRO_BITMAP *vine109;
        vine109 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine109);

        ALLEGRO_BITMAP *vine110;
        vine110 = al_load_bitmap("../src/imagenes/fondomenu.png");
        insertVine(vine110);
    }

void createBlueKremlins() {

    ALLEGRO_BITMAP *blueKremlin0;
    blueKremlin0 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertBlueKremlin(blueKremlin0);

    ALLEGRO_BITMAP *blueKremlin1;
    blueKremlin1 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertBlueKremlin(blueKremlin1);

    ALLEGRO_BITMAP *blueKremlin2;
    blueKremlin2 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertBlueKremlin(blueKremlin2);

    ALLEGRO_BITMAP *blueKremlin3;
    blueKremlin3 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertBlueKremlin(blueKremlin3);

    ALLEGRO_BITMAP *blueKremlin4;
    blueKremlin4 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertBlueKremlin(blueKremlin4);

    ALLEGRO_BITMAP *blueKremlin5;
    blueKremlin5 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertBlueKremlin(blueKremlin5);

    ALLEGRO_BITMAP *blueKremlin6;
    blueKremlin6 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertBlueKremlin(blueKremlin6);

    ALLEGRO_BITMAP *blueKremlin7;
    blueKremlin7 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertBlueKremlin(blueKremlin7);

    ALLEGRO_BITMAP *blueKremlin8;
    blueKremlin8 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertBlueKremlin(blueKremlin8);

    ALLEGRO_BITMAP *blueKremlin9;
    blueKremlin9 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertBlueKremlin(blueKremlin9);

    ALLEGRO_BITMAP *blueKremlin10;
    blueKremlin10 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertBlueKremlin(blueKremlin10);

}

void createRedKremlins() {

    ALLEGRO_BITMAP *redKremlin0;
    redKremlin0 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertRedKremlin(redKremlin0);

    ALLEGRO_BITMAP *redKremlin1;
    redKremlin1 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertRedKremlin(redKremlin1);

    ALLEGRO_BITMAP *redKremlin2;
    redKremlin2 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertRedKremlin(redKremlin2);

    ALLEGRO_BITMAP *redKremlin3;
    redKremlin3 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertRedKremlin(redKremlin3);

    ALLEGRO_BITMAP *redKremlin4;
    redKremlin4 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertRedKremlin(redKremlin4);

    ALLEGRO_BITMAP *redKremlin5;
    redKremlin5 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertRedKremlin(redKremlin5);

    ALLEGRO_BITMAP *redKremlin6;
    redKremlin6 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertRedKremlin(redKremlin6);

    ALLEGRO_BITMAP *redKremlin7;
    redKremlin7 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertRedKremlin(redKremlin7);

    ALLEGRO_BITMAP *redKremlin8;
    redKremlin8 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertRedKremlin(redKremlin8);

    ALLEGRO_BITMAP *redKremlin9;
    redKremlin9 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertRedKremlin(redKremlin9);

    ALLEGRO_BITMAP *redKremlin10;
    redKremlin10 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertRedKremlin(redKremlin10);

}

void createFruits() {

    ALLEGRO_BITMAP *fruit0;
    fruit0 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFruitBitmap(fruit0);

    ALLEGRO_BITMAP *fruit1;
    fruit1 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFruitBitmap(fruit1);

    ALLEGRO_BITMAP *fruit2;
    fruit2 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFruitBitmap(fruit2);

    ALLEGRO_BITMAP *fruit3;
    fruit3 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFruitBitmap(fruit3);

    ALLEGRO_BITMAP *fruit4;
    fruit4 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFruitBitmap(fruit4);

    ALLEGRO_BITMAP *fruit5;
    fruit5 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFruitBitmap(fruit5);

    ALLEGRO_BITMAP *fruit6;
    fruit6 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFruitBitmap(fruit6);

    ALLEGRO_BITMAP *fruit7;
    fruit7 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFruitBitmap(fruit7);

    ALLEGRO_BITMAP *fruit8;
    fruit8 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFruitBitmap(fruit8);

    ALLEGRO_BITMAP *fruit9;
    fruit9 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFruitBitmap(fruit9);

    ALLEGRO_BITMAP *fruit10;
    fruit10 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFruitBitmap(fruit10);
}

void createFloors() {

    ALLEGRO_BITMAP *floor0;
    floor0 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor0);

    ALLEGRO_BITMAP *floor1;
    floor1 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor1);

    ALLEGRO_BITMAP *floor2;
    floor2 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor2);

    ALLEGRO_BITMAP *floor3;
    floor3 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor3);

    ALLEGRO_BITMAP *floor4;
    floor4 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor4);

    ALLEGRO_BITMAP *floor5;
    floor5 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor5);

    ALLEGRO_BITMAP *floor6;
    floor6 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor6);

    ALLEGRO_BITMAP *floor7;
    floor7 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor7);

    ALLEGRO_BITMAP *floor8;
    floor8 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor8);

    ALLEGRO_BITMAP *floor9;
    floor9 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor9);

    ALLEGRO_BITMAP *floor10;
    floor10 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor10);

    ALLEGRO_BITMAP *floor11;
    floor11 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor11);

    ALLEGRO_BITMAP *floor12;
    floor12 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor12);

    ALLEGRO_BITMAP *floor13;
    floor13 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor13);

    ALLEGRO_BITMAP *floor14;
    floor14 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor14);

    ALLEGRO_BITMAP *floor15;
    floor15 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor15);

    ALLEGRO_BITMAP *floor16;
    floor16 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor16);

    ALLEGRO_BITMAP *floor17;
    floor17 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor17);

    ALLEGRO_BITMAP *floor18;
    floor18 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor18);

    ALLEGRO_BITMAP *floor19;
    floor19 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor19);

    ALLEGRO_BITMAP *floor20;
    floor20 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor20);

    ALLEGRO_BITMAP *floor21;
    floor21 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor21);

    ALLEGRO_BITMAP *floor22;
    floor22 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor22);

    ALLEGRO_BITMAP *floor23;
    floor23 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor23);

    ALLEGRO_BITMAP *floor24;
    floor24 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor24);

    ALLEGRO_BITMAP *floor25;
    floor5 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor25);

    ALLEGRO_BITMAP *floor26;
    floor26 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor26);

    ALLEGRO_BITMAP *floor27;
    floor27 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor27);

    ALLEGRO_BITMAP *floor28;
    floor28 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor28);

    ALLEGRO_BITMAP *floor29;
    floor29 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor29);

    ALLEGRO_BITMAP *floor30;
    floor30 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor30);

    ALLEGRO_BITMAP *floor31;
    floor31 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor31);

    ALLEGRO_BITMAP *floor32;
    floor32 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor32);

    ALLEGRO_BITMAP *floor33;
    floor33 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor33);

    ALLEGRO_BITMAP *floor34;
    floor34 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor34);

    ALLEGRO_BITMAP *floor35;
    floor35 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor35);

    ALLEGRO_BITMAP *floor36;
    floor36 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor36);

    ALLEGRO_BITMAP *floor37;
    floor37 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor37);

    ALLEGRO_BITMAP *floor38;
    floor38 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor38);

    ALLEGRO_BITMAP *floor39;
    floor39 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor39);

    ALLEGRO_BITMAP *floor40;
    floor40 = al_load_bitmap("../src/imagenes/fondomenu.png");
    insertFloor(floor40);
}

int calculateXposition(int i){
    int posX = i * 44;
    return posX;
}

int calculateYposition(int j){
    int posY = j * 29;
    return posY;
}
