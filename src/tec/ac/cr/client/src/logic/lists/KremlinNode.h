//
// Created by Kevin Cordero Zúñiga on 9/18/2019.
//

#ifndef DONCEYKONGJR_KREMLINNODE_H
#define DONCEYKONGJR_KREMLINNODE_H

#include <limits.h>
#include "../entity/Kremlin.h"

static struct KremlinNode* kremlinHead = NULL;

struct KremlinNode{
    struct Kremlin* kremlin;
    struct KremlinNode* next;
};

void insertKremlin(struct Kremlin* kremlin);
void deleteKremlinByID(int id);
struct Kremlin* findKremlinByPos(int i, int j);
struct KremlinNode* returnKremlinHead();

#endif //DONCEYKONGJR_KREMLINNODE_H
