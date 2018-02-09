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
    blockPtr->size = 5000 - sizeof(metaData);
    blockPtr->isFree = 0;
    blockPtr->next = NULL;
}

//if first block found is greater than required size, then split
char* allocate(metaData *allocatedBlock, int requiredSize){
    metaData *requiredBlock = (char*)(char*) requiredSize + sizeof(metaData) ;
    requiredBlock->size = requiredSize;
    allocatedBlock->size = allocatedBlock->size - requiredSize - sizeof(metaData);
    requiredBlock->isFree = 0; //slot is still free
    allocatedBlock->isFree = 1; //allocated slot is no longer free
    requiredBlock->next = allocatedBlock;
    allocatedBlock->next = NULL;
    return requiredBlock;
}

void* my_malloc(int size){
    metaData *current = myblock;
    metaData*previous;
    while(((current->size < size) || (current->isFree == 0)) && (current->next != NULL)){
        previous = current;
        current = current ->next;
    }
    if(current->size == size){
        return previous;
    }else{
      return allocate(current, size);
    }
    printf("%s", "Space has been allocated");
}

void merge(){
    metaData *current,*previous = myblock;
    while(current->next != NULL){
        while((current->isFree == 1) && (previous->isFree ==1)){
            previous = current;
            current = current->next;
        }
        previous->size = previous->size + current->size + sizeof(metaData);
        previous->isFree = 0;
        current = current->next;
        previous->next = current;
    }
    printf("%s", "MERGED");
   
}
void my_free(){
    
}
