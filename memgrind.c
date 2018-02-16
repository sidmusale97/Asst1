#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
int main()
{
    //Workload A: Malloc() 1 byte and immediately free it x150
    
     int i;
     for (i = 0; i < 150;i++)
     {
     void * p = my_malloc(1);
     my_free(p);
     }
    
    //Workload B: Malloc(), store pointer in arrayx150 times
    
   char * ptrs[150];
     for(i = 0; i < 150;i++)
     {
     ptrs[i] = my_malloc(1);
     }
     for(i = 0;i < 150;i++)
     {
     my_free(ptrs[i]);
     }
    
    //Workload C: Randomly choose b/w 1 byte malloc and 1 byte free, continue until 150 mallocs
    
   int mallocCounter = 0;  //counts total number of mallocs
     int pointersMalloc = 0; //counts pointers currently malloc
     char*p = NULL;
     while(mallocCounter <= 150){
     if(pointersMalloc == 0){ //if no byte has been allocated, then first malloc
     p = my_malloc(1);
     mallocCounter++;
     pointersMalloc++;
     }
     int r = rand()%2;
     if(r==1){           //if r = 1 malloc 1 byte
     p = my_malloc(1);
     mallocCounter++;
     pointersMalloc++;
     }else{
     my_free(p);     //if r=0 free byte
     pointersMalloc--;
     }
     }
     while(pointersMalloc!=0){  // after 150 mallocs, free
     my_free(p);
     pointersMalloc--;
     }
    
    //Workload D: Randomly-sized malloc() or free() pointers
    
        int mallocSize = 0; //size of malloc bytes
        int operation = 0;  //determines free or malloc
         mallocCounter = 0;     //keeps track of total number of mallocs
         pointersMalloc = 0; //keeps track of number of current pointers malloc
        char *ptr = NULL;
        while(mallocCounter <= 5000){
            if(mallocCounter ==0 || pointersMalloc ==0){
                mallocSize = rand()%64;
                ptr= my_malloc(mallocSize);
                mallocCounter++;
                pointersMalloc++;
            }
            operation = rand()%2;
            if(operation ==1){
                mallocSize = rand()%64;
                ptr= my_malloc(mallocSize);
                mallocCounter++;
                pointersMalloc++;
            }else{
                my_free(ptr);
                pointersMalloc--;
            }
        }
        while(pointersMalloc >0){
            my_free(ptr);
            pointersMalloc--;
        }
    

    //Workload E: Malloc randomly sized chunk random number of times (size of chunk stays consistent) and free
    
         char *ptrE =NULL;
        mallocSize = rand()%5000;    //size of malloc chunks
        mallocCounter = rand()%25;    //total number of malloc sizes (must be b/w 1 and 150)
        int remainingSize = mallocSize;     //remaining size of memory after each chunk is malloc
        int counter = 0;
        while(counter != mallocCounter || (remainingSize < mallocSize)){
            ptrE = my_malloc(mallocSize);
            remainingSize = 5000 - remainingSize;
            counter++;
         }
        while(mallocCounter >0){
            my_free(ptrE);
            mallocCounter --;
        }
    
    //Workload F: Malloc random number of times, free half that number of times - continue 150 times
         int mallocCounterF = rand()%150;
         int counterF = 0;
        char* ptrF = NULL;
        while(counterF != mallocCounterF){
            ptrF = my_malloc(1);
            counterF++;
        }
        counterF = 0;
        while(counterF != (mallocCounterF * .5)){
            my_free(ptrF);
            counterF++;
        }
}

