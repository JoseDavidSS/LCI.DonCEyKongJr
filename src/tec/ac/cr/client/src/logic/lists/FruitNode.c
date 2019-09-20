//
// Created by Kevin Cordero Zúñiga on 9/18/2019.
//

#include "FruitNode.h"
#include <stdlib.h>

void insertFruit(struct Fruit* fruit){
    struct FruitNode* tmp = (struct FruitNode*) malloc(sizeof(struct FruitNode));
    tmp->fruit = fruit;
    tmp->next = fruitHead;
    fruitHead = tmp;
}

void deleteFruitByID(int id){
    struct FruitNode* current = fruitHead;
    struct FruitNode* previous = NULL;
    if (fruitHead == NULL) {
        return;
    }
    while(current->fruit->id != id) {
        if(current->next == NULL) {
            return;
        } else {
            previous = current;
            current = current->next;
        }
    }
    if(current == fruitHead) {
        fruitHead = fruitHead->next;
    } else {
        previous->next = current->next;
    }
}

struct Fruit* findFruitByPos(int i, int j){
    struct FruitNode* tmp = fruitHead;
    if (fruitHead == NULL) {
        return NULL;
    }
    while(tmp->fruit->posI != i && tmp->fruit->posJ != j) {
        if(tmp->next == NULL) {
            return NULL;
        } else {
            tmp = tmp->next;
        }
    }
    return tmp->fruit;
}

struct FruitNode* returnFruitHead(){
    return fruitHead;
}

