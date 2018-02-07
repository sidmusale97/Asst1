//
//  mymalloc.h
//  Asst1
//
//  Created by Ridhima Sakhuja on 2/4/18.
//  Copyright © 2018 Ridhima Sakhuja. All rights reserved.
//


#include <stdio.h>


static char myblock[5000];  //array size simulated

typedef struct metaData{
    int size; //size of data
    int isFree;       //flag to indicate if block is empty or not
    struct metaData *next;  //pointer to next block
}metaData;

metaData *memoryArray = (char*) myblock; //points to first block of memory




