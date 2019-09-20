//
// Created by josed on 19/9/2019.
//

#include "bitmapNode.h"

void insertVine(ALLEGRO_BITMAP* bitmap){
    struct BitMapNode* tmp = (struct BitMapNode*) malloc(sizeof(struct BitMapNode));
    tmp->bitmap = bitmap;
    tmp->next = vineBitMapHead;
    vineBitMapHead = tmp;
}

struct BitMapNode* searchVine(int position){
    struct BitMapNode* tmp = vineBitMapHead;
    int i = 0;
    while (i != position){
        tmp = tmp->next;
        i++;
    }
    return tmp;
}

void insertBlueKremlin(ALLEGRO_BITMAP* bitmap){
    struct BitMapNode* tmp = (struct BitMapNode*) malloc(sizeof(struct BitMapNode));
    tmp->bitmap = bitmap;
    tmp->next = blueKremlinBitMapHead;
    blueKremlinBitMapHead = tmp;
}

struct BitMapNode* searchBlueKremlin (int position){
    struct BitMapNode* tmp = blueKremlinBitMapHead;
    int i = 0;
    while (i != position){
        tmp = tmp->next;
        i++;
    }
    return tmp;
}

void insertRedKremlin(ALLEGRO_BITMAP* bitmap){
    struct BitMapNode* tmp = (struct BitMapNode*) malloc(sizeof(struct BitMapNode));
    tmp->bitmap = bitmap;
    tmp->next = redKremlinBitMapHead;
    redKremlinBitMapHead = tmp;
}

struct BitMapNode* searchRedKremlin (int position){
    struct BitMapNode* tmp = redKremlinBitMapHead;
    int i = 0;
    while (i != position){
        tmp = tmp->next;
        i++;
    }
    return tmp;
}

void insertFruitBitmap (ALLEGRO_BITMAP* bitmap){
    struct BitMapNode* tmp = (struct BitMapNode*) malloc(sizeof(struct BitMapNode));
    tmp->bitmap = bitmap;
    tmp->next = fruitBitMapHead;
    fruitBitMapHead = tmp;
}

struct BitMapNode* searchFruit (int position){
    struct BitMapNode* tmp = fruitBitMapHead;
    int i = 0;
    while (i != position){
        tmp = tmp->next;
        i++;
    }
    return tmp;
}

void insertFloor (ALLEGRO_BITMAP* bitmap){
    struct BitMapNode* tmp = (struct BitMapNode*) malloc(sizeof(struct BitMapNode));
    tmp->bitmap = bitmap;
    tmp->next = floorBitMapHead;
    floorBitMapHead = tmp;
}

struct BitMapNode* searchFloor (int position){
    struct BitMapNode* tmp = floorBitMapHead;
    int i = 0;
    while (i != position){
        tmp = tmp->next;
        i++;
    }
    return tmp;
}