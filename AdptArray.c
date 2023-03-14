#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct AdptArray_{
    int size;
    int capacity;
    PElement* array;
    DEL_FUNC delete;
    COPY_FUNC copy;
    PRINT_FUNC print;
} AdptArray;
PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete,PRINT_FUNC print){
    PAdptArray ans = (PAdptArray)malloc(sizeof(AdptArray));
    if (ans == NULL){
        return NULL;
    }
    ans->array = (PElement*)malloc(sizeof(PElement));   
    if (ans->array == NULL){
        free(ans);
        return NULL;
    }   
    ans->delete = delete;
    ans->copy = copy;
    ans->print = print;
    ans->size = 0;
    ans->capacity = 1;
    return ans;
}
Result SetAdptArrayAt (PAdptArray adptArray, int i, PElement element){
    if (i < 0){
        return FAIL;
    }

    if (i >= adptArray->capacity){
        int new_capacity = i + 1;
        PElement* new_array = (PElement*)realloc(adptArray->array, new_capacity * sizeof(PElement));
        if (new_array == NULL){
            return FAIL;
        }
        adptArray->array = new_array;
        adptArray->capacity = new_capacity;
    }

    if (i >= adptArray->size){
        adptArray->size = i + 1;
    }

    if (adptArray->array[i] != NULL){
        adptArray->delete(adptArray->array[i]);
    }

    adptArray->array[i] = adptArray->copy(element);

    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray adptArray, int i ){
    if (i >= adptArray->size || i < 0 ){

        return NULL;
    }

    return adptArray->copy(adptArray->array[i]);
}

int GetAdptArraySize(PAdptArray adptArray){
    if(adptArray == NULL){
        return -1;
    }
    return adptArray->size;
}

void DeleteAdptArray(PAdptArray adptArray){
    for (int i = 0; i < adptArray->size; i++){
        if (adptArray->array[i] != NULL){
            adptArray->delete(adptArray->array[i]);
        }
    }
    free(adptArray->array);
    free(adptArray);
}

void PrintDB(PAdptArray adptArray){
    for (int i = 0; i < adptArray->size; i++){
        adptArray->print(adptArray->array[i]);
    }
}