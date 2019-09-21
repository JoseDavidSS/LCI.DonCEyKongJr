//
// Created by Kevin Cordero Zúñiga on 9/18/2019.
//
#include <stdio.h>
#include "Game.h"
#include "lists/FruitNode.h"
#include "lists/KremlinNode.h"

void initializeGameMatrix(int* gameMatrix[24][16]){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            if ((i == 20 && (j >= 12 && j <= 14)) || (i == 21 && (j == 4 || (j >= 9 && j <= 11))) || (i == 22 && (j >= 5 && j <= 8)) || (i == 23 && j <= 2)){
                gameMatrix[i][j] = (int *) tree;
            }else if ((i == 2 && (j >= 4 && j <= 5)) || (i == 4 && j <= 8) || (i == 5 && (j >= 8 && j <= 11)) || (i == 9 && j == 2) || (i == 13 && j >= 11) || (i == 15 && (j >= 2 && j <= 3))){
                gameMatrix[i][j] = (int *) tile;
            }else if ((j == 0 && (i >= 5 && i <= 20)) || (j == 2 && ((i >= 10 && i <= 12) || (i >= 16 && i <= 20))) || (j == 4 && (i >= 5 && i <= 17)) || (j == 6 && (i <= 1 || (i >= 5 && i <= 13))) || (j == 8 && (i >= 7 && i <= 17)) || (j == 9 && i == 0) || (j == 10 && (i >= 6 && i <= 15)) || (j == 12 && (i <= 10 || (i >= 14 && i <= 17))) || (j == 14 && (i <= 10 || (i >= 14 && i <= 17)))){
                gameMatrix[i][j] = (int *) vine;
            }else if (i == 22 && j == 0){
                gameMatrix[i][j] = (int *) dkjrRight1;
            }else{
                gameMatrix[i][j] = (int *) nothing;
            }
        }
    }
}

void updateGameMatrix(int direction, int* gameMatrix[24][16]){
    if (dkJr.dead == 1){
        resetDKJrPosition(gameMatrix);
        dkJr.dead = 0;
        direction = 0;
        dkJr.airUp = 0;
        dkJr.airRight = 0;
        dkJr.airLeft = 0;
    }
    if (dkJr.falling >= 1){
        makeDKJrFall(gameMatrix);
        direction = 0;
    }
    if (dkJr.airUp == 1){
        moveDKJrUpAir(gameMatrix);
        direction = 0;
        dkJr.airUp = 0;
    }
    if (dkJr.airLeft == 1){
        moveDKJrLeftAir(gameMatrix);
        direction = 0;
        dkJr.airLeft = 0;
    }
    if (dkJr.airRight == 1){
        moveDKJrRightAir(gameMatrix);
        direction = 0;
        dkJr.airRight = 0;
    }
    if (direction != 0){
        if (dkJr.inVine == 1){
            moveDKJrVertical(direction, gameMatrix);
        }if (dkJr.inVine == 0){
            moveDKJrHorizontal(direction, gameMatrix);
        }
    }
    if (returnFruitHead() != NULL){
        updateFruits(gameMatrix);
    }
    if (returnKremlinHead() != NULL){
        updateKremlins(gameMatrix);
    }
}

void updateFruits(int* gameMatrix[24][16]){
    struct FruitNode* fruitNode = returnFruitHead();
    struct Fruit* fruit;
    int posI;
    int posJ;
    while (fruitNode != NULL){
        fruit = fruitNode->fruit;
        if (fruit->onScreen == 0){
            deleteFruitByID(fruit->id);
            fruitNode = fruitNode->next;
        }else{
            posI = fruit->posI;
            posJ = fruit->posJ;
            if (fruit->placed == 1){
                fruitNode = fruitNode->next;
            }else if (gameMatrix[posI][posJ] == (int*) vine){
                switch (fruit->type){
                    case 31:
                        gameMatrix[posI][posJ] = (int*) fruit1Vine;
                        break;
                    case 32:
                        gameMatrix[posI][posJ] = (int*) fruit2Vine;
                        break;
                    case 33:
                        gameMatrix[posI][posJ] = (int*) fruit3Vine;
                        break;
                }
                fruit->placed = 1;
                fruitNode = fruitNode->next;
            }else if (gameMatrix[posI][posJ] == (int*) nothing){
                switch (fruit->type){
                    case 31:
                        gameMatrix[posI][posJ] = (int*) fruit1Blanck;
                        break;
                    case 32:
                        gameMatrix[posI][posJ] = (int*) fruit2Blanck;
                        break;
                    case 33:
                        gameMatrix[posI][posJ] = (int*) fruit3Blanck;
                        break;
                }
                fruit->placed = 1;
                fruitNode = fruitNode->next;
            }else{
                fruit->onScreen = 0;
            }
        }
    }
}

void updateKremlins(int* gameMatrix[24][16]){
    struct KremlinNode* kremlinNode = returnKremlinHead();
    struct Kremlin* kremlin;
    while (kremlinNode != NULL){
        kremlin = kremlinNode->kremlin;
        if (kremlin->onScreen == 0){
            deleteKremlinByID(kremlin->id);
            kremlinNode = kremlinNode->next;
        }else if (kremlin->placed == 0){
            if (gameMatrix[kremlin->posI][kremlin->posJ] == (int*) nothing){
                switch (kremlin->type){
                    case 21:
                        gameMatrix[kremlin->posI][kremlin->posJ] = (int*) redKremlinRight1;
                        break;
                    case 22:
                        gameMatrix[kremlin->posI][kremlin->posJ] = (int*) blueKremlinRight1;
                        break;
                }
                kremlin->placed = 1;
                kremlinNode = kremlinNode->next;
            }else{
                kremlin->onScreen = 0;
                kremlinNode = kremlinNode->next;
            }
        }else if (kremlin->inVine == 0){
            searchVineForKremlin(kremlin, gameMatrix);
            kremlinNode = kremlinNode->next;
        }else{
            moveKremlinInVine(kremlin, gameMatrix);
            kremlinNode = kremlinNode->next;
        }
    }
}

void searchVineForKremlin(struct Kremlin* kremlin, int* gameMatrix[24][16]){
    int posI = kremlin->posI;
    int posJ = kremlin->posJ;
    kremlin->previousI = posI;
    kremlin->previousJ = posJ;
    int currentSprite = 0;
    if (posI < rows - 2 && gameMatrix[posI + 2][posJ] == (int *) vine){
        kremlin->posI += 2;
        kremlin->inVine = 1;
        gameMatrix[posI][posJ] = (int *) nothing;
        if (kremlin->type == 21){
            gameMatrix[kremlin->posI][posJ] = (int *) redKremlinDown1;
        }else{
            gameMatrix[kremlin->posI][posJ] = (int *) blueKremlinDown1;
        }
    }else if (posJ < (columns - kremlin->velocity) && (gameMatrix[posI + kremlin->velocity][posJ + kremlin->velocity] == (int *) tree || gameMatrix[posI + kremlin->velocity][posJ + kremlin->velocity] == (int *) tile)){
        kremlin->posJ += kremlin->velocity;
        currentSprite = (int) gameMatrix[posI][posJ];
        gameMatrix[posI][posJ] = (int *) nothing;
        if (kremlin->type == 21){
            switch (currentSprite){
                case 2141:
                    gameMatrix[posI][kremlin->posJ] = (int *) redKremlinRight2;
                    break;
                case 2142:
                    gameMatrix[posI][kremlin->posJ] = (int *) redKremlinRight1;
                    break;
            }
        }else{
            switch (currentSprite){
                case 2241:
                    gameMatrix[posI][kremlin->posJ] = (int *) blueKremlinRight2;
                    break;
                case 2242:
                    gameMatrix[posI][kremlin->posJ] = (int *) blueKremlinRight1;
                    break;
            }
        }
    }

    else{
        kremlin->posJ -= kremlin->velocity;
        currentSprite = (int) gameMatrix[posI][posJ];
        gameMatrix[posI][posJ] = (int *) nothing;
        if (kremlin->type == 21){
            switch (currentSprite){
                case 2131:
                    gameMatrix[posI][kremlin->posJ] = (int *) redKremlinLeft2;
                    break;
                case 2132:
                    gameMatrix[posI][kremlin->posJ] = (int *) redKremlinLeft1;
                    break;
            }
        }else{
            switch (currentSprite){
                case 2231:
                    gameMatrix[posI][kremlin->posJ] = (int *) blueKremlinLeft2;
                    break;
                case 2232:
                    gameMatrix[posI][kremlin->posJ] = (int *) blueKremlinLeft1;
                    break;
            }
        }
    }
}


void moveKremlinInVine(struct Kremlin* kremlin, int* gameMatrix[24][16]){
    int posI = kremlin->posI;
    int posJ = kremlin->posJ;
    kremlin->previousI = posI;
    kremlin->previousJ = posJ;
    int currentSprite = 0;
    if (gameMatrix[posI + kremlin->velocity][posJ] == (int*) vine) {
        kremlin->posI += kremlin->velocity;
        currentSprite = (int) gameMatrix[posI][posJ];
        gameMatrix[posI][posJ] = (int*) vine;
        if (kremlin->type == 21){
            switch (currentSprite){
                case 2121:
                    gameMatrix[kremlin->posI][posJ] = (int*) redKremlinDown2;
                    break;
                case 2122:
                    gameMatrix[kremlin->posI][posJ] = (int*) redKremlinDown1;
                    break;
            }
        }else{
            switch (currentSprite){
                case 2221:
                    gameMatrix[kremlin->posI][posJ] = (int*) blueKremlinDown2;
                    break;
                case 2222:
                    gameMatrix[kremlin->posI][posJ] = (int*) blueKremlinDown1;
                    break;
            }
        }
    }else if (kremlin->type == 21){
        kremlin->velocity *= -1;
        kremlin->posI += kremlin->velocity;
        currentSprite = (int) gameMatrix[posI][posJ];
        gameMatrix[posI][posJ] = (int*) vine;
        if (kremlin->type == 21){
            switch (currentSprite){
                case 2111:
                    gameMatrix[kremlin->posI][posJ] = (int*) redKremlinUp2;
                    break;
                case 2112:
                    gameMatrix[kremlin->posI][posJ] = (int*) redKremlinUp1;
                    break;
            }
        }else{
            switch (currentSprite){
                case 2211:
                    gameMatrix[kremlin->posI][posJ] = (int*) blueKremlinUp2;
                    break;
                case 2212:
                    gameMatrix[kremlin->posI][posJ] = (int*) blueKremlinUp1;
                    break;
            }
        }
        gameMatrix[kremlin->posI][posJ] = (int*) kremlin->type;
    }else{
        kremlin->inVine = 0;
        kremlin->onScreen = 0;
        gameMatrix[posI][posJ] = (int*) vine;
    }
}

void moveDKJrHorizontal(int direction, int* gameMatrix[24][16]){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    int currentSprite = 0;
    switch (direction){
        case 1: //Derecha
            if (posJ < columns - 1 && gameMatrix[posI][posJ + dkJr.velocity] == (int*) nothing){
                currentSprite = (int) gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = (int*) nothing;
                posJ += dkJr.velocity;
                dkJr.posJ = posJ;
                switch (currentSprite){
                    case 421:
                        gameMatrix[posI][posJ] = (int*) dkjrRight1;
                        break;
                    case 422:
                        gameMatrix[posI][posJ] = (int*) dkjrRight1;
                        break;
                    case 423:
                        gameMatrix[posI][posJ] = (int*) dkjrRight1;
                        break;
                    case 411:
                        gameMatrix[posI][posJ] = (int*) dkjrRight2;
                        break;
                    case 412:
                        gameMatrix[posI][posJ] = (int*) dkjrRight3;
                        break;
                    case 413:
                        gameMatrix[posI][posJ] = (int*) dkjrRight1;
                        break;
                }if (gameMatrix[posI + 1][posJ] == 0){
                    dkJr.falling = 1;
                }
                break;
            }else if (posJ < columns - 1 && (gameMatrix[posI][posJ + dkJr.velocity] == (int*) 21 || gameMatrix[posI][posJ + dkJr.velocity] == (int*) 22)){
                dkJr.lives--;
                dkJr.dead = 1;
                struct Kremlin* kremlin = findKremlinByPos(posI, posJ + dkJr.velocity);
                kremlin->onScreen = 0;
                gameMatrix[posI][posJ + dkJr.velocity] = (int*) nothing;
                break;
            }else if (posJ < columns - 1 && (gameMatrix[posI][posJ + dkJr.velocity] == (int*) fruit1Blanck || gameMatrix[posI][posJ + dkJr.velocity] == (int*) fruit2Blanck || gameMatrix[posI][posJ + dkJr.velocity] == (int*) fruit3Blanck)){
                struct Fruit* delFruit = findFruitByPos(posI, posJ + dkJr.velocity);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                currentSprite = (int) gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = (int*) nothing;
                posJ += dkJr.velocity;
                dkJr.posJ = posJ;
                switch (currentSprite){
                    case 421:
                        gameMatrix[posI][posJ] = (int*) dkjrRight1;
                        break;
                    case 422:
                        gameMatrix[posI][posJ] = (int*) dkjrRight1;
                        break;
                    case 423:
                        gameMatrix[posI][posJ] = (int*) dkjrRight1;
                        break;
                    case 411:
                        gameMatrix[posI][posJ] = (int*) dkjrRight2;
                        break;
                    case 412:
                        gameMatrix[posI][posJ] = (int*) dkjrRight3;
                        break;
                    case 413:
                        gameMatrix[posI][posJ] = (int*) dkjrRight1;
                        break;
                }if (gameMatrix[posI + 1][posJ] == 0){
                    dkJr.falling = 1;
                }
                break;
            }else{
                break;
            }
        case 2: //Izquierda
            if (posJ > 0 && gameMatrix[posI][posJ - dkJr.velocity] == (int*) nothing){
                currentSprite = (int) gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = (int*) nothing;
                posJ -= dkJr.velocity;
                dkJr.posJ = posJ;
                switch (currentSprite){
                    case 411:
                        gameMatrix[posI][posJ] = (int*) dkjrLeft1;
                        break;
                    case 412:
                        gameMatrix[posI][posJ] = (int*) dkjrLeft1;
                        break;
                    case 413:
                        gameMatrix[posI][posJ] = (int*) dkjrLeft1;
                        break;
                    case 421:
                        gameMatrix[posI][posJ] = (int*) dkjrLeft2;
                        break;
                    case 422:
                        gameMatrix[posI][posJ] = (int*) dkjrLeft3;
                        break;
                    case 423:
                        gameMatrix[posI][posJ] = (int*) dkjrLeft1;
                        break;
                }if (gameMatrix[posI + 1][posJ] == 0){
                    dkJr.falling = 1;
                }
                break;
            }else if (posJ > 0 && (gameMatrix[posI][posJ - dkJr.velocity] == (int*) 21 || gameMatrix[posI][posJ - dkJr.velocity] == (int*) 22)){
                dkJr.lives--;
                dkJr.dead = 1;
                struct Kremlin* kremlin = findKremlinByPos(posI, posJ - dkJr.velocity);
                kremlin->onScreen = 0;
                gameMatrix[posI][posJ - dkJr.velocity] = (int*) nothing;
                break;
            }else if (posJ > 0 && (gameMatrix[posI][posJ - dkJr.velocity] == (int*) fruit1Blanck || gameMatrix[posI][posJ - dkJr.velocity] == (int*) fruit2Blanck || gameMatrix[posI][posJ - dkJr.velocity] == (int*) fruit3Blanck)){
                struct Fruit* delFruit = findFruitByPos(posI, posJ - dkJr.velocity);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                currentSprite = (int) gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = (int*) nothing;
                posJ -= dkJr.velocity;
                dkJr.posJ = posJ;
                switch (currentSprite){
                    case 411:
                        gameMatrix[posI][posJ] = (int*) dkjrLeft1;
                        break;
                    case 412:
                        gameMatrix[posI][posJ] = (int*) dkjrLeft1;
                        break;
                    case 413:
                        gameMatrix[posI][posJ] = (int*) dkjrLeft1;
                        break;
                    case 421:
                        gameMatrix[posI][posJ] = (int*) dkjrLeft2;
                        break;
                    case 422:
                        gameMatrix[posI][posJ] = (int*) dkjrLeft3;
                        break;
                    case 423:
                        gameMatrix[posI][posJ] = (int*) dkjrLeft1;
                        break;
                }if (gameMatrix[posI + 1][posJ] == 0){
                    dkJr.falling = 1;
                }
                break;
            }else{
                break;
            }
        case 3: //Salta
            if (posI > 0 && gameMatrix[posI - dkJr.velocity][posJ] == (int*) vine){
                gameMatrix[posI][posJ] = (int*) nothing;
                posI -= dkJr.velocity;
                dkJr.posI = posI;
                gameMatrix[posI][posJ] = (int*) dkjrVine1;
                dkJr.inVine = 1;
                break;
            }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit3Vine)){
                gameMatrix[posI][posJ] = (int*) nothing;
                posI -= dkJr.velocity;
                dkJr.posI = posI;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = (int*) dkjrVine1;
                dkJr.inVine = 1;
                break;
            }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit3Blanck)){
                gameMatrix[posI][posJ] = (int*) nothing;
                posI -= dkJr.velocity;
                dkJr.posI = posI;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
                dkJr.airUp = 1;
                break;
            }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == (int*) tree || gameMatrix[posI - dkJr.velocity][posJ] == (int*) tile)){
                break;
            }else{
                dkJr.airUp = 1;
                gameMatrix[posI][posJ] = (int*) nothing;
                posI -= dkJr.velocity;
                dkJr.posI = posI;
                gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
                break;
            }
        case 4: //Salta Izq
            if (posI > 0 && posJ > 0 && gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) vine){
                gameMatrix[posI][posJ] = (int*) nothing;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = (int*) dkjrVine1;
                dkJr.inVine = 1;
                break;
            }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit3Vine)){
                gameMatrix[posI][posJ] = (int*) nothing;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = (int*) dkjrVine1;
                dkJr.inVine = 1;
                break;
            }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit3Blanck)){
                gameMatrix[posI][posJ] = (int*) nothing;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = (int*) dkjrJumpLeft;
                dkJr.airLeft = 1;
                break;
            }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) tile || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) tree)){
                break;
            }else{
                dkJr.airLeft = 1;
                gameMatrix[posI][posJ] = (int*) nothing;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = (int*) dkjrJumpLeft;
                break;
            }
        case 5: //Salta Der
            if (posI > 0 && posJ < columns - 1 && gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) vine){
                gameMatrix[posI][posJ] = (int*) nothing;
                posI -= dkJr.velocity;
                posJ += dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = (int*) dkjrVine1;
                dkJr.inVine = 1;
                break;
            }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit3Vine)){
                gameMatrix[posI][posJ] = (int*) nothing;
                posI -= dkJr.velocity;
                posJ += dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = (int*) dkjrVine1;
                dkJr.inVine = 1;
                break;
            }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit3Blanck)){
                gameMatrix[posI][posJ] = (int*) nothing;
                posI -= dkJr.velocity;
                posJ += dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
                dkJr.airRight = 1;
                break;
            }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) tile || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) tree)){
                break;
            }else{
                dkJr.airRight = 1;
                gameMatrix[posI][posJ] = (int*) nothing;
                posI -= dkJr.velocity;
                posJ += dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
                break;
            }
    }
}

void moveDKJrVertical(int direction, int* gameMatrix[24][16]){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    int currentSprite = 0;
    switch (direction){
        case 4: //Salta izq de liana
            if (posI > 0 && posJ > 0 && gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) vine){
                gameMatrix[posI][posJ] = (int*) vine;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = (int*) dkjrVine1;
                dkJr.inVine = 1;
                break;
            }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit3Vine)){
                gameMatrix[posI][posJ] = (int*) vine;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = (int*) dkjrVine1;
                dkJr.inVine = 1;
                break;
            }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit3Blanck)){
                gameMatrix[posI][posJ] = (int*) vine;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = (int*) dkjrJumpLeft;
                dkJr.airLeft = 1;
                break;
            }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) tile || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) tree)){
                gameMatrix[posI][posJ] = (int*) vine;
                posJ -= dkJr.velocity;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = (int*) dkjrJumpLeft;
                dkJr.falling = 1;
                break;
            }else{
                dkJr.airLeft = 1;
                gameMatrix[posI][posJ] = (int*) vine;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = (int*) dkjrJumpLeft;
                break;
            }
        case 5: //Salta der de liana
            if (posI > 0 && posJ < columns - 1 && gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) vine){
                gameMatrix[posI][posJ] = (int*) vine;
                posI -= dkJr.velocity;
                posJ += dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = (int*) dkjrVine1;
                dkJr.inVine = 1;
                break;
            }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit3Vine)){
                gameMatrix[posI][posJ] = (int*) vine;
                posI -= dkJr.velocity;
                posJ += dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = (int*) dkjrVine1;
                dkJr.inVine = 1;
                break;
            }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit3Blanck)){
                gameMatrix[posI][posJ] = (int*) vine;
                posI -= dkJr.velocity;
                posJ += dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
                dkJr.airRight = 1;
                break;
            }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) tile || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) tree)){
                gameMatrix[posI][posJ] = (int*) vine;
                posJ += dkJr.velocity;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
                dkJr.falling = 1;
                break;
            }else{
                dkJr.airRight = 1;
                gameMatrix[posI][posJ] = (int*) vine;
                posI -= dkJr.velocity;
                posJ += dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
                break;
            }
        case 6: //Sube
            if (posI > 0 && gameMatrix[posI - dkJr.velocity][posJ] == (int*) vine){
                currentSprite = (int) gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = (int*) vine;
                posI -= dkJr.velocity;
                dkJr.posI = posI;
                switch (currentSprite){
                    case 431:
                        gameMatrix[posI][posJ] = (int*)  dkjrVine2;
                        break;
                    case 432:
                        gameMatrix[posI][posJ] = (int*) dkjrVine1;
                        break;
                }
                break;
            }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == (int*) 21 || gameMatrix[posI - dkJr.velocity][posJ] == (int*) 22)){
                dkJr.lives--;
                dkJr.dead = 1;
                struct Kremlin* kremlin = findKremlinByPos(posI - dkJr.velocity, posJ);
                kremlin->onScreen = 0;
                gameMatrix[posI - dkJr.velocity][posJ] = (int*) vine;
                break;
            }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit3Vine)){
                struct Fruit* delFruit = findFruitByPos(posI - dkJr.velocity, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                currentSprite = (int) gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = (int*) vine;
                posI -= dkJr.velocity;
                dkJr.posI = posI;
                switch (currentSprite){
                    case 431:
                        gameMatrix[posI][posJ] = (int*) dkjrVine2;
                        break;
                    case 432:
                        gameMatrix[posI][posJ] = (int*) dkjrVine1;
                        break;
                }
                break;
            }else{
                break;
            }
        case 7: //Baja
            if (posI < rows - 1 && gameMatrix[posI + 1][posJ] == (int*) vine){
                currentSprite = (int) gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = (int*) vine;
                posI += dkJr.velocity;
                dkJr.posI = posI;
                switch (currentSprite){
                    case 431:
                        gameMatrix[posI][posJ] = (int*) dkjrVine2;
                        break;
                    case 432:
                        gameMatrix[posI][posJ] = (int*) dkjrVine1;
                        break;
                }
                break;
            }else if (posI < rows - 1 && (gameMatrix[posI + dkJr.velocity][posJ] == (int*) 21 || gameMatrix[posI + dkJr.velocity][posJ] == (int*) 22)){
                dkJr.lives--;
                dkJr.dead = 1;
                struct Kremlin* kremlin = findKremlinByPos(posI + dkJr.velocity, posJ);
                kremlin->onScreen = 0;
                gameMatrix[posI + dkJr.velocity][posJ] = (int*) vine;
                break;
            }else if (posI < rows - 1 && (gameMatrix[posI + dkJr.velocity][posJ] == (int*) fruit1Vine || gameMatrix[posI + dkJr.velocity][posJ] == (int*) fruit2Vine || gameMatrix[posI + dkJr.velocity][posJ] == (int*) fruit3Vine)){
                struct Fruit* delFruit = findFruitByPos(posI + dkJr.velocity, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                currentSprite = (int) gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = (int*) vine;
                posI += dkJr.velocity;
                dkJr.posI = posI;
                switch (currentSprite){
                    case 431:
                        gameMatrix[posI][posJ] = (int*) dkjrVine2;
                        break;
                    case 432:
                        gameMatrix[posI][posJ] = (int*) dkjrVine1;
                        break;
                }
                break;
            }else{
                gameMatrix[posI][posJ] = (int*) vine;
                posI += dkJr.velocity;
                dkJr.posI = posI;
                gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
                dkJr.falling = 1;
                break;
            }
    }
}

void moveDKJrUpAir(int* gameMatrix[24][16]){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    if (posI > 0 && gameMatrix[posI - dkJr.velocity][posJ] == (int*) vine){
        gameMatrix[posI][posJ] = (int*) nothing;
        posI -= dkJr.velocity;
        dkJr.posI = posI;
        gameMatrix[posI][posJ] = (int*) dkjrVine1;
        dkJr.inVine = 1;
    }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit3Vine)){
        gameMatrix[posI][posJ] = (int*) nothing;
        posI -= dkJr.velocity;
        dkJr.posI = posI;
        struct Fruit* delFruit = findFruitByPos(posI, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        gameMatrix[posI][posJ] = (int*) dkjrVine1;
        dkJr.inVine = 1;
    }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ] == (int*) fruit3Blanck)){
        gameMatrix[posI][posJ] = (int*) nothing;
        posI -= dkJr.velocity;
        dkJr.posI = posI;
        struct Fruit* delFruit = findFruitByPos(posI, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
        dkJr.falling = 1;
    }else{
        dkJr.falling = 1;
        gameMatrix[posI][posJ] = (int*) nothing;
        posI -= dkJr.velocity;
        dkJr.posI = posI;
        gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
    }
}

void moveDKJrLeftAir(int* gameMatrix[24][16]){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    if (posI > 0 && posJ > 0 && gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) vine){
        gameMatrix[posI][posJ] = (int*) nothing;
        posI -= dkJr.velocity;
        posJ -= dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = (int*) dkjrVine1;
        dkJr.inVine = 1;
    }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit3Vine)){
        gameMatrix[posI][posJ] = (int*) nothing;
        posI -= dkJr.velocity;
        posJ -= dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        struct Fruit* delFruit = findFruitByPos(posI, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        gameMatrix[posI][posJ] = (int*) dkjrVine1;
        dkJr.inVine = 1;
    }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) fruit3Blanck)){
        gameMatrix[posI][posJ] = (int*) nothing;
        posI -= dkJr.velocity;
        posJ -= dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        struct Fruit* delFruit = findFruitByPos(posI, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        gameMatrix[posI][posJ] = (int*) dkjrJumpLeft;
        dkJr.falling = 1;
    }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) tile || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == (int*) tree)){
        gameMatrix[posI][posJ] = (int*) vine;
        posJ -= dkJr.velocity;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = (int*) dkjrJumpLeft;
        dkJr.falling = 1;
    }else{
        dkJr.falling = 1;
        gameMatrix[posI][posJ] = (int*) nothing;
        posI -= dkJr.velocity;
        posJ -= dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = (int*) dkjrJumpLeft;
    }
}

void moveDKJrRightAir(int* gameMatrix[24][16]){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    if (posI > 0 && posJ < columns - 1 && gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) vine){
        gameMatrix[posI][posJ] = (int*) nothing;
        posI -= dkJr.velocity;
        posJ += dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = (int*) dkjrVine1;
        dkJr.inVine = 1;
    }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit3Vine)){
        gameMatrix[posI][posJ] = (int*) nothing;
        posI -= dkJr.velocity;
        posJ += dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        struct Fruit* delFruit = findFruitByPos(posI, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        gameMatrix[posI][posJ] = (int*) dkjrVine1;
        dkJr.inVine = 1;
    }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) fruit3Blanck)){
        gameMatrix[posI][posJ] = (int*) nothing;
        posI -= dkJr.velocity;
        posJ += dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        struct Fruit* delFruit = findFruitByPos(posI, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
        dkJr.falling = 1;
    }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) tile || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == (int*) tree)) {
        gameMatrix[posI][posJ] = (int*) vine;
        posJ += dkJr.velocity;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
        dkJr.falling = 1;
    }else{
        dkJr.falling = 1;
        gameMatrix[posI][posJ] = (int*) nothing;
        posI -= dkJr.velocity;
        posJ += dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = (int*) dkjrJumpRight;
    }
}

void makeDKJrFall(int* gameMatrix[24][16]){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    int currentSprite = 0;
    if (posI < rows - 1 && (gameMatrix[posI + dkJr.velocity][posJ] == (int*) tile || gameMatrix[posI + dkJr.velocity][posJ] == (int*) tree)){
        if (dkJr.falling > 6){
            dkJr.lives--;
            dkJr.dead = 1;
            dkJr.falling = 0;
            dkJr.inVine = 0;
        }else{
            dkJr.falling = 0;
            dkJr.inVine = 0;
            gameMatrix[posI][posJ] = (int*) dkjrRight1;
        }
    }else if (posI < rows - 1 && (gameMatrix[posI + dkJr.velocity][posJ] == (int*) fruit1Blanck || gameMatrix[posI + dkJr.velocity][posJ] == (int*) fruit2Blanck || gameMatrix[posI + dkJr.velocity][posJ] == (int*) fruit3Blanck)){
        struct Fruit* delFruit = findFruitByPos(posI + dkJr.velocity, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        currentSprite = (int) gameMatrix[posI][posJ];
        gameMatrix[posI][posJ] = (int*) nothing;
        posI += dkJr.velocity;
        dkJr.posI = posI;
        gameMatrix[posI][posJ] = (int*) currentSprite;
        dkJr.falling++;
    }else if (posI < rows - 1 && gameMatrix[posI + dkJr.velocity][posJ] == (int*) nothing){
        currentSprite = (int) gameMatrix[posI][posJ];
        gameMatrix[posI][posJ] = (int*) nothing;
        posI += dkJr.velocity;
        dkJr.posI = posI;
        gameMatrix[posI][posJ] = (int*) currentSprite;
        dkJr.falling++;
    }else{
        dkJr.lives--;
        dkJr.dead = 1;
    }
}

void resetDKJrPosition(int* gameMatrix[24][16]){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    if (dkJr.inVine == 1){
        gameMatrix[posI][posJ] = (int*) vine;
        posI = 22;
        posJ = 0;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = (int*) dkjrRight1;
        dkJr.inVine = 0;
    }else{
        gameMatrix[posI][posJ] = (int*) nothing;
        posI = 22;
        posJ = 0;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = (int*) dkjrRight1;
    }
}

void printMatrix(int* gameMatrix[24][16]){
    printf("\n");
    for(int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            printf("%d ", (int) gameMatrix[i][j]);
        }
        printf("\n");
    }
}

struct DKJr* returnDKJr(){
    return &dkJr;
}