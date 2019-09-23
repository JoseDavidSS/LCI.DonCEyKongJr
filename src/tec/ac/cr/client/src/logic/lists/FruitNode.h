//
// Created by Kevin Cordero Zúñiga on 9/18/2019.
//

#ifndef DONCEYKONGJR_FRUITNODE_H
#define DONCEYKONGJR_FRUITNODE_H

#include <windef.h>
#include "../entity/Fruit.h"

static struct FruitNode* fruitHead = NULL;

struct FruitNode{
    struct Fruit* fruit;
    struct FruitNode* next;
};

void insertFruit(struct Fruit* fruit);
void deleteFruitByID(int id);
void deleteFruitByPos(int i, int j);
struct Fruit* findFruitByPos(int i, int j);
struct FruitNode* returnFruitHead();

#endif //DONCEYKONGJR_FRUITNODE_H
