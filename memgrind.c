#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.c"
int main()
{
    int i;
    void * a = my_malloc(1);
    void * b = my_malloc(5);
    void * c = my_malloc(10);
    printblocks();
    my_free(c);
    printblocks();
    //Workload A: Malloc() 1 byte and immediately free it x150
    /*
     for (i = 0; i < 150;i++)
     {
     void * p = my_malloc(1);
     my_free(p);
     }
     */
    //Workload B: Malloc(), store pointer in arrayx150 times
    /*char * ptrs[10];
     for(i = 0; i < 10;i++)
     {
     ptrs[i] = my_malloc(1);
     }
     printblocks();
     */
    //Workload C: Randomly choose b/w 1 byte malloc and 1 byte free, continue until 150 mallocs
    /*
     int mallocCounter = 0;  //counts total number of mallocs
     char*p = NULL;
     while(mallocCounter <= 150){
        if(mallocCounter == 0){ //if no byte has been allocated, then first malloc
            p = my_malloc(1);
            mallocCounter++;
            if (mallocCounter >= 150)break;
        }
        int r = rand()%2;
        if(r==1){           //if r = 1 malloc 1 byte
            p = my_malloc(1);
            mallocCounter++;
            if (mallocCounter >= 150)break;
        }
        else
            {
                metaData * a = blockPtr;
                while (a != NULL)
                    {
                    if(!(a->isFree))
                    {
                        my_free(++a);
                        break;
                    }
                    a = a->next;
                    }
            }
     }
    freeall();
*/

    //Workload D: Randomly-sized malloc() or free() pointers

//    int mallocSize = 0; //size of malloc bytes
//    int operation = 0;  //determines free or malloc
//    int mallocCounter = 0;     //keeps track of total number of mallocs
//    int pointersMalloc = 0; //keeps track of number of current pointers malloc
//    char *ptr = NULL;
//    while(mallocCounter <= 5000){
//        if(mallocCounter ==0 || pointersMalloc ==0){
//            mallocSize = rand()%64;
//            ptr= my_malloc(mallocSize);
//            mallocCounter++;
//            pointersMalloc++;
//        }
//        operation = rand()%2;
//        if(operation ==1){
//            mallocSize = rand()%64;
//            ptr= my_malloc(mallocSize);
//            mallocCounter++;
//            pointersMalloc++;
//        }else{
//            my_free(ptr);
//            pointersMalloc--;
//        }
//    }
//    while(pointersMalloc >0){
//        my_free(ptr);
//        pointersMalloc--;
//    }
//}

//Workload E: Malloc randomly sized chunk random number of times (size of chunk stays consistent) and free

//    char* ptr = NULL;
//    int mallocSize = rand()%5000;    //size of malloc chunks
//    int mallocCounter = rand()%150;    //total number of malloc sizes (must be b/w 1 and 150)
//    int remainingSize = mallocSize;     //remaining size of memory after each chunk is malloc
//    int counter = 0;
//    while(counter != mallocCounter || (remainingSize < mallocSize)){
//        ptr = my_malloc(mallocSize);
//        remainingSize = 5000 - remainingSize;
//        counter++;
//     }
//    while(mallocCounter >0){
//        my_free(ptr);
//        mallocCounter --;
//    }

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
    return 0;
}

