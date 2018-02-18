#include <stdio.h>
#include<stddef.h>



typedef struct metaData{
    int size; //size of data
    int isFree;       //flag to indicate if block is empty or not: 0 = empty, 1 = not empty
    struct metaData *next;  //pointer to next block
}metaData;

void initialize();
void allocate(metaData *allocatedBlock, int requiredSize);
void* my_malloc(int size, char * File, int Line);
void merge();
void my_free(void * p, char * File, int Line);
void printblocks(void);
void freeall();
//void errorOut(char * file, int line);




