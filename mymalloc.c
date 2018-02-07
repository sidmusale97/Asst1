//
//  mymalloc.c
//  Asst1
//
//  Created by Ridhima Sakhuja on 2/4/18.
//  Copyright © 2018 Ridhima Sakhuja. All rights reserved.
//

#include<stdio.h>
#include<stddef.h>
#include "mymalloc.h"

void initialize(){
    memoryArray->size = 5000 - sizeof(metaData);
    memoryArray->isFree = 1;
    memoryArray->next = NULL;
}


//if first block found is greater than required size, then split
char* split(metaData *allocatedBlock, int requiredSize){
    metaData *requiredBlock = (char*)(char*) requiredSize + sizeof(metaData) ;
    requiredBlock->size = requiredSize;
    allocatedBlock->size = allocatedBlock->size - requiredSize - sizeof(metaData);
    requiredBlock->isFree = 0; //slot is not longer free
    allocatedBlock->isFree = 1; //allocated slot is still free
    requiredBlock->next = allocatedBlock;
    allocatedBlock->next = NULL;
    return requiredBlock;
}
char* MyMalloc(int size){
    metaData *current, *previous;
    while(((current->size < size) || (current->isFree == 0)) && (current->next != NULL)){
        previous = current;
        current = current ->next;
    }
    if(current->size == size){
        return previous;
    }else{
        split(current, size);
    }
