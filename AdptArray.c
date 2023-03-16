#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct AdptArray_{
    int capacity;
    PElement* array;
    DEL_FUNC delete;
    COPY_FUNC copy;
    PRINT_FUNC print;
} AdptArray;
PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete,PRINT_FUNC print)
{
    PAdptArray ans = (PAdptArray)malloc(sizeof(AdptArray));
    if (ans == NULL){
        return NULL;
    }
    ans->array = (PElement*)malloc(sizeof(PElement));   
    if (ans->array == NULL ){
        free(ans);
        return NULL;
    }   
    ans->delete = delete;
    ans->copy = copy;
    ans->print = print;
    ans->capacity = 1;
    return ans;
}

Result SetAdptArrayAt (PAdptArray adptArray, int i, PElement element)
{
    if (i < 0){
        return FAIL;
    }
    if (i >= adptArray->capacity){
        PElement* temp = (PElement*)realloc(adptArray->array, sizeof(PElement)*(i+1));
        if (temp == NULL){
            DeleteAdptArray(adptArray);
            return FAIL;
        }
        adptArray->array = temp;
        adptArray->capacity = i+1;
        
    }
    
    adptArray->array[i] = adptArray->copy(element);
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray adptArray, int i )
{
    if (i >= adptArray->capacity || i < 0){

        return NULL;
    }
    if(adptArray->array[i] == NULL){
        return NULL;
    }
    return adptArray->copy(adptArray->array[i]);
}

int GetAdptArraySize(PAdptArray adptArray)
{
    if(adptArray == NULL){
        return -1;
    }
    return adptArray->capacity;
}

void DeleteAdptArray(PAdptArray adptArray)
{
    for (int i = 0; i < adptArray->capacity; i++){
        if (adptArray->array[i] != NULL){

            adptArray->delete(adptArray->array[i]);
        }
    }
    free(adptArray->array);

    free(adptArray);
}

void PrintDB(PAdptArray adptArray)
{
    for (int i = 0; i < adptArray->capacity; i++){
        if(adptArray->array[i] != NULL){
            adptArray->print(adptArray->array[i]);
        }
        
    }
}