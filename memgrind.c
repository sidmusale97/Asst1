#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.c"
#include <sys/time.h>
void workloadA();
void workloadB();
void workloadC();       //prototypes for each workload
void workloadD();
void workloadE();
int main()
{
    struct timeval tv,tv1; //timeval structure to hold time values in test phase
    double start,end,beginning,total;   //variables to hold
    gettimeofday(&tv,NULL); //get the start time in seconds after a certain default date set by the time.h header file
    beginning = tv.tv_sec + tv.tv_usec/1000000.0;
    int i;
    for(i = 0; i < 100; i++) //run workload A 100 times
    {
    workloadA();
    }
    gettimeofday(&tv1,NULL); //get the end time
    end = tv1.tv_sec + tv1.tv_usec/1000000.0;
    printf("Time elapsed for 100 iterations of workload A: %.8lf seconds\n", end - beginning);

    gettimeofday(&tv,NULL);
    start = tv1.tv_sec + tv1.tv_usec/1000000.0;
    for(i = 0; i < 100; i++)
    {
    workloadB();
    }
    gettimeofday(&tv1,NULL);
    end = tv1.tv_sec + tv1.tv_usec/1000000.0;
    printf("Time elapsed for 100 iterations of workload B: %.8lf seconds\n", end - start);

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

    gettimeofday(&tv1,NULL);
    start = tv1.tv_sec + tv1.tv_usec/1000000.0;
    for(i = 0; i < 100; i++)
    {
    workloadE();
    }
    gettimeofday(&tv1,NULL);
    end = tv1.tv_sec + tv1.tv_usec/1000000.0;
    printf("Time elapsed for 100 iterations of workload E: %.8lf seconds\n", end - start);

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
            while(a != NULL)
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
    }
    freeall();
    }
    //Workload D: Randomly-sized malloc() or free() pointers
    void workloadD(){
    int mallocSize = 0; //size of malloc bytes
    int operation = 0;  //determines free or malloc
    int mallocCounter = 0;     //keeps track of total number of malloc
    int canFree = 0;
    void * ptr;
    while(mallocCounter < 150){
        mallocSize = (rand()%64) + 1;
        if (!canFree)
        {
            ptr = malloc(mallocSize);
            mallocCounter++;
            canFree++;
            if(mallocCounter >= 150)break;
            continue;
        }
        operation = rand()%2;
        if(operation == 1 && (findMostFree() - mallocSize) > 0){
            ptr = malloc(mallocSize);
            mallocCounter++;
            canFree++;
            if(mallocCounter >= 150)break;
        }
        else{
            metaData * a = blockPtr;
            while(a!=NULL)
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
    freeall();
    }
    }
//Workload E: Malloc randomly large sized chunk random number of times (size of chunk stays consistent) and free
void workloadE(){
    int mallocSize = (rand()%1000) + 1000;; //size of malloc bytes
    int operation = 0;  //determines free or malloc
    int mallocCounter = 0;     //keeps track of total number of malloc
    int numMallocs = rand()%200+1;
    int canFree = 0;
    int mostFree = 0;
    void * ptr;
    while(mallocCounter < numMallocs){
        if (!canFree)
        {
            ptr = malloc(mallocSize);
            mallocCounter++;
            canFree++;
            if(mallocCounter >= numMallocs)break;
            continue;
        }
        operation = rand()%2;
        if(operation == 1 && ((findMostFree() - mallocSize) > 0)){
            ptr = malloc(mallocSize);
            mallocCounter++;
            canFree++;
            if(mallocCounter >= numMallocs)break;
        }
        else{
            metaData * a = blockPtr;
            while(a!=NULL)
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
    }
    freeall();
}
//Workload F:
