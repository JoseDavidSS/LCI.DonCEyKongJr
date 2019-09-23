//
// Created by Kevin Cordero Zúñiga on 9/18/2019.
//

#ifndef DONCEYKONGJR_KREMLINNODE_H
#define DONCEYKONGJR_KREMLINNODE_H

#include "../entity/Kremlin.h"
#include <windef.h>


static struct KremlinNode* kremlinHead = NULL;

struct KremlinNode{
    struct Kremlin* kremlin;
    struct KremlinNode* next;
};

void insertKremlin(struct Kremlin* kremlin);
void deleteKremlinByID(int id);
void deleteKremlinByPos(int i, int j);
struct Kremlin* findKremlinByPos(int i, int j);
struct KremlinNode* returnKremlinHead();

#endif //DONCEYKONGJR_KREMLINNODE_H
