#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.c"

void workloadA();
void workloadB();
void workloadC();
void workloadD();
void workloadE();

int main()
{
    workloadD();
    return 0;
}
    //Workload A: Malloc() 1 byte and immediately free it x150
    void workloadA(){
     int i;
     for (i = 0; i < 150;i++)
     {
     void * p = malloc(1);
     free(p);
     }
}

    //Workload B: Malloc(), store pointer in arrayx150 times
    void workloadB()
    {
     int i;
     char * ptrs[150];
     for(i = 0; i < 150;i++)
     {
     ptrs[i] = malloc(1);
     }
     freeall();
    }

    //Workload C: Randomly choose b/w 1 byte malloc and 1 byte free, continue until 150 mallocs
    void workloadC(){
     int mallocCounter = 0;  //counts total number of mallocs
     int canFree = 0;
     void*p = NULL;
     while(mallocCounter <= 150){
        if(!canFree){ //if no byte has been allocated, then first malloc
            p = malloc(1);
            mallocCounter++;
            canFree++;
            if (mallocCounter >= 150)break;
            continue;
        }
        int r = rand()%2;
        if(r==1){           //if r = 1 malloc 1 byte
            p = malloc(1);
            mallocCounter++;
            canFree++;
            if (mallocCounter >= 150)break;
        }
        else
            {
                metaData * a = blockPtr;
                while (a != NULL)
                    {
                    if(!(a->isFree))
                    {
                        free(++a);
                        canFree--;
                        break;
                    }
                    a = a->next;
                    }
            }
            printblocks();
     }
     freeall();
    }
    //Workload D: Randomly-sized malloc() or free() pointers
    void workloadD(){
    int mallocSize = 0; //size of malloc bytes
    int operation = 0;  //determines free or malloc
    int mallocCounter = 0;     //keeps track of total number of malloc
    int canFree = 0;
    int remainingSize = blockPtr->size;
    void * ptr = NULL;
    while(mallocCounter < 150){
        mallocSize = (rand()%64) + 1;
        if (!canFree)
        {
            ptr = malloc(mallocSize);
            mallocCounter++;
            canFree++;
            remainingSize -= mallocSize + sizeof(metaData);
            if(mallocCounter >= 150)break;
            printblocks();
            continue;
        }
        operation = rand()%2;
        if(operation == 1 && (remainingSize - (mallocSize + sizeof(metaData))) > 0){
            ptr = malloc(mallocSize);
            mallocCounter++;
            canFree++;
            remainingSize -= mallocSize + sizeof(metaData);
            if(mallocCounter >= 150)break;
        }
        else{
            metaData * a = blockPtr;
                while (a != NULL)
                    {
                    if(!(a->isFree))
                    {
                        free(++a);
                        canFree--;
                        remainingSize += (a->size) + sizeof(metaData);
                        break;
                    }
                    a = a->next;
                    }
        }
        printblocks();
    }
   freeall();
    }
//Workload E: Malloc randomly sized chunk random number of times (size of chunk stays consistent) and free
    void workloadE(){
    void * ptr = NULL;
    int mallocSize = rand()%5000;    //size of malloc chunks
    int mallocCounter = rand()%150;    //total number of malloc sizes (must be b/w 1 and 150)
    int remainingSize = blockPtr->size;     //remaining size of memory after each chunk is malloc
    int counter = 0;
    while(counter < mallocCounter){
        if(remainingSize - mallocSize < 0)break;
        ptr = malloc(mallocSize);
        counter++;
    }
    printblocks();
    freeall();
    }

//Workload F: Malloc random number of times, free half that number of times - continue 150 times
//    int mallocCounter = rand()%150;
//    int counter = 0;
//    char* ptr = NULL;
//    while(counter != mallocCounter){
//        ptr = my_malloc(1);
//        counter++;
//    }
//    counter = 0;
//    while(counter != (mallocCounter * .5)){
//        my_free(ptr);
//        counter++;
//    }


