#include<stdio.h>
#include<stddef.h>
#include "mymalloc.h"
#define malloc( x ) my_malloc( x, __FILE__, __LINE__ )
#define free( x ) my_free( x, __FILE__, __LINE__ )
static char myblock[5012];  //array size simulated
metaData *blockPtr = (void*) myblock;  //sets pointer to first index in arrays
void merge();
void initialize();
int initFlag = 1;
void allocate(metaData *allocatedBlock, int requiredSize);
void initialize(){
    blockPtr->size = 5012 - sizeof(metaData);
    blockPtr->isFree = 1;
    blockPtr->next = NULL;
}
//
////if first block found is greater than required size, then split
void allocate(metaData *largeBlock, int requiredSize){
    metaData *newBlock = (void*)((void *)largeBlock + requiredSize + sizeof(metaData));//new block is pointing to the space after the metadata and required space of large block
    newBlock->size = largeBlock->size - requiredSize - sizeof(metaData);//new block size is equal to how much space is left in large block after required space and metadata are inserted in
    largeBlock->size = requiredSize; //large block now becomes just a small block with size equal to its required size
    newBlock->isFree = 1; //slot is still free
    largeBlock->isFree = 0; //large slot is no longer free becuase it has been previously malloced
    newBlock->next = largeBlock->next; //newblock is now "after" large block in the mem LL so it should inherit large block's next node
    largeBlock->next = newBlock; //large block is now "before" new block so its next node is new block
}
//
void* my_malloc(int size, char * File, int Line)
{
    if(initFlag){
    initialize();//executes when the isFree value in the structure is NULL. This only happens once.
    initFlag = 0;
    }
    metaData *current = blockPtr;
    while(current != NULL)
    {
    if((current->size == size) && current->isFree)
    {
        current->isFree = 0;
        current++; //move the current pointer past all the metaData and have it point to beginning of the allocated space
        return (void *)current;
    }
    else if (current->size >(size + sizeof(metaData)) && current ->isFree)
    {
        allocate(current, size);
        current++; //move the current pointer past all the metaData and have it point to beginning of the allocated space
        return (void *)current;
    }
    current = current->next;
    }
    fprintf(stderr,"Error in file: %s Line: %d. Not Enough Space\n", File, Line);
    return NULL;
}
//

void merge(){
    metaData *current = blockPtr->next;
    metaData *prev = blockPtr;
    while(current != NULL)
    {
        if((current->isFree) && (prev->isFree)){ //if adjacent free blocks are found they should be merged
            prev->size = prev->size + current->size + sizeof(metaData); //previous block size is increase to include the block next to it
            prev->isFree = 1;   //prev is freed
            current=current->next;  //current is moved forward
            prev->next = current;   //prev next must be updated
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }

}
void my_free(void* p, char * File, int Line){
    if(((void *)myblock > p) || ((void*)(myblock + 5012) < p)) //if pointer is not inbetween the memory addresses encompassing memory then its an invalid pointer
    {
        fprintf(stderr,"Error in file: %s on Line: %d. Cannot free pointer that was not allocated by malloc\n", File, Line);
        return;
    }
    else
    {
        metaData* current = p;
        current--;
        if(current-> isFree){ //if a pointer is already free it cannot be freed again
           fprintf(stderr,"Error in file: %s on Line: %d. Pointer is already freed\n", File, Line);
           return;
        }
        current->isFree = 1;
        merge();
        return;
    }

}
void printblocks()
{
    metaData * p = blockPtr;
    int counter = 1;
    while(p!=NULL)
    {
        printf("Block %d: size: %d  Free:%d\n", counter, p->size, p->isFree);
        counter++;
        p = p->next;
    }
}

void freeall()  //free all memory blocks
{
    metaData * p = blockPtr;
    while (p != NULL)
    {
        if(!(p->isFree))
        {
            free(++p);
            p--;
        }

        p = p->next;
    }
}

int findMostFree()
{
    metaData * p = blockPtr->next;
    int mostFree = blockPtr ->size;
    while (p != NULL)
    {
        if(p->size > mostFree)
        {
           mostFree = p->size;
        }
        p = p->next;
    }
    return mostFree;
}

metaData * getBlockPtr(){
    return blockPtr;
}
