//
// Created by Kevin Cordero Zúñiga on 9/18/2019.
//

#include "../logic/entity/Kremlin.h"
#include "entity/DKJr.h"

#ifndef DONCEYKONGJR_GAME_H
#define DONCEYKONGJR_GAME_H

static int nothing = 0;

static int tree = 11;
static int tile = 12;
static int vine = 13;

static int redKremlinUp1 = 2111;
static int redKremlinUp2 = 2112;
static int redKremlinDown1 = 2121;
static int redKremlinDown2 = 2122;
static int redKremlinLeft1 = 2131;
static int redKremlinLeft2 = 2132;
static int redKremlinRight1 = 2141;
static int redKremlinRight2 = 2142;

static int blueKremlinUp1 = 2211;
static int blueKremlinUp2 = 2212;
static int blueKremlinDown1 = 2221;
static int blueKremlinDown2 = 2222;
static int blueKremlinLeft1 = 2231;
static int blueKremlinLeft2 = 2232;
static int blueKremlinRight1 = 2241;
static int blueKremlinRight2 = 2242;

static int fruit1Blanck = 311;
static int fruit1Vine = 312;
static int fruit2Blanck = 321;
static int fruit2Vine = 322;
static int fruit3Blanck = 331;
static int fruit3Vine = 332;

static int dkjrRight1 = 411;
static int dkjrRight2 = 412;
static int dkjrRight3 = 413;
static int dkjrLeft1 = 421;
static int dkjrLeft2 = 422;
static int dkjrLeft3 = 423;
static int dkjrVine1 = 431;
static int dkjrVine2 = 432;
static int dkjrJumpRight = 441;
static int dkjrJumpLeft = 442;

static int mario = 5;

static int dk = 6;

static int key = 7;

static int rows = 24;
static int columns = 16;
static struct DKJr dkJr = {1, 22, 0, 3, 0, 0, 0, 0, 0, 0, 0};

void initializeGameMatrix(int* gameMatrix[24][16]);
int updateGameMatrix(int direction, int* gameMatrix[24][16]);
void updateFruits(int* gameMatrix[24][16]);
void updateKremlins(int* gameMatrix[24][16]);
void searchVineForKremlin(struct Kremlin* kremlin, int* gameMatrix[24][16]);
void moveKremlinInVine(struct Kremlin* kremlin, int* gameMatrix[24][16]);
void makeKremlinFall(struct Kremlin* kremlin, int* gameMatrix[24][16]);
void moveDKJrHorizontal(int direction, int* gameMatrix[24][16]);
void moveDKJrVertical(int direction, int* gameMatrix[24][16]);
void moveDKJrUpAir(int* gameMatrix[24][16]);
void moveDKJrLeftAir(int* gameMatrix[24][16]);
void moveDKJrRightAir(int* gameMatrix[24][16]);
void makeDKJrFall(int* gameMatrix[24][16]);
void resetDKJrPosition(int* gameMatrix[24][16]);
void printMatrix(int* gameMatrix[24][16]);
struct DKJr* returnDKJr();

#endif //DONCEYKONGJR_GAME_H
