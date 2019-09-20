//
// Created by josed on 19/9/2019.
//

#ifndef DONCEYKONGJR_BITMAPNODE_H
#define DONCEYKONGJR_BITMAPNODE_H

#include <allegro5/bitmap.h>

static struct BitMapNode* vineBitMapHead = NULL;
static struct BitMapNode* blueKremlinBitMapHead = NULL;
static struct BitMapNode* redKremlinBitMapHead = NULL;
static struct BitMapNode* fruitBitMapHead = NULL;
static struct BitMapNode* floorBitMapHead = NULL;

struct BitMapNode{
    ALLEGRO_BITMAP* bitmap;
    struct BitMapNode* next;
};

void insertVine(ALLEGRO_BITMAP* bitmap);
void insertBlueKremlin(ALLEGRO_BITMAP* bitmap);
void insertRedKremlin(ALLEGRO_BITMAP* bitmap);
void insertFruitBitmap(ALLEGRO_BITMAP* bitmap);
void insertFloor(ALLEGRO_BITMAP* bitmap);

struct BitMapNode* searchVine(int position);
struct BitMapNode* searchBlueKremlin(int position);
struct BitMapNode* searchRedKremlin(int position);
struct BitMapNode* searchFruit(int position);
struct BitMapNode* searchFloor(int position);

#endif //DONCEYKONGJR_BITMAPNODE_H
