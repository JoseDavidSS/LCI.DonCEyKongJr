//
// Created by Kevin Cordero Zúñiga on 9/18/2019.
//

#include "KremlinNode.h"
#include <stdlib.h>

void insertKremlin(struct Kremlin* kremlin){
    struct KremlinNode* tmp = (struct KremlinNode*) malloc(sizeof(struct KremlinNode));
    tmp->kremlin = kremlin;
    tmp->next = kremlinHead;
    kremlinHead = tmp;
}

void deleteKremlinByID(int id){
    struct KremlinNode* current = kremlinHead;
    struct KremlinNode* previous = NULL;
    if (kremlinHead == NULL) {
        return;
    }
    while(current->kremlin->id != id) {
        if(current->next == NULL) {
            return;
        } else {
            previous = current;
            current = current->next;
        }
    }
    if(current == kremlinHead) {
        kremlinHead = kremlinHead->next;
    } else {
        previous->next = current->next;
    }
}

struct Kremlin* findKremlinByPos(int i, int j){
    struct KremlinNode* tmp = kremlinHead;
    if (kremlinHead == NULL) {
        return NULL;
    }
    while(tmp->kremlin->posI != i && tmp->kremlin->posJ != j) {
        if(tmp->next == NULL) {
            return NULL;
        } else {
            tmp = tmp->next;
        }
    }
    return tmp->kremlin;
}

struct KremlinNode* returnKremlinHead(){
    return kremlinHead;
}
