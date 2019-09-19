//
// Created by josed on 19/9/2019.
//

#ifndef DONCEYKONGJR_BITMAPNODE_H
#define DONCEYKONGJR_BITMAPNODE_H

#include <allegro5/bitmap.h>

static struct BitMapNode* vineHead = NULL;
static struct BitMapNode* blueKremlinHead = NULL;
static struct BitMapNode* redKremlinHead = NULL;
static struct BitMapNode* fruitHead = NULL;
static struct BitMapNode* floorHead = NULL;

struct BitMapNode{
    ALLEGRO_BITMAP* bitmap;
    struct BitMapNode* next;
};

void insertVine(ALLEGRO_BITMAP* bitmap);
void insertBlueKremlin(ALLEGRO_BITMAP* bitmap);
void insertRedKremlin(ALLEGRO_BITMAP* bitmap);
void insertFruit(ALLEGRO_BITMAP* bitmap);
void insertFloor(ALLEGRO_BITMAP* bitmap);

struct BitMapNode* searchVine(int position);
struct BitMapNode* searchBlueKremlin(int position);
struct BitMapNode* searchRedKremlin(int position);
struct BitMapNode* searchFruit(int position);
struct BitMapNode* searchFloor(int position);

#endif //DONCEYKONGJR_BITMAPNODE_H
