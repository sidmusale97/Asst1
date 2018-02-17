#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <time.h>

int main()
{
    clock_t start,end;
    double elapsedA=0,elapsedB=0,elapsedC=0, elapsedD=0, elapsedE=0, elapsedF = 0;
    double totalRunTimeA=0, totalRunTimeB=0,totalRunTimeC=0,totalRunTimeD=0,totalRunTimeE=0, totalRunTimeF = 0;
    
    int programCounter = 0;
// while(programCounter <100){
    
//        //Workload A: Malloc() 1 byte and immediately free it x150
//      start = clock();
//     int i;
//        for (i = 0; i < 150;i++)
//        {
//            void * p = my_malloc(1);
//            my_free(p);
//            printblocks();
//        }
//        end = clock();
//
//        //Manage RunTimeA for iteration
//        elapsedA =(double)( end - start);
//        totalRunTimeA = totalRunTimeA + elapsedA;
//        end = 0; start = 0; //reset end and start markers for next workload
//
//
//        //Workload B: Malloc(), store pointer in arrayx150 times
//        start = clock();
//        char * ptrs[150];
//        for(i = 0; i < 150;i++)
//        {
//            ptrs[i] = my_malloc(1);
//        }
//        freeall();
//        printblocks();
//        end = clock();
//
//        //Manage RunTimeB for iteration
//        elapsedB = (double)(end - start);
//        totalRunTimeB = totalRunTimeB + elapsedB;
//        end = 0; start = 0; //reset end and start maker for next workload

        //Workload C: Randomly choose b/w 1 byte malloc and 1 byte free, continue until 150 mallocs

//    start = clock();
//    int mallocCounter = 0;  //counts total number of mallocs
//    int pointersMalloc = 0; //counts pointers currently malloc
//    char*p = NULL;
//    while(mallocCounter <= 150){
//        if(mallocCounter == 0){ //if no byte has been allocated, then first malloc
//            p = my_malloc(1);
//            mallocCounter++;
//            if(mallocCounter >=150)break;
//        }
//        int r = rand()%2;
//        if(r==1){           //if r = 1 malloc 1 byte
//            p = my_malloc(1);
//            mallocCounter++;
//            if(mallocCounter >=150)break;
//        }else{
//            metaData *a= blockPtr;
//            while(a!=NULL){
//                if(!(a->isFree)){
//                    my_free(++a);
//                    break;
//                }
//                a = a->next;
//            }
//        }
//    }
//    freeall();
//    printblocks();
//    end = clock();
//
//    //Manage RunTimeC for iteration
//    elapsedC = (double)(end - start);
//    totalRunTimeC = totalRunTimeC + elapsedC;
//    end = 0; start = 0; //reset end and start for next workload
    
        //Workload D: Randomly-sized malloc() or free() pointers
    start = clock();
    int mallocSize = 0; //size of malloc bytes
    int operation = 0;  //determines free or malloc
    int mallocCounter = 0;     //keeps track of total number of mallocs
    int pointersMalloc = 0; //keeps track of number of current pointers malloc
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
            if(mallocCounter >150)break;
            pointersMalloc++;
        }else{
            metaData *a= blockPtr;
            while(a!=NULL){
                if(!(a->isFree)){
                    my_free(++a);
                    break;
                }
                a = a->next;
            }
        }
    }
    freeall();
    end = clock();

        //Manage RunTimeD for iteration
        elapsedD = (double)(end - start);
        totalRunTimeD = totalRunTimeD + elapsedD;
        end = 0; start = 0;

//        //Workload E: Malloc randomly sized chunk random number of times (size of chunk stays consistent) and free
//        start = clock();
//        char *ptrE = NULL;
//        mallocSize = rand()%5000;    //size of malloc chunks
//        mallocCounter = rand()%25;    //total number of malloc sizes (must be b/w 1 and 150)
//        int remainingSize = 5000;     //remaining size of memory after each chunk is malloc
//        int counter = 0;
//        while(counter != mallocCounter || (remainingSize < mallocSize)){
//            ptrE = my_malloc(mallocSize);
//            remainingSize = remainingSize - mallocSize;
//            counter++;
//        }
//        while(mallocCounter >0){
//            my_free(ptrE);
//            mallocCounter --;
//        }
//        end = clock();
//
//        //Manage RunTimeE for iteration
//        elapsedE = (double)(end - start);
//        totalRunTimeE = totalRunTimeE+ elapsedE;
//        end = 0; start = 0;
//
//       // Workload F: Free every other block
//        start = clock();
//        int mallocCounterF = 0;
//        char* ptrF = NULL;
//
//        while(mallocCounterF < 150){
//            ptrF = my_malloc(1);
//            mallocCounter++;
//        }
//        while(mallocCounterF > 0){
//            if(mallocCounterF%2 ==0){
//                my_free(ptrF);
//            }
//            mallocCounterF --;
//        }
//        end = clock();
//
//        //Manage RunTimeF for iteration
//        elapsedF = (double)(end - start);
//        totalRunTimeF = totalRunTimeF+ elapsedF;
//        end = 0; start = 0;
//        //increment program counter for next iteration
//       programCounter++;
//    }
//
    //Calculate average for each workload
//    double avgTimeA = totalRunTimeA/100;     //avg run time for A
//    printf("%s %f\n", "Average RunTime for A:", avgTimeA);
//    double avgTimeB = totalRunTimeB/100;     //avg run time for B
//    printf("%s %f\n", "Average RunTime for B:", avgTimeB);
//    double avgTimeC = totalRunTimeC/100;     //avg run time for C
//    printf("%s %f\n", "Average RunTime for C:", avgTimeC);
//    double avgTimeD = totalRunTimeD/100;     //avg run time for D
//    printf("%s %f\n", "Average RunTime for D:", avgTimeD);
//    double avgTimeE = totalRunTimeE/100;     //avg run time for E
//    printf("%s %f\n", "Average RunTime for E:", avgTimeE);
//    double avgTimeF = totalRunTimeF/100;     //avg run time for F
//    printf("%s %f\n", "Average RunTime for F:", avgTimeF);
}

