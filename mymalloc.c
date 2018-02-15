#include<stdio.h>
#include<stddef.h>
#include "mymalloc.h"
//
void initialize(){
    blockPtr->size = 5000 - sizeof(metaData);
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
void* my_malloc(int size)
{
    if(!blockPtr->isFree)initialize();//executes when the isFree value in the structure is NULL. This only happens once.
    metaData *current = blockPtr;
    metaData*previous;
    while(((current->size < size) || !(current->isFree)) && (current->next != NULL))
    {
        previous = current;
        current = current ->next;
    }
    if(current->size == size)
    {
        current->isFree = 0;
        printf("%s", "Space has been allocated\n");
        current++; //move the current pointer past all the metaData and have it point to beginning of the allocated space
        return (void *)current;
    }
    else if (current->size >(size + sizeof(metaData)))
    {
        allocate(current, size);
        printf("%s", "Space has been allocated\n");
        current++; //move the current pointer past all the metaData and have it point to beginning of the allocated space
        return (void *)current;
    }
    else
    {
        puts("Not enough space. Malloc error");
        return NULL;
    }
}
//

void merge(){
    metaData *current = blockPtr->next;
    metaData *prev = blockPtr;
    do{
        if((current->isFree) && (prev->isFree)){
            prev->size = prev->size + current->size + sizeof(metaData);
            prev->isFree = 1;
            current=current->next;
            printf("%s", "MERGED\n");
            break;
        }
        else
        {
            prev = current;
            current = current->next;
        }
        
    }while(current != NULL);
    
    
}
void my_free(void* p){
    if(((void *)myblock > p) || ((void*)(myblock + 5000) < p))
    {
        puts("invalid pointer");
        return;
    }
    else
    {
        metaData * current = p;
        current--;
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
        printf("Block %d: size: %d", counter, p->size);
        counter++;
        p = p->next;
    }
}

