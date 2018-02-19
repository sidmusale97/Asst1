#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <sys/time.h>
#define malloc( x ) my_malloc( x, __FILE__, __LINE__ )
#define free( x ) my_free( x, __FILE__, __LINE__ )
void workloadA();
void workloadB();
void workloadC();       //prototypes for each workload
void workloadD();
void workloadE();
void workloadF();
int allFree();

int main()
{
    struct timeval tv,tv1; //timeval structure to hold time values in test phase
    double start,end,beginning,total;   //variables to hold

    //Workload A
    gettimeofday(&tv,NULL); //get the start time in seconds after a certain default date set by the time.h header file
    beginning = tv.tv_sec + tv.tv_usec/1000000.0; //add seconds and microseconds part of time to get the full time in seconds
    int i;
    for(i = 0; i < 100; i++) //run workload A 100 times
    {
    workloadA();
    }
    gettimeofday(&tv1,NULL); //get the end time
    end = tv1.tv_sec + tv1.tv_usec/1000000.0; //add second and microseconds to get full time
    printf("Time elapsed for 100 iterations of workload A: %.8lf seconds\n", end - beginning); //difference between end and start time is elapsed time for workload

    //Workload B
    gettimeofday(&tv,NULL);
    start = tv1.tv_sec + tv1.tv_usec/1000000.0;
    for(i = 0; i < 100; i++)
    {
    workloadB();
    }
    gettimeofday(&tv1,NULL);
    end = tv1.tv_sec + tv1.tv_usec/1000000.0;
    printf("Time elapsed for 100 iterations of workload B: %.8lf seconds\n", end - start);

    //Workload C
    gettimeofday(&tv1,NULL);
    start = tv1.tv_sec + tv1.tv_usec/1000000.0;
    for(i = 0; i < 100; i++)
    {
    workloadC();
    }
    gettimeofday(&tv1,NULL);
    end = tv1.tv_sec + tv1.tv_usec/1000000.0;
    printf("Time elapsed for 100 iterations of workload C: %.8lf seconds\n", end - start);

    //Workload D
    gettimeofday(&tv1,NULL);
    start = tv1.tv_sec + tv1.tv_usec/1000000.0;
    for(i = 0; i < 100; i++)
    {
    workloadD();
    }
    gettimeofday(&tv1,NULL);
    end = tv1.tv_sec + tv1.tv_usec/1000000.0;
    printf("Time elapsed for 100 iterations of workload D: %.8lf seconds\n", end - start);


    //Workload E
    gettimeofday(&tv1,NULL);
    start = tv1.tv_sec + tv1.tv_usec/1000000.0;
    for(i = 0; i < 100; i++)
    {
    workloadE();
    }
    gettimeofday(&tv1,NULL);
    end = tv1.tv_sec + tv1.tv_usec/1000000.0;
    printf("Time elapsed for 100 iterations of workload E: %.8lf seconds\n", end - start);

    //Workload F
    gettimeofday(&tv,NULL);
    start = tv1.tv_sec + tv1.tv_usec/1000000.0;
    for(i = 0; i < 100; i++)
    {
    workloadF();
    }
    gettimeofday(&tv1,NULL);
    end = tv1.tv_sec + tv1.tv_usec/1000000.0;
    printf("Time elapsed for 100 iterations of workload F: %.8lf seconds\n", end - start);
    return 0;

}
    //Workload A: Malloc() 1 byte and immediately free it x150
void workloadA(){
    int i;
     for (i = 0; i < 150;i++)
     {
     void * p = malloc(1); //malloc 1 byte
     free(p);               //free pointer immediately
     }
}
//Workload B: Malloc(), store pointer in arrayx150 times
void workloadB()
    {
     int i;
     void * ptr; //pointer to hold malloc return address
     for(i = 0; i < 150;i++)
     {
     ptr = malloc(1);   //malloc 1 byte
     }
     freeall(); //free all malloc pointers
    }

    //Workload C: Randomly choose b/w 1 byte malloc and 1 byte free, continue until 150 mallocs
    void workloadC(){
    int mallocCounter = 0;  //counts total number of mallocs
    int canFree = 0;    //flag that determines if any mallocs have occurred
    void*p = NULL;
    while(mallocCounter <= 150){
           if(!canFree){ //if no byte has been allocated, then first malloc
            p = malloc(1); //malloc 1 byte
            mallocCounter++;    //malloc occured so increase mallocCounter
            canFree++;          //malloc occured so flag is turned off
            if (mallocCounter >= 150)break; //if enough malloc have occurred workload complete
            continue;
        }
        int r = rand()%2;   //random num to determine if malloc or free
        if(r==1){           //if r = 1 malloc 1 byte
            p = malloc(1);
            mallocCounter++;
            canFree++;  //increase flag to make sure an extra malloc doesn't occur
            if (mallocCounter >= 150)break;
        }
        else    //if r==0 free first block that is not already free
        {
            metaData * a = getBlockPtr();
            while(a != NULL)
            {
                if(!(a->isFree))
                {
                    free(++a);
                    canFree--; //reduce flag in case of back to back malloc and free
                    break;
                }
                a = a->next;
            }
        }
    }
    freeall();
    }
    //Workload D: Randomly-sized malloc() or free() pointers
    void workloadD(){
    int mallocCounter = 0;  //counts total number of mallocs
    int canFree = 0;    //flag that determines if any mallocs have occurred
    void * p[150];
    int isfreeable[150];
    while(mallocCounter <= 50){
        int mallocSize = (rand()%64) +1;
        if(!canFree){ //if no byte has been allocated, then first malloc
        p[mallocCounter] = malloc(mallocSize); //malloc random bytes
        isfreeable[mallocCounter] = 1;
        mallocCounter++;    //malloc occured so increase mallocCounter
        canFree++;          //malloc occured so flag is turned off
        if (mallocCounter >= 150)break; //if enough malloc have occurred workload complete
        continue;
        }
        int r = rand()%2;   //random num to determine if malloc or free
        mallocSize = (rand()%64) +1;
        if(r==1 && findMostFree() > mallocSize){           //if r = 1 malloc random bytes
            p[mallocCounter] = malloc(mallocSize);
            isfreeable[mallocCounter] = 1;
            mallocCounter++;
            canFree++;  //increase flag to make sure an extra malloc doesn't occur
            if (mallocCounter >= 150)break;
        }
        else    //if r==0 free first block that is not already free
        {
           metaData * p = getBlockPtr();
           while(p != NULL)
           {
               if(!(p->isFree))
               {
                   free(++p);
                   break;
               }
            p = p->next;
           }
        }
    }
    freeall();
}
//Workload E
void workloadE(){
    int mallocCounter;     //keeps track of total number of malloc
    int numMallocs = (rand()%50) + 1;
    int mallocSize = 1;
    void * ptr[numMallocs];
    int freed[numMallocs];
    for (mallocCounter = 0; mallocCounter < numMallocs; mallocCounter++)
    {
        ptr[mallocCounter] = malloc(mallocSize);
        mallocSize++;
        freed[mallocCounter] = 0;
    }
    while(!(allFree(freed,numMallocs)))
    {
        int r = rand()%numMallocs;
        if(!freed[r])
        {
            free(ptr[r]);
            freed[r] = 1;
        }
    }

}

//Workload F
void workloadF(){
    int mallocCounter;     //keeps track of total number of malloc
    void * ptr[10];
    int freed[10];
    int i;
    int j;
    for(j = 0; j < 15; j++)
    {
    for (mallocCounter = 0; mallocCounter < 10; mallocCounter++)
    {
        ptr[mallocCounter] = malloc(10);
        freed[mallocCounter] = 0;
    }
    for(i = 0; i < 5; i++)
    {
        int r = rand()%10;
        if(!freed[r])
        {
            free(ptr[r]);
            freed[r] = 1;
        }
    }
    }
    freeall();
}


int allFree(int freed[], int numMallocs)
{
    int i;
    for(i = 0; i < numMallocs;i++)
    {
        if (!freed[i])
        {
            return 0;
        }
    }
    return 1;
}


