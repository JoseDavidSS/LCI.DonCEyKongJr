//
// Created by josed on 18/9/2019.
//

#include "gui.h"
#include "../logic/Game.h"
#include "../logic/lists/KremlinNode.h"
#include "../logic/lists/FruitNode.h"
#include "../socket/Socket.h"
#include "../socket/Serializer.h"

void init_matrix(){
    initializeGameMatrix(gameMatrix);
}

int dibujarMatriz(int direction, ALLEGRO_DISPLAY* display) {

    if (firstTime == 0){
        thread = al_create_thread(Func_Thread, "");
        al_start_thread(thread);
        firstTime = 1;
    }

    al_hold_bitmap_drawing(true);
    dibujarKremlin();
    dibujarFruta();
    dibujarDKJr();
    dibujarPiso();
    dibujarLiana();
    dibujarMarioyDK();

    al_hold_bitmap_drawing(false);
    al_flip_display();
    al_set_target_bitmap(al_get_backbuffer(display));
    flag = updateGameMatrix(direction, gameMatrix);
    if (flag != 0 ){
        return flag;
    }

    if (receivedJson != NULL){
        if (isFruit(receivedJson) == 2){
            struct Fruit* fruit = deserializeFruit(receivedJson);
            insertFruit(fruit);
            receivedJson = NULL;
        }else{
            struct Kremlin* kremlin = deserializeKremlin(receivedJson);
            insertKremlin(kremlin);
            receivedJson = NULL;
        }
    }
    return 0;
}

void dibujarPiso(){
    bitmap = al_load_bitmap("../src/imagenes/floor.png");
    int j = 0;
    for (j = 4; j < 6; j++){
        al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(2), 0);
    }
    for (j = 0; j < 9; j++){
        al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(4), 0);
    }
    for (j = 8; j < 12; j++){
        al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(5), 0);
    }
    al_draw_bitmap(bitmap, calculateXposition(2), calculateYposition(9), 0);
    for (j = 11; j < 16; j++){
        al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(13), 0);
    }
    for (j = 2; j < 4; j++){
        al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(15), 0);
    }
    for (j = 12; j < 15; j++){
        al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(20), 0);
    }
    al_draw_bitmap(bitmap, calculateXposition(4), calculateYposition(21), 0);
    for (j = 9; j < 12; j++){
        al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(21), 0);
    }
    for (j = 5; j < 9; j++){
        al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(22), 0);
    }
    for (j = 0; j < 3; j++){
        al_draw_bitmap(bitmap, calculateXposition(j), calculateYposition(23), 0);
    }
}

void dibujarLiana(){
    bitmap = al_load_bitmap("../src/imagenes/vine.png");
    int i = 0;
    for (i = 5; i < 21; i++){
        al_draw_bitmap(bitmap, calculateXposition(0), calculateYposition(i), 0);
    }
    for (i = 10; i < 13; i++){
        al_draw_bitmap(bitmap, calculateXposition(2), calculateYposition(i), 0);
    }
    for (i = 16; i < 21; i++){
        al_draw_bitmap(bitmap, calculateXposition(2), calculateYposition(i), 0);
    }
    for (i = 5; i < 18; i++){
        al_draw_bitmap(bitmap, calculateXposition(4), calculateYposition(i), 0);
    }
    for (i = 0; i < 2; i++){
        al_draw_bitmap(bitmap, calculateXposition(6), calculateYposition(i), 0);
    }
    for (i = 5; i < 14; i++){
        al_draw_bitmap(bitmap, calculateXposition(6), calculateYposition(i), 0);
    }
    for (i = 6; i < 18; i++){
        al_draw_bitmap(bitmap, calculateXposition(8), calculateYposition(i), 0);
    }
    al_draw_bitmap(bitmap, calculateXposition(9), calculateYposition(0), 0);
    for (i = 6; i < 16; i++){
        al_draw_bitmap(bitmap, calculateXposition(10), calculateYposition(i), 0);
    }
    for (i = 0; i < 11; i++){
        al_draw_bitmap(bitmap, calculateXposition(12), calculateYposition(i), 0);
    }
    for (i = 0; i < 11; i++){
        al_draw_bitmap(bitmap, calculateXposition(14), calculateYposition(i), 0);
    }
    for (i = 14; i < 18; i++){
        al_draw_bitmap(bitmap, calculateXposition(12), calculateYposition(i), 0);
    }
    for (i = 14; i < 18; i++){
        al_draw_bitmap(bitmap, calculateXposition(14), calculateYposition(i), 0);
    }
}

void dibujarDKJr(){
    struct DKJr* localDKJr = returnDKJr();
    int posI = localDKJr->posI;
    int posJ = localDKJr->posJ;
    bitmap = al_load_bitmap("../src/imagenes/empty.png");
    al_draw_bitmap(bitmap, calculateXposition(previousIntJ), calculateYposition(previousIntI), 0);
    switch ((int)gameMatrix[posI][posJ]) {
        case 411:
            bitmap = al_load_bitmap("../src/imagenes/walk_right1.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
            if (previousIntI != posI || previousIntJ != posJ){
                bitmap = al_load_bitmap("../src/imagenes/empty.png");
                al_draw_bitmap(bitmap, calculateXposition(previousIntJ), calculateYposition(previousIntI), 0);
            }
            break;
        case 412:
            bitmap = al_load_bitmap("../src/imagenes/walk_right2.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
            bitmap = al_load_bitmap("../src/imagenes/empty.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ - 1), calculateYposition(posI), 0);
            if (previousIntI != posI || previousIntJ != posJ){
                bitmap = al_load_bitmap("../src/imagenes/empty.png");
                al_draw_bitmap(bitmap, calculateXposition(previousIntJ), calculateYposition(previousIntI), 0);
            }
            break;
        case 413:
            bitmap = al_load_bitmap("../src/imagenes/walk_right3.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
            bitmap = al_load_bitmap("../src/imagenes/empty.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ - 1), calculateYposition(posI), 0);
            if (previousIntI != posI || previousIntJ != posJ){
                bitmap = al_load_bitmap("../src/imagenes/empty.png");
                al_draw_bitmap(bitmap, calculateXposition(previousIntJ), calculateYposition(previousIntI), 0);
            }
            break;
        case 421:
            bitmap = al_load_bitmap("../src/imagenes/walk_left1.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
            bitmap = al_load_bitmap("../src/imagenes/empty.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ + 1), calculateYposition(posI), 0);
            if (previousIntI != posI || previousIntJ != posJ){
                bitmap = al_load_bitmap("../src/imagenes/empty.png");
                al_draw_bitmap(bitmap, calculateXposition(previousIntJ), calculateYposition(previousIntI), 0);
            }
            break;
        case 422:
            bitmap = al_load_bitmap("../src/imagenes/walk_left2.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
            bitmap = al_load_bitmap("../src/imagenes/empty.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ + 1), calculateYposition(posI), 0);
            if (previousIntI != posI || previousIntJ != posJ){
                bitmap = al_load_bitmap("../src/imagenes/empty.png");
                al_draw_bitmap(bitmap, calculateXposition(previousIntJ), calculateYposition(previousIntI), 0);
            }
            break;
        case 423:
            bitmap = al_load_bitmap("../src/imagenes/walk_left3.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
            bitmap = al_load_bitmap("../src/imagenes/empty.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ + 1), calculateYposition(posI), 0);
            if (previousIntI != posI || previousIntJ != posJ){
                bitmap = al_load_bitmap("../src/imagenes/empty.png");
                al_draw_bitmap(bitmap, calculateXposition(previousIntJ), calculateYposition(previousIntI), 0);
            }
            break;
        case 431:
            bitmap = al_load_bitmap("../src/imagenes/onvine.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
            break;
        case 432:
            bitmap = al_load_bitmap("../src/imagenes/onvine.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
            break;
        case 441:
            bitmap = al_load_bitmap("../src/imagenes/jumpright.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
            if (previousIntI != posI || previousIntJ != posJ){
                bitmap = al_load_bitmap("../src/imagenes/empty.png");
                al_draw_bitmap(bitmap, calculateXposition(previousIntJ), calculateYposition(previousIntI), 0);
            }
            break;
        case 442:
            bitmap = al_load_bitmap("../src/imagenes/jumpleft.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
            if (previousIntI != posI || previousIntJ != posJ){
                bitmap = al_load_bitmap("../src/imagenes/empty.png");
                al_draw_bitmap(bitmap, calculateXposition(previousIntJ), calculateYposition(previousIntI), 0);
            }
            break;
    }
    previousIntI = posI;
    previousIntJ = posJ;
}

void dibujarKremlin(){
    struct KremlinNode* kremlinNode = returnKremlinHead();
    struct Kremlin* kremlin;
    int posI;
    int posJ;
    int previousI;
    int previousJ;
    while (kremlinNode != NULL){
        kremlin = kremlinNode->kremlin;
        posI = kremlin->posI;
        posJ = kremlin->posJ;
        previousI = kremlin->previousI;
        previousJ = kremlin->previousJ;
        if (kremlin->onScreen == 0){
            bitmap = al_load_bitmap("../src/imagenes/empty.png");
            al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
            kremlinNode = kremlinNode->next;
        }else if (kremlin->type == 21){
            switch ((int) gameMatrix[posI][posJ]){
                case 2111:
                    bitmap = al_load_bitmap("../src/imagenes/redcroc_onvine_up.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    bitmap = al_load_bitmap("../src/imagenes/empty.png");
                    al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    break;
                case 2112:
                    bitmap = al_load_bitmap("../src/imagenes/redcroc_onvine_up_open.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    bitmap = al_load_bitmap("../src/imagenes/empty.png");
                    al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    break;
                case 2121:
                    bitmap = al_load_bitmap("../src/imagenes/redcroc_onvine_down.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    bitmap = al_load_bitmap("../src/imagenes/empty.png");
                    al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    break;
                case 2122:
                    bitmap = al_load_bitmap("../src/imagenes/redcroc_onvine_down_open.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    bitmap = al_load_bitmap("../src/imagenes/empty.png");
                    al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    break;
                case 2131:
                    bitmap = al_load_bitmap("../src/imagenes/redcroc_left.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    if (previousI != posI || previousJ != posJ){
                        bitmap = al_load_bitmap("../src/imagenes/empty.png");
                        al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    }
                    break;
                case 2132:
                    bitmap = al_load_bitmap("../src/imagenes/redcroc_open_left.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    if (previousI != posI || previousJ != posJ){
                        bitmap = al_load_bitmap("../src/imagenes/empty.png");
                        al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    }
                    break;
                case 2141:
                    bitmap = al_load_bitmap("../src/imagenes/redcroc.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    if (previousI != posI || previousJ != posJ){
                        bitmap = al_load_bitmap("../src/imagenes/empty.png");
                        al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    }
                    break;
                case 2142:
                    bitmap = al_load_bitmap("../src/imagenes/redcroc_open.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    if (previousI != posI || previousJ != posJ){
                        bitmap = al_load_bitmap("../src/imagenes/empty.png");
                        al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    }
                    break;
            }
            kremlinNode = kremlinNode->next;
        }else{
            switch ((int) gameMatrix[posI][posJ]){
                case 2211:
                    bitmap = al_load_bitmap("../src/imagenes/bluecroc_onvine_up.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    bitmap = al_load_bitmap("../src/imagenes/empty.png");
                    al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    break;
                case 2212:
                    bitmap = al_load_bitmap("../src/imagenes/bluecroc_onvine_up_open.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    bitmap = al_load_bitmap("../src/imagenes/empty.png");
                    al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    break;
                case 2221:
                    bitmap = al_load_bitmap("../src/imagenes/bluecroc_onvine_down.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    bitmap = al_load_bitmap("../src/imagenes/empty.png");
                    al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    break;
                case 2222:
                    bitmap = al_load_bitmap("../src/imagenes/bluecroc_onvine_down_open.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    bitmap = al_load_bitmap("../src/imagenes/empty.png");
                    al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    break;
                case 2231:
                    bitmap = al_load_bitmap("../src/imagenes/bluecroc_left.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    if (previousI != posI || previousJ != posJ){
                        bitmap = al_load_bitmap("../src/imagenes/empty.png");
                        al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    }
                    break;
                case 2232:
                    bitmap = al_load_bitmap("../src/imagenes/bluecroc_open_left.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    if (previousI != posI || previousJ != posJ){
                        bitmap = al_load_bitmap("../src/imagenes/empty.png");
                        al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    }
                    break;
                case 2241:
                    bitmap = al_load_bitmap("../src/imagenes/bluecroc.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    if (previousI != posI || previousJ != posJ){
                        bitmap = al_load_bitmap("../src/imagenes/empty.png");
                        al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    }
                    break;
                case 2242:
                    bitmap = al_load_bitmap("../src/imagenes/bluecroc_open.png");
                    al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                    if (previousI != posI || previousJ != posJ){
                        bitmap = al_load_bitmap("../src/imagenes/empty.png");
                        al_draw_bitmap(bitmap, calculateXposition(previousJ), calculateYposition(previousI), 0);
                    }
                    break;
            }
            kremlinNode = kremlinNode->next;
        }
    }
}

void dibujarFruta(){
    struct FruitNode* fruitNode = returnFruitHead();
    struct Fruit* fruit;
    int posI;
    int posJ;
    while (fruitNode != NULL){
        fruit = fruitNode->fruit;
        posI = fruit->posI;
        posJ = fruit->posJ;
        switch ((int) gameMatrix[posI][posJ]){
            case 311:
                bitmap = al_load_bitmap("../src/imagenes/apple.png");
                al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                break;
            case 312:
                bitmap = al_load_bitmap("../src/imagenes/apple_onvine.png");
                al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                break;
            case 321:
                bitmap = al_load_bitmap("../src/imagenes/banana.png");
                al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                break;
            case 322:
                bitmap = al_load_bitmap("../src/imagenes/banana_onvine.png");
                al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                break;
            case 331:
                bitmap = al_load_bitmap("../src/imagenes/mango.png");
                al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                break;
            case 332:
                bitmap = al_load_bitmap("../src/imagenes/mango_onvine.png");
                al_draw_bitmap(bitmap, calculateXposition(posJ), calculateYposition(posI), 0);
                break;
        }
        fruitNode = fruitNode->next;
    }
}

void dibujarMarioyDK(){
    bitmap = al_load_bitmap("../src/imagenes/mario.png");
    al_draw_bitmap(bitmap, calculateXposition(3), calculateYposition(3), 0);
    bitmap = al_load_bitmap("../src/imagenes/key.png");
    al_draw_bitmap(bitmap, calculateXposition(7), calculateYposition(0), 0);
    bitmap = al_load_bitmap("../src/imagenes/dk1.png");
    al_draw_bitmap(bitmap, calculateXposition(0), calculateYposition(1), 0);
    bitmap = al_load_bitmap("../src/imagenes/dk2.png");
    al_draw_bitmap(bitmap, calculateXposition(1), calculateYposition(1), 0);
    bitmap = al_load_bitmap("../src/imagenes/dk3.png");
    al_draw_bitmap(bitmap, calculateXposition(2), calculateYposition(1), 0);
    bitmap = al_load_bitmap("../src/imagenes/dk4.png");
    al_draw_bitmap(bitmap, calculateXposition(0), calculateYposition(2), 0);
    bitmap = al_load_bitmap("../src/imagenes/dk5.png");
    al_draw_bitmap(bitmap, calculateXposition(1), calculateYposition(2), 0);
    bitmap = al_load_bitmap("../src/imagenes/dk6.png");
    al_draw_bitmap(bitmap, calculateXposition(2), calculateYposition(2), 0);
    bitmap = al_load_bitmap("../src/imagenes/dk7.png");
    al_draw_bitmap(bitmap, calculateXposition(0), calculateYposition(3), 0);
    bitmap = al_load_bitmap("../src/imagenes/dk8.png");
    al_draw_bitmap(bitmap, calculateXposition(1), calculateYposition(3), 0);
    bitmap = al_load_bitmap("../src/imagenes/dk9.png");
    al_draw_bitmap(bitmap, calculateXposition(2), calculateYposition(3), 0);
}

int calculateXposition(int j){
    int posX = j * 44;
    return posX;
}

int calculateYposition(int i){
    int posY = i * 29;
    return posY;
}

static void* Func_Thread(ALLEGRO_THREAD *thr, void* arg){
    int a = 1;
    while (true){
        while (a == 1){
            if (enviar(serverIp, port, serializeMatrix(gameMatrix)) == 0){
                a = 0;
            }
        }
        receivedJson = escuchar(port, serverIp);
        a = 1;

    }
}

void setPort(int nport){
    port = nport;
}