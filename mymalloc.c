#include<stdio.h>
#include<stddef.h>
#include "mymalloc.h"

void initialize(){
    blockPtr->size = ARRAY_SIZE - sizeof(metaData);
    blockPtr->isFree = 1;
    blockPtr->next = NULL;
    blockPtr->isFirstBlock=1;
    printf("Memory Initialized\n");
}

//if first block found is greater than required size, then split
void allocate(metaData *current, int size){
//    printf("ALLOC Called %p   %i\n",current,size);
    
    
    metaData *newBlock = (void*)((void *)current + size + sizeof(metaData));//new block is pointing to the space after the metadata and required space of large block
    newBlock->size = current->size - size - sizeof(metaData);//new block size is equal to how much space is left in large block after required space and metadata are inserted in
    current->size = size; //large block now becomes just a small block with size equal to its required size
    newBlock->isFree = 1; //slot is still free
    current->isFree = 0; //large slot is no longer free becuase it has been previously malloced
    newBlock->next = current->next;
    current->next = newBlock; //newblock is now "after" large block in the mem LL so it should inherit large block's next node
    
    newBlock->isFirstBlock=0;
    
    traverse(" Malloc ");
}

void* my_malloc(int size){
        if(!memoryInitializedFlag){
            initialize();//executes when the isFree value in the structure is NULL. This only happens once.
            memoryInitializedFlag=1;
        }
    
    if(size == 0) return NULL;
    
        metaData *current = blockPtr;
    
        while(current != NULL)
        {
            if(current->isFree){
                if(current->size == size){
                    // we do not need to create the meta data block
                    // simply mark the block as NOT free
                    current->isFree = 0;
                    return current;
                } else if (current->size > (size + sizeof(metaData))){
                    // New metadata block needs to be created ... so call allocate
                    allocate(current,size);
                    return current;
                } else {
                    // This block is smaller than what we need so lets check next
                    current = current->next;
                }
            } else {
                current = current->next;
            }
        }
    return current;
}

//void* my_malloc(int size)
//{
//    if(!memoryInitializedFlag){
//        initialize();//executes when the isFree value in the structure is NULL. This only happens once.
//        memoryInitializedFlag=1;
//    }
//    metaData *current = blockPtr;
//    while(current != NULL)
//    {
//
//        if((current->size == size) && current->isFree)
//        {
//           // printf("WHYYYYY\n");
//
//            //current++; //move the current pointer past all the metaData and have it point to beginning of the allocated space
////
////            if(current->isFirstBlock && current->next==NULL && current->isFree){
////                metaData *newBlock = (void*)((void *)current  + sizeof(metaData));
////                newBlock->size=current->size - sizeof(metaData);
////                newBlock->isFree=1;
////                newBlock->isFirstBlock=0;
////                newBlock->next=NULL;
////                current->size=0;
////                current->isFree=0;
////                current->next=newBlock;
////
////                current=newBlock;
////            }
//
////            current->isFree = 0;
////            printf("Space has been allocated %p\n", current);
//
//            allocate(current, size);
//
//            //printf("Validity=%i",isPointerValid(current));
//
//            return (void *)current;
//        }
////        else if (current->size >(size + sizeof(metaData)))
////        {
////            allocate(current, size);
////            printf("%s", "Space has been allocated\n");
////            current++; //move the current pointer past all the metaData and have it point to beginning of the allocated space
////            return (void *)current;
////        }
//        current = current->next;
//    }
//    puts("Not enough memory. Malloc error");
//    return NULL;
//}

void merge(){
    metaData *current = blockPtr->next;
    metaData *prev = blockPtr;
    while(current != NULL)
    {
        if((current->isFree) && (prev->isFree)){
            prev->size = prev->size + current->size + sizeof(metaData);
            prev->isFree = 1;
            current=current->next;
            prev->next = current;
            printf("%s", "MERGED\n");
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }

}

int isPointerValid(void* p){
    if( (char*)p >= myblock && (char*)p < myblock+ARRAY_SIZE)
        return 1;
    else
        return 0;
}

void my_free(void* p){
    //if pointer is not located within array
//    if(((void *)myblock > p) || ((void*)(myblock + ARRAY_SIZE) < p))
    if(!isPointerValid(p))
    {
        printf("my_free   invalid pointer %p",p);
        return;
    }
    else
    {
        metaData* current = p;
//        current--;
        if(current-> isFree){
            printf("my_free-2  point points to free memory %p \n", current);
            return;
        }
        current->isFree = 1;
        merge();
        
        traverse(" Free ");
        
        return;
    }

}

void printblocks(char* location)
{
    metaData * p = blockPtr;
    int counter = 1;
    while(p!=NULL)
    {
        printf("Block %d: location: %s size: %d  Free:%d\n", counter, location, p->size, p->isFree);
        counter++;
        p = p->next;
    }
}

void freeall()
{
    blockPtr->isFree= 1;
    blockPtr->size = ARRAY_SIZE-sizeof(metaData);
    blockPtr->next = NULL;
//    metaData * p = blockPtr;
//    while (p != NULL)
//    {
//        if(!(p->isFree))
//        {
//            my_free(++p);
//            p--;
//        }
//
//        p = p->next;
//    }
}

metaData* getBlockPointer(){
    return blockPtr;
}

void traverse(char* location){
    
    metaData* x = blockPtr;
    printf("===============BLK PTR=%p============\n", blockPtr);
    
    printf("TRAVERSAL %s \n[blk=0, size=%d, free=%d next=%p  me=%p]\n",location, x->size,x->isFree,x->next,x);
    int ctr = 0;
    while(x->next != NULL){
        x = x->next;
        ctr++;
        printf("[blk=%d, size=%d, free=%d next=%p  me=%p]\n",ctr,x->size,x->isFree,x->next,x);
    }
    printf("===================================\n");
}

