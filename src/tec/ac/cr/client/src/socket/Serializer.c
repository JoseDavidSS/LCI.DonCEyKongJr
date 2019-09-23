//
// Created by Kevin Cordero Zuniga on 9/22/2019.
//

#include "Serializer.h"

/**
 * Serializa matriz
 * @param matrix
 * @return
 */
char* serializeMatrix(int matrix[24][16]){
    char *json_File = "";
    cJSON *_row = cJSON_CreateArray();
    cJSON *json_Object = cJSON_CreateObject();
    if(json_Object == NULL)
        goto end;
    cJSON *_matrix = cJSON_CreateArray();
    if(_matrix == NULL)
        goto end;
    cJSON *_item;

    for(int i = 0; i < 24; i++) {
        _row = cJSON_CreateArray();
        for (int j = 0; j < 16; j++) {
            _item = cJSON_CreateNumber(matrix[i][j]);
            cJSON_AddItemToArray(_row, _item);
        }
        cJSON_AddItemToArray(_matrix,_row);
    }

    cJSON_AddItemToObject(json_Object,"objMatrix",_matrix);
    json_File = cJSON_Print(json_Object);
    if (json_File == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }

    end:
    cJSON_Delete(json_Object);
    return json_File;
}

/**
 * Verifica si es un kremlin
 * @param json
 * @return
 */
int isKremlin(const char* json){
    cJSON *kremlinJson = cJSON_Parse(json);
    int a = 0;
    if (kremlinJson == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }


    cJSON *id = cJSON_GetObjectItemCaseSensitive(kremlinJson,"id");
    if(cJSON_IsNumber(id)){
        a = 1;
    }

    end:
    cJSON_Delete(kremlinJson);
    return a;
}

/**
 * Verifica si es una fruta
 * @param json
 * @return
 */
int isFruit(const char* json){
    cJSON *fruitJson = cJSON_Parse(json);
    int a = 0;
    if (fruitJson == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }


    cJSON *id = cJSON_GetObjectItemCaseSensitive(fruitJson,"id");
    if(cJSON_IsNumber(id)){
        a = id->valueint;
    }

    end:
    return a;
}

/**
 * Deseariliza un kremlin
 * @param json
 * @return
 */
struct Kremlin* deserializeKremlin(const char *json){
    struct Kremlin* kremlin;
    cJSON* id;
    cJSON* posI;
    cJSON* posJ;
    cJSON* previousI;
    cJSON* previousJ;
    cJSON* onScreen;
    cJSON* velocity;
    cJSON* inVine;
    cJSON* type;
    cJSON* placed;
    cJSON* falling;

    cJSON *kremlinJson = cJSON_Parse(json);
    if (kremlinJson == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }


    id = cJSON_GetObjectItemCaseSensitive(kremlinJson,"id");
    if(cJSON_IsNumber(id)){
        kremlin->id = id->valueint;
    }

    posI = cJSON_GetObjectItemCaseSensitive(kremlinJson,"posI");
    if(cJSON_IsNumber(posI)){
        kremlin->posI = posI->valueint;
    }

    posJ = cJSON_GetObjectItemCaseSensitive(kremlinJson,"posJ");
    if(cJSON_IsNumber(posJ)){
        kremlin->posJ = posJ->valueint;
    }

    previousI = cJSON_GetObjectItemCaseSensitive(kremlinJson,"previousI");
    if(cJSON_IsNumber(posI)){
        kremlin->previousI = previousI->valueint;
    }

    previousJ = cJSON_GetObjectItemCaseSensitive(kremlinJson,"previousJ");
    if(cJSON_IsNumber(posJ)){
        kremlin->previousJ = previousJ->valueint;
    }

    onScreen = cJSON_GetObjectItemCaseSensitive(kremlinJson,"onScreen");
    if(cJSON_IsNumber(onScreen)){
        kremlin->onScreen = onScreen->valueint;
    }

    velocity = cJSON_GetObjectItemCaseSensitive(kremlinJson,"velocity");
    if(cJSON_IsNumber(velocity)){
        kremlin->velocity = velocity->valueint;
    }

    inVine = cJSON_GetObjectItemCaseSensitive(kremlinJson,"inVine");
    if(cJSON_IsNumber(inVine)){
        kremlin->inVine = inVine->valueint;
    }

    type = cJSON_GetObjectItemCaseSensitive(kremlinJson,"type");
    if(cJSON_IsNumber(type)){
        kremlin->type = type->valueint;
    }

    placed = cJSON_GetObjectItemCaseSensitive(kremlinJson,"placed");
    if(cJSON_IsNumber(placed)){
        kremlin->placed = placed->valueint;
    }

    falling = cJSON_GetObjectItemCaseSensitive(kremlinJson,"falling");
    if(cJSON_IsNumber(falling)){
        kremlin->falling = falling->valueint;
    }

    end:
    cJSON_Delete(kremlinJson);
    return kremlin;
}

/**
 * Deserializa una fruta
 * @param json
 * @return
 */
struct Fruit* deserializeFruit(const char *json){
    struct Fruit* fruit;
    // cJSON data tokens
    cJSON* id;
    cJSON* posI;
    cJSON* posJ;
    cJSON* onScreen;
    cJSON* pointsValue;
    cJSON* type;
    cJSON* placed;

    cJSON *fruitJson = cJSON_Parse(json);
    if (fruitJson == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }


    id = cJSON_GetObjectItemCaseSensitive(fruitJson,"id");
    if(cJSON_IsNumber(id)){
        fruit->id = id->valueint;
    }

    posI = cJSON_GetObjectItemCaseSensitive(fruitJson,"posI");
    if(cJSON_IsNumber(posI)){
        fruit->posI = posI->valueint;
    }

    posJ = cJSON_GetObjectItemCaseSensitive(fruitJson,"posJ");
    if(cJSON_IsNumber(posJ)){
        fruit->posJ = posJ->valueint;
    }

    onScreen = cJSON_GetObjectItemCaseSensitive(fruitJson,"onScreen");
    if(cJSON_IsNumber(onScreen)){
        fruit->onScreen = onScreen->valueint;
    }

    pointsValue = cJSON_GetObjectItemCaseSensitive(fruitJson,"pointsValue");
    if(cJSON_IsNumber(pointsValue)){
        fruit->pointsValue = pointsValue->valueint;
    }

    type = cJSON_GetObjectItemCaseSensitive(fruitJson,"type");
    if(cJSON_IsNumber(type)){
        fruit->type = type->valueint;
    }

    placed = cJSON_GetObjectItemCaseSensitive(fruitJson,"placed");
    if(cJSON_IsNumber(placed)){
        fruit->placed = placed->valueint;
    }

    end:
    cJSON_Delete(fruitJson);
    return fruit;
}