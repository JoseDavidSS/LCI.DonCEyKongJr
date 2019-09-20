//
// Created by Kevin Cordero Zúñiga on 9/18/2019.
//
#include <stdio.h>
#include "Game.h"
#include "lists/FruitNode.h"
#include "lists/KremlinNode.h"

void initializeGameMatrix(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            if ((i == 20 && (j >= 12 && j <= 14)) || (i == 21 && (j == 4 || (j >= 9 && j <= 11))) || (i == 22 && (j >= 5 && j <= 8)) || (i == 23 && j <= 2)){
                gameMatrix[i][j] = tree;
            }else if ((i == 4 && (j >= 4 && j <= 5)) || (i == 4 && j <= 8) || (i == 5 && (j >= 8 && j <= 11)) || (i == 9 && j == 2) || (i == 13 && j >= 11) || (i == 15 && (j >= 2 && j <= 3))){
                gameMatrix[i][j] = tile;
            }else if ((j == 0 && (i >= 5 && i <= 20)) || (j == 2 && ((i >= 10 && i <= 14) || (i >= 16 && i <= 20))) || (j == 4 && (i >= 5 && i <= 17)) || (j == 7 && (i <= 1 || (i >= 5 && i <= 13))) || (j == 8 && (i >= 6 && i <= 17)) || (j == 9 && i == 0) || (j == 10 && (i >= 6 && i <= 15)) || ((j == 12 || j == 14) && (i <= 12 || (i >= 14 && i <= 17)))){
                gameMatrix[i][j] = vine;
            }else if (i == 22 && j == 0){
                gameMatrix[i][j] = dkjrRight1;
            }else{
                gameMatrix[i][j] = nothing;
            }
        }
    }
}

void updateGameMatrix(int direction){
    if (dkJr.dead == 1){
        resetDKJrPosition();
        dkJr.dead = 0;
        direction = 0;
        dkJr.airUp = 0;
        dkJr.airRight = 0;
        dkJr.airLeft = 0;
    }
    if (dkJr.falling >= 1){
        makeDKJrFall();
        direction = 0;
    }
    if (dkJr.airUp == 1){
        moveDKJrUpAir();
        direction = 0;
        dkJr.airUp = 0;
    }
    if (dkJr.airLeft == 1){
        moveDKJrLeftAir();
        direction = 0;
        dkJr.airLeft = 0;
    }
    if (dkJr.airRight == 1){
        moveDKJrRightAir();
        direction = 0;
        dkJr.airRight = 0;
    }
    if (direction != 0){
        if (dkJr.inVine == 1){
            moveDKJrVertical(direction);
        }if (dkJr.inVine == 0){
            moveDKJrHorizontal(direction);
        }
    }
    if (returnFruitHead() != NULL){
        deleteFruits();
    }
    if (returnKremlinHead() != NULL){
        moveKremlins();
        deleteKremlins();
    }
}

void deleteFruits(){
    struct FruitNode* fruitNode = returnFruitHead();
    struct Fruit* delFruit;
    while (fruitNode != NULL){
        delFruit = fruitNode->fruit;
        if (delFruit->onScreen == 0){
            deleteFruitByID(delFruit->id);
        }
        fruitNode = fruitNode->next;
    }
}

void deleteKremlins(){
    struct KremlinNode* kremlinNode = returnKremlinHead();
    struct Kremlin* kremlin;
    while (kremlinNode != NULL){
        kremlin = kremlinNode->kremlin;
        if (kremlin->onScreen == 0){
            deleteKremlinByID(kremlin->id);
        }
        kremlinNode = kremlinNode->next;
    }
}

void moveKremlins(){
    struct KremlinNode* kremlinNode = returnKremlinHead();
    struct Kremlin* kremlin;
    while (kremlinNode != NULL){
        kremlin = kremlinNode->kremlin;
        if (kremlin->inVine == 0){
            searchVineForKremlin(kremlin);
            kremlinNode = kremlinNode->next;
        }
        else{
            moveKremlinInVine(kremlin);
            kremlinNode = kremlinNode->next;
        }
    }
}

void searchVineForKremlin(struct Kremlin* kremlin){
    int posI = kremlin->posI;
    int posJ = kremlin->posJ;
    int currentSprite = 0;
    if (posI < rows - 2){
        if (gameMatrix[posI + 2][posJ] == vine){
            kremlin->posI += 2;
            kremlin->inVine = 1;
            gameMatrix[posI][posJ] = nothing;
            if (kremlin->type == 21){
                gameMatrix[kremlin->posI][posJ] = redKremlinDown1;
            }else{
                gameMatrix[kremlin->posI][posJ] = blueKremlinDown1;
            }
        }
    }else{
        if (posJ < (columns - kremlin->velocity) && posI < rows - 1){
            if (gameMatrix[posI + kremlin->velocity][posJ + kremlin->velocity] == tree || gameMatrix[posI + kremlin->velocity][posJ + kremlin->velocity] == tile){
                kremlin->posJ += kremlin->velocity;
                currentSprite = gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = nothing;
                if (kremlin->type == 21){
                    switch (currentSprite){
                        case 2141:
                            gameMatrix[posI][kremlin->posJ] = redKremlinRight2;
                            break;
                        case 2142:
                            gameMatrix[posI][kremlin->posJ] = redKremlinRight1;
                            break;
                    }
                }else{
                    switch (currentSprite){
                        case 2241:
                            gameMatrix[posI][kremlin->posJ] = blueKremlinRight2;
                            break;
                        case 2242:
                            gameMatrix[posI][kremlin->posJ] = blueKremlinRight1;
                            break;
                    }
                }
            }
        }if (posJ > kremlin->velocity && posI < rows - 1){
            if (gameMatrix[posI - kremlin->velocity][posJ - kremlin->velocity] == tree || gameMatrix[posI - kremlin->velocity][posJ - kremlin->velocity] == tile){
                kremlin->posJ -= kremlin->velocity;
                currentSprite = gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = nothing;
                if (kremlin->type == 21){
                    switch (currentSprite){
                        case 2131:
                            gameMatrix[posI][kremlin->posJ] = redKremlinLeft2;
                            break;
                        case 2132:
                            gameMatrix[posI][kremlin->posJ] = redKremlinLeft1;
                            break;
                    }
                }else{
                    switch (currentSprite){
                        case 2231:
                            gameMatrix[posI][kremlin->posJ] = blueKremlinLeft2;
                            break;
                        case 2232:
                            gameMatrix[posI][kremlin->posJ] = blueKremlinLeft1;
                            break;
                    }
                }
            }
        }
    }
}

void moveKremlinInVine(struct Kremlin* kremlin){
    int posI = kremlin->posI;
    int posJ = kremlin->posJ;
    int currentSprite = 0;
    if (gameMatrix[posI + kremlin->velocity][posJ] == vine) {
        kremlin->posI += kremlin->velocity;
        currentSprite = gameMatrix[posI][posJ];
        gameMatrix[posI][posJ] = vine;
        if (kremlin->type == 21){
            switch (currentSprite){
                case 2121:
                    gameMatrix[kremlin->posI][posJ] = redKremlinDown2;
                    break;
                case 2122:
                    gameMatrix[kremlin->posI][posJ] = redKremlinDown1;
                    break;
            }
        }else{
            switch (currentSprite){
                case 2221:
                    gameMatrix[kremlin->posI][posJ] = blueKremlinDown2;
                    break;
                case 2222:
                    gameMatrix[kremlin->posI][posJ] = blueKremlinDown1;
                    break;
            }
        }
    }else if (kremlin->type == 21){
        kremlin->velocity *= -1;
        kremlin->posI += kremlin->velocity;
        currentSprite = gameMatrix[posI][posJ];
        gameMatrix[posI][posJ] = vine;
        if (kremlin->type == 21){
            switch (currentSprite){
                case 2111:
                    gameMatrix[kremlin->posI][posJ] = redKremlinUp2;
                    break;
                case 2112:
                    gameMatrix[kremlin->posI][posJ] = redKremlinUp1;
                    break;
            }
        }else{
            switch (currentSprite){
                case 2211:
                    gameMatrix[kremlin->posI][posJ] = blueKremlinUp2;
                    break;
                case 2212:
                    gameMatrix[kremlin->posI][posJ] = blueKremlinUp1;
                    break;
            }
        }
        gameMatrix[kremlin->posI][posJ] = kremlin->type;
    }else{
        kremlin->inVine = 0;
        kremlin->onScreen = 0;
        gameMatrix[posI][posJ] = vine;
    }
}

void moveDKJrHorizontal(int direction){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    int currentSprite = 0;
    switch (direction){
        case 1: //Derecha
            if (posJ < columns - 1 && gameMatrix[posI][posJ + dkJr.velocity] == nothing){
                currentSprite = gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = nothing;
                posJ += dkJr.velocity;
                dkJr.posJ = posJ;
                switch (currentSprite){
                    case 411:
                        gameMatrix[posI][posJ] = dkjrRight2;
                        break;
                    case 412:
                        gameMatrix[posI][posJ] = dkjrRight3;
                        break;
                    case 413:
                        gameMatrix[posI][posJ] = dkjrRight1;
                        break;
                }
                break;
            }else if (posJ < columns - 1 && (gameMatrix[posI][posJ + dkJr.velocity] == 21 || gameMatrix[posI][posJ + dkJr.velocity] == 22)){
                dkJr.lives--;
                dkJr.dead = 1;
                struct Kremlin* kremlin = findKremlinByPos(posI, posJ + dkJr.velocity);
                kremlin->onScreen = 0;
                gameMatrix[posI][posJ + dkJr.velocity] = vine;
                break;
            }else if (posJ < columns - 1 && (gameMatrix[posI][posJ + dkJr.velocity] == fruit1Blanck || gameMatrix[posI][posJ + dkJr.velocity] == fruit2Blanck || gameMatrix[posI][posJ + dkJr.velocity] == fruit3Blanck)){
                struct Fruit* delFruit = findFruitByPos(posI, posJ + dkJr.velocity);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                currentSprite = gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = vine;
                posJ += dkJr.velocity;
                dkJr.posJ = posJ;
                switch (currentSprite){
                    case 421:
                        gameMatrix[posI][posJ] = dkjrRight1;
                        break;
                    case 422:
                        gameMatrix[posI][posJ] = dkjrRight1;
                        break;
                    case 423:
                        gameMatrix[posI][posJ] = dkjrRight1;
                        break;
                    case 411:
                        gameMatrix[posI][posJ] = dkjrRight2;
                        break;
                    case 412:
                        gameMatrix[posI][posJ] = dkjrRight3;
                        break;
                    case 413:
                        gameMatrix[posI][posJ] = dkjrRight1;
                        break;
                }
                break;
            }else{
                break;
            }
        case 2: //Izquierda
            if (posJ > 0 && gameMatrix[posI][posJ - dkJr.velocity] == nothing){
                currentSprite = gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = nothing;
                posJ -= dkJr.velocity;
                dkJr.posJ = posJ;
                switch (currentSprite){
                    case 411:
                        gameMatrix[posI][posJ] = dkjrLeft1;
                        break;
                    case 412:
                        gameMatrix[posI][posJ] = dkjrLeft1;
                        break;
                    case 413:
                        gameMatrix[posI][posJ] = dkjrLeft1;
                        break;
                    case 421:
                        gameMatrix[posI][posJ] = dkjrLeft2;
                        break;
                    case 422:
                        gameMatrix[posI][posJ] = dkjrLeft3;
                        break;
                    case 423:
                        gameMatrix[posI][posJ] = dkjrLeft1;
                        break;
                }
                break;
            }else if (posJ > 0 && (gameMatrix[posI][posJ - dkJr.velocity] == 21 || gameMatrix[posI][posJ - dkJr.velocity] == 22)){
                dkJr.lives--;
                dkJr.dead = 1;
                struct Kremlin* kremlin = findKremlinByPos(posI, posJ - dkJr.velocity);
                kremlin->onScreen = 0;
                gameMatrix[posI][posJ - dkJr.velocity] = vine;
                break;
            }else if (posJ > 0 && (gameMatrix[posI][posJ - dkJr.velocity] == fruit1Blanck || gameMatrix[posI][posJ - dkJr.velocity] == fruit2Blanck || gameMatrix[posI][posJ - dkJr.velocity] == fruit3Blanck)){
                struct Fruit* delFruit = findFruitByPos(posI, posJ - dkJr.velocity);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                currentSprite = gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = vine;
                posJ -= dkJr.velocity;
                dkJr.posJ = posJ;
                switch (currentSprite){
                    case 421:
                        gameMatrix[posI][posJ] = dkjrLeft2;
                        break;
                    case 422:
                        gameMatrix[posI][posJ] = dkjrLeft3;
                        break;
                    case 423:
                        gameMatrix[posI][posJ] = dkjrLeft1;
                        break;
                }
                break;
            }else{
                break;
            }
        case 3: //Salta
            if (posI > 0 && gameMatrix[posI - dkJr.velocity][posJ] == vine){
                gameMatrix[posI][posJ] = nothing;
                posI -= dkJr.velocity;
                dkJr.posI = posI;
                gameMatrix[posI][posJ] = dkjrVine1;
                break;
            }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ] == fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ] == fruit3Vine)){
                gameMatrix[posI][posJ] = nothing;
                posI -= dkJr.velocity;
                dkJr.posI = posI;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = dkjrVine1;
                break;
            }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ] == fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ] == fruit3Blanck)){
                gameMatrix[posI][posJ] = nothing;
                posI -= dkJr.velocity;
                dkJr.posI = posI;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = dkjrJumpRight;
                dkJr.airUp = 1;
                break;
            }else{
                dkJr.airUp = 1;
                gameMatrix[posI][posJ] = nothing;
                posI -= dkJr.velocity;
                dkJr.posI = posI;
                gameMatrix[posI][posJ] = dkjrJumpRight;
                break;
            }
        case 4: //Salta Izq
            if (posI > 0 && posJ > 0 && gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == vine){
                gameMatrix[posI][posJ] = nothing;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = dkjrVine1;
                break;
            }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit3Vine)){
                gameMatrix[posI][posJ] = nothing;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = dkjrVine1;
                break;
            }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit3Blanck)){
                gameMatrix[posI][posJ] = nothing;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = dkjrJumpLeft;
                dkJr.airLeft = 1;
                break;
            }else{
                dkJr.airLeft = 1;
                gameMatrix[posI][posJ] = nothing;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = dkjrJumpLeft;
                break;
            }
        case 5: //Salta Der
            if (posI > 0 && posJ < columns - 1 && gameMatrix[posI - dkJr.velocity][posJ + dkjrJumpRight] == vine){
                gameMatrix[posI][posJ] = nothing;
                posI -= dkJr.velocity;
                posJ += dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = dkjrVine1;
                break;
            }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit3Vine)){
                gameMatrix[posI][posJ] = nothing;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = dkjrVine1;
                break;
            }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit3Blanck)){
                gameMatrix[posI][posJ] = nothing;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = dkjrJumpRight;
                dkJr.airRight = 1;
                break;
            }else{
                dkJr.airRight = 1;
                gameMatrix[posI][posJ] = nothing;
                posI -= dkJr.velocity;
                posJ += dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = dkjrJumpRight;
                break;
            }
    }
}

void moveDKJrVertical(int direction){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    int currentSprite = 0;
    switch (direction){
        case 4: //Salta izq de liana
            if (posI > 0 && posJ > 0 && gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == vine){
                gameMatrix[posI][posJ] = vine;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = dkjrVine1;
                break;
            }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit3Vine)){
                gameMatrix[posI][posJ] = vine;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = dkjrVine1;
                break;
            }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit3Blanck)){
                gameMatrix[posI][posJ] = vine;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = dkjrJumpLeft;
                dkJr.airLeft = 1;
                break;
            }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == tile || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == tree)){
                gameMatrix[posI][posJ] = vine;
                posJ -= dkJr.velocity;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = dkjrJumpLeft;
                dkJr.falling = 1;
                break;
            }else{
                dkJr.airLeft = 1;
                gameMatrix[posI][posJ] = vine;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = dkjrJumpLeft;
                break;
            }
        case 5: //Salta der de liana
            if (posI > 0 && posJ < columns - 1 && gameMatrix[posI - dkJr.velocity][posJ + dkjrJumpRight] == vine){
                gameMatrix[posI][posJ] = vine;
                posI -= dkJr.velocity;
                posJ += dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = dkjrVine1;
                break;
            }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == fruit3Vine)){
                gameMatrix[posI][posJ] = vine;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = dkjrVine1;
                break;
            }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == fruit3Blanck)){
                gameMatrix[posI][posJ] = vine;
                posI -= dkJr.velocity;
                posJ -= dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                struct Fruit* delFruit = findFruitByPos(posI, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                gameMatrix[posI][posJ] = dkjrJumpRight;
                dkJr.airRight = 1;
                break;
            }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == tile || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == tree)){
                gameMatrix[posI][posJ] = vine;
                posJ += dkJr.velocity;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = dkjrJumpRight;
                dkJr.falling = 1;
                break;
            }else{
                dkJr.airRight = 1;
                gameMatrix[posI][posJ] = vine;
                posI -= dkJr.velocity;
                posJ += dkJr.velocity;
                dkJr.posI = posI;
                dkJr.posJ = posJ;
                gameMatrix[posI][posJ] = dkjrJumpRight;
                break;
            }
        case 6: //Sube
            if (posI > 0 && gameMatrix[posI - dkJr.velocity][posJ] == vine){
                currentSprite = gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = vine;
                posI -= dkJr.velocity;
                dkJr.posI = posI;
                switch (currentSprite){
                    case 431:
                        gameMatrix[posI][posJ] = dkjrVine2;
                        break;
                    case 432:
                        gameMatrix[posI][posJ] = dkjrVine1;
                        break;
                }
                break;
            }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == 21 || gameMatrix[posI - dkJr.velocity][posJ] == 22)){
                dkJr.lives--;
                dkJr.dead = 1;
                struct Kremlin* kremlin = findKremlinByPos(posI - dkJr.velocity, posJ);
                kremlin->onScreen = 0;
                gameMatrix[posI - dkJr.velocity][posJ] = vine;
                break;
            }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ] == fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ] == fruit3Vine)){
                struct Fruit* delFruit = findFruitByPos(posI - dkJr.velocity, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                currentSprite = gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = vine;
                posI -= dkJr.velocity;
                dkJr.posI = posI;
                switch (currentSprite){
                    case 431:
                        gameMatrix[posI][posJ] = dkjrVine2;
                        break;
                    case 432:
                        gameMatrix[posI][posJ] = dkjrVine1;
                        break;
                }
                break;
            }else{
                break;
            }
        case 7: //Baja
            if (posI < rows - 1 && gameMatrix[posI + 1][posJ] == vine){
                currentSprite = gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = vine;
                posI += dkJr.velocity;
                dkJr.posI = posI;
                switch (currentSprite){
                    case 431:
                        gameMatrix[posI][posJ] = dkjrVine2;
                        break;
                    case 432:
                        gameMatrix[posI][posJ] = dkjrVine1;
                        break;
                }
                break;
            }else if (posI < rows - 1 && (gameMatrix[posI + dkJr.velocity][posJ] == 21 || gameMatrix[posI + dkJr.velocity][posJ] == 22)){
                dkJr.lives--;
                dkJr.dead = 1;
                struct Kremlin* kremlin = findKremlinByPos(posI + dkJr.velocity, posJ);
                kremlin->onScreen = 0;
                gameMatrix[posI + dkJr.velocity][posJ] = vine;
                break;
            }else if (posI < rows - 1 && (gameMatrix[posI + dkJr.velocity][posJ] == fruit1Vine || gameMatrix[posI + dkJr.velocity][posJ] == fruit2Vine || gameMatrix[posI + dkJr.velocity][posJ] == fruit3Vine)){
                struct Fruit* delFruit = findFruitByPos(posI + dkJr.velocity, posJ);
                dkJr.currentPoints += delFruit->pointsValue;
                delFruit->onScreen = 0;
                currentSprite = gameMatrix[posI][posJ];
                gameMatrix[posI][posJ] = vine;
                posI += dkJr.velocity;
                dkJr.posI = posI;
                switch (currentSprite){
                    case 431:
                        gameMatrix[posI][posJ] = dkjrVine2;
                        break;
                    case 432:
                        gameMatrix[posI][posJ] = dkjrVine1;
                        break;
                }
                break;
            }else{
                gameMatrix[posI][posJ] = vine;
                posI += dkJr.velocity;
                dkJr.posI = posI;
                gameMatrix[posI][posJ] = dkjrJumpRight;
                dkJr.falling = 1;
                break;
            }
    }
}

void moveDKJrUpAir(){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    if (posI > 0 && gameMatrix[posI - dkJr.velocity][posJ] == vine){
        gameMatrix[posI][posJ] = nothing;
        posI -= dkJr.velocity;
        dkJr.posI = posI;
        gameMatrix[posI][posJ] = dkjrVine1;
        dkJr.inVine = 1;
    }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ] == fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ] == fruit3Vine)){
        gameMatrix[posI][posJ] = nothing;
        posI -= dkJr.velocity;
        dkJr.posI = posI;
        struct Fruit* delFruit = findFruitByPos(posI, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        gameMatrix[posI][posJ] = dkjrVine1;
        dkJr.inVine = 1;
    }else if (posI > 0 && (gameMatrix[posI - dkJr.velocity][posJ] == fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ] == fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ] == fruit3Blanck)){
        gameMatrix[posI][posJ] = nothing;
        posI -= dkJr.velocity;
        dkJr.posI = posI;
        struct Fruit* delFruit = findFruitByPos(posI, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        gameMatrix[posI][posJ] = dkjrJumpRight;
        dkJr.falling = 1;
    }else{
        dkJr.falling = 1;
        gameMatrix[posI][posJ] = nothing;
        posI -= dkJr.velocity;
        dkJr.posI = posI;
        gameMatrix[posI][posJ] = dkjrJumpRight;
    }
}

void moveDKJrLeftAir(){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    if (posI > 0 && posJ > 0 && gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == vine){
        gameMatrix[posI][posJ] = nothing;
        posI -= dkJr.velocity;
        posJ -= dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = dkjrVine1;
        dkJr.inVine = 1;
    }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit3Vine)){
        gameMatrix[posI][posJ] = nothing;
        posI -= dkJr.velocity;
        posJ -= dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        struct Fruit* delFruit = findFruitByPos(posI, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        gameMatrix[posI][posJ] = dkjrVine1;
        dkJr.inVine = 1;
    }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == fruit3Blanck)){
        gameMatrix[posI][posJ] = nothing;
        posI -= dkJr.velocity;
        posJ -= dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        struct Fruit* delFruit = findFruitByPos(posI, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        gameMatrix[posI][posJ] = dkjrJumpLeft;
        dkJr.falling = 1;
    }else if (posI > 0 && posJ > 0 && (gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == tile || gameMatrix[posI - dkJr.velocity][posJ - dkJr.velocity] == tree)){
        gameMatrix[posI][posJ] = vine;
        posJ -= dkJr.velocity;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = dkjrJumpLeft;
        dkJr.falling = 1;
    }else{
        dkJr.falling = 1;
        gameMatrix[posI][posJ] = nothing;
        posI -= dkJr.velocity;
        posJ -= dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = dkjrJumpLeft;
    }
}

void moveDKJrRightAir(){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    if (posI > 0 && posJ < columns - 1 && gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == vine){
        gameMatrix[posI][posJ] = nothing;
        posI -= dkJr.velocity;
        posJ += dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = dkjrVine1;
        dkJr.inVine = 1;
    }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == fruit1Vine || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == fruit2Vine || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == fruit3Vine)){
        gameMatrix[posI][posJ] = nothing;
        posI -= dkJr.velocity;
        posJ += dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        struct Fruit* delFruit = findFruitByPos(posI, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        gameMatrix[posI][posJ] = dkjrVine1;
        dkJr.inVine = 1;
    }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == fruit1Blanck || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == fruit2Blanck || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == fruit3Blanck)){
        gameMatrix[posI][posJ] = nothing;
        posI -= dkJr.velocity;
        posJ += dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        struct Fruit* delFruit = findFruitByPos(posI, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        gameMatrix[posI][posJ] = dkjrJumpRight;
        dkJr.falling = 1;
    }else if (posI > 0 && posJ < columns - 1 && (gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == tile || gameMatrix[posI - dkJr.velocity][posJ + dkJr.velocity] == tree)) {
        gameMatrix[posI][posJ] = vine;
        posJ += dkJr.velocity;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = dkjrJumpRight;
        dkJr.falling = 1;
    }else{
        dkJr.falling = 1;
        gameMatrix[posI][posJ] = nothing;
        posI -= dkJr.velocity;
        posJ += dkJr.velocity;
        dkJr.posI = posI;
        dkJr.posJ = posJ;
        gameMatrix[posI][posJ] = dkjrJumpRight;
    }
}

void makeDKJrFall(){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    int currentSprite = 0;
    if (posI < rows - 1 && (gameMatrix[posI + dkJr.velocity][posJ] == tile || gameMatrix[posI + dkJr.velocity][posJ] == tree)){
        if (dkJr.falling > 2){
            dkJr.lives--;
            dkJr.dead = 1;
            dkJr.falling = 0;
            dkJr.inVine = 0;
        }else{
            dkJr.falling = 0;
            dkJr.inVine = 0;
            gameMatrix[posI][posJ] = dkjrRight1;
        }
    }else if (posI < rows - 1 && (gameMatrix[posI + dkJr.velocity][posJ] == fruit1Blanck || gameMatrix[posI + dkJr.velocity][posJ] == fruit2Blanck || gameMatrix[posI + dkJr.velocity][posJ] == fruit3Blanck)){
        struct Fruit* delFruit = findFruitByPos(posI + dkJr.velocity, posJ);
        dkJr.currentPoints += delFruit->pointsValue;
        delFruit->onScreen = 0;
        currentSprite = gameMatrix[posI][posJ];
        gameMatrix[posI][posJ] = nothing;
        posI += dkJr.velocity;
        dkJr.posI = posI;
        gameMatrix[posI][posJ] = currentSprite;
        dkJr.falling++;
    }else if (posI < rows - 1 && gameMatrix[posI + dkJr.velocity][posJ] == nothing){
        currentSprite = gameMatrix[posI][posJ];
        gameMatrix[posI][posJ] = nothing;
        posI += dkJr.velocity;
        dkJr.posI = posI;
        gameMatrix[posI][posJ] = currentSprite;
        dkJr.falling++;
    }else{
        dkJr.lives--;
        dkJr.dead = 1;
    }
}

void resetDKJrPosition(){
    int posI = dkJr.posI;
    int posJ = dkJr.posJ;
    if (dkJr.inVine == 1){
        gameMatrix[posI][posJ] = vine;
        posI = 22;
        posJ = 0;
        gameMatrix[posI][posJ] = dkjrRight1;
        dkJr.inVine = 0;
    }else{
        gameMatrix[posI][posJ] = nothing;
        posI = 22;
        posJ = 0;
        gameMatrix[posI][posJ] = dkjrRight1;
    }
}

void printMatrix(){
    printf("\n");
    for(int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            printf("%d ", gameMatrix[i][j]);
        }
        printf("\n");
    }
}