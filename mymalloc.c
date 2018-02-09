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
void allocate(metaData *largeBlock, int requiredSize){
    metaData *newBlock = (void*)((void *)largeBlock + requiredSize + sizeof(metaData));//new block is pointing to the space after the metadata and required space of large block
    newBlock->size = largeBlock->size - requiredSize - sizeof(metaData);//new block size is equal to how much space is left in large block after required space and metadata are inserted in
    largeBlock->size = requiredSize; //large block now becomes just a small block with size equal to its required size
    newBlock->isFree = 0; //slot is still free
    largeBlock->isFree = 1; //large slot is no longer free becuase it has been previously malloced
    newBlock->next = largeBlock->next; //newblock is now "after" large block in the mem LL so it should inherit large block's next node
    largeBlock->next = newBlock; //large block is now "before" new block so its next node is new block
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
