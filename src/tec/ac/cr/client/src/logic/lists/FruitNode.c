//
// Created by Kevin Cordero Zúñiga on 9/18/2019.
//

#include "FruitNode.h"
#include <stdlib.h>

/**
 * Metodo para insertar una fruta en la lista
 * @param fruit
 */
void insertFruit(struct Fruit* fruit){
    struct FruitNode* tmp = (struct FruitNode*) malloc(sizeof(struct FruitNode));
    tmp->fruit = fruit;
    tmp->next = fruitHead;
    fruitHead = tmp;
}

/**
 * Metodo para eliminar una fruta por id
 * @param id
 */
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

/**
 * Metodo para eliminar una fruta por posicion
 * @param i
 * @param j
 */
void deleteFruitByPos(int i, int j){
    struct FruitNode* current = fruitHead;
    struct FruitNode* previous = NULL;
    if (fruitHead == NULL) {
        return;
    }
    while(current->fruit->posI != i && current->fruit->posJ != j){
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

/**
 * Metodo para buscar una fruta por posicion
 * @param i
 * @param j
 * @return la fruta encontrada
 */
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

/**
 * Metodo para obtener la cabeza de la lista de frutas
 * @return lista de frutas
 */
struct FruitNode* returnFruitHead(){
    return fruitHead;
}

