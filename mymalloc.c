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
    freeList->size = 5000 - sizeof(metaData);
    freeList->isFree = 1;
    freeList->next = NULL;
}

void split(metaData *allocatedSlot, int size){
    metaData *temp = (char*)((char*)allocatedSlot->size + size + sizeof(metaData));
    temp->size = allocatedSlot->size - size - sizeof(metaData);
    temp->isFree = 1;
    temp->next = allocatedSlot->next;
    allocatedSlot->size = size;
    allocatedSlot->isFree = 0;
    allocatedSlot->next = temp;
}

