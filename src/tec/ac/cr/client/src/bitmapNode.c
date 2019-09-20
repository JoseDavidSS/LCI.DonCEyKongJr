//
// Created by josed on 19/9/2019.
//

#include "bitmapNode.h"

void insertVine(ALLEGRO_BITMAP* bitmap){
    struct BitMapNode* tmp = (struct BitMapNode*) malloc(sizeof(struct BitMapNode));
    tmp->bitmap = bitmap;
    tmp->next = vineHead;
    vineHead = tmp;
}

struct BitMapNode* searchVine(int position){
    struct BitMapNode* tmp = vineHead;
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
    tmp->next = blueKremlinHead;
    vineHead = tmp;
}

struct BitMapNode* searchBlueKremlin (int position){
    struct BitMapNode* tmp = blueKremlinHead;
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
    tmp->next = redKremlinHead;
    vineHead = tmp;
}

struct BitMapNode* searchRedKremlin (int position){
    struct BitMapNode* tmp = redKremlinHead;
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
    tmp->next = fruitHead;
    vineHead = tmp;
}

struct BitMapNode* searchFruit (int position){
    struct BitMapNode* tmp = fruitHead;
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
    tmp->next = floorHead;
    vineHead = tmp;
}

struct BitMapNode* searchFloor (int position){
    struct BitMapNode* tmp = floorHead;
    int i = 0;
    while (i != position){
        tmp = tmp->next;
        i++;
    }
    return tmp;
}